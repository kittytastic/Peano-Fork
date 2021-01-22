#include "grid.h"
#include "GridStatistics.h"
#include "GridControlEvent.h"
#include "Spacetree.h"



peano4::grid::GridVertex peano4::grid::createVertex(
  GridVertex::State                            state,
  const tarch::la::Vector<Dimensions,double>&  x,
  int                                          level,
  const tarch::la::Vector<TwoPowerD,int>&      adjacentRanks,
  bool                                         isNewFineGridVertex
) {
  GridVertex result;

  result.setState( state );
  result.setAdjacentRanks( adjacentRanks );
  result.setHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep(not isNewFineGridVertex);
  result.setIsAntecessorOfRefinedVertexInCurrentTreeSweep(not isNewFineGridVertex);
  result.setX(x);
  result.setLevel(level);

  // not required logically, but makes valgrind's memchecker happy
  result.setBackupOfAdjacentRanks( tarch::la::Vector<TwoPowerD,int>(Spacetree::InvalidRank) );
  result.setNumberOfAdjacentRefinedLocalCells(0);

  return result;
}



std::vector< peano4::grid::GridControlEvent > peano4::grid::merge( std::vector< GridControlEvent>   events, const double Tolerance ) {
  static tarch::logging::Log _log( "peano4::grid" );
  logTraceInWith1Argument( "merge(...)", events.size() );

  std::vector< peano4::grid::GridControlEvent > result;

  for ( auto currentEvent: events ) {
    std::vector< GridControlEvent >::iterator i = result.begin();

    bool hasInserted = false;

    while (i!=result.end()) {
      // fuse two adjacent refinement commands
      tarch::la::Vector<Dimensions,double> boundingEventOffset = tarch::la::min( i->getOffset(), currentEvent.getOffset() );
      tarch::la::Vector<Dimensions,double> boundingEventSize   = tarch::la::max( i->getOffset()+i->getWidth(), currentEvent.getOffset()+currentEvent.getWidth() ) - boundingEventOffset;

      logDebug( "merge(...)", "compare " << currentEvent.toString() << "+" << i->toString() << " vs. a fused event of " << boundingEventOffset << "x" << boundingEventSize );

      bool twoEventsAreAdjacent = tarch::la::volume(boundingEventSize) <= (1.0+Tolerance) * (tarch::la::volume(i->getWidth()) + tarch::la::volume(currentEvent.getWidth()));
      bool twoEventsOverlap     = true;
      for (int d=0; d<Dimensions; d++) {
        twoEventsOverlap &= i->getOffset()(d)+i->getWidth()(d) >= currentEvent.getOffset()(d);
        twoEventsOverlap &= i->getOffset()(d)                  <= currentEvent.getOffset()(d) + currentEvent.getWidth()(d);
      }

      if (
        twoEventsOverlap
        and
        currentEvent.getRefinementControl()==GridControlEvent::RefinementControl::Erase
        and
        i->getRefinementControl()!=GridControlEvent::RefinementControl::Erase
      ) {
        logInfo( "merge(...)", "drop event " << currentEvent.toString() );
        i = result.end();
        hasInserted = true;
      }
      else if (
        twoEventsOverlap
        and
        currentEvent.getRefinementControl()!=GridControlEvent::RefinementControl::Erase
        and
        i->getRefinementControl()==GridControlEvent::RefinementControl::Erase
      ) {
        logInfo( "merge(...)", "replace event " << i->toString() << " with " << currentEvent.toString() );
        *i = currentEvent;
        i = result.end();
        hasInserted = true;
      }
      else if (
        (i->getRefinementControl()==GridControlEvent::RefinementControl::Refine and currentEvent.getRefinementControl()==GridControlEvent::RefinementControl::Refine)
        and
        tarch::la::equals( i->getH(), currentEvent.getH(), tarch::la::relativeEps( tarch::la::max(i->getH()), tarch::la::max(currentEvent.getH()), 0.1 ))
        and
        twoEventsAreAdjacent
      ) {
        *i = GridControlEvent(
          GridControlEvent::RefinementControl::Refine,
          boundingEventOffset, boundingEventSize, i->getH()
        );
        logDebug( "merge(...)", "merged into " << currentEvent.toString() );
        hasInserted = true;
        i           = result.end();
      }
      else if (
        (i->getRefinementControl()==GridControlEvent::RefinementControl::Erase and currentEvent.getRefinementControl()==GridControlEvent::RefinementControl::Erase)
        and
        tarch::la::equals( i->getH(), currentEvent.getH(), tarch::la::relativeEps( tarch::la::max(i->getH()), tarch::la::max(currentEvent.getH()), 0.1 ))
        and
        twoEventsAreAdjacent
      ) {
        *i = GridControlEvent(
          GridControlEvent::RefinementControl::Erase,
          boundingEventOffset, boundingEventSize, i->getH()
        );
        logDebug( "merge(...)", "merged into " << currentEvent.toString() );
        hasInserted = true;
        i           = result.end();
      }
      else {
        i++;
      }
    }

    if (not hasInserted ) {
      result.push_back( currentEvent );
    }
  }

  logTraceOutWith1Argument( "merge(...)", events.size() );
  return events.size()>result.size() ? merge(result, Tolerance) : result;
}


peano4::grid::GridStatistics operator+( peano4::grid::GridStatistics lhs, peano4::grid::GridStatistics rhs ) {
  return peano4::grid::GridStatistics(
    lhs.getNumberOfLocalUnrefinedCells()  + rhs.getNumberOfLocalUnrefinedCells(),
    lhs.getNumberOfRemoteUnrefinedCells() + rhs.getNumberOfRemoteUnrefinedCells(),
    lhs.getNumberOfLocalRefinedCells()  + rhs.getNumberOfLocalRefinedCells(),
    lhs.getNumberOfRemoteRefinedCells() + rhs.getNumberOfRemoteRefinedCells(),
    std::min(lhs.getStationarySweeps(),rhs.getStationarySweeps()),
    lhs.getCoarseningHasBeenVetoed() | rhs.getCoarseningHasBeenVetoed(),
    tarch::la::min( lhs.getMinH(), rhs.getMinH() )
  );
}


void peano4::grid::clear( GridStatistics& statistics, bool isGlobalMasterTree ) {
  statistics.setNumberOfLocalUnrefinedCells(0);
  statistics.setNumberOfRemoteUnrefinedCells(0);
  statistics.setNumberOfLocalRefinedCells(isGlobalMasterTree ? 1 : 0);
  statistics.setNumberOfRemoteRefinedCells(isGlobalMasterTree ? 0 : 1);
  statistics.setCoarseningHasBeenVetoed(false);
  statistics.setStationarySweeps( statistics.getStationarySweeps()+1 );
  statistics.setMinH( tarch::la::Vector<Dimensions,double>( std::numeric_limits<double>::max() ) );
}

