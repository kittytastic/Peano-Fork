// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _TOOLBOX_LOAD_BALANCING_RECURSIVE_SUBDIVISION_
#define _TOOLBOX_LOAD_BALANCING_RECURSIVE_SUBDIVISION_



#include "tarch/logging/Log.h"
#include "tarch/mpi/mpi.h"
#include <map>



namespace toolbox {
  namespace loadbalancing {
    class RecursiveSubdivision;
  }
}


/**
 * Recursive load balancing micking the behaviour of the guided partitioning in OpenMP
 *
 * This is one of the simplest load balancing strategies one can think about. We
 * try to mimick the behaviour of OpenMP's guided scheduling: We determine the
 * maximum number of unrefined inner cells around and compute an optimal load per
 * rank. We first spread out over all ranks, and then ensure that there is at least
 * one tree per core. From thereon, we examine whether we violate the per-rank
 * load balancing. If a rank does this, it splits its heaviest tree and deploys the
 * new subtree to the most underbooked rank.
 *
 *
 * <h2> Implementation remarks </h2>
 *
 * The strategy runs through different phases.
 *
 * <h3> Phase 1: The tree is too small so there would not be enough cells if we had even only one cell per tree </h3>
 *
 * We wait and do nothing. After all, this might be the first step of the grid
 * construction, so we are well-advised to wait for a few iterations to get
 * an idea what the final grid will look like and in particular to get enough
 * cells so we can keep all threads/ranks busy.
 *
 * <h3> Phase 2: We have not yet used all ranks </h3>
 *
 * First of all, we make all ranks busy. This can be done in one rush: Rank 0
 * splits up equally sized tree to each and every rank. As phase 1 has
 * terminated already, we know that there are enough cells around.
 *
 * <h3> Phase 3: Get reasonably many cores into the game </h3>
 *
 * We'd like to occupy a lot of cores. We should trigger
 * this step asap. At the same time, we might already be in a situation where
 * the per-rank mesh is pretty detailed, i.e. too many forks in one rush might
 * be too ambitious.
 *
 * This phase still is rank-local, i.e. I do not spread between ranks.
 * Consequently, I should not overdecompose. It might be reasonable to wait
 * with further splits and to balance later on a case-by-case base such that
 * we can deploy cells to other ranks, too. This throttling is implemented via
 * getNumberOfSplitsOnLocalRank().
 *
 * <h3> Phase 4: Load balancing between the ranks (dynamic) </h3>
 *
 * This is the dynamic load balancing phase. Take the biggest tree, check
 * whether it is too heavy and split it. When you split it, search for the
 * rank with the lowest total load and get the new subtree there. To avoid
 * that too many ranks deploy to one rank at the same time, we use kind of
 * a round-robin token here.
 *
 * <h2> Broad vs. deep trees </h2>
 *
 * The splitting has to be reasonably aggressive. If we worked iteratively
 * depth first, i.e. identified the biggest tree, split it, and then continue,
 * then we run into situations where we have a complex master-worker
 * topology. This restricts our flexibility as we have to preserve the
 * topology. The broader a tree the better.
 *
 * Therefore, it is absolutely mandatory (and it took me a while to recognise
 * this) to use the min functions and always try to split from a very heavy
 * tree just that part that you need.
 *
 * <h2> Blacklisting </h2>
 *
 * The recursive subdivision works with one tree at a time: It always identifies the
 * one tree with the biggest load and subdivides this one further. A tree however
 * requires two traversals to split. If a tree is identified as split candidate, the
 * code hence will tell it to split, but will try to split exactly the same tree again
 * in the subsequent iteration.
 *
 * The tree's stats (how many cells does it own) at this point are skewed, as the
 * tree has not yet successfully given away cells. Indeed, a tree needs at least three
 * iterations to 'recover'. The first one initialises the split. The second traversal
 * conducts the split and eventually moves around data, but the ownership in this
 * traversal still is with the master. Therefore, the master still has all the local
 * cells. After the third split, the master has actually given away its cells.
 *
 * Therefore, we work with a blacklist map: Whenever we have identified a tree that is to
 * be split, we memorise it and give it an internal weight of 3. Memorise means it is
 * stored in a map. As long as a rank is on the blacklist map, it may not be selected
 * as potential split tree. After each iteration, we reduce the weight of the blacklisted
 * trees by one. If a weight becomes zero, we eventually remove it from the blacklist.
 *
 * <h2> Cool-down phases </h2>
 *
 * It is important that we have some kind of cool-down phases, i.e. certain blocks of
 * sweeps where no rebalancing is done no matter how imbalanced we are. Splits are
 * notoriously expensive as they serialise parts of the traversals. Furthermore, we
 * will never reach a stationary grid throughout the grid construction phase if we
 * split all the time (and perhaps then are unsuccessful as the grids have a layout
 * that we can't split actually).
 */
class toolbox::loadbalancing::RecursiveSubdivision {
  public:
    /**
     * @param targetBalancingRation Ratio which ill-balancing we accept. A ratio of
     *   almost one means we do not accept any ill-balancing. The smaller the value,
     *   the more relaxed we are.
     */
    RecursiveSubdivision(double targetBalancingRation=0.9);
    ~RecursiveSubdivision();

    /**
     * Triggers actual load balancing data exchange, triggers reblaancing, and
     * dumps statistics.
     *
     * <h2> Spread equally </h2>
     * This step is usually called early throughout the grid construction. At
     * this point, we want to bring in ranks as soon as possible. However, it
     * is very unlikely that the grid at that point will allow us to balance
     * properly. We will likely have something like 27 cells for 8 ranks. With
     * integer arithmetics, we would now get 3 cells per rank with the
     * remainder of cells remaining on rank 0. This is not a big issue for
     * small meshes, but for large meshes even a tiny overloading of rank 0 can
     * result in an out-of-memory situation. I therefore have this module
     * increment within the for loop such that module imbalances are at least
     * spread out.
     */
    void finishStep();
    void finishSimulation();

    /**
     * I need the stats here mainly for debugging purposes. The load balancing
     * alread dumps information per time step. This routine however is more
     * elaborate/detailed and not used by default.
     */
    std::string toString() const;

    bool hasSplitRecently() const;

    /**
     * Switch on/off.
     */
    void enable(bool);

    /**
     * Clarifies whether load balancing is, in principle, enabled. Might however
     * mean that the load balancing is currently (temporarily) disabled. In 
     * this case, the routine still returns true.
     */
    bool isEnabled(bool globally) const;

    int getGlobalNumberOfTrees() const;
  private:
    /**
     * @see getStrategyStep()
     */
    enum class StrategyStep {
      Wait,
      SpreadEquallyOverAllRanks,
      SplitHeaviestLocalTreeMultipleTimes_UseLocalRank_UseRecursivePartitioning,
      SplitHeaviestLocalTreeOnce_UseAllRanks_UseRecursivePartitioning,
      SplitHeaviestLocalTreeOnce_DontUseLocalRank_UseRecursivePartitioning,
      SplitHeaviestLocalTreeOnce_UseLocalRank_UseRecursivePartitioning
    };

    /**
     * It is totally annoying, but it seems that MPI's maxloc and reduction are broken
     * in some MPI implementations if we use them for integers.
     */
    struct ReductionBuffer {
      double   _unrefinedCells;
      int      _rank;
    };

    static std::string toString( StrategyStep step );

    /**
     * Analyse current global situation and commit to a strategy. This routine
     * analyses the rank state and returns an action.
     */
    StrategyStep getStrategyStep() const;

    static tarch::logging::Log  _log;

    const double _TargetBalancingRatio;

    std::map< int, int>    _blacklist;

    bool _hasSpreadOutOverAllRanks;

    /**
     * Status variable required to compute good load balancing. 
     */
    int _localNumberOfInnerUnrefinedCell;

    /**
     * Status variable required to compute good load balancing
     */
    int _globalNumberOfInnerUnrefinedCells;

    int _globalNumberOfTrees;

    int _globalNumberOfRanksWithEnabledLoadBalancing; 

    ReductionBuffer  _lightestRank;

    /**
     * This is my local accumulator where I keep track of how often I did
     * split in this iteration. At the end of each iteration, I roll this 
     * one over into global or send it out. 
     */
    int _localNumberOfSplits;

    /**
     * Lags behind global number by one iteration in an MPI world as data
     * will arrive with one iteration delay.
     */
    int _globalNumberOfSplits;

    int _numberOfStateUpdatesWithoutAnySplit;

    enum class StrategyState {
      Standard,
      WaitForRoundRobinToken,
      PostponedDecisionDueToLackOfCells,
      Stagnation
    };

    static std::string toString( StrategyState state );

    StrategyState  _state;

    bool _enabled;

    void updateGlobalView();
    
    bool doesRankViolateBalancingCondition() const;

    void updateBlacklist();

    /**
     * Wrapper around the spacetree set which also updates the blacklist.
     */
    void triggerSplit( int sourceTree, int numberOfCells, int targetRank );

    /**
     * <h2> Init has-spread-over-all-ranks flag </h2>
     *
     * By the time we construct the load balancing, we often haven't
     * initialised the MPI environment properly yet. At least, I don't want
     * to rely on this. Therefore, I set _hasSpreadOutOverAllRanks to false
     * by default, and then make updateGlobalView() set it to true for the
     * non-0 rank. The 0-rank case is covered anyway.
     *
     * <h2> Round-robin balancing </h2>
     *
     * I test my load balancing typically first with a rather regular grid.
     * What happens here is that the grid is decomposed and one or two ranks
     * are slightly ``too light''. All the others identify a rank to which
     * they could outsource cells and then all outsource to the same ranks
     * at the same time. To avoid this, I introduce a round-robin token such
     * that only one rank at a time does balance in-between ranks (the other
     * types of lb are not affected). This way, it cannot happen that a high
     * number of ranks all outsource cells to the same ''victim'' in one
     * rush.
     *
     * <h2> Stagnation </h2>
     *
     * Weird things can happen with our greedy approach: We might have three
     * heavy trees on our rank which all cover regions that cannot be forked
     * further (as they have already children or cover boundaries or some 
     * AMR regions). In this case, it might happen that we rotate through: We
     * ask tree 1 to split, then tree 2, then 3. Once the split of 3 has 
     * finished (unsuccessfully), 1 has already left the blacklist. We end up
     * with a cycle.
     *
     * Therefore, we increase the time how long a tree stays on the blacklist
     * everytime the maximum tree weight has not changed. This way, we avoid
     * the rotations.
     *
     * If everybody is on the blacklist, then we have obviously tried to 
     * split every tree and it did not really work, so we would like to split 
     * further, but we have run into a stagnation.
     */
    void updateState();

    /**
     * This is part of the action SplitHeaviestLocalTreeMultipleTimes_UseLocalRank_UseRecursivePartitioning.
     *
     * @param cellsPerCore I think I could reconstruct these guys manually, but
     *          I have this value available when I call the function anyway.
     */
    int getNumberOfSplitsOnLocalRank() const;

    /**
     * Ensure enough memory is left-over.
     */
    bool canSplitLocally() const;

    #ifdef Parallel
    MPI_Request*    _globalSumRequest;
    MPI_Request*    _globalLightestRankRequest;
    MPI_Request*    _globalNumberOfSplitsRequest;
    MPI_Request*    _globalNumberOfTreesRequest;
    MPI_Request*    _globalNumberOfRanksWithEnabledLoadBalancingRequest;

    /**
     * It is totally annoying, but it seems that MPI's maxloc and reduction are broken
     * in some MPI implementations if we use them for integers.
     */

    int             _globalNumberOfInnerUnrefinedCellsBufferIn;
    ReductionBuffer _lightestRankIn;
    ReductionBuffer _lightestRankOut;
    int             _globalNumberOfSplitsIn;
    int             _localNumberOfSplitsOut;
    int             _numberOfLocalTreesOut;   
    int             _globalNumberOfRanksWithEnabledLoadBalancingOut;
    #endif

    /**
     * @see updateState()
     */
    int _roundRobinToken;

    int _maxTreeWeightAtLastSplit;

    void waitForGlobalStatisticsExchange();
};


#endif

