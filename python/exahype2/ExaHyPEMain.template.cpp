#include "{MAIN_NAME}.h"
#include "Constants.h"

#include "tarch/logging/Log.h"
#include "tarch/logging/Statistics.h"
#include "tarch/UnitTests.h"
#include "tarch/multicore/multicore.h"
#include "tarch/multicore/Core.h"
#include "tarch/timing/Watch.h"
#include "tarch/timing/Measurement.h"

#include "peano4/peano.h"
#include "peano4/grid/Spacetree.h"
#include "peano4/parallel/SpacetreeSet.h"
#include "peano4/UnitTests.h"

#include "repositories/DataRepository.h"
#include "repositories/StepRepository.h"
#include "repositories/SolverRepository.h"

#include "observers/CreateGrid.h"
#include "observers/CreateGridButPostponeRefinement.h"
#include "observers/InitGrid.h"
#include "observers/PlotSolution.h"
#include "observers/TimeStep.h"



#include "exahype2/NonCriticalAssertions.h"
#include "exahype2/UserInterface.h"
#include "exahype2/SmartEnclaveTask.h"



using namespace {FULL_NAMESPACE};



tarch::logging::Log _log("::");



tarch::timing::Measurement   gridConstructionMeasurement;
tarch::timing::Measurement   timeStepMeasurement;
tarch::timing::Measurement   plotMeasurement;


/**
 *
 * <h2> Control of the parallel grid construction </h2>
 *
 * We realise a very simplistic parallel grid construction strategy: When I run
 * the grid creation, I allow refinement if no rebalancing has happened, and I 
 * stop the grid construction as soon as I've met the minimal mesh width. 
 * Otherwise, I use refinement. There's exceptions to this:
 *
 * - Every @K = f$ 3^d @f$ iterations, I run a refinement even if I rebalance. It 
 *   might happen that rebalancing is extremely slow or not successful on one 
 *   rank, making another drop in, and so forth. So I use K, as 
 *   there are at most that many splits possible due to a grid refinement.
 *   K might be chosen slightly smaller (see code).
 * - In each step, I identify whether I've changed the minimal mesh. If not, 
 *   I increment a counter. If this counter is $3K$, I know that the mesh 
 *   refinement would have had the opportunity to refine the grid three times.
 *   It hasn't done so. So I can assume that the minimal mesh size not yet 
 *   yet reached, but the mesh refinement criteria don't need that minimal mesh
 *   (yet). Such effects arise for smooth boundary conditions, e.g., that 
 *   create shocks later on, i.e. they arise for non-linear PDEs.
 * 
 * @return continues to run
 */
bool selectNextAlgorithmicStep() {{
  static bool   gridConstructed                             = false;
  static bool   gridInitialised                             = false;
  static double nextPlotTimeStamp                           = FirstPlotTimeStamp;
  static bool   haveJustWrittenSnapshot                     = false;
  static bool   haveReceivedNoncriticialAssertion           = false;
  static bool   addGridSweepWithoutGridRefinementNext       = false;
  static int    iterationsWithoutGridRefinement             = 0;
  static int    iterationsWithGridRefinement                = 0;
  static tarch::la::Vector<Dimensions,double> minH          = tarch::la::Vector<Dimensions,double>( std::numeric_limits<double>::max() );

  bool          continueToSolve   = true;
  
  if (exahype2::hasNonCriticalAssertionBeenViolated() and not haveReceivedNoncriticialAssertion) {{
    peano4::parallel::Node::getInstance().setNextProgramStep(
      repositories::StepRepository::toProgramStep( repositories::StepRepository::Steps::PlotSolution )
    );
    haveReceivedNoncriticialAssertion = true;
    logError( "selectNextAlgorithmicStep()", "non-critical assertion has been triggered in code. Dump final state and terminate" );
  }}
  else if (exahype2::hasNonCriticalAssertionBeenViolated()) {{
    continueToSolve = false;
  }}
  else if (gridConstructed and not gridInitialised) {{
    gridInitialised = true;
    
    peano4::parallel::Node::getInstance().setNextProgramStep(
      repositories::StepRepository::toProgramStep( repositories::StepRepository::Steps::InitGrid )
    );
 
    assertionNumericalEquals( repositories::getMinTimeStamp(), 0.0 );
  }}
  else if (not gridConstructed) {{
    // Grid construction termination criterion
    if (
      tarch::la::max( peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH() ) <= repositories::getMinMeshSize()
      and
      peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getRemovedEmptySubtree()
    ) {{
      logInfo( "selectNextAlgorithmicStep()", "finest mesh resolution of " << repositories::getMinMeshSize() << " reached with h_min=" << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH() << " and also overdecomposed before" );
      gridConstructed = true;
      addGridSweepWithoutGridRefinementNext = false;
    }}
    else if (
      tarch::la::max( peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH() ) <= repositories::getMinMeshSize()
      and
      iterationsWithGridRefinement>ThreePowerD
    ) {{
      logInfo( "selectNextAlgorithmicStep()", "finest mesh resolution of " << repositories::getMinMeshSize() << " reached with a sufficient number of refinements" );
      gridConstructed = true;
      addGridSweepWithoutGridRefinementNext = false;
    }}
    else {{
      logDebug( "selectNextAlgorithmicStep()", "finest mesh resolution of " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH() << " does not yet meet mesh requirements of " << repositories::getMinMeshSize() );
    }}

    // Actual grid traversal choice
    if (addGridSweepWithoutGridRefinementNext) {{
      peano4::parallel::Node::getInstance().setNextProgramStep(
        repositories::StepRepository::toProgramStep( repositories::StepRepository::Steps::CreateGridButPostponeRefinement )
      );
      iterationsWithoutGridRefinement++;
      iterationsWithGridRefinement = 0;
    }}
    else {{
      peano4::parallel::Node::getInstance().setNextProgramStep(
        repositories::StepRepository::toProgramStep( repositories::StepRepository::Steps::CreateGrid )
      );
      iterationsWithoutGridRefinement = 0;
      iterationsWithGridRefinement++;
    }}

    //  A posterioi sweep analysis. Not really a posteriori though
    static int maxNumberOfLocalSpacetrees         = 0;
    if ( tarch::la::max( peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH() ) < tarch::la::max( minH ) ) {{
      minH = peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH();
      logDebug( "selectNextAlgorithmicStep()", "mesh has refined, so reset minH=" << minH << " and postpone further refinement" );
      addGridSweepWithoutGridRefinementNext           = true;
    }}
    else {{
      if (repositories::loadBalancer.hasSplitRecently() and static_cast<int>(peano4::parallel::SpacetreeSet::getInstance().getLocalSpacetrees().size())>=maxNumberOfLocalSpacetrees) {{
        logInfo( 
          "selectNextAlgorithmicStep()", 
          "mesh has rebalanced recently, so postpone further refinement (former max tree count " << maxNumberOfLocalSpacetrees << ", current count " << peano4::parallel::SpacetreeSet::getInstance().getLocalSpacetrees().size() << ")" 
        );
        addGridSweepWithoutGridRefinementNext = true;
      }} 
      else if (repositories::loadBalancer.hasSplitRecently()) {{
        logInfo( "selectNextAlgorithmicStep()", "mesh wanted to rebalance recently but it seems that splits have been unsuccessful" );
        addGridSweepWithoutGridRefinementNext = false;
      }}
      else {{
        logInfo( "selectNextAlgorithmicStep()", "mesh rebalancing seems to be kind of stationary, so study whether to refine mesh further in next sweep" );
        addGridSweepWithoutGridRefinementNext = false;
      }}

      if (static_cast<int>(peano4::parallel::SpacetreeSet::getInstance().getLocalSpacetrees().size())>maxNumberOfLocalSpacetrees) {{
        maxNumberOfLocalSpacetrees += 1;
      }}
    }}

    continueToSolve = true;
  }}
  else {{
    if ( repositories::getMinTimeStamp()>=nextPlotTimeStamp  and TimeInBetweenPlots>0.0 ) {{
      nextPlotTimeStamp += TimeInBetweenPlots;
      if ( nextPlotTimeStamp < repositories::getMinTimeStamp() ) {{
        logWarning( "selectNextAlgorithmicStep()", "code is asked to plot every dt=" << TimeInBetweenPlots << ", but this seems to be less than the minimal time step size of the solvers" );
        nextPlotTimeStamp = repositories::getMinTimeStamp() + TimeInBetweenPlots;
        logWarning( "selectNextAlgorithmicStep()", "plot solution at t=" << repositories::getMinTimeStamp() << ", but next plot will be due at t=" << nextPlotTimeStamp );
      }}
      peano4::parallel::Node::getInstance().setNextProgramStep(
        repositories::StepRepository::toProgramStep( repositories::StepRepository::Steps::PlotSolution )
      );
      haveJustWrittenSnapshot = true;
      continueToSolve         = true;
    }}
    else if ( repositories::getMinTimeStamp()<TerminalTime ) {{
      peano4::parallel::Node::getInstance().setNextProgramStep(
        repositories::StepRepository::toProgramStep( repositories::StepRepository::Steps::TimeStep )
      );
      continueToSolve         = true;
      haveJustWrittenSnapshot = false;
    }}
    else {{
      if (not haveJustWrittenSnapshot and TimeInBetweenPlots>0.0) {{
        peano4::parallel::Node::getInstance().setNextProgramStep(
          repositories::StepRepository::toProgramStep( repositories::StepRepository::Steps::PlotSolution )
        );
        continueToSolve         = true; // don't want to terminate immediately
        haveJustWrittenSnapshot = true;
        nextPlotTimeStamp       = std::numeric_limits<double>::max();
      }}
      else {{
        continueToSolve = false;
      }}
    }}
  }}

  return continueToSolve;
}}


void step() {{
  int  stepIdentifier = peano4::parallel::Node::getInstance().getCurrentProgramStep();
  auto stepName       = repositories::StepRepository::toStepEnum(stepIdentifier);

  static tarch::logging::Log _log("");
  logInfo( "step()", "run " << repositories::StepRepository::toString(stepName) );

  tarch::timing::Watch  watch( "::", "step()", false );

  switch ( stepName ) {{
    case repositories::StepRepository::Steps::CreateGridButPostponeRefinement:
      {{
        repositories::startGridConstructionStep();

        observers::CreateGridButPostponeRefinement  observer;
        peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
        watch.stop();
        gridConstructionMeasurement.setValue( watch.getCalendarTime() );

        repositories::finishGridConstructionStep();
      }}
      break;
    case repositories::StepRepository::Steps::CreateGrid:
      {{
        // @todo Muss ich nochmal anschauen
        if (
          tarch::la::max( peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH() ) <= repositories::getMinMeshSize()
          and
          peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getRemovedEmptySubtree()
        ) {{
          logInfo( "step()", "switch off load balancing manually as finest grid resolution met and fork has failed before" );
          repositories::loadBalancer.enable(false);
        }}

        repositories::startGridConstructionStep();
        
        observers::CreateGrid  observer;
        peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
        watch.stop();
        gridConstructionMeasurement.setValue( watch.getCalendarTime() );

        repositories::finishGridConstructionStep();
      }}
      break;
    case repositories::StepRepository::Steps::InitGrid:
      {{
        //if (
        //  tarch::la::max( peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH() ) <= repositories::getMinMeshSize()
        //) {{
          logInfo( "step()", "disable load balancing throughout initialisation (to be removed in later releases)" );
          repositories::loadBalancer.enable(false);
        //}}
    
        repositories::startGridInitialisationStep();
        
        observers::InitGrid  observer;
        peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
        watch.stop();
        gridConstructionMeasurement.setValue( watch.getCalendarTime() );

        repositories::finishGridInitialisationStep();
      }}
      break;
    case repositories::StepRepository::Steps::PlotSolution:
      {{
        const double minTimeStamp    = repositories::getMinTimeStamp();
        const double maxTimeStamp    = repositories::getMaxTimeStamp();
        const double minTimeStepSize = repositories::getMinTimeStepSize();
        const double maxTimeStepSize = repositories::getMaxTimeStepSize();

        repositories::startPlottingStep( minTimeStamp, maxTimeStamp, minTimeStepSize, maxTimeStepSize );

        observers::PlotSolution  observer;
        peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
        watch.stop();
        plotMeasurement.setValue( watch.getCalendarTime() );
        
        repositories::finishPlottingStep();
      }}
      break;
    case repositories::StepRepository::Steps::TimeStep:
      {{
        const double minTimeStamp    = repositories::getMinTimeStamp();
        const double maxTimeStamp    = repositories::getMaxTimeStamp();
        const double minTimeStepSize = repositories::getMinTimeStepSize();
        const double maxTimeStepSize = repositories::getMaxTimeStepSize();

        if ( tarch::mpi::Rank::getInstance().isGlobalMaster() ) {{
          logInfo( "step()", "t_{{min}}  = " << minTimeStamp );
          logInfo( "step()", "t_{{max}}  = " << maxTimeStamp );
          logInfo( "step()", "dt_{{min}} = " << minTimeStepSize );
          logInfo( "step()", "dt_{{max}} = " << maxTimeStepSize );
        }}
        repositories::startTimeStep( minTimeStamp, maxTimeStamp, minTimeStepSize, maxTimeStepSize );
        
        observers::TimeStep  observer;
        peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
        watch.stop();
        timeStepMeasurement.setValue( watch.getCalendarTime() );
        
        repositories::finishTimeStep();
      }}
      break;
    case repositories::StepRepository::Steps::Undef:
      assertion(false);
      break;
  }}
}}
  
  
int main(int argc, char** argv) {{
  const int ExitCodeSuccess          = 0;
  const int ExitCodeUnitTestsFailed  = 1;
  const int ExitCodeInvalidArguments = 2;
  const int ExitCodeInvalidBuild     = 3;
  
  peano4::initParallelEnvironment(&argc,&argv);
  exahype2::initNonCritialAssertionEnvironment();
  exahype2::initSmartMPI();
  peano4::fillLookupTables();
 
  
  peano4::initSingletons(
    DomainOffset,
    DomainSize,
    {PERIODIC_BC}
  );
  
  if ( tarch::mpi::Rank::getInstance().getNumberOfRanks()>1 and tarch::multicore::Core::getInstance().getNumberOfThreads()<=1 ) {{
    logError("main()", "MPI runs without multithreading are not supported currently.");
    return ExitCodeInvalidBuild;
  }}

  if (not exahype2::parseCommandLineArguments(argc,argv) ) {{
    return ExitCodeInvalidArguments;
  }}
  
  {FULL_NAMESPACE}::repositories::DataRepository::initDatatypes();
  
  #if PeanoDebug>=2
  tarch::tests::TestCase* peanoCoreTests = peano4::getUnitTests();
  peanoCoreTests->run();
  if (peanoCoreTests->getNumberOfErrors() != 0) {{
    logError("main()", "Peano4 core unit tests failed. Quit.");
    tarch::mpi::Rank::abort( ExitCodeUnitTestsFailed );
  }}
  delete peanoCoreTests;

  tarch::tests::TestCase* peanoTarchTests = tarch::getUnitTests();
  peanoTarchTests->run();
  if (peanoTarchTests->getNumberOfErrors() != 0) {{
    logError("main()", "technical architecture (tarch) unit tests failed. Quit.");
    tarch::mpi::Rank::abort( ExitCodeUnitTestsFailed );
  }}
  delete peanoTarchTests;
  #endif

  repositories::startSimulation();

  tarch::logging::Statistics::getInstance().clear();

  #if defined(SharedOMP)
  #pragma omp parallel
  {{
  #pragma omp master 
  {{
  #endif
  if (tarch::mpi::Rank::getInstance().isGlobalMaster() ) {{
    while ( selectNextAlgorithmicStep() ) {{
      step();
    }}

    logInfo("main()", "terminated successfully");
    logInfo("main()", "initial grid construction:  " << gridConstructionMeasurement.getAccumulatedValue() << "s\t" << gridConstructionMeasurement.toString() );
    logInfo("main()", "plotting:                   " << plotMeasurement.getAccumulatedValue() << "s\t" << plotMeasurement.toString() );
    logInfo("main()", "time stepping:              " << timeStepMeasurement.getAccumulatedValue() << "s\t" << timeStepMeasurement.toString() );
  }}
  else {{
    while (peano4::parallel::Node::getInstance().continueToRun()) {{
      step();
    }}
  }}
  #if defined(SharedOMP)
  }}
  }}
  #endif

  tarch::logging::Statistics::getInstance().writeToCSV();

  repositories::finishSimulation();

  peano4::shutdownSingletons();
  {FULL_NAMESPACE}::repositories::DataRepository::shutdownDatatypes();
  exahype2::shutdownSmartMPI();
  exahype2::shutdownNonCritialAssertionEnvironment();
  peano4::shutdownParallelEnvironment();

  return ExitCodeSuccess;
}}
