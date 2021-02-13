#include "peanosph-main.h"
#include "Constants.h"

#include "tarch/logging/Log.h"
#include "tarch/logging/LogFilter.h"
#include "tarch/logging/LogFilterFileReader.h"
#include "tarch/logging/CommandLineLogger.h"

#include "tarch/multicore/multicore.h"

#include "peano4/peano.h"
#include "peano4/grid/Spacetree.h"
#include "peano4/parallel/SpacetreeSet.h"


#include "observers/DataRepository.h"
#include "observers/StepRepository.h"


//
// =================
// inserted manually
// =================
//
#include "observers/CreateGrid.h"
#include "observers/Plot.h"
#include "observers/MoveParticles.h"


#include "peano4/UnitTests.h"
#include "tarch/UnitTests.h"


tarch::logging::Log _log("::");


int main(int argc, char** argv) {
  const int ExitCodeSuccess         = 0;
  const int ExitCodeUnitTestsFailed = 1;


  #if Dimensions==2
  auto DomainOffset = {0.0, 0.0};
  auto DomainSize   = {1.0, 1.0};
  #else
  auto DomainOffset = {0.0, 0.0, 0.0};
  auto DomainSize   = {1.0, 1.0, 1.0};
  #endif


  peano4::initParallelEnvironment(&argc,&argv);
  peano4::fillLookupTables();
  peanosph::observers::DataRepository::initDatatypes();
  peano4::initSingletons(
    DomainOffset,
    DomainSize,
    0
  );

  std::string logFilterFile = "peano4.log-filter";
  if ( not tarch::logging::LogFilterFileReader::parsePlainTextFile( logFilterFile ) ) {
    logWarning( "main()", "no exahype.log-filter file found or file has been corrupted. Use default logging configuration" );
  }

  #if PeanoDebug>=2
  tarch::tests::TestCase* peanoCoreTests = peano4::getUnitTests();
  peanoCoreTests->run();
  if (peanoCoreTests->getNumberOfErrors() != 0) {
    logError("main()", "Peano4 core unit tests failed. Quit.");
    exit(ExitCodeUnitTestsFailed);
  }
  delete peanoCoreTests;

  tarch::tests::TestCase* peanoTarchTests = tarch::getUnitTests();
  peanoTarchTests->run();
  if (peanoTarchTests->getNumberOfErrors() != 0) {
    logError("main()", "technical architecture (tarch) unit tests failed. Quit.");
    exit(ExitCodeUnitTestsFailed);
  }
  delete peanoTarchTests;

  #endif

  #if defined(SharedOMP)
  #pragma omp parallel
  {
  #pragma omp master
  {
  #endif
  if (tarch::mpi::Rank::getInstance().isGlobalMaster() ) {
    //
    // =================
    // inserted manually
    // =================
    //
    int gridConstructionSteps = 0;
    while (peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getStationarySweeps()<5) {
      peanosph::observers::CreateGrid observer;
      peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
      gridConstructionSteps++;
      tarch::logging::CommandLineLogger::getInstance().closeOutputStreamAndReopenNewOne();
    }

    logInfo( "main()", "finished grid construction after " << gridConstructionSteps << " steps, start timestepping" )

    peanosph::observers::Plot observer;
    peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
    logInfo( "main()", "dumped initial condition" )
    for (int i=0; i<1; i++) {
      for (int j=0; j<10; j++) {
        peanosph::observers::MoveParticles observer;
        peano4::parallel::SpacetreeSet::getInstance().traverse(observer);
      }
      logInfo( "main()", "plot" )
      peanosph::observers::Plot observer;
      peano4::parallel::SpacetreeSet::getInstance().traverse(observer);

      tarch::logging::CommandLineLogger::getInstance().closeOutputStreamAndReopenNewOne();
    }

    logInfo( "main()", "terminated successfully" )
  }
  else {
    while (peano4::parallel::Node::getInstance().continueToRun()) {
      logDebug( "runParallel(...)", "trigger a new sweep with step " << peano4::parallel::Node::getInstance().getCurrentProgramStep() );
    }
  }
  #if defined(SharedOMP)
  }
  }
  #endif

  peano4::shutdownSingletons();
  peanosph::observers::DataRepository::shutdownDatatypes();
  peano4::shutdownParallelEnvironment();

  return ExitCodeSuccess;
}
