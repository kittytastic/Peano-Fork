#include "SolverRepository.h"

#include <algorithm>

#include "peano4/grid/grid.h"
#include "peano4/parallel/SpacetreeSet.h"

#include "exahype2/LoadBalancingConfiguration.h"


namespace project {namespace base_2d_euler_inline {namespace repositories {

int statisticsExchangeTag = tarch::mpi::Rank::reserveFreeTag("SolverRepository - statistics exchange tag");

tarch::logging::Log _log( "SolverRepository" );

::exahype2::RefinementControl  refinementControl;
::exahype2::PlotFilter         plotFilter;
peano4::grid::GridStatistics   gridStatisticsAfterGridConstruction;


toolbox::loadbalancing::RecursiveSubdivision              loadBalancer(new ::exahype2::LoadBalancingConfiguration());
euler2D InstanceOfeuler2D;


bool mayPlot() {
  bool result = true;
  result &= InstanceOfeuler2D.mayPlot();
  return result;
}


double getMinTimeStamp(bool ofCurrentlyRunningGridSweep) {
  double result = std::numeric_limits<double>::max();
  result = std::min( result, InstanceOfeuler2D.getMinTimeStamp(ofCurrentlyRunningGridSweep) );
  return result;
}


double getMaxTimeStamp(bool ofCurrentlyRunningGridSweep) {
  double result = 0.0;
  result = std::max( result, InstanceOfeuler2D.getMaxTimeStamp(ofCurrentlyRunningGridSweep) );
  return result;
}


double getMinMeshSize() {
  double result = std::numeric_limits<double>::max();
  result = std::min( result, InstanceOfeuler2D.getMinMeshSize() );
  return result;
}


double getMaxMeshSize() {
  double result = 0.0;
  result = std::max( result, InstanceOfeuler2D.getMaxMeshSize() );
  return result;
}


double getMaxAdmissibleMeshSize() {
  double result = 0.0;
  result = std::max( result, InstanceOfeuler2D.MaxAdmissiblePatchH );
  return result;
}


double getMinAdmissibleMeshSize() {
  double result = 0.0;
  result = std::max( result, InstanceOfeuler2D.MinAdmissiblePatchH );
  return result;
}


double getMinTimeStepSize() {
  double result = std::numeric_limits<double>::max();
  result = std::min( result, InstanceOfeuler2D.getMinTimeStepSize() );
  return result;
}


double getMaxTimeStepSize() {
  double result = 0.0;
  result = std::max( result, InstanceOfeuler2D.getMaxTimeStepSize() );
  return result;
}


void startGridConstructionStep() {
  InstanceOfeuler2D.startGridConstructionStep();

  refinementControl.clear();
}


void startGridInitialisationStep() {
  InstanceOfeuler2D.startGridInitialisationStep();
}


void startTimeStep(
  double minTimeStamp,
  double maxTimeStamp,
  double minTimeStepSize,
  double maxTimeStepSize
) {
  InstanceOfeuler2D.startTimeStep(minTimeStamp,maxTimeStamp,minTimeStepSize,maxTimeStepSize);

  refinementControl.clear();
}


void startPlottingStep(
  double minTimeStamp,
  double maxTimeStamp,
  double minTimeStepSize,
  double maxTimeStepSize
) {
  InstanceOfeuler2D.startPlottingStep(minTimeStamp,maxTimeStamp,minTimeStepSize,maxTimeStepSize);
}


void finishTimeStep() {
  InstanceOfeuler2D.finishTimeStep();

  refinementControl.finishStep();
  loadBalancer.finishStep();

  #ifdef UseSmartMPI
  smartmpi::tick();
  #endif
}


void finishGridConstructionStep() {
  InstanceOfeuler2D.finishGridConstructionStep();

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
          [&]() {
            tarch::services::ServiceRepository::getInstance().receiveDanglingMessages();
          },
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
      [&]() {
        tarch::services::ServiceRepository::getInstance().receiveDanglingMessages();
      },
      tarch::mpi::Rank::getInstance().getCommunicator()
    );
  }
  #endif
}


void finishGridInitialisationStep() {
  InstanceOfeuler2D.finishGridInitialisationStep();

  loadBalancer.finishStep();
}


void finishPlottingStep() {
  InstanceOfeuler2D.finishPlottingStep();

  plotFilter.finishPlottingStep();
}


void startSimulation() {
  
}


void finishSimulation() {
  loadBalancer.finishStep();
  refinementControl.finishStep();
}


}}}
