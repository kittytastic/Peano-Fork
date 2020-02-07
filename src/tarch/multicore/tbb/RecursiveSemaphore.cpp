#include "tarch/multicore/multicore.h"


#ifdef SharedTBB
#include "RecursiveSemaphore.h"


tarch::multicore::RecursiveSemaphore::RecursiveSemaphore():
  _recursiveMutex() {
}


tarch::multicore::RecursiveSemaphore::~RecursiveSemaphore() {
}


bool tarch::multicore::RecursiveSemaphore::tryEnterCriticalSection() {
  return _recursiveMutex.try_lock();
}


void tarch::multicore::RecursiveSemaphore::enterCriticalSection() {
  _recursiveMutex.lock();
}


void tarch::multicore::RecursiveSemaphore::leaveCriticalSection() {
  _recursiveMutex.unlock();
}

#endif
