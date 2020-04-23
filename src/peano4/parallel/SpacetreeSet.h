// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _PEANO4_PARALLEL_SPACETREE_SET_H_
#define _PEANO4_PARALLEL_SPACETREE_SET_H_


#include "tarch/logging/Log.h"
#include "tarch/services/Service.h"
#include "peano4/grid/Spacetree.h"
#include "peano4/grid/TraversalObserver.h"
#include "tarch/multicore/Tasks.h"
#include "tarch/multicore/BooleanSemaphore.h"
#include "Tasks.h"


#include <list>
#include <map>


namespace peano4 {
  namespace parallel {
    class SpacetreeSet;
  }
}


/**
 * The spacetree set has to be a singleton, as it is reponsible to accept
 * requests for new trees from remote ranks. So there is only one set.
 *
 * @author Tobias Weinzierl
 */
class peano4::parallel::SpacetreeSet: public tarch::services::Service {
  private:
    friend class peano4::grid::Spacetree;

    /**
     * Each task triggers the traversal of one specific spacetree. After
     * that, we might directly trigger the data exchanges. Yet, this is not a
     * good idea as other tasks might linger in the background not have sent
     * the data out yet. So we don't to anything here.
     */
    class TraverseTask: public tarch::multicore::Task {
      private:
        peano4::grid::Spacetree&          _spacetree;
        SpacetreeSet&                     _spacetreeSet;
        peano4::grid::TraversalObserver&  _observer;
      public:
        TraverseTask( peano4::grid::Spacetree&  tree, SpacetreeSet& set, peano4::grid::TraversalObserver&  observer );

  	    /**
         * I create the copy of the observer, run the traversal on my local
         * tree _spacetree and finally destroy the local observer copy.
         */
        bool run() override;
	      void prefetch() override;
    };

  public:
    /**
     * This is the kind of routine that does boundary data exchange, i.e.
     * send outs in iteration n and receives (see counterpart routine), but
     * the received data is used only in traversal n+1. The whole exchange
     * thus asynchronous (logically).
     *
     * Typically, this routine is called by user observers to for their
     * user-defined data. We however also use it within the grid to trigger
     * the actual vertex data exchange. As these routines all are invoked
     * via tasks, this routine is typically invoked by multiple threads
     * concurrently.
     *
     * @param symmetricDataCardinality If two ranks A and B are adjacent to
     *   each other, and if A send n entries to B, then B received exactly
     *   n entries in turn.
     *
     * @see finishAllOutstandingSendsAndReceives();
     */
    template <class Container>
    static void exchangeAllHorizontalDataExchangeStacks( Container& stackContainer, int spacetreeId, bool symmetricDataCardinality );

    template <class Container>
    static void exchangeAllPeriodicBoundaryDataStacks( Container& stackContainer, int spacetreeId );

    static std::string toString(VerticalDataExchangeMode mode);

    /**
     * <h2> Prepare new children after fork </h2>
     *
     * When we prepare new children, we have to map output stack on output stack, as both
     * trees are not yet inverted at the time we invoke this routine. That is, the master's
     * output stack is mapped on to the new child's outpu stack. The master is inverted
     * automatically later on (that's the last thing we do throughout the traversal). For
     * the new child, we have to invert manually however. This is done in
     * exchangeDataBetweenExistingAndNewTreesAndRerunNewTrees().
     *
     * @param childrenIds Depending on the context, this is either the children or
     *   the new children that are just about to be kicked off
     */
    template <class Container>
    static void exchangeAllVerticalDataExchangeStacks(
      Container& stackContainer,
      int spacetreeId, int parentId,
      VerticalDataExchangeMode mode
    );

    template <class Container>
    static void finishAllOutstandingSendsAndReceives( Container& stackContainer, int spacetreeId );

  private:
    /**
     * Logging device.
     */
    static tarch::logging::Log _log;

    /**
     * Semaphore to protect container holding all the local trees.
     */
    static tarch::multicore::BooleanSemaphore                      _semaphore;

    enum class SpacetreeSetState {
      Waiting,
      TraverseTreesAndExchangeData
    };

    const int     _requestMessageTag;
    const int     _answerMessageTag;

    std::list< peano4::grid::Spacetree >  _spacetrees;

    /**
     * The state identifies what the set is doing right now. The flag is for example
     * used by receiveDanglingMessages() as we may not create new trees or change
     * tree states while we are running through them or realise their data exchange.
     */
    SpacetreeSetState                     _state;

    /**
     * I create/clone one observer per local tree. This is an
     * on-the-fly process. At the end of the set traversal, we delete all of
     * clones. Originally, I did this delete right after the creation and the
     * subsequent traversal. However, we need the observer clone once more for
     * the data exchange. To avoid reclones, I store all clones in this map and
     * then delete them en bloc.
     *
     * @see deleteClonedObservers
     */
    std::map< int, peano4::grid::TraversalObserver* >    _clonedObserver;

    peano4::grid::Spacetree& getSpacetree(int id);

    const peano4::grid::Spacetree& getSpacetree(int id) const;

    /**
     * @return tag that one should use to answer one particular spacetree
     */
    int getAnswerTag( int targetSpacetreeId ) const;

    /**
     *
     * @see split()
     * @see exchangeDataBetweenExistingAndNewTreesAndRerunClones()
     */
    void traverseNonMergingExistingTrees(peano4::grid::TraversalObserver& observer);

    /**
     * <h2> Forks </h2>
     *
     * If we are forking, we first have to establish the new (forked) trees
     * before we issue any data transfer.
     *
     * <h2> Multithreading </h2>
     *
     * I originally intended to make this routine use tasks. However, the data
     * transfer routines do modify the underlying map/stack structures of Peano,
     * as new containers are created, data is moved around, and so forth. So the
     * data exchange per se is not thread-safe. As we do not/can not use threads,
     * we have to be careful with the order. I originally had a loop over the
     * trees that triggered per tree the data exchange and then waited for MPI.
     * Obviously, this does not work with rendezvous protocol. We need two loops.
     * The first one triggers all the MPI sends/receives and it also realises the
     * local data exchange. The second one waits for all MPI operations to
     * terminate.
     */
    void exchangeDataBetweenTrees(peano4::grid::TraversalObserver&  observer);

    /**
     * This operation should be called pretty close towards the end of a traversal.
     * I recommend to invoke it after cleanUpTrees(). It creates new trees and thus
     * might invoke remote method calls on other ranks. It is thus important that
     * all the data exchange locally is done - otherwise we might ask another rank
     * to create a tree for us, while the other rank still waits for boundary data
     * from our side.
     *
     * @see exchangeDataBetweenTrees() for details.
     * @see split() For a description of the overall split process.
     */
    void createNewTrees();

    /**
     * @see _clonedObserver
     */
    void deleteClonedObservers();

    /**
     * @see traverse()
     */
    void exchangeDataBetweenExistingAndNewTreesAndRerunNewTrees(peano4::grid::TraversalObserver& observer);

    /**
     * Counterpart to exchangeDataBetweenExistingAndNewTreesAndRerunClones(), i.e.
     * counterpart to the dry run. We assume the merging worker has already
     * traversed its grid. Therefore, all data which has to be streamed is
     * already in the respective queues. We thus can copy them over and
     * issue the traversal of the master tree.
     *
     * For there is a strong order (first the merging child, then the father), we
     * explicitly traverse only non merging trees in the first step of a traversal.
     *
     * @see traverseNonMergingExistingTrees()
     */
    void exchangeDataBetweenMergingTreesAndTraverseMaster(const std::set<int>& trees, peano4::grid::TraversalObserver& observer);

    /**
     * Adds a new spacetree to the set. The responsibility goes over to the
     * set. The operation clones the original spacetree handed in into a new
     * spacetree with the id newTreeId.
     *
     * <h2> Local node </h2>
     *
     * If the new tree will be a local tree, we simply add a new tree object.
     * The Spacetree's constructor takes care of all the "cloning". Clone here
     * means a setup. We traverse this tree afterwards separately to stream all
     * data in.
     *
     * <h2> Distributed memory <h2>
     *
     * In a distributed memory environment, we have to break up the creation
     * into a set of sends forth and back through TreeManagementMessages.
     *
     * \section Multithreading
     *
     * I may not globally lock this routine, as I otherwise would block the
     * createObserverCloneIfRequired(). So I literally "only" protect the
     * actual push back in the vector.
     */
    void addSpacetree( int masterId, int newTreeId );

    bool canJoinWorkerWithMaster( int workerId );

    /**
     * Join the tree into its master. You are not allowed to run this
     * routine unless the tree with treeId holds mayJoinWithMaster().
     *
     * @todo Hinschreiben, dass das im Gegenzug trivial ist, d.h. beim
     * split duplizieren wir alles, aber hier joinen wir nur, wenn eh
     * schon alles auf Grobgitter da ist. Also ist es trivial.
     */
    void join(int treeId);

    /**
     * <h2> Merge process </h2>
     *
     * We make the worker first of all decide whether to merge or not. A
     * worker has the control/knowledge whether to join or not. When a rank
     * wants to join, we first of all run the workers. Then, all data is the
     * join buffers. After that, we sweep through the masters to take up the
     * data. So we may not merge both the worker and the master into their
     * workers at the same time. If we did so, we'd not be able to run all
     * the merging trees in parallel.
     */
    void cleanUpTrees();

    /**
     * I need this routine for technical reasons: Prior to the sweep of trees,
     * I have to identify all of those trees which wanna merge with their
     * workers. This is an analysis I have to do before I actually traverse
     * any worker. Because of this traversal, more trees might denote their
     * workers as joining, so if I query the joining field after the traversal,
     * I intermix newly joining and old joining ranks.
     */
    std::set<int>                 getLocalTreesMergingWithWorkers() const;

    /**
     * Quick lookup whether an observer clone for this tree id does already exist.
     * If not, we create one quickly.
     *
     * \section Multithreading
     *
     * This operation uses a lock on the semaphore to ensure that no two threads
     * insert an observer into the global table at the same time.
     */
    void createObserverCloneIfRequired(peano4::grid::TraversalObserver& observer, int treeId);

    SpacetreeSet();
    SpacetreeSet(const SpacetreeSet& ) = delete;
    SpacetreeSet& operator=(const SpacetreeSet& ) = delete;

  public:
    /**
     * As the setis a singleton and a service, it has to deregister itself. Otherwise, the overall
     * service landscape still might try to call receiveDanglingMessages().
     */
    ~SpacetreeSet();

    static SpacetreeSet& getInstance();

    /**
     * We poll the tree management messages.
     *
     * If a new spacetree request drops in, we book the tree and send it back.
     *
     * <h2> Message exchange modes </h2>
     *
     * I have to be careful with nonblocking data exchange here. Some messages
     * belong logically together. So if I receive the first of two messages in
     * a row and then go to receiveDanglingMessages again, part two of the message
     * might drop in and I might consider it to be another part one. That may not
     * happen. So as soon as the iprobe says "go", I switch to blocking data
     * exchange here.
     */
    void receiveDanglingMessages() override;

    /**
     * @see Spacetree::Spacetree()
     */
    void init(
      const tarch::la::Vector<Dimensions,double>&  offset,
      const tarch::la::Vector<Dimensions,double>&  width,
      const std::bitset<Dimensions>&               periodicBC = 0
    );

    /**
     * Invoke traverse on all spacetrees in parallel.
     *
     */
    void traverse(peano4::grid::TraversalObserver& observer);

    /**
     * Return statistics object for primary spacetree.
     */
    peano4::grid::GridStatistics  getGridStatistics() const;

    peano4::grid::GridStatistics  getGridStatistics(int treeId) const;

    /**
     * If the target tree shall be stored on the local node, then you pass
     *
     * <pre>
      peano4::parallel::Node::getInstance().getRank(treeId)
       </pre>
     * as last argument. Splits on the local node allow Peano to exploit more
     * cores on the node.
     *
     * <h2> Split process </h2>
     *
     * @image html SpacetreeSet_split.png
     *
     * If you split a tree, the original tree, i.e. the source of the data,
     * makes the new tree run through two states: split triggered and splitting.
     *
     * In a usual run, Peano's trees do exchange data in a way similar to the
     * Jacobi smoothing: Each tree traverses its domain and sends out all
     * boundary data. I call this horizontal communication as it is data exchange
     * between non-overlapping domains which can be arranged on one grid level.
     * In the next iteration, the data from neighbours has arrived and can be
     * merged in. We obtain a criss-cross communication pattern (blue steps)
     * where an iteration feeds into the neighbour's iteration n+1.
     *
     * While a new id is booked by one tree if a split is triggered, this new tree
     * does not yet physically exist. The original (source) tree keeps the
     * complete ownership of all data, i.e. it does all refines and coarses and
     * also creates all events. However, it already enters the new, yet to be
     * created, tree's indices into all adjacency lists with are consequently
     * sent out to the other ranks. This is the yellow step above. After the grid
     * sweep, we mark the new tree id as splitting. At this point, all neighbours
     * continue to send to the original tree, as they are not yet aware of any
     * domain partition updates.
     *
     * While an id is associated with splitting (orange), we know that all the other
     * trees around start to send data to the new tree that is yet to be
     * created: they receive the information about the updated adjacency and can
     * send out their stuff to the new tree. Which does not exist yet (grey).
     *
     * So the splitting rank (orange) traverses its domain and invokes all
     * events. It has the semantic ownership. It merges in all boundary data from
     * neighbours, but is does not send out the boundary data (anymore).
     * After the splitting tree traversal has terminated, we establish
     * the new tree by duplicating all the local data. This includes the
     * user data, too.
     *
     * The new tree (light green) subsequently is traversed once as empty
     * tree. That is, all data travel over the stacks, but no events are invoked
     * and no communication is happening. The purpose of this empty traversal is
     * to get all data inot the right order.
     *
     * Once the empty traversal has terminated, we run over the new tree
     * again. This time, we label it as new (dark green). While we still do not
     * invoke any event, we now do send out data. This is the sole purpose of the
     * new traversal.
     *
     *
     * @todo Not clear. Koennten auch bei New alles machen?
     *
     *
     * @param treeId  Id of tree that should split, i.e. give away cells to a
     *   new tree
     * @param cells   Number of cells to deploy to a new tree. This count refers
     *   to the status-quo, i.e. if dynamic adaptivity makes an unrefined node
     *   of the tree unfold in the next step, the new @f$ 3^d @f$ children do
     *   count only with one towards this quota.
     * @param targetRank  Rank which should host the new tree.
     */
    bool split(int treeId, int cells, int targetRank);

    /**
     * Codes hold one spacetree set per rank. With this routine, you can find
     * out whether a local set contains a particular id.
     */
    bool isLocalSpacetree(int treeId) const;

    /**
     * @return Set of ids of local spacetrees
     */
    std::set<int> getLocalSpacetrees() const;
};


#include "SpacetreeSet.cpph"


#endif
