#include "RecursiveSubdivision.h"
#include "peano4/utils/Globals.h"
#include "peano4/parallel/SpacetreeSet.h"

#include "tarch/Assertions.h"
#include "tarch/mpi/Rank.h"
#include "tarch/multicore/Core.h"




tarch::logging::Log  toolbox::loadbalancing::RecursiveSubdivision::_log( "toolbox::loadbalancing::RecursiveSubdivision" );


toolbox::loadbalancing::RecursiveSubdivision::RecursiveSubdivision(double percentageOfCoresThatShouldInTheoryGetAtLeastOneCell):
  _PercentageOfCoresThatShouldInTheoryGetAtLeastOneCell( percentageOfCoresThatShouldInTheoryGetAtLeastOneCell ),
  _blacklist(),
  _hasSpreadOutOverAllRanks(false),
  _localNumberOfInnerUnrefinedCell( 0 ),
  _globalNumberOfInnerUnrefinedCell( 0 ),
  _totalNumberOfSplits(0),
  _isInCoolDownPhase(false) {
}


void toolbox::loadbalancing::RecursiveSubdivision::dumpStatistics() {
  std::set<int> idsOfLocalSpacetrees = peano4::parallel::SpacetreeSet::getInstance().getLocalSpacetrees();
  for (auto p: idsOfLocalSpacetrees) {
	logInfo(
      "dumpStatistics()",
	  "tree " << p << ": " << peano4::parallel::SpacetreeSet::getInstance().getGridStatistics(p).getNumberOfLocalUnrefinedCells()
	  << ( _blacklist.count(p)>0 ? " (on blacklist with weight=" + std::to_string(_blacklist[p]) + ")" : "" )
    );
  }
}


void toolbox::loadbalancing::RecursiveSubdivision::updateGlobalView() {
  _localNumberOfInnerUnrefinedCell = peano4::parallel::SpacetreeSet::getInstance().getGridStatistics().getNumberOfLocalUnrefinedCells();

  if (tarch::mpi::Rank::getInstance().getNumberOfRanks()<=1) {
    _globalNumberOfInnerUnrefinedCell = _localNumberOfInnerUnrefinedCell;
  }
  else {
    _globalNumberOfInnerUnrefinedCell = _localNumberOfInnerUnrefinedCell;
  }
}


int toolbox::loadbalancing::RecursiveSubdivision::getMaximumSpacetreeSize() const {
  return std::max(
    _globalNumberOfInnerUnrefinedCell
     / tarch::mpi::Rank::getInstance().getNumberOfRanks()
     / tarch::multicore::Core::getInstance().getNumberOfThreads()
     / 2, 1 );
}


int toolbox::loadbalancing::RecursiveSubdivision::getIdOfHeaviestLocalSpacetree() const {
  std::set<int> idsOfLocalSpacetrees = peano4::parallel::SpacetreeSet::getInstance().getLocalSpacetrees();
  int result = NoHeaviestTreeAvailable;
  int maxLocalUnrefinedCells = -1;
  for (auto p: idsOfLocalSpacetrees) {
    if (
      peano4::parallel::SpacetreeSet::getInstance().getGridStatistics(p).getNumberOfLocalUnrefinedCells()>maxLocalUnrefinedCells
      and
      _blacklist.count(p)==0
    ) {
      maxLocalUnrefinedCells = peano4::parallel::SpacetreeSet::getInstance().getGridStatistics(p).getNumberOfLocalUnrefinedCells();
      result = p;
    }
  }
  return result;
}


bool toolbox::loadbalancing::RecursiveSubdivision::doesBiggestLocalSpactreeViolateOptimalityCondition() const {
  bool result = false;
  std::set<int> idsOfLocalSpacetrees = peano4::parallel::SpacetreeSet::getInstance().getLocalSpacetrees();
  for (auto p: idsOfLocalSpacetrees) {
    result |= peano4::parallel::SpacetreeSet::getInstance().getGridStatistics(p).getNumberOfLocalUnrefinedCells()>getMaximumSpacetreeSize();
  }
  return result;
}


bool toolbox::loadbalancing::RecursiveSubdivision::isInCoolDownPhase() {
  if ( _isInCoolDownPhase and _totalNumberOfSplits>0 ) {
    _totalNumberOfSplits--;
    // @todo If we sleep more aggressively (mainly to bring the grid construction down), then
    // we get errors, as it seems that dynamic LB is not yet working properly. I have checked
    // it with the purge mechanism turned off, and it still does not work properly. Needs more
    // debugging, but it is a difficult problem. We have to reduce it to a two tree setup

    // @TODO Wieder ne Division durch zwei reinbauen, sonst dauert der Gitteraufbau Ewigkeiten.
    //       Aber jetzt lass ich erst erst mal drin, weil ich den Bug finden will!
    return true;

    // @todo Ich brauch evtl dann doch wieder mehr als eine Split. Das geht so einfach net - es ist zu langsam
    //    Aber vielleicht ist Problem auch weg mit dem aggressiverem Cool-down
  }
  else if ( _isInCoolDownPhase and _totalNumberOfSplits<=0 ) {
    _isInCoolDownPhase   = false;
    _totalNumberOfSplits = 0;
    return true;
  }
  else if ( not _isInCoolDownPhase and _totalNumberOfSplits<tarch::multicore::Core::getInstance().getNumberOfThreads() ) {
    return false;
  }
  else {
	logInfo( "isInCoolDownPhase()", "lots of splits triggered, enter cool-down phase, i.e. postpone further splits" );
    _isInCoolDownPhase = true;
    return true;
  }
}


void toolbox::loadbalancing::RecursiveSubdivision::finishStep() {
  updateGlobalView();
  updateBlacklist();

  if (
    static_cast<double>(_globalNumberOfInnerUnrefinedCell) < static_cast<double>(
      tarch::mpi::Rank::getInstance().getNumberOfRanks() * tarch::multicore::Core::getInstance().getNumberOfThreads() * _PercentageOfCoresThatShouldInTheoryGetAtLeastOneCell
    )
  ) {
    logInfo( "finishStep()", "problem size of " << _globalNumberOfInnerUnrefinedCell << " is too small to keep all cores busy - wait for larger mesh to be constructed" );
  }
  else if (
    not _hasSpreadOutOverAllRanks
    and
    tarch::mpi::Rank::getInstance().getNumberOfRanks()<=1
  ) {
    _hasSpreadOutOverAllRanks = true;
  }
  else if (_hasSpreadOutOverAllRanks and isInCoolDownPhase()) {
    logDebug( "finishStep()", "currently in cool-down phase" );
  }
  else if ( not _hasSpreadOutOverAllRanks ) {
    int cells             = getMaximumSpacetreeSize();
    assertion( cells>tarch::mpi::Rank::getInstance().getNumberOfRanks() );
    int cellsPerRank = cells / tarch::mpi::Rank::getInstance().getNumberOfRanks();

    _hasSpreadOutOverAllRanks = true;

    logInfo( "finishStep()", "spread over all ranks. Assign each rank " << cellsPerRank << " cells" );
    for (int targetRank=1; targetRank<tarch::mpi::Rank::getInstance().getNumberOfRanks(); targetRank++ ) {
      triggerSplit(0, cellsPerRank, targetRank);
    }
  }
  else if (
    _hasSpreadOutOverAllRanks
    and
    peano4::parallel::SpacetreeSet::getInstance().getLocalSpacetrees().size() > 0
    and
    static_cast<double>(peano4::parallel::SpacetreeSet::getInstance().getLocalSpacetrees().size()) < 2.0 * tarch::multicore::Core::getInstance().getNumberOfThreads() * _PercentageOfCoresThatShouldInTheoryGetAtLeastOneCell
  ) {
    int heaviestSpacetree                              = getIdOfHeaviestLocalSpacetree();
    if (heaviestSpacetree!=NoHeaviestTreeAvailable) {
      int numberOfLocalUnrefinedCellsOfHeaviestSpacetree = peano4::parallel::SpacetreeSet::getInstance().getGridStatistics(heaviestSpacetree).getNumberOfLocalUnrefinedCells();
      if (numberOfLocalUnrefinedCellsOfHeaviestSpacetree>getMaximumSpacetreeSize()) {
        int cellsPerCore      = std::min(numberOfLocalUnrefinedCellsOfHeaviestSpacetree/2,getMaximumSpacetreeSize());
        logInfo( "finishStep()", "insufficient number of cores occupied on this rank, so split " << cellsPerCore << " cells from tree " << heaviestSpacetree << " on local rank (hosts " << numberOfLocalUnrefinedCellsOfHeaviestSpacetree << " unrefined cells)" );
        triggerSplit(heaviestSpacetree, cellsPerCore, tarch::mpi::Rank::getInstance().getRank());
      }
    }
  }
  else if (
    _hasSpreadOutOverAllRanks
    and
    peano4::parallel::SpacetreeSet::getInstance().getLocalSpacetrees().size() > 0
    and
    doesBiggestLocalSpactreeViolateOptimalityCondition()
  ) {
    int heaviestSpacetree                              = getIdOfHeaviestLocalSpacetree();
    if (heaviestSpacetree!=NoHeaviestTreeAvailable) {
      int numberOfLocalUnrefinedCellsOfHeaviestSpacetree = peano4::parallel::SpacetreeSet::getInstance().getGridStatistics(heaviestSpacetree).getNumberOfLocalUnrefinedCells();
      if ( numberOfLocalUnrefinedCellsOfHeaviestSpacetree>getMaximumSpacetreeSize() ) {
        logInfo(
          "finishStep()",
          "biggest local tree " << heaviestSpacetree << " is too heavy as it hosts " <<
          numberOfLocalUnrefinedCellsOfHeaviestSpacetree << " cells (max size should be " << getMaximumSpacetreeSize() << ")"
        );
        #ifdef Parallel
         // @todo Das ist falsch. Hier muss jetzt genau das intra-Rank-Balancing rein
        const int targetRank = 0;
        #else
        const int targetRank = 0;
        #endif
        int cellsPerCore      = std::min(numberOfLocalUnrefinedCellsOfHeaviestSpacetree/2,getMaximumSpacetreeSize());
        triggerSplit(heaviestSpacetree, cellsPerCore, targetRank);
      }
    }
  }
}



void toolbox::loadbalancing::RecursiveSubdivision::updateBlacklist() {
  for (std::map<int,int>::iterator p = _blacklist.begin(); p!=_blacklist.end(); ) {
    if (p->second>0) {
      p->second--;
      p++;
    }
    else {
      p = _blacklist.erase(p);
    }
  }
}


void toolbox::loadbalancing::RecursiveSubdivision::triggerSplit( int sourceTree, int numberOfCells, int targetRank ) {
  if (not peano4::parallel::SpacetreeSet::getInstance().split(sourceTree,numberOfCells,targetRank)) {
    logInfo( "triggerSplit()", "wanted to split local rank " << sourceTree << " but failed" );
  }
  _blacklist.insert( std::pair<int,int>(sourceTree,3) );
  _totalNumberOfSplits++;
}
