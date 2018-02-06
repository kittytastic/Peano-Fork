#if defined(SharedTBB)
#include "tarch/multicore/MulticoreDefinitions.h"
#include "tarch/multicore/tbb/Core.h"
#include "tarch/Assertions.h"


tarch::logging::Log  tarch::multicore::Core::_log( "tarch::multicore::Core" );


tarch::multicore::Core::Core():
  _numberOfThreads(::tbb::task_scheduler_init::default_num_threads()),
  _task_scheduler_init(_numberOfThreads),
  _pinningObserver(1) {
}


tarch::multicore::Core::~Core() {
}


void tarch::multicore::Core::pinThreads(bool value) {
  _pinningObserver.observe(value);
}


tarch::multicore::Core& tarch::multicore::Core::getInstance() {
  static tarch::multicore::Core singleton;
  return singleton;
}


void tarch::multicore::Core::shutDown() {
  _task_scheduler_init.terminate();
  _numberOfThreads = -1;
}


void tarch::multicore::Core::configure( int numberOfThreads ) {
  logInfo( "configure(int)", "manually set number of threads to " << numberOfThreads );
  if (_task_scheduler_init.is_active()) {
    _task_scheduler_init.terminate();
  }

  if (numberOfThreads==UseDefaultNumberOfThreads) {
    _numberOfThreads = ::tbb::task_scheduler_init::default_num_threads();
  }
  else {
    _numberOfThreads = numberOfThreads;
  }

  _task_scheduler_init.initialize( _numberOfThreads );
}


int tarch::multicore::Core::getNumberOfThreads() const {
  assertion( isInitialised() );
  return _numberOfThreads;
}


bool tarch::multicore::Core::isInitialised() const {
  return _task_scheduler_init.is_active();
}

#endif
