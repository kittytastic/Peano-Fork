#include "tarch/multicore/Core.h"
#include "tarch/multicore/MulticoreDefinitions.h"
#include "tarch/compiler/CompilerSpecificSettings.h"


#ifdef CompilerHasSysinfo
#include <sched.h>
#endif


#if defined(SharedCPP)
#include <sstream>


tarch::logging::Log tarch::multicore::Core::_log( "tarch::multicore::Core" );


tarch::multicore::Core::Core():
  _numberOfThreads(std::thread::hardware_concurrency()) {
}


tarch::multicore::Core::~Core() {
}


tarch::multicore::Core& tarch::multicore::Core::getInstance() {
  static Core instance;
  return instance;
}

void tarch::multicore::Core::configure( int numberOfThreads, int maxNumberOfConcurrentBackgroundTasks, int maxNumberOfConcurrentBandwidthBoundTasks ) {
  if (numberOfThreads != UseDefaultNumberOfThreads) {
    _numberOfThreads = numberOfThreads;
    if (_numberOfThreads>getNumberOfUnmaskedThreads()) {
      logWarning( "configure(int,int,int)", "number of configured threads (" << numberOfThreads << ") is bigger than available unmasked threads (" << getNumberOfUnmaskedThreads() << ")" );
    }
  }
  else {
    _numberOfThreads = std::thread::hardware_concurrency();
  }
}


void tarch::multicore::Core::shutDown() {
}


bool tarch::multicore::Core::isInitialised() const {
  return true;
}


int tarch::multicore::Core::getNumberOfThreads() const {
  return _numberOfThreads;
}


std::string tarch::multicore::Core::getThreadId() const {
  std::ostringstream msg;
  msg << std::this_thread::get_id();
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




int tarch::multicore::Core::getNumberOfUnmaskedThreads() {
  #ifdef CompilerHasSysinfo
  cpu_set_t mask;
  sched_getaffinity(0, sizeof(cpu_set_t), &mask);

  int result = 0;
  for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
    if ( CPU_ISSET(i, &mask)!=0 ) {
      result++;
    }
  }

  return result;
/*
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(i, &cpuset);

  int sched_setaffinity(pid_t pid,size_t cpusetsize,cpu_set_t *mask);
*/
  #else
  return std::thread::hardware_concurrency();
  #endif
}


#endif
