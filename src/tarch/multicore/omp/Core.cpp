#include "tarch/multicore/Core.h"
#include "tarch/multicore/multicore.h"
#include "tarch/compiler/CompilerSpecificSettings.h"


#ifdef CompilerHasSysinfo
#include <sched.h>
#endif


#if defined(SharedOMP)

#include <omp.h>

#include "config.h"

#if defined(UseNVIDIA)
#include <cuda_runtime_api.h>
#include <cuda.h>
#endif


tarch::logging::Log  tarch::multicore::Core::_log( "tarch::multicore::Core" );





tarch::multicore::Core::Core() {
}


tarch::multicore::Core::~Core() {
}


tarch::multicore::Core& tarch::multicore::Core::getInstance() {
  static Core instance;
  return instance;
}


void tarch::multicore::Core::configure( int numberOfThreads, int maxNumberOfConcurrentBackgroundTasks, int maxNumberOfConcurrentBandwidthBoundTasks ) {
  if (numberOfThreads!=UseDefaultNumberOfThreads) {
    if ( omp_get_max_threads()!=numberOfThreads ) {
      logWarning( "configure(int,int,int)", "number of threads configured (" << numberOfThreads << ") does not match system thread level of " << omp_get_max_threads() << ". OpenMP may ignore manual thread count reset");
    }

    omp_set_num_threads(numberOfThreads);
    logInfo( "configure(...)", "manually reset number of threads used to " << numberOfThreads );
  }
  else {
    omp_set_num_threads(omp_get_max_threads());
  }
}


void tarch::multicore::Core::shutdown() {
}


bool tarch::multicore::Core::isInitialised() const {
  return true;
}


int tarch::multicore::Core::getNumberOfThreads() const {
  return omp_get_max_threads();
}


int tarch::multicore::Core::getNumberOfGPUs() const {
  // @todo Holger
  return 1;
}


std::string tarch::multicore::Core::getThreadId() const {
  std::ostringstream msg;
  msg << omp_get_thread_num();
  return msg.str();
}


int tarch::multicore::Core::getCoreNumber() const {
  #ifdef CompilerHasSysinfo
  return sched_getcpu();
  #else
  //  https://stackoverflow.com/questions/33745364/sched-getcpu-equivalent-for-os-x
  return 1;
  #endif
}

#endif
