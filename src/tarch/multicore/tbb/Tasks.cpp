#include "tarch/Assertions.h"


#include <thread>
#include <queue>
#include "tarch/multicore/multicore.h"


#ifdef SharedTBB
#include "../Tasks.h"
#include "TBB.h"

#include "tarch/logging/Log.h"
#include "tarch/Assertions.h"


#include <vector>
#include <limits>
#include <cmath>


#include <tbb/task.h>
#include <tbb/task_group.h>
#include <tbb/concurrent_priority_queue.h>
#include <tbb/concurrent_hash_map.h>


namespace {
  //
  // This is a bug in Intel's TBB as documented on
  //
  // https://software.intel.com/en-us/forums/intel-threading-building-blocks/topic/700057
  //
  // These task groups have to be static inside a cpp file.
  //
  static tbb::task_group_context  backgroundTaskContext(tbb::task_group_context::isolated);

  typedef tbb::concurrent_priority_queue< tarch::multicore::Task* >   TaskQueue;

  TaskQueue nonblockingTasks;

  tbb::atomic<int> numberOfConsumerTasks;

  const int MinNumberOfTasksPerConsumer = 16;

  /**
   * This is a task which consumes background jobs, as it invokes
   * processBackgroundJobs(). Typically, I make such a job consume up to
   * half of the available background jobs, before it then stops the
   * processing. When it stops and finds out that there would still
   * have been more jobs to process, then it enqueues another consumer task
   * to continue to work on the jobs at a later point.
   */
  class ConsumerTask: public tbb::task {
    private:
      const int _maxJobs;

      ConsumerTask(int maxJobs):
        _maxJobs(maxJobs) {
      }

    public:
      static tbb::task_group_context  backgroundTaskContext;

      /**
       * Schedule a new background job consumer task. We have to tell
      * each consumer how many jobs it may process at most. By default,
       * I have a look into the background queue and divide this number
         * by the number of existing threads. If it is smaller than the
         * magic constant TBBMinimalNumberOfJobsPerBackgroundConsumerRun,
         * then I use this one instead. So this approach balanced between
         * a reasonable distribution of jobs among all available threads
         * and a reasonable overhead (materialising in queue locking, e.g.).
         *
         * @see TBBMinimalNumberOfJobsPerBackgroundConsumerRun
         */
      static void enqueue(int maxTasks = nonblockingTasks.size()) {
        numberOfConsumerTasks.fetch_and_add(1);
        ConsumerTask* tbbTask = new (tbb::task::allocate_root(::backgroundTaskContext)) ConsumerTask(maxTasks);
        tbb::task::enqueue(*tbbTask);
        //::backgroundTaskContext.set_priority(tbb::priority_low);
      }

      ConsumerTask(const ConsumerTask& copy):
        _maxJobs(copy._maxJobs) {
      }

      /**
       * Process _maxJobs from the background job queue and then
       * @see enqueue()
       */
      tbb::task* execute() {
    	int  numberOfPendingTasksPriorToStart = nonblockingTasks.size();
    	bool handledTasks                     = tarch::multicore::processPendingTasks(_maxJobs);

    	if (handledTasks and nonblockingTasks.size()>numberOfPendingTasksPriorToStart and nonblockingTasks.size()>MinNumberOfTasksPerConsumer) {
          enqueue(_maxJobs*2);
          enqueue(_maxJobs*2);
    	}
    	else if (handledTasks and _maxJobs>1) {
          enqueue(_maxJobs/2);
    	}
        numberOfConsumerTasks.fetch_and_add(-1);

        return nullptr;
      }
  };

  class TBBWrapperAroundTask: public tbb::task {
    private:
      tarch::multicore::Task*  _task;
    public:
      TBBWrapperAroundTask( tarch::multicore::Task* task ):
        _task(task) {
      }

      tbb::task* execute() {
        while ( _task->run() ) {}
        delete _task;
        return nullptr;
      }
  };
}


/**
 * If we are tasks and if there are still jobs left once
 * we've done our share, then we spawn a new background task consumer job.
 * This is done for cases where the master processes background jobs and there
 * are plenty of them left. In such a case, the master might be totally blocked
 * by the background jobs (if processJobs() is called in a while loop) and
 * should actually use further tasks instead.
 *
 * @return Have done one
 */
bool tarch::multicore::processPendingTasks( int maxTasks ) {
  assertion(maxTasks>=1);
  bool result = false;
  while ( maxTasks>0 ) {
	// try to get a task and store in p
    Task* myTask = nullptr;
    bool gotTask = nonblockingTasks.try_pop(myTask);
    #if defined(TBBPrefetchesJobData)
    Task* myPrefetchTask = nullptr;
    bool gotPrefetchTask = nonblockingTasks.try_pop(myPrefetchTask);
    if (gotPrefetchTask) {
      myPrefetchTask->prefetch();
      nonblockingTasks.push(myPrefetchTask);
    }
    #endif
    if (gotTask) {
      bool requeue = myTask->run();
      if (requeue) {
        spawnTask( myTask );
      }
      else {
        delete myTask;
      }
      maxTasks--;
      result = true;
    }
    else {
      maxTasks=0;
    }
  }
  return result;
}


/**
 * Used to be in the tbb namespace but now moved into std as C++ picks up on
 * multithreading, too
 */
void tarch::multicore::yield() {
  std::this_thread::yield();
}


void tarch::multicore::spawnTask(Task*  task) {
  nonblockingTasks.push( task );
  if ( numberOfConsumerTasks==0 ) {
    ConsumerTask::enqueue();
  }
}


void tarch::multicore::spawnAndWait(
  const std::vector< tarch::multicore::Task* >&  tasks
) {
  tbb::task_group g;
  for (auto& p: tasks) {
    g.run([=]{
      tarch::multicore::Task* task = p;
      task->run();
      delete task;
    });
  }
  g.wait();
}

#endif
