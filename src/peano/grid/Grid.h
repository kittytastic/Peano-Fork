// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _PEANO_GRID_GRID_H_
#define _PEANO_GRID_GRID_H_


#include "peano/utils/Globals.h"
#include "peano/geometry/Geometry.h"


#include "peano/grid/nodes/Leaf.h"
#include "peano/grid/nodes/Refined.h"
#include "peano/grid/nodes/RegularRefined.h"
#include "peano/grid/nodes/Root.h"

#include "peano/grid/RegularGridContainer.h"
#include "peano/grid/TraversalOrderOnTopLevel.h"


namespace peano {
    namespace grid {
      template <
        class Vertex,
        class Cell,
        class State,
        class VertexStack,
        class CellStack,
        class EventHandle
      >
      class Grid;
    }
}


/**
 * The root element manages the @f$ 2^d @f$ vertices of the super element that
 * encloses the unit square (if the program is configured to have the domain
 * contained within the unit square). Therefore, the event next to the root
 * element always is a refined element.
 *
 * Furthermore, the root event holds the state corresponding to the whole grid
 * and is responsible for inverting the state.
 *
 * @image html grid_RootElement.gif
 *
 * @author Tobias Weinzierl
 * @version $Revision: 1.55 $
 */
template <class Vertex, class Cell, class State, class VertexStack, class CellStack, class EventHandle>
class peano::grid::Grid {
  public:
    typedef peano::grid::RegularGridContainer<Vertex,Cell>   RegularGridContainer;
  private:
    typedef peano::grid::nodes::Leaf<Vertex,Cell,State,VertexStack,CellStack,EventHandle>            LeafNode;
    typedef peano::grid::nodes::Root<Vertex,Cell,State,VertexStack,CellStack,EventHandle>            RootNode;
    typedef peano::grid::nodes::Refined<Vertex,Cell,State,VertexStack,CellStack,EventHandle>         RefinedNode;
    typedef peano::grid::nodes::RegularRefined<Vertex,Cell,State,VertexStack,CellStack,EventHandle>  RegularRefinedNode;

    /**
     * Logging device.
     */
    static tarch::logging::Log _log;

    State&  _state;

    /**
     * Holds the event handle associated to this event.
     */
    EventHandle   _eventHandle;

    /**
     * The grid container for the regular patches is a pure temporary
     * container, i.e. it is only used to swap data temporarily to another
     * data structure. At the same time, it might become really large.
     * Therefore, all the grids should share one implementation, and this
     * is the reason why I made this container a class attribute.
     */
    RegularGridContainer&                   _regularGridContainer;
    peano::grid::TraversalOrderOnTopLevel&  _traversalOrderOnTopLevel;

    /**
     * Nodes of the spacetree (flyweight pattern)
     */
    LeafNode            _leafNode;
    RefinedNode         _refinedNode;
    RegularRefinedNode  _regularRefinedNode;
    RootNode            _root;

    /**
     * Receive state and cell from the master
     *
     * This operation becomes nop if we do not compile Peano with -DParallel.
     * Otherwise, it does a blocking receive waiting for the the following
     * data from its master:
     *
     * - load balancing information that is directly forwarded to the load
     *   balancing's oracle, and
     * - state of the traversal automaton.
     *
     * If the operation is ran on the global master, it also becomes nop. As
     * the worker is responsible for the root cell,
     * - it is the only node that holds valid data (though it is replicated on the master), and
     * - its content is copied to the master after each iteration.
     *
     * In turn, there's no cell data to be exchanged at the startup by the grid.
     * However, the root node does exchange cell and vertex data. See
     * Root::receiveCellAndVerticesFromMaster().
     *
     * The counterpart of this operation is Node::updateCellsParallelStateAfterLoadForRootOfDeployedSubtree().
     *
     * @param reduceState This is the reduce flag passed by the repository, i.e.
     *        it is neglected if this operation is invoked on a worker. On workers,
     *        the master decides whether to reduce or not. The repository does not
     *        have this influence.
     */
    void receiveStartupDataFromMaster(bool reduceState);

    /**
     * Is invoked if and only if
     *
     * - there is a master node,
     * - the reduction is switched on,
     * - the node is not joining, and
     * - the node has not just forked.
     *
     * For the rationale for the latter constraint, please see Node::updateCellsParallelStateBeforeStore()
     */
    void sendStateToMaster();
  public:
    /**
     * Create new grid
     *
     * Construct a new grid with the given parameters. You have to init
     * the geometry and the stacks before you call any further operations on
     * the grid.
     */
    Grid(
      VertexStack&                                  vertexStack,
      CellStack&                                    cellStack,
      peano::geometry::Geometry&                    geometry,
      State&                                        state,
      const tarch::la::Vector<DIMENSIONS,double>&   domainSize,
      const tarch::la::Vector<DIMENSIONS,double>&   domainOffset,
      RegularGridContainer&                         regularGridContainer,
      TraversalOrderOnTopLevel&                     traversalOrderOnTopLevel
    );

    /**
     * If you use this constructor, you have to initialise the traversal due to
     * traversalOrderOnTopLevel yourself.
     */
    Grid(
      VertexStack&                                  vertexStack,
      CellStack&                                    cellStack,
      peano::geometry::Geometry&                    geometry,
      State&                                        state,
      RegularGridContainer&                         regularGridContainer,
      TraversalOrderOnTopLevel&                     traversalOrderOnTopLevel
    );

    /**
     * Works only on MPI ranks that are not equal to the master node.
     */
    void restart(
      const tarch::la::Vector<DIMENSIONS,double>&  domainSize,
      const tarch::la::Vector<DIMENSIONS,double>&  domainOffset,
      int                                          domainLevel
    );

    /**
     *
     * !!! Implementation
     *
     * It is important to release the join data before we release the boundary
     * messages. Otherwise, we create a deadlock: Throughout a fork, the master
     * streams data to its worker. At the same time, it sends parallel boundary
     * data to the new worker. The worker recevies the streamed data, and in
     * turn sends out boundary information to its master (if they share a
     * common boundary). Now, the release operation on the master waits until
     * the worker has sent all its boundary data. At the same time, the worker
     * cannot complete its work, as the master still might buffer some stream
     * data. Therefore, it is important that the master releases the stream
     * data to enable the worker to finish and to send out all the boundary
     * information.
     *
     * @todo TW: I'm pretty sure that this model to release the join data so
     *           late slows down the application throughout the join process.
     *           Hence, it might make sense to speed-up this stuff, e.g.
     *           release message on-the-fly throughout the traversal.
     */
    void iterate(bool reduceState);

    /**
     * nop
     */
    void terminate();
};


#include "peano/grid/Grid.cpph"


#endif
