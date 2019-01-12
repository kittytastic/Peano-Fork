#include "tarch/Assertions.h"


#include <thread>
#include <queue>
#include "Tasks.h"
#include "MulticoreDefinitions.h"


tarch::multicore::TaskWithCopyOfFunctor::TaskWithCopyOfFunctor( const std::function<bool()>& taskFunctor ):
  _taskFunctor(taskFunctor)  {
}


bool tarch::multicore::TaskWithCopyOfFunctor::run() {
  return _taskFunctor();
}


void tarch::multicore::TaskWithCopyOfFunctor::prefetch() {
}


tarch::multicore::TaskWithoutCopyOfFunctor::TaskWithoutCopyOfFunctor( std::function<bool()>& taskFunctor ):
  _taskFunctor(taskFunctor)  {
}


bool tarch::multicore::TaskWithoutCopyOfFunctor::run() {
  return _taskFunctor();
}


void tarch::multicore::TaskWithoutCopyOfFunctor::prefetch() {
}



#ifndef SharedMemoryParallelisation

#include <thread>

namespace {
  std::queue<tarch::multicore::Task* > backgroundJobs;
}


bool tarch::multicore::processPendingTasks() {
  // Note: Only invoked if no shared memory parallelisation activated. If
  // TBB/C++/OpenMP are enabled, the routine of the respective subfolder is
  // invoked
  if (backgroundJobs.empty()) {
    return false;
  }
  else {
    while ( !backgroundJobs.empty() ) {
      Task* p = backgroundJobs.front();
      backgroundJobs.pop();
      while (p->run()) {};
      delete p;
    }
    return true;
  }
}


void tarch::multicore::spawnTask(Task*  job) {
  backgroundJobs.push(job);
}


void tarch::multicore::spawnHighBandwidthTask(Task*  job) {
  backgroundJobs.push(job);
}


void tarch::multicore::spawnHighPriorityTask(Task*  job) {
  while( job->run() ) {};
  delete job;
}


void tarch::multicore::spawnAndWait(
  const std::vector< Task* >&  tasks
) {
  for (auto& p: tasks) {
    while (p->run()) {}
    delete p;
  }
}


void tarch::multicore::yield() {
  std::this_thread::yield();
}

#endif
