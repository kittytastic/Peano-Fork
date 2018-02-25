#ifdef SharedCPP

#include "tarch/multicore/cpp/JobQueue.h"
#include "tarch/multicore/Jobs.h"


tarch::logging::Log tarch::multicore::internal::JobQueue::_log( "tarch::multicore::internal::JobQueue" );


tarch::multicore::internal::JobQueue::JobQueue() {
  _numberOfPendingJobs = 0;
}


tarch::multicore::internal::JobQueue::~JobQueue() {

}


tarch::multicore::internal::JobQueue&  tarch::multicore::internal::JobQueue::getBackgroundQueue() {
  static tarch::multicore::internal::JobQueue queue;
  return queue;
}


bool tarch::multicore::internal::JobQueue::processJobs( int maxNumberOfJobs ) {
  #ifdef UseNaiveImplementation
  _mutex.lock();
  if ( !_jobs.empty() && maxNumberOfJobs>0 ) {
    maxNumberOfJobs--;
    result = true;
    jobs::Job* job = _jobs.front();
    _jobs.pop_front();
    bool reenqueue = job->run();
    if (reenqueue) {
      _jobs.push_back( job );
    }
    else {
      delete job;
      _numberOfPendingJobs--;
    }
  }
  _mutex.unlock();
  return result;
  #else
  _mutex.lock();

  maxNumberOfJobs = std::min( maxNumberOfJobs, static_cast<int>( _jobs.size() ));

  if (maxNumberOfJobs==0) {
    _mutex.unlock();
    return false;
  }
  else {
    std::list< jobs::Job* >::iterator lastElementToBeProcessed  = _jobs.begin();
    for (int i=0; i<maxNumberOfJobs; i++) {
      lastElementToBeProcessed++;
    }
    std::list< jobs::Job* > localList;
    localList.splice( localList.begin(), _jobs, _jobs.begin(), lastElementToBeProcessed );

    //#ifdef Asserts
    //logInfo( "processJobs(int)", "spliced " << maxNumberOfJobs << " job(s) from job queue and will process those now" );
    //#endif

    _numberOfPendingJobs-=maxNumberOfJobs;
    _mutex.unlock();

    for (auto& p: localList) {
      bool reenqueue = p->run();
      if (reenqueue) {
        addJob( p );
      }
      else {
        delete p;
      }
    }

    return true;
  }
  #endif
}


void tarch::multicore::internal::JobQueue::addJob( jobs::Job* job ) {
  _numberOfPendingJobs++;
  _mutex.lock();
  _jobs.push_back(job);
  _mutex.unlock();
}


void tarch::multicore::internal::JobQueue::addJobWithHighPriority( jobs::Job* job ) {
  _numberOfPendingJobs++;
  _mutex.lock();
  _jobs.push_front(job);
  _mutex.unlock();
}


int tarch::multicore::internal::JobQueue::getNumberOfPendingJobs() const {
  return _numberOfPendingJobs;
}


#endif
