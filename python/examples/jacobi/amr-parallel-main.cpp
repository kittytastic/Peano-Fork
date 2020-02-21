#include "main.h"
#include "Constants.h"

#include "tarch/logging/Log.h"

#include "tarch/tests/TestCaseRegistry.h"
#include "tarch/logging/LogFilter.h"
#include "tarch/multicore/multicore.h"
#include "tarch/multicore/Core.h"

#include "peano4/peano.h"
#include "peano4/grid/Spacetree.h"
#include "peano4/parallel/SpacetreeSet.h"

#include "observers/DataRepository.h"

#include "observers/DataRepository.h"
#include "observers/PlotSolution.h"
#include "observers/PlotMaterialParameter.h"
#include "observers/CreateGrid.h"
#include "observers/SetupScenario.h"
#include "observers/ComputeResidualWithGeometricOperators.h"
#include "observers/ComputeGlobalResidualAndError.h"
#include "observers/JacobiUpdate.h"
#include "observers/FusedSolverSteps.h"


tarch::logging::Log _log("::");


int main(int argc, char** argv) {
  const int ExitCodeSuccess         = 0;
  const int ExitCodeUnitTestsFailed = 1;

  peano4::initParallelEnvironment(&argc,&argv);
  peano4::initSharedMemoryEnvironment();
  peano4::fillLookupTables();

  tarch::logging::LogFilter::getInstance().addFilterListEntry( tarch::logging::LogFilter::FilterListEntry(
    tarch::logging::LogFilter::FilterListEntry::TargetDebug, 
    tarch::logging::LogFilter::FilterListEntry::AnyRank, 
    "peano4", 
    tarch::logging::LogFilter::FilterListEntry::BlackListEntry
  ));
  tarch::logging::LogFilter::getInstance().addFilterListEntry( tarch::logging::LogFilter::FilterListEntry(
    tarch::logging::LogFilter::FilterListEntry::TargetInfo, 
    tarch::logging::LogFilter::FilterListEntry::AnyRank, 
    "peano4", 
    tarch::logging::LogFilter::FilterListEntry::WhiteListEntry
  ));
  tarch::logging::LogFilter::getInstance().addFilterListEntry( tarch::logging::LogFilter::FilterListEntry(
    tarch::logging::LogFilter::FilterListEntry::TargetTrace, 
    tarch::logging::LogFilter::FilterListEntry::AnyRank, 
    "peano4", 
    tarch::logging::LogFilter::FilterListEntry::WhiteListEntry
  ));
  tarch::logging::LogFilter::getInstance().addFilterListEntry( tarch::logging::LogFilter::FilterListEntry(
    tarch::logging::LogFilter::FilterListEntry::TargetDebug, 
    tarch::logging::LogFilter::FilterListEntry::AnyRank, 
    "tarch", 
    tarch::logging::LogFilter::FilterListEntry::BlackListEntry
  ));
  tarch::logging::LogFilter::getInstance().addFilterListEntry( tarch::logging::LogFilter::FilterListEntry(
    tarch::logging::LogFilter::FilterListEntry::TargetInfo, 
    tarch::logging::LogFilter::FilterListEntry::AnyRank, 
    "tarch", 
    tarch::logging::LogFilter::FilterListEntry::WhiteListEntry
  ));
  tarch::logging::LogFilter::getInstance().addFilterListEntry( tarch::logging::LogFilter::FilterListEntry(
    tarch::logging::LogFilter::FilterListEntry::TargetTrace, 
    tarch::logging::LogFilter::FilterListEntry::AnyRank, 
    "tarch", 
    tarch::logging::LogFilter::FilterListEntry::WhiteListEntry
  ));
 
  // @todo Add your namespace here
//  tarch::logging::LogFilter::getInstance().addFilterListEntry( tarch::logging::LogFilter::FilterListEntry(
//    tarch::logging::LogFilter::FilterListEntry::Target..., 
//    tarch::logging::LogFilter::FilterListEntry::AnyRank, 
//    "mynamespace", 
//    tarch::logging::LogFilter::FilterListEntry::BlackListEntry
//  ));

  #if PeanoDebug>=2
  tarch::tests::TestCaseRegistry::getInstance().getTestCaseCollection().run();
  int unitTestsErrors = tarch::tests::TestCaseRegistry::getInstance()
                       .getTestCaseCollection()
                       .getNumberOfErrors();

  if (unitTestsErrors != 0) {
    logError("main()", "unit tests failed. Quit.");
    exit(ExitCodeUnitTestsFailed);
  }
  #endif


  int coreCount = 1;
  if (argc==2) {
    #ifdef SharedMemoryParallelisation
    coreCount = std::atof( argv[1] );
    logInfo( "main()", "use " << coreCount << " core(s)" );
    #else
    logWarning( "main()", "you should not set the thread count if you translate without multicore support" );
    #endif
    tarch::multicore::Core::getInstance().configure(coreCount);
  }
  else {
    #ifdef SharedMemoryParallelisation
    logError( "main()", "expect core count as additional argument" );
    exit(-1);
    #endif
  }


  peano4::parallel::SpacetreeSet::getInstance().init(
    examples::jacobi::actions::SetupScenario::getDomainOffset(),
    examples::jacobi::actions::SetupScenario::getDomainSize()
  );
  
  if (tarch::mpi::Rank::getInstance().isGlobalMaster() ) {
    // Construct grid until we are told that it hasn't changed for 
    // more than two iterations.
    // ===========================================================
    do {
      examples::jacobi::observers::CreateGrid  observer;
      peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
    }
    while (peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getStationarySweeps()<2);

    // Setup mesh and dump material parameter epsilon
    // ===========================================================
    {
      examples::jacobi::observers::SetupScenario  setupScenario;
      peano4::parallel::SpacetreeSet::getInstance().traverse(setupScenario);

      examples::jacobi::observers::PlotMaterialParameter  plotMaterialParameter;
      peano4::parallel::SpacetreeSet::getInstance().traverse(plotMaterialParameter);
    }

    // Split up domain among threads
    // ===========================================================
    if (coreCount>1) {
      int cellsPerCore = peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells() / coreCount;
      logInfo( "main()", "should host " << cellsPerCore << " cells per core" );

      for (int thread=1; thread<coreCount; thread++) {
        if ( not peano4::parallel::SpacetreeSet::getInstance().split(0,cellsPerCore,0)) {
          logWarning( "runParallel(...)", "failed to assign thread " << thread << " " << cellsPerCore << " cell(s)" );
        }
      }
    }
    
    // Solve problem
    // ===========================================================
    const int MaxIterations = 80;

    for (int i=0; i<MaxIterations; i++)
    {
      examples::jacobi::observers::FusedSolverSteps observer;
      peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
    }

    // Plot output
    // ===========================================================
    {
      examples::jacobi::observers::PlotSolution  observer;
      peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
    }
  }
  else {
    while (peano4::parallel::Node::getInstance().continueToRun()) {
      logDebug( "runParallel(...)", "trigger a new sweep with step " << peano4::parallel::Node::getInstance().getCurrentProgramStep() );
    }
  }

  peano4::shutdownSharedMemoryEnvironment();
  peano4::shutdownParallelEnvironment();

  return ExitCodeSuccess;
}
