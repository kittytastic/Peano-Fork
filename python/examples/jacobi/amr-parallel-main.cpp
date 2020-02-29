#include "amr-parallel-main.h"
#include "Constants.h"

#include "tarch/logging/Log.h"

#include "tarch/tests/TestCaseRegistry.h"

#include "tarch/logging/LogFilter.h"
#include "tarch/logging/CommandLineLogger.h"

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


tarch::logging::Log _log("");


class ProgramRun {
  private:
  public:
    /**
     * Init spacetree set
     */
    ProgramRun() {
      peano4::parallel::SpacetreeSet::getInstance().init(
        examples::jacobi::actions::SetupScenario::getDomainOffset(),
        examples::jacobi::actions::SetupScenario::getDomainSize()
      );
    }


    void step() {
      int stepIdentifier = peano4::parallel::Node::getInstance().getCurrentProgramStep();
      // @todo Debug
      logInfo( "ProgramRun::step()", "run step " << stepIdentifier );

      // @todo Hier waere ein Case schoen
      switch (stepIdentifier) {
        case 0:
          {
            examples::jacobi::observers::CreateGrid  observer;
            peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
          }
          break;
        case 1:
          {
            examples::jacobi::observers::SetupScenario  observer;
            peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
          }
          break;
        case 2:
          {
            examples::jacobi::observers::PlotMaterialParameter  observer;
            peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
          }
          break;
        case 10:
          {
            if ( tarch::mpi::Rank::getInstance().getNumberOfRanks()>1 ) {
              int cellsPerRank = peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells() / tarch::mpi::Rank::getInstance().getNumberOfRanks();
              logInfo( "ProgramRun::step()", "should host " << cellsPerRank << " cells per rank (total number of cells: " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells() << ")" );

              for (int rank=1; rank<tarch::mpi::Rank::getInstance().getNumberOfRanks(); rank++) {
                if ( not peano4::parallel::SpacetreeSet::getInstance().split(0,cellsPerRank,rank)) {
                  logWarning( "runParallel(...)", "failed to assign rank " << rank << " " << cellsPerRank << " cell(s)" );
                }
              }
            }
          }
          break;
        case 11:
          {
            if (tarch::multicore::Core::getInstance().getNumberOfThreads()>1) {
              assertion(false);
              int cellsPerCore = peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells() / tarch::multicore::Core::getInstance().getNumberOfThreads();
              logInfo( "ProgramRun::step()", "should host " << cellsPerCore << " cells per core" );
              for (int thread=1; thread<tarch::multicore::Core::getInstance().getNumberOfThreads(); thread++) {
                // @todo aber mein Rank und mein Tree
                if ( not peano4::parallel::SpacetreeSet::getInstance().split(0,cellsPerCore,0)) {
                  logWarning( "runParallel(...)", "failed to assign thread " << thread << " " << cellsPerCore << " cell(s)" );
                }
              }
            }
          }
          break;
        case 50:
          {
            examples::jacobi::observers::FusedSolverSteps  observer;
            peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
          }
          break;
        case 99:
          {
            examples::jacobi::observers::PlotSolution  observer;
            peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
          }
          break;
        default:
          assertionMsg(false, "step unknown");
      }

      tarch::logging::CommandLineLogger::getInstance().closeOutputStreamAndReopenNewOne();
    }

    void runGlobalMaster(int iterations) {
      // Construct grid until we are told that it hasn't changed for
      // more than two iterations.
      // ===========================================================
      do {
        peano4::parallel::Node::getInstance().setNextProgramStep(0);
        step();
      }
      while (peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getStationarySweeps()<2);

      peano4::parallel::Node::getInstance().setNextProgramStep(1); // setup scenario
      step();

      peano4::parallel::Node::getInstance().setNextProgramStep(2); // dump parameters
      step();

      peano4::parallel::Node::getInstance().setNextProgramStep(10); // dump parameters
      step();

      peano4::parallel::Node::getInstance().setNextProgramStep(11); // dump parameters
      step();

      for (int i=0; i<iterations; i++) {
        peano4::parallel::Node::getInstance().setNextProgramStep(50); // solve problem
        step();
      }

      peano4::parallel::Node::getInstance().setNextProgramStep(99); // plot solution
      step();
    }
};



int main(int argc, char** argv) {
  const int ExitCodeSuccess         = 0;
  const int ExitCodeUnitTestsFailed = 1;

  peano4::initParallelEnvironment(&argc,&argv);
  peano4::initSharedMemoryEnvironment();
  peano4::fillLookupTables();

  examples::jacobi::observers::DataRepository::initDatatypes();

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
    // @todo Black
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
    tarch::logging::LogFilter::FilterListEntry::BlackListEntry
  ));
  tarch::logging::LogFilter::getInstance().addFilterListEntry( tarch::logging::LogFilter::FilterListEntry(
    tarch::logging::LogFilter::FilterListEntry::TargetDebug,
    tarch::logging::LogFilter::FilterListEntry::AnyRank,
    "examples",
    tarch::logging::LogFilter::FilterListEntry::WhiteListEntry
  ));
 
  // @todo Add your namespace here
//  tarch::logging::LogFilter::getInstance().addFilterListEntry( tarch::logging::LogFilter::FilterListEntry(
//    tarch::logging::LogFilter::FilterListEntry::Target..., 
//    tarch::logging::LogFilter::FilterListEntry::AnyRank, 
//    "mynamespace", 
//    tarch::logging::LogFilter::FilterListEntry::BlackListEntry
//  ));

  //tarch::logging::CommandLineLogger::getInstance().setOutputFile( "trace.log" );
  tarch::logging::CommandLineLogger::getInstance().setLogFormat(
    " ", false, false, false, false, false, true, "trace.log"
  );



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


  ProgramRun programRun;
  
  if (tarch::mpi::Rank::getInstance().isGlobalMaster() ) {
    const int MaxIterations = 10;
    programRun.runGlobalMaster(MaxIterations);
  }
  else {
    while (peano4::parallel::Node::getInstance().continueToRun()) {
      programRun.step();
    }
  }

  examples::jacobi::observers::DataRepository::shutdownDatatypes();

  peano4::shutdownSharedMemoryEnvironment();
  peano4::shutdownParallelEnvironment();

  return ExitCodeSuccess;
}
