#include "MyObserver.h"

#include "tarch/logging/Log.h"
#include "tarch/tests/TestCaseRegistry.h"
#include "tarch/logging/CommandLineLogger.h"
#include "tarch/multicore/Core.h"
#include "tarch/mpi/Rank.h"

#include "peano4/peano.h"
#include "peano4/grid/Spacetree.h"
#include "peano4/parallel/SpacetreeSet.h"
#include "peano4/parallel/Node.h"


tarch::logging::Log _log("examples::regulargridupscaling");


void runTests() {
  #if PeanoDebug>=1
  tarch::tests::TestCaseRegistry::getInstance().getTestCaseCollection().run();
  int unitTestsErrors = tarch::tests::TestCaseRegistry::getInstance()
                       .getTestCaseCollection()
                       .getNumberOfErrors();

  if (unitTestsErrors != 0) {
    logError("main()", "unit tests failed. Quit.");
    exit(-2);
  }
  #endif
}


void updateDomainDecomposition() {
  static int phase = 0;

  int targetRank = (phase+1) % tarch::mpi::Rank::getInstance().getNumberOfRanks();

  if (phase==0) {
    const int spacetreeOfInterest = 0;

    if ( peano4::parallel::SpacetreeSet::getInstance().isLocalSpacetree(spacetreeOfInterest) ) {
      if (
        peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells()>=ThreePowerD
        and
        peano4::parallel::SpacetreeSet::getInstance().split(0,peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells()/3,targetRank)
        and
        peano4::parallel::SpacetreeSet::getInstance().split(0,peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells()/3,targetRank)
      ) {
        phase++;
      }
    }
    else phase++;
  }
  else if (
    phase==1
    and
    peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells()>=ThreePowerD*2
  ) {
    const int spacetreeOfInterest = 1;

    if ( peano4::parallel::SpacetreeSet::getInstance().isLocalSpacetree(spacetreeOfInterest) ) {
      if ( not peano4::parallel::SpacetreeSet::getInstance().split(1,peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells()/3/3,targetRank) ) {
        phase++;
      }
    }
    else phase++;
  }
  else if (
    phase==3
    and
    peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells()>=ThreePowerD*6
  ) {
    const int spacetreeOfInterest = 2;
    if ( peano4::parallel::SpacetreeSet::getInstance().isLocalSpacetree(spacetreeOfInterest) ) {
      if ( not peano4::parallel::SpacetreeSet::getInstance().split(2,peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells()/3/3/3/3,targetRank) ) {
        phase++;
      }
    }
    else phase++;
  }
  else if (
    phase==4
    and
    peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells()>=ThreePowerD*8
  ) {
    const int spacetreeOfInterest = 2;
    if ( peano4::parallel::SpacetreeSet::getInstance().isLocalSpacetree(spacetreeOfInterest) ) {
      if ( not peano4::parallel::SpacetreeSet::getInstance().split(spacetreeOfInterest,peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells()/3/3/3/3/3,targetRank) ) {
        phase++;
      }
    }
    else phase++;
  }
  else if (
    phase==5
    and
    peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells()>=ThreePowerD*10
  ) {
    const int spacetreeOfInterest = 1;
    if ( peano4::parallel::SpacetreeSet::getInstance().isLocalSpacetree(spacetreeOfInterest) ) {
      if ( not peano4::parallel::SpacetreeSet::getInstance().split(1,10,targetRank) ) {
        phase++;
      }
    }
    else phase++;
  }
}


void runParallel(double h, int numberOfCellsPerRank, int numberOfCellsPerThread) {
  peano4::parallel::SpacetreeSet::getInstance().init(
    #if Dimensions==2
    {0.0, 0.0},
    {1.0, 1.0},
    #else
    {0.0, 0.0, 0.0},
    {1.0, 1.0, 1.0},
    #endif
    0
  );

  examples::regulargridupscaling::MyObserver emptyObserver(examples::regulargridupscaling::MyObserver::RanksObserverTemplate,h);

  // @todo Change
//  const int numberOfThreads = tarch::multicore::Core::getInstance().getNumberOfThreads();
  const int numberOfThreads = 3;

  if (tarch::mpi::Rank::getInstance().isGlobalMaster() ) {
    logInfo( "runParallel(...)", "create initial grid (step #1)" );
    while (
      peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells() <
	  tarch::mpi::Rank::getInstance().getNumberOfRanks() * numberOfCellsPerRank
	) {
      peano4::parallel::Node::getInstance().setNextProgramStep(1);
      tarch::logging::CommandLineLogger::getInstance().closeOutputStreamAndReopenNewOne();
      peano4::parallel::SpacetreeSet::getInstance().traverse( emptyObserver );
    }
    logInfo( "runParallel(...)", "created initial grid with " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().toString() );
    logInfo( "runParallel(...)", "refined vertices = " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfRefinedVertices() );
    logInfo( "runParallel(...)", "unrefined vertices = " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfUnrefinedVertices() );
    logInfo( "runParallel(...)", "refining vertices = " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfRefiningVertices() );
    logInfo( "runParallel(...)", "erasing vertices = " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfErasingVertices() );
    logInfo( "runParallel(...)", "local unrefined cells = " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells());
    logInfo( "runParallel(...)", "local refined cell= " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalRefinedCells() );
    logInfo( "runParallel(...)", "remote unrefined cells = " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfRemoteUnrefinedCells() );
    logInfo( "runParallel(...)", "remote refined cells= " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfRemoteRefinedCells() );

    logInfo( "runParallel(...)", "trigger split of initial grid among ranks" );
    for (int rank=1; rank<tarch::mpi::Rank::getInstance().getNumberOfRanks(); rank++) {
      if ( not peano4::parallel::SpacetreeSet::getInstance().split(0,numberOfCellsPerRank,rank)) {
        logWarning( "runParallel(...)", "failed to assign rank " << rank << " " << numberOfCellsPerRank << " cell(s)" );
      }
    }

    logInfo( "runParallel(...)", "commit split and give ranks time to 'recover' (step #2)" );
    for (int i=0; i<3; i++) {
      peano4::parallel::Node::getInstance().setNextProgramStep(2);
      tarch::logging::CommandLineLogger::getInstance().closeOutputStreamAndReopenNewOne();
      peano4::parallel::SpacetreeSet::getInstance().traverse( emptyObserver );
    }

    logInfo( "runParallel(...)", "trigger split of master rank into threads" );
    for (int thread=1; thread<numberOfThreads; thread++) {
      if ( not peano4::parallel::SpacetreeSet::getInstance().split(0,numberOfCellsPerThread,0)) {
        logWarning( "runParallel(...)", "failed to assign thread " << thread << " " << numberOfCellsPerThread << " cell(s)" );
      }
    }

    logInfo( "runParallel(...)", "run one step committing split and telling other ranks to split as well (step #3)" );
    peano4::parallel::Node::getInstance().setNextProgramStep(3);
    tarch::logging::CommandLineLogger::getInstance().closeOutputStreamAndReopenNewOne();
    peano4::parallel::SpacetreeSet::getInstance().traverse( emptyObserver );

    logInfo( "runParallel(...)", "commit split and give ranks time to 'recover' (step #4)" );
    for (int i=0; i<3; i++) {
      peano4::parallel::Node::getInstance().setNextProgramStep(4);
      tarch::logging::CommandLineLogger::getInstance().closeOutputStreamAndReopenNewOne();
      peano4::parallel::SpacetreeSet::getInstance().traverse( emptyObserver );
    }

    logInfo( "runParallel(...)", "start parallel traversals (step #5)" );
    for (int i=0; i<20; i++) {
      peano4::parallel::Node::getInstance().setNextProgramStep(5);
      tarch::logging::CommandLineLogger::getInstance().closeOutputStreamAndReopenNewOne();
      peano4::parallel::SpacetreeSet::getInstance().traverse( emptyObserver );
    }
    logInfo( "runParallel(...)", "terminated successfully" );
  }
  else { // not the global master
    while (peano4::parallel::Node::getInstance().continueToRun()) {
      if (
        peano4::parallel::Node::getInstance().getCurrentProgramStep()==2
		or
        peano4::parallel::Node::getInstance().getCurrentProgramStep()==4
		or
        peano4::parallel::Node::getInstance().getCurrentProgramStep()==5
      ) {
        tarch::logging::CommandLineLogger::getInstance().closeOutputStreamAndReopenNewOne();
        peano4::parallel::SpacetreeSet::getInstance().traverse(emptyObserver);
      }
      else if (peano4::parallel::Node::getInstance().getCurrentProgramStep()==3) {
        assertionEquals( peano4::parallel::SpacetreeSet::getInstance().getLocalSpacetrees().size(), 1);
        const int localTree = *(peano4::parallel::SpacetreeSet::getInstance().getLocalSpacetrees().begin());
        logInfo( "runParallel(...)", "trigger split of rank " << tarch::mpi::Rank::getInstance().getRank() << " (tree " << localTree << ") into threads" );
        for (int thread=1; thread<numberOfThreads; thread++) {
          if ( not peano4::parallel::SpacetreeSet::getInstance().split(localTree,numberOfCellsPerThread,tarch::mpi::Rank::getInstance().getRank())) {
            logWarning( "runParallel(...)", "failed to assign thread " << thread << " " << numberOfCellsPerThread << " cell(s)" );
          }
        }
        tarch::logging::CommandLineLogger::getInstance().closeOutputStreamAndReopenNewOne();
        peano4::parallel::SpacetreeSet::getInstance().traverse(emptyObserver);
      }
    }
  }
}


int main(int argc, char** argv) {
  const int ExitCodeSuccess         = 0;
  const int ExitCodeUnitTestsFailed = 1;

  peano4::initParallelEnvironment(&argc,&argv);
  peano4::initSharedMemoryEnvironment();
  peano4::fillLookupTables();

  tarch::logging::CommandLineLogger::getInstance().addFilterListEntry( tarch::logging::CommandLineLogger::FilterListEntry(
    "debug", tarch::logging::CommandLineLogger::FilterListEntry::AnyRank, "tarch::multicore", true
  ));
  tarch::logging::CommandLineLogger::getInstance().addFilterListEntry( tarch::logging::CommandLineLogger::FilterListEntry(
    "info", tarch::logging::CommandLineLogger::FilterListEntry::AnyRank, "peano4::grid::EmptyTraversalObserver", true
  ));
  tarch::logging::CommandLineLogger::getInstance().addFilterListEntry( tarch::logging::CommandLineLogger::FilterListEntry(
    "debug", tarch::logging::CommandLineLogger::FilterListEntry::AnyRank, "peano4", false
  ));
  tarch::logging::CommandLineLogger::getInstance().setOutputFile( "trace.txt" );

  if (argc!=2) {
	logError( "main(...)", "Usage: ./executable mesh-width");
	return 1;
  }

  double meshWidth = std::atof( argv[1] );
  if (meshWidth<=0) {
    logError( "main(...)", "Usage: ./executable mesh-width");
    logError( "main(...)", "  mesh-width has to be a positive value");
    return 2;
  }
  if (meshWidth>=1.0) {
    logError( "main(...)", "Usage: ./executable mesh-width");
    logError( "main(...)", "  mesh-width has to be smaller than one");
    return 2;
  }

  runTests();

  const int numberOfRanks = tarch::mpi::Rank::getInstance().getNumberOfRanks();
  const int numberOfCores = tarch::multicore::Core::getInstance().getNumberOfThreads();
  logInfo( "main(...)", "run on " << numberOfRanks << " ranks with " << numberOfCores << " thread(s) each" );

  const int numberOfFineGridCells = std::round( std::pow( 1.0 / meshWidth, Dimensions ));
  logInfo( "main(...)", "expect more than " << numberOfFineGridCells << " cell(s) in total" );

  const int numberOfCellsPerRank   = numberOfFineGridCells / numberOfRanks;
  const int numberOfCellsPerThread = numberOfCellsPerRank / numberOfCores;
  logInfo( "main(...)", "deploy around " << numberOfCellsPerRank << " cell(s) to each rank with at least " << numberOfCellsPerThread << " cell(s) per thread" );

  runParallel(meshWidth, numberOfCellsPerRank, numberOfCellsPerThread);

  peano4::shutdownSharedMemoryEnvironment();
  peano4::shutdownParallelEnvironment();

  return 0;
}
