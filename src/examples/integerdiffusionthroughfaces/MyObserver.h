// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _EXAMPLES_INTEGER_DIFFUSION_THROUGH_FACES_MYOBSERVER_H_
#define _EXAMPLES_INTEGER_DIFFUSION_THROUGH_FACES_MYOBSERVER_H_


#include "peano4/grid/TraversalObserver.h"
#include "peano4/stacks/STDVectorStack.h"


//#include <pair>
#include <map>


#include "Mapping.h"
#include "FaceData.h"
#include "CellData.h"


namespace examples {
  namespace integerdiffusionthroughfaces {
    class MyObserver;
  }
}


class examples::integerdiffusionthroughfaces::MyObserver: public peano4::grid::TraversalObserver {
  private:
	static tarch::logging::Log  _log;

	const int _spacetreeId;
	/**
	 * We use this counter to steer/hardcode dynamic AMR
	 */
	int _iterationCounter;

	/**
	 * To look up the right stack, we use a combination of tree number (id) and
	 * stack number.
	 */
	typedef std::pair<int,int>  DataKey;

	typedef peano4::stacks::STDVectorStack< FaceData >   FaceDataContainer;
	typedef peano4::stacks::STDVectorStack< CellData >   CellDataContainer;

	/**
	 * It is absolutely essential that these guys are static. They are global
	 * repositories shared by all observers.
	 */
	static std::map< DataKey, FaceDataContainer >   _faceData;
	static std::map< DataKey, CellDataContainer >   _cellData;

	/**
	 * All observers share one mapping, i.e. you have to make it thread-safe
	 */
	Mapping*                                _mapping;
  public:
	MyObserver();
	MyObserver(int spacetreeId, int counter, Mapping* mapping);
	~MyObserver();

	virtual void beginTraversal() override;
	virtual void endTraversal() override;

	virtual void enterCell(
      const peano4::grid::GridTraversalEvent&  event
    ) override;


	virtual void leaveCell(
	  const peano4::grid::GridTraversalEvent&  event
    ) override;

	/**
	 * I use the clone to create one observer object per traversal thread. So
	 * between different spacetrees of one spacetree set, there can be no race
	 * condition. Yet, the clone() itself could be called in parallel.
	 */
	virtual TraversalObserver* clone(int spacetreeId) override;

	virtual std::vector< peano4::grid::GridControlEvent > getGridControlEvents() override;
};

#endif
