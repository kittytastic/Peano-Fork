#include "Statistics.h"
#include "tarch/multicore/Lock.h"
#include "tarch/mpi/Rank.h"

#include <fstream>


tarch::logging::Statistics          tarch::logging::Statistics::_singleton;
tarch::logging::Log                 tarch::logging::Statistics::_log( "tarch::logging::Statistics" );
tarch::multicore::BooleanSemaphore  tarch::logging::Statistics::_semaphore;


tarch::logging::Statistics& tarch::logging::Statistics::getInstance() {
  static tarch::logging::Statistics singleton;
  return singleton;
}



tarch::logging::Statistics::Statistics():
  _maxCountInBetweenTwoMeasurements(100),
  _maxTimeInBetweenTwoMeasurements(2.0),
  _globalWatch( "tarch::logging::Statistics", "Statistics", false) {
}



tarch::logging::Statistics::DataSet::DataSet():
  _watch("tarch::logging::Statistics", "Statistics", false),
  _counter(0) {
}


void tarch::logging::Statistics::clear() {
  _map.clear();
}


bool tarch::logging::Statistics::acceptNewData(const std::string& identifier, bool disableSampling) {
  if ( _map.count( identifier )==0 ) {
    _map.insert( std::pair<std::string,DataSet>( identifier, DataSet() ));
  }

  _map[identifier]._counter++;
  _map[identifier]._watch.stop();

  bool counterGuard = _map[identifier]._counter>_maxCountInBetweenTwoMeasurements;
  bool timerGuard   = _map[identifier]._watch.getCalendarTime() > _maxTimeInBetweenTwoMeasurements;

  bool guard = disableSampling or counterGuard or timerGuard;

  if (guard) {
    _map[identifier]._counter = 0;
    _map[identifier]._watch.start();
    return true;
  }
  else return false;
}



#ifdef TrackStatistics
void tarch::logging::Statistics::log( const std::string& identifier, double value, bool disableSampling ) {
  tarch::multicore::Lock lock(_semaphore);
  if ( acceptNewData(identifier, disableSampling) ) {
    _globalWatch.stop();
    double t = _globalWatch.getCalendarTime();
    logDebug( "log(string,double)", identifier << "=" << value );
    _map[identifier]._data.push_back( std::pair<double,double>(t,value) );
  }
}


void tarch::logging::Statistics::inc( const std::string& identifier, double value, bool disableSampling ) {
  tarch::multicore::Lock lock(_semaphore);

  if ( _map.count( identifier )==0 ) {
     _globalWatch.stop();
     double t = _globalWatch.getCalendarTime();

    _map.insert( std::pair<std::string,DataSet>( identifier, DataSet() ));
    _map[identifier]._data.push_back( std::pair<double,double>(t,value) );
    _map[identifier]._data.push_back( std::pair<double,double>(t,value) ); // second one will be updated
  }
  else {
    double newValue = _map[identifier]._data.back().second + value;
    _map[identifier]._data.back().second = newValue;

    if ( acceptNewData(identifier, disableSampling) ) {
      _globalWatch.stop();
      double t = _globalWatch.getCalendarTime();
      _map[identifier]._data.back().first  = t;

      _map[identifier]._data.push_back( std::pair<double,double>(t,newValue) );
    }
  }
}
#endif


void tarch::logging::Statistics::writeToCSV( std::string filename ) {
  #ifdef TrackStatistics
  logDebug( "writeToCSV(string)", "start to dump statistics into file " << filename );

  if (tarch::mpi::Rank::getInstance().getNumberOfRanks()>0 ) {
    filename += "-rank-" + std::to_string( tarch::mpi::Rank::getInstance().getRank() );
  }

  filename += ".csv";

  std::ofstream file( filename );
  file << "t";
  for (auto& p: _map) {
    file << ", " << p.first;
  }
  file << std::endl;

  double t = 0.0;
  while (t<std::numeric_limits<double>::max()) {
    t = std::numeric_limits<double>::max();
    for (auto& p: _map) {
      if (not p.second._data.empty()) {
        t = std::min(t,p.second._data.front().first);
      }
    } 
    if (t<std::numeric_limits<double>::max()) {
      file << t; 
      for (auto& p: _map) {
        if (
          not p.second._data.empty()
          and
          p.second._data.front().first < t + _maxTimeInBetweenTwoMeasurements
        ) {
          file << ", " << p.second._data[0].second;
          p.second._data.erase(p.second._data.begin());
        }
        else {
          file << ", ";
        }
      }
    }
    file << std::endl;
  }

  file.close();
  logInfo( "writeToCSV(string)", "wrote statistics to file " << filename );
  #else
  logWarning( "writeToCSV(string)", "no statistics available. Recompile with -DTrackStatistics for runtime sampling" );
  #endif
}


