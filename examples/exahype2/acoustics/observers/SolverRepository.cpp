#include "SolverRepository.h"

#include <algorithm>

#include "peano4/grid/grid.h"
#include "peano4/parallel/SpacetreeSet.h"



namespace examples {namespace exahype2 {namespace acoustics {namespace observers {

int statisticsExchangeTag = tarch::mpi::Rank::reserveFreeTag("SolverRepository - statistics exchange tag");

tarch::logging::Log _log( "SolverRepository" );

::exahype2::RefinementControl  refinementControl;



peano4::grid::GridStatistics   gridStatisticsAfterGridConstruction;


toolbox::loadbalancing::NoLoadBalancing  loadBalancer;
Acoustics InstanceOfAcoustics;



double getMinTimeStamp() {
  double result = std::numeric_limits<double>::max();
  result = std::min( result, InstanceOfAcoustics.getMinTimeStamp() );
  return result;
}


double getMaxTimeStamp() {
  double result = 0.0;
  result = std::max( result, InstanceOfAcoustics.getMaxTimeStamp() );
  return result;
}


double getMinMeshSize() {
  double result = std::numeric_limits<double>::max();
  result = std::min( result, InstanceOfAcoustics.getMinMeshSize() );
  return result;
}


double getMaxMeshSize() {
  double result = 0.0;
  result = std::max( result, InstanceOfAcoustics.getMaxMeshSize() );
  return result;
}


double getMinTimeStepSize() {
  double result = std::numeric_limits<double>::max();
  result = std::min( result, InstanceOfAcoustics.getMinTimeStepSize() );
  return result;
}


double getMaxTimeStepSize() {
  double result = 0.0;
  result = std::max( result, InstanceOfAcoustics.getMaxTimeStepSize() );
  return result;
}


void startGridConstructionStep() {
  InstanceOfAcoustics.startGridConstructionStep();

  refinementControl.clear();
}


void startGridInitialisationStep() {
  InstanceOfAcoustics.startGridInitialisationStep();
}


void startTimeStep(
  double minTimeStamp,
  double maxTimeStamp,
  double minTimeStepSize,
  double maxTimeStepSize
) {
  InstanceOfAcoustics.startTimeStep(minTimeStamp,maxTimeStamp,minTimeStepSize,maxTimeStepSize);

  refinementControl.clear();
}


void startPlottingStep(
  double minTimeStamp,
  double maxTimeStamp,
  double minTimeStepSize,
  double maxTimeStepSize
) {
  InstanceOfAcoustics.startPlottingStep(minTimeStamp,maxTimeStamp,minTimeStepSize,maxTimeStepSize);
}


void finishTimeStep() {
  InstanceOfAcoustics.finishTimeStep();

  refinementControl.finishStep();
  loadBalancer.finishStep();
}


void finishGridConstructionStep() {
  InstanceOfAcoustics.finishGridConstructionStep();

  refinementControl.finishStep();
  loadBalancer.finishStep();

  gridStatisticsAfterGridConstruction = peano4::parallel::SpacetreeSet::getInstance().getGridStatistics();
  #ifdef Parallel
  if ( tarch::mpi::Rank::getInstance().isGlobalMaster() ) {
    for (int rank=0; rank<tarch::mpi::Rank::getInstance().getNumberOfRanks(); rank++ ) {
      if (rank!=tarch::mpi::Rank::getGlobalMasterRank()) {
        peano4::grid::GridStatistics rankLocalStats;
        logDebug( "finishGridConstructionStep()", "receive grid statistics from rank " << rank << " via tag " << statisticsExchangeTag );
        peano4::grid::GridStatistics::receive(
          rankLocalStats,
          rank,
          statisticsExchangeTag,
          tarch::mpi::Rank::getInstance().getCommunicator()
        );
        gridStatisticsAfterGridConstruction = gridStatisticsAfterGridConstruction + rankLocalStats;
      }
    }
  }
  else {
    logDebug( "finishGridConstructionStep()", "send out local statistics " << gridStatisticsAfterGridConstruction.toString() << " to global master via tag " << statisticsExchangeTag );
    peano4::grid::GridStatistics::send(
      gridStatisticsAfterGridConstruction,
      tarch::mpi::Rank::getInstance().getGlobalMasterRank(),
      statisticsExchangeTag,
      tarch::mpi::Rank::getInstance().getCommunicator()
    );
  }
  #endif
}


void finishGridInitialisationStep() {
  InstanceOfAcoustics.finishGridInitialisationStep();
}


void finishPlottingStep() {
  InstanceOfAcoustics.finishPlottingStep();
}


void finishSimulation() {
  loadBalancer.finishStep();
  refinementControl.finishStep();
}


}}}}
