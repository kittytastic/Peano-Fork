#include "tarch/Assertions.h"
#include "BooleanSemaphore.h"
#include "Lock.h"


#include <thread>
#include <queue>
#include <set>
#include "Tasks.h"
#include "multicore.h"

namespace {
  tarch::multicore::BooleanSemaphore  activeTasksSemaphore;
  std::set<int>                       activeTaskNumbers;
}


int tarch::multicore::getNumberOfReservedTaskNumbers() {
  return activeTaskNumbers.size();
}


void tarch::multicore::releaseTaskNumber(int number) {
  tarch::multicore::Lock activeTasksLock( activeTasksSemaphore );
  assertionEquals( activeTaskNumbers.count(number),1 );
  activeTaskNumbers.erase( number );
}


int tarch::multicore::reserveTaskNumber() {
  tarch::multicore::Lock lock( activeTasksSemaphore );
  int result = activeTaskNumbers.size();
  while (activeTaskNumbers.count( result )>0) {
    result+=23;
  }
  activeTaskNumbers.insert( result );
  return result;
}


bool operator<( const tarch::multicore::Task& lhs, const tarch::multicore::Task& rhs ) {
  return lhs.getPriority() < rhs.getPriority();
}


bool tarch::multicore::TaskComparison::operator() (const Task& lhs, const Task& rhs) const {
  return lhs < rhs;
}


bool tarch::multicore::TaskComparison::operator() (Task* lhs, Task* rhs) const {
  return *lhs < *rhs;
}


tarch::multicore::Task::Task( int id, int taskType, int priority ):
  _id(id),
  _taskType( taskType ),
  _priority( priority ) {
}


int tarch::multicore::Task::getPriority() const {
  return _priority;
}


void tarch::multicore::Task::setPriority( int priority ) {
  _priority = priority;
}


int tarch::multicore::Task::getTaskType() const {
  return _taskType;
}


bool tarch::multicore::Task::fuse( const std::list<Task*>& otherTasks ) {
  for (auto pp: otherTasks) {
    tarch::multicore::Task* currentTask = pp;
    while (currentTask->run()) {}
    delete currentTask;
  }
  return true;
}


int tarch::multicore::Task::getTaskId() const {
  return _id;
}


tarch::multicore::TaskWithCopyOfFunctor::TaskWithCopyOfFunctor( int id, int taskType, int priority, const std::function<bool()>& taskFunctor ):
  Task(id, taskType, priority),
  _taskFunctor(taskFunctor)  {
}


bool tarch::multicore::TaskWithCopyOfFunctor::run() {
  return _taskFunctor();
}


tarch::multicore::TaskWithoutCopyOfFunctor::TaskWithoutCopyOfFunctor( int id, int taskType, int priority, std::function<bool()>& taskFunctor ):
  Task(id, taskType, priority),
  _taskFunctor(taskFunctor)  {
}


bool tarch::multicore::TaskWithoutCopyOfFunctor::run() {
  return _taskFunctor();
}


#ifndef SharedMemoryParallelisation

#include <thread>

namespace {
  std::queue<tarch::multicore::Task* > nonblockingTasks;
}


bool tarch::multicore::processTask(int number) {
  int currentTaskNumber = -1;
  while ( currentTaskNumber!=number and !nonblockingTasks.empty() ) {
    Task* p = nonblockingTasks.front();
    nonblockingTasks.pop();
    currentTaskNumber = p->getTaskId();
    while (p->run()) {};
    delete p;
  }
  return currentTaskNumber==number;
}


bool tarch::multicore::processPendingTasks(int maxTasks) {
  // Note: Only invoked if no shared memory parallelisation activated. If
  // TBB/C++/OpenMP are enabled, the routine of the respective subfolder is
  // invoked
  if (nonblockingTasks.empty()) {
    return false;
  }
  else {
    while ( maxTasks>0 and !nonblockingTasks.empty() ) {
      Task* p = nonblockingTasks.front();
      nonblockingTasks.pop();
      while (p->run()) {};
      delete p;
      maxTasks--;
    }
    return true;
  }
}


void tarch::multicore::spawnTask(Task*  job) {
  nonblockingTasks.push(job);
}


void tarch::multicore::spawnAndWait(
  const std::vector< Task* >&  tasks
) {
  for (auto& p: tasks) {
    while (p->run()) {}
    delete p;
  }
}


/**
 * This has to be the standard C++ implementation. Even if multithreading is
 * disabled, the code might logically run with multiple threads, and then we
 * have to switch the thread context from time to time.
 */
void tarch::multicore::yield() {
  std::this_thread::yield();
}


int tarch::multicore::getNumberOfPendingTasks() {
  return nonblockingTasks.size();
}

#endif
