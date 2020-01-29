// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _PEANO4_GRID_TRAVERSAL_OBSERVER_H_
#define _PEANO4_GRID_TRAVERSAL_OBSERVER_H_


#include "peano4/parallel/parallel.h"
#include "peano4/utils/Globals.h"
#include "tarch/la/Vector.h"


#include <vector>


namespace peano4 {
  namespace grid {
    class TraversalObserver;
    class GridControlEvent;
    class GridTraversalEvent;
  }
}


/**
 *
 * \section  Copy behaviour
 *
 * There is one observer by grid traversal thread and per rank. The observers
 * are generated from the original observer via the clone() operator.
 * Therefore, you never should be required to write a copy constructor. If you
 * run without multithreading but with MPI, you still have to use a
 * SpacetreeSet. The code therefore continues to copy observers.
 */
class peano4::grid::TraversalObserver {
  public:
	virtual ~TraversalObserver() {}

    static constexpr int CreateOrDestroyPersistentGridEntity = -1;
    static constexpr int CreateOrDestroyHangingGridEntity    = -2;
    static constexpr int NoData                              = -3;

	/**
	 * Event is invoked per cell. It is however not called for the root cell,
	 * i.e. for the cell with level 0 that does not have a parent.
	 */
	virtual void enterCell(
      const GridTraversalEvent&  event
    ) = 0;


	virtual void leaveCell(
	  const GridTraversalEvent&  event
    ) = 0;

	/**
	 * I use the clone to create one observer object per traversal thread. So
	 * between different spacetrees of one spacetree set, there can be no race
	 * condition. Yet, the clone() itself could be called in parallel.
	 *
	 * \section  Global per-sweep actions
	 *
	 * If you want to implement an operation once per sweep in a parallel
	 * environment, then you can exploit the fact that the spacetree set also
	 * creates an observer for the global master thread, i.e. tree no 0. So if
	 * you add a statement alike
	 *
	 * <pre>
  if (peano4::parallel::Node::isGlobalMaster(spacetreeId)) {
    ...
  }
	   </pre>
	 *
	 * then you can be sure that the branch body is executed only once globally
	 * per grid sweep.
	 *
	 *
	 * The counterpart of the clone operation is the destructor.
	 */
	virtual TraversalObserver* clone(int spacetreeId) = 0;

	/**
	 * The tree traversal invokes this operation before beginIteration.
	 *
	 * \section  Content
	 *
	 * Dynamic AMR is controlled via a sequence of grid control events. Each
	 * event spans a certain region and prescribes an h resolution over this
	 * region. Depending on the type of the event (erase or refine), the grid
	 * adopts. A simple snippet just creating a refined area in a square is
	 *
	 * <pre>
std::vector< peano4::grid::GridControlEvent > applications4::grid::MyObserver::getGridControlEvents() {
  std::vector< peano4::grid::GridControlEvent >  controlEvents;
  peano4::grid::GridControlEvent newEvent;
  newEvent.setRefinementControl( peano4::grid::GridControlEvent::RefinementControl::Refine );
  newEvent.setOffset( {0.0,0.0} );
  newEvent.setWidth( {0.5,0.5} );
  newEvent.setH( {0.05,0.05} );
  controlEvents.push_back(newEvent);
  return controlEvents;
}
	 </pre>
	 *
	 * The entries are logically ordered. The later the entry, the more
	 * important it is. So entry 2 overrules entry 1.
	 */
	virtual std::vector< GridControlEvent > getGridControlEvents() = 0;

  /**
   * We do not really need stack numbers et al here, as everything will
   * reside on the call stack anyway. If the routine is called on tree
   * no 0, this operation has to establish the master of the global root
   * tree (which usually is ill-defined, but the data should be there
   * anyway).
   */
  virtual void beginTraversal(
    const tarch::la::Vector<Dimensions,double>&  x,
    const tarch::la::Vector<Dimensions,double>&  h
  ) = 0;

  virtual void endTraversal(
    const tarch::la::Vector<Dimensions,double>&  x,
    const tarch::la::Vector<Dimensions,double>&  h
  ) = 0;


  virtual void exchangeAllVerticalDataExchangeStacks( int spacetreeId, int masterId, peano4::parallel::VerticalDataExchangeMode mode ) = 0;
  virtual void exchangeAllHorizontalDataExchangeStacks( int spacetreeId, bool symmetricDataCardinality ) = 0;
  virtual void exchangeAllPeriodicBoundaryDataStacks( int spacetreeId ) = 0;
  virtual void finishAllOutstandingSendsAndReceives( int spacetreeId ) = 0;
};

#endif
