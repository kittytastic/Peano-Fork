#include "exaclaw-main.h"
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

#include "observers/DataRepository.h"
#include "observers/StepRepository.h"
#include "observers/SolverRepository.h"
#include "observers/CreateGrid.h"
#include "observers/CreateGridButPostponeRefinement.h"
#include "observers/InitGrid.h"
#include "observers/PlotSolution.h"
#include "observers/TimeStep.h"



#include "exahype2/NonCriticalAssertions.h"
#include "exahype2/UserInterface.h"



using namespace examples::exahype2::acoustics;



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
bool selectNextAlgorithmicStep() {
  static bool   gridConstructed                             = false;
  static double nextPlotTimeStamp                           = FirstPlotTimeStamp;
  static bool   haveJustWrittenSnapshot                     = false;
  static bool   haveReceivedNoncriticialAssertion           = false;
  static bool   addGridSweepWithoutGridRefinementNext       = false;
  static int    iterationsWithoutGridRefinement             = 0;
  static int    iterationsWithGridRefinementSinceLastRefinement  = 0;
  static int    initGridIterations                               = 0;
  static tarch::la::Vector<Dimensions,double> minH               = tarch::la::Vector<Dimensions,double>( std::numeric_limits<double>::max() );

  bool          continueToSolve   = true;
  
  // Once we have hit the finest grid, we have to inject a few
  // CreateGrid sweeps, as some subpartitions might lag behind
  // by means of the mesh construction. As a consequence, there
  // might still be an adaptive mesh even though we want to 
  // operate with a regular one. See the FAQ in the guidebook 
  const int InitGridIterations = 3;
  
  if (exahype2::hasNonCriticalAssertionBeenViolated() and not haveReceivedNoncriticialAssertion) {
    peano4::parallel::Node::getInstance().setNextProgramStep(
      observers::StepRepository::toProgramStep( observers::StepRepository::Steps::PlotSolution )
    );
    haveReceivedNoncriticialAssertion = true;
    logError( "selectNextAlgorithmicStep()", "non-critical assertion has been triggered in code. Dump final state and terminate" );
  }
  else if (exahype2::hasNonCriticalAssertionBeenViolated()) {
    continueToSolve = false;
  }
  else if (gridConstructed and initGridIterations<InitGridIterations) {
    initGridIterations++;
    
    if (initGridIterations==InitGridIterations) {
      peano4::parallel::Node::getInstance().setNextProgramStep(
        observers::StepRepository::toProgramStep( observers::StepRepository::Steps::InitGrid )
      );
    }
    else {
      peano4::parallel::Node::getInstance().setNextProgramStep(
        observers::StepRepository::toProgramStep( observers::StepRepository::Steps::CreateGrid )
      );
    }
 
    assertionNumericalEquals( observers::getMinTimeStamp(), 0.0 );
  }
  else if (not gridConstructed) {
    if (
      tarch::la::max( peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH() ) <= observers::getMinMeshSize()
    ) {
      logInfo( "selectNextAlgorithmicStep()", "finest mesh resolution of " << observers::getMinMeshSize() << " reached with h_min=" << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH() );
      gridConstructed = true;
      addGridSweepWithoutGridRefinementNext = false;
      
      logInfo( "selectNextAlgorithmicStep()", "switch off load balancing manually (to be removed in later releases)" );
      observers::loadBalancer.enable(false);
    }
    else if (
      peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getStationarySweeps()>=4
      and
      observers::StepRepository::toStepEnum( peano4::parallel::Node::getInstance().getCurrentProgramStep() )==observers::StepRepository::Steps::CreateGrid
      and 
      iterationsWithGridRefinementSinceLastRefinement>3
    ) {
      logInfo( "selectNextAlgorithmicStep()", "grid has been stationary for a while, so continue with solve. Finest mesh resolution is " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH()  );
      gridConstructed = true;
      addGridSweepWithoutGridRefinementNext = false;
    }
    else {
      logDebug( "selectNextAlgorithmicStep()", "finest mesh resolution of " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH() << " does not yet meet mesh requirements of " << observers::getMinMeshSize() );
    }

    if (addGridSweepWithoutGridRefinementNext) {
      peano4::parallel::Node::getInstance().setNextProgramStep(
        observers::StepRepository::toProgramStep( observers::StepRepository::Steps::CreateGridButPostponeRefinement )
      );
      iterationsWithoutGridRefinement++;
    }
    else {
      peano4::parallel::Node::getInstance().setNextProgramStep(
        observers::StepRepository::toProgramStep( observers::StepRepository::Steps::CreateGrid )
      );
      iterationsWithoutGridRefinement = 0;
    }

    const int MaxIterationsWithoutGridRefinement = ThreePowerD;
    if ( tarch::la::max( peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH() ) < tarch::la::max( minH ) ) {
      minH = peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getMinH();
      logDebug( "selectNextAlgorithmicStep()", "mesh has refined, so reset minH=" << minH << " and postpone further refinement" );
      iterationsWithGridRefinementSinceLastRefinement = 0;
      addGridSweepWithoutGridRefinementNext           = true;
    }
    else {
      if (not addGridSweepWithoutGridRefinementNext) iterationsWithGridRefinementSinceLastRefinement++;

      if (observers::loadBalancer.hasSplitRecently() and iterationsWithoutGridRefinement<MaxIterationsWithoutGridRefinement) {
        logInfo( "selectNextAlgorithmicStep()", "mesh has rebalanced recently, so postpone further refinement" );
        addGridSweepWithoutGridRefinementNext = true;
      } 
      else if (observers::loadBalancer.hasSplitRecently() and iterationsWithoutGridRefinement>=MaxIterationsWithoutGridRefinement) {
        logInfo( "selectNextAlgorithmicStep()", "mesh has rebalanced recently but I've done so many iterations without refinement that I insert one refinement next" );
        addGridSweepWithoutGridRefinementNext = false;
      }
      else {
        logInfo( "selectNextAlgorithmicStep()", "mesh rebalancing seems to be kind of stationary, so refine mesh further in next sweep" );
        addGridSweepWithoutGridRefinementNext = false;
      }
    }

    continueToSolve = true;
  }
  else {
    if ( observers::getMinTimeStamp()>=nextPlotTimeStamp  and TimeInBetweenPlots>0.0 ) {
      nextPlotTimeStamp += TimeInBetweenPlots;
      if ( nextPlotTimeStamp < observers::getMinTimeStamp() ) {
        logWarning( "selectNextAlgorithmicStep()", "code is asked to plot every dt=" << TimeInBetweenPlots << ", but this seems to be less than the minimal time step size of the solvers" );
        nextPlotTimeStamp = observers::getMinTimeStamp() + TimeInBetweenPlots;
        logWarning( "selectNextAlgorithmicStep()", "plot solution at t=" << observers::getMinTimeStamp() << ", but next plot will be due at t=" << nextPlotTimeStamp );
      }
      peano4::parallel::Node::getInstance().setNextProgramStep(
        observers::StepRepository::toProgramStep( observers::StepRepository::Steps::PlotSolution )
      );
      haveJustWrittenSnapshot = true;
      continueToSolve         = true;
    }
    else if ( observers::getMinTimeStamp()<TerminalTime ) {
      peano4::parallel::Node::getInstance().setNextProgramStep(
        observers::StepRepository::toProgramStep( observers::StepRepository::Steps::TimeStep )
      );
      continueToSolve         = true;
      haveJustWrittenSnapshot = false;
    }
    else {
      if (not haveJustWrittenSnapshot and TimeInBetweenPlots>0.0) {
        peano4::parallel::Node::getInstance().setNextProgramStep(
          observers::StepRepository::toProgramStep( observers::StepRepository::Steps::PlotSolution )
        );
        continueToSolve         = true; // don't want to terminate immediately
        haveJustWrittenSnapshot = true;
        nextPlotTimeStamp       = std::numeric_limits<double>::max();
      }
      else {
        continueToSolve = false;
      }
    }
  }

  return continueToSolve;
}


void step() {
  int  stepIdentifier = peano4::parallel::Node::getInstance().getCurrentProgramStep();
  auto stepName       = observers::StepRepository::toStepEnum(stepIdentifier);

  static tarch::logging::Log _log("");
  logInfo( "step()", "run " << observers::StepRepository::toString(stepName) );

  tarch::timing::Watch  watch( "::", "step()", false );

  switch ( stepName ) {
    case observers::StepRepository::Steps::CreateGridButPostponeRefinement:
      {
        observers::startGridConstructionStep();

        observers::CreateGridButPostponeRefinement  observer;
        peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
        watch.stop();
        gridConstructionMeasurement.setValue( watch.getCalendarTime() );

        observers::finishGridConstructionStep();
      }
      break;
    case observers::StepRepository::Steps::CreateGrid:
      {
        observers::startGridConstructionStep();
        
        observers::CreateGrid  observer;
        peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
        watch.stop();
        gridConstructionMeasurement.setValue( watch.getCalendarTime() );

        observers::finishGridConstructionStep();
      }
      break;
    case observers::StepRepository::Steps::InitGrid:
      {
        #ifdef Parallel
        observers::loadBalancer.enable(false);
        #endif
    
        observers::startGridInitialisationStep();
        
        observers::InitGrid  observer;
        peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
        watch.stop();
        gridConstructionMeasurement.setValue( watch.getCalendarTime() );

        observers::finishGridInitialisationStep();
      }
      break;
    case observers::StepRepository::Steps::PlotSolution:
      {
        const double minTimeStamp    = observers::getMinTimeStamp();
        const double maxTimeStamp    = observers::getMaxTimeStamp();
        const double minTimeStepSize = observers::getMinTimeStepSize();
        const double maxTimeStepSize = observers::getMaxTimeStepSize();

        observers::startPlottingStep( minTimeStamp, maxTimeStamp, minTimeStepSize, maxTimeStepSize );

        observers::PlotSolution  observer;
        peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
        watch.stop();
        plotMeasurement.setValue( watch.getCalendarTime() );
        
        observers::finishPlottingStep();
      }
      break;
    case observers::StepRepository::Steps::TimeStep:
      {
        const double minTimeStamp    = observers::getMinTimeStamp();
        const double maxTimeStamp    = observers::getMaxTimeStamp();
        const double minTimeStepSize = observers::getMinTimeStepSize();
        const double maxTimeStepSize = observers::getMaxTimeStepSize();

        if ( tarch::mpi::Rank::getInstance().isGlobalMaster() ) {
          logInfo( "step()", "t_{min}  = " << minTimeStamp );
          logInfo( "step()", "t_{max}  = " << maxTimeStamp );
          logInfo( "step()", "dt_{min} = " << minTimeStepSize );
          logInfo( "step()", "dt_{max} = " << maxTimeStepSize );
        }
        observers::startTimeStep( minTimeStamp, maxTimeStamp, minTimeStepSize, maxTimeStepSize );
        
        observers::TimeStep  observer;
        peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
        watch.stop();
        timeStepMeasurement.setValue( watch.getCalendarTime() );
        
        observers::finishTimeStep();
      }
      break;
    case observers::StepRepository::Steps::Undef:
      assertion(false);
      break;
  }
}
  
  
int main(int argc, char** argv) {
  const int ExitCodeSuccess          = 0;
  const int ExitCodeUnitTestsFailed  = 1;
  const int ExitCodeInvalidArguments = 2;
  const int ExitCodeInvalidBuild     = 3;
  
  peano4::initParallelEnvironment(&argc,&argv);
  exahype2::initNonCritialAssertionEnvironment();
  peano4::fillLookupTables();
  
  peano4::initSingletons(
    DomainOffset,
    DomainSize,
    0
  );
  
  if ( tarch::mpi::Rank::getInstance().getNumberOfRanks()>1 and tarch::multicore::Core::getInstance().getNumberOfThreads()<=1 ) {
    logError("main()", "MPI runs without multithreading are not supported currently.");
    return ExitCodeInvalidBuild;
  }

  if (not exahype2::parseCommandLineArguments(argc,argv) ) {
    return ExitCodeInvalidArguments;
  }
  
  examples::exahype2::acoustics::observers::DataRepository::initDatatypes();
  
  #if PeanoDebug>=2
  tarch::tests::TestCase* peanoCoreTests = peano4::getUnitTests();
  peanoCoreTests->run();
  if (peanoCoreTests->getNumberOfErrors() != 0) {
    logError("main()", "Peano4 core unit tests failed. Quit.");
    tarch::mpi::Rank::abort( ExitCodeUnitTestsFailed );
  }
  delete peanoCoreTests;

  tarch::tests::TestCase* peanoTarchTests = tarch::getUnitTests();
  peanoTarchTests->run();
  if (peanoTarchTests->getNumberOfErrors() != 0) {
    logError("main()", "technical architecture (tarch) unit tests failed. Quit.");
    tarch::mpi::Rank::abort( ExitCodeUnitTestsFailed );
  }
  delete peanoTarchTests;
  #endif

  tarch::logging::Statistics::getInstance().clear();

  #if defined(SharedOMP)
  #pragma omp parallel
  {
  #pragma omp master 
  {
  #endif
  if (tarch::mpi::Rank::getInstance().isGlobalMaster() ) {
    while ( selectNextAlgorithmicStep() ) {
      step();
    }

    logInfo("main()", "terminated successfully");
    logInfo("main()", "initial grid construction:  " << gridConstructionMeasurement.getAccumulatedValue() << "s\t" << gridConstructionMeasurement.toString() );
    logInfo("main()", "plotting:                   " << plotMeasurement.getAccumulatedValue() << "s\t" << plotMeasurement.toString() );
    logInfo("main()", "time stepping:              " << timeStepMeasurement.getAccumulatedValue() << "s\t" << timeStepMeasurement.toString() );
  }
  else {
    while (peano4::parallel::Node::getInstance().continueToRun()) {
      step();
    }
  }
  #if defined(SharedOMP)
  }
  }
  #endif

  tarch::logging::Statistics::getInstance().writeToCSV();

  observers::finishSimulation();

  peano4::shutdownSingletons();
  examples::exahype2::acoustics::observers::DataRepository::shutdownDatatypes();
  exahype2::shutdownNonCritialAssertionEnvironment();
  peano4::shutdownParallelEnvironment();

  return ExitCodeSuccess;
}
