// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _PEANO_DATA_TRAVERSAL_AUTOTUNING_ORACLE_FOR_ONE_PHASE_H_
#define _PEANO_DATA_TRAVERSAL_AUTOTUNING_ORACLE_FOR_ONE_PHASE_H_


#include <map>
#include <string>


namespace peano {
  namespace datatraversal {
    namespace autotuning {
      class OracleForOnePhase;

      enum MethodTrace {
        LoadVertices                                     = 3,
        LoadVerticesOnRegularStationaryGrid              = 4, // not unrolled
        LoadVerticesOnIrregularStationaryGrid            = 5,
        LoadVerticesOnStationaryGridWithParallelBoundary = 6,
        StoreVertices                                    = 7,
        StoreVerticesOnRegularStationaryGrid             = 8, // not unrolled
        StoreVerticesOnIrregularStationaryGrid           = 9,
        SetCounter                                       = 10,
        CallEnterCellAndLoadSubCellsWithinTraverse       = 11,
        CallLeaveCellAndStoreSubCellsWithinTraverse      = 12,
        CallEnterCellAndInitialiseEnumeratorsOnRegularStationaryGrid = 13,
        CallTouchFirstTimeOnRegularStationaryGrid        = 14,
        CallTouchLastTimeOnRegularStationaryGrid         = 15,
        CallEnterCellOnRegularStationaryGrid             = 16,
        CallLeaveCellOnRegularStationaryGrid             = 17,
        ParalleliseAscend                                = 18,
        ParalleliseDescend                               = 19,
        SplitLoadVerticesTaskOnRegularStationaryGrid     = 20,
        SplitStoreVerticesTaskOnRegularStationaryGrid    = 21,
        NumberOfDifferentMethodsCalling                               = 22
      };

      std::string toString( const MethodTrace& methodTrace );
      MethodTrace toMethodTrace(int value);
    }
  }
}



/**
 * Abstract superclass of all oracles
 *
 * !!! Copy constructor
 *
 * The oracle singleton never works with the original oracle. Instead, it
 * clones its oracle strategy for each new phase (see createNewOracle()).
 *
 * @author Svetlana Nogina, Tobias Weinzierl
 */
class peano::datatraversal::autotuning::OracleForOnePhase {
  public:
    virtual ~OracleForOnePhase() {}

    /**
     * This operation is not const, as the oracle might insert further computations.
     *
     * @see peano::datatraversal::autotuning::Oracle::parallelise()
     *
     * @return Tuple with grain size plus flag indicating weather you wanna be informed about runtime
     */
    virtual std::pair<int,bool> parallelise(int problemSize) = 0;

    /**
     * Informs oracle that the parallel code fraction has terminated. The last
     * fraction is the one, parallelise() has been called for before. There's
     * never more than one section running in parallel.
     */
    virtual void parallelSectionHasTerminated(double elapsedCalendarTime) = 0;

    /**
     * Plot something to info log device.
     */
    virtual void plotStatistics() const = 0;

    /**
     * This operation is called by the oracle (management) on the prototype of
     * the individual oracles. Can be used to adopt oracle behaviour to global
     * runtime.
     */
    virtual void informAboutElapsedTimeOfLastTraversal(double elapsedTime) = 0;

    /**
     * Clone this oracle. This operation is used by the singleton whenever a
     * piece of code asks for parallelisation that never asked before.
     *
     * @param adapterNumber Number of your adapter. Have a closer look to your
     *        repository's state if you want to find out which adapters are
     *        mapped to which state. You can even use the toString() operation
     *        there to map this parameter to a string. Sometimes, I use the
     *        term phase as an alias.
     */
    virtual OracleForOnePhase* createNewOracle(int adapterNumber, const MethodTrace& methodTrace) const = 0;
};


#endif
