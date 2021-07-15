#include "tarch/Assertions.h"


#include "tarch/mpi/Rank.h"


#include <sstream>
#include <iostream>
#include "LogFilter.h"


#if defined(UseLikwid)
#include <likwid-marker.h>
#endif


const int tarch::logging::LogFilter::FilterListEntry::AnyRank = -1;

const std::string tarch::logging::LogFilter::FilterListEntry::TargetAll   = "all";
const std::string tarch::logging::LogFilter::FilterListEntry::TargetInfo  = "info";
const std::string tarch::logging::LogFilter::FilterListEntry::TargetDebug = "debug";
const std::string tarch::logging::LogFilter::FilterListEntry::TargetTrace = "trace";

const std::string tarch::logging::LogFilter::FilterListEntry::AlwaysOn = "always-on";

const bool tarch::logging::LogFilter::FilterListEntry::BlackListEntry = true;
const bool tarch::logging::LogFilter::FilterListEntry::WhiteListEntry = false;


tarch::logging::LogFilter::FilterListEntry::FilterListEntry( const std::string& targetName, bool isBlackListEntry ):
  _targetName(targetName),
  _rank(AnyRank),
  _namespaceName(""),
  _isBlackEntry(isBlackListEntry),
  _programPhase(AlwaysOn) {
  assertion1( targetName==TargetInfo or targetName==TargetDebug or targetName==TargetAll or targetName==TargetTrace, targetName );
}


tarch::logging::LogFilter::FilterListEntry::FilterListEntry( const std::string& targetName, int rank, const std::string& className, bool isBlackListEntry, const std::string& programPhase ):
  _targetName(targetName),
  _rank(rank),
  _namespaceName(className),
  _isBlackEntry(isBlackListEntry),
  _programPhase(programPhase) {
  assertion1( targetName==TargetInfo or targetName==TargetDebug or targetName==TargetAll or targetName==TargetTrace, targetName );
}


std::string tarch::logging::LogFilter::FilterListEntry::toString() const {
  std::ostringstream msg;
  msg << "(";
  msg << "target:" << _targetName << ",";
  msg << _namespaceName << ",";
  #ifdef Parallel
  msg << "rank:" << _rank;
  msg << ",";
  #endif
  if (_isBlackEntry) {
    msg << "blacklist-entry";
  }
  else {
    msg << "whitelist-entry";
  }
  msg << ",phase:" << _programPhase;
  msg << ")";
  return msg.str();
}


bool tarch::logging::LogFilter::FilterListEntry::operator<(const FilterListEntry& b) const {
  return _rank < b._rank
      or _namespaceName < b._namespaceName
      or _targetName < b._targetName
      or _programPhase < b._programPhase;
}


bool tarch::logging::LogFilter::FilterListEntry::operator==(const FilterListEntry& b) const {
  return  _rank == b._rank
      and _namespaceName == b._namespaceName
      and _targetName == b._targetName
      and _programPhase == b._programPhase;
}


bool tarch::logging::LogFilter::FilterListEntry::operator!=(const FilterListEntry& b) const {
  return not operator==(b);
}


tarch::logging::LogFilter::LogFilter():
  _activeProgramPhase("undef") {
  addFilterListEntry( FilterListEntry( FilterListEntry::TargetAll, false )  );
  #if defined(UseLikwid)
  likwid_markerInit();

  likwid_markerStartRegion( _activeProgramPhase.c_str() );
  #endif
}


tarch::logging::LogFilter::~LogFilter() {
  #if defined(UseLikwid)
  likwid_markerStopRegion( _activeProgramPhase.c_str() );
  likwid_markerClose();
  #endif
}


void tarch::logging::LogFilter::printFilterListToCout() const {
  if (_filterlist.empty()) {
    std::cout << "filter list is empty" << std::endl;
  }
  else {
    std::cout << "filter list is not empty and contains " << _filterlist.size() << " entries" << std::endl;
    for (FilterList::const_iterator p = _filterlist.begin(); p!=_filterlist.end(); p++ ) {
      std::cout <<  p->toString() << std::endl;
    }
  }
}


tarch::logging::LogFilter& tarch::logging::LogFilter::getInstance() {
  static LogFilter* _singleton = new LogFilter();
  return *_singleton;
}


void tarch::logging::LogFilter::switchProgramPhase(const std::string& activeProgramPhase) {
  #if PeanoDebug>=4
  std::cout << "switch program phase to " << activeProgramPhase << " and, hence, activate potentially different filter set" << std::endl;
  #endif
  _activeProgramPhase = activeProgramPhase;
  #if defined(UseLikwid)
  likwid_markerStopRegion( _activeProgramPhase.c_str() );
  likwid_markerStartRegion( _activeProgramPhase.c_str() );
  #endif
}


bool tarch::logging::LogFilter::writeDebug(const std::string& className) {
  #if PeanoDebug>=4
  return !filterOut(FilterListEntry::TargetDebug,className);
  #else
  return false;
  #endif
}


bool tarch::logging::LogFilter::writeInfo(const std::string& className) {
  return !filterOut(FilterListEntry::TargetInfo,className);
}


bool tarch::logging::LogFilter::writeTrace(const std::string& className) {
  #if PeanoDebug>=1
  const bool result = !filterOut(FilterListEntry::TargetTrace,className);
  return result;
  #else
  return false;
  #endif
}


void tarch::logging::LogFilter::addFilterListEntries( const FilterList&    entries) {
  for (FilterList::const_iterator p = entries.begin(); p!=entries.end(); p++ ) {
    addFilterListEntry(*p);
  }
}


void tarch::logging::LogFilter::clearFilterList() {
  _filterlist.clear();
}


bool tarch::logging::LogFilter::filterOut(
  const std::string& targetName,
  const std::string& className
) {
  bool result    = false;
  bool foundRule = false;
  int lengthActive = 0;
  for (FilterList::const_iterator p = _filterlist.begin(); p!=_filterlist.end(); p++ ) {
    int length = static_cast<int>(p->_namespaceName.size());
    if ( length >= lengthActive ) {
      if (
        ( targetName == p->_targetName or p->_targetName==FilterListEntry::TargetAll )
        and
        ( _activeProgramPhase.find( p->_programPhase,0 )==0 or p->_programPhase==FilterListEntry::AlwaysOn )
        and
        ( className.find(p->_namespaceName,0)==0 )
        #ifdef Parallel
        and
        (p->_rank == FilterListEntry::AnyRank || p->_rank == tarch::mpi::Rank::getInstance().getRank())
        #endif
      ) {
        lengthActive = length;
        result       = p->_isBlackEntry;
        foundRule    = true;
      }
    }
  }

  if (!foundRule) {
    std::cerr << "did not find filter rule for target \"" << targetName << "\" and class \"" << className << "\" on rank " << tarch::mpi::Rank::getInstance().getRank() << std::endl;
  }
  return result;
}


void tarch::logging::LogFilter::addFilterListEntry( const FilterListEntry& entry) {
  if (_filterlist.count(entry)!=0) {
    std::cerr << "tried to insert log filter " << entry.toString() << " multiple times" << std::endl;
    assertion(false);
  }
  else {
    _filterlist.insert( entry );
  }
}
