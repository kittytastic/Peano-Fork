#include "SolverRepository.h"

#include <algorithm>

#include "peano4/grid/grid.h"
#include "peano4/parallel/SpacetreeSet.h"

#include "exahype2/LoadBalancingConfiguration.h"


{% for item in NAMESPACE -%}
  namespace {{ item }} {
{%- endfor %}

int statisticsExchangeTag = tarch::mpi::Rank::reserveFreeTag("SolverRepository - statistics exchange tag");

tarch::logging::Log _log( "SolverRepository" );

::exahype2::RefinementControl  refinementControl;
::exahype2::PlotFilter         plotFilter;
peano4::grid::GridStatistics   gridStatisticsAfterGridConstruction;


{% if LOAD_BALANCER!="" -%}
{{LOAD_BALANCER}}              loadBalancer{{LOAD_BALANCER_ARGUMENTS}};
{% else -%}
toolbox::loadbalancing::NoLoadBalancing  loadBalancer;
{% endif -%}



{% for item in SOLVERS -%}
{{ item[0] }} {{ item[1] }};
{%- endfor %}


bool mayPlot() {
  bool result = true;
  {% for item in SOLVERS -%}
    result &= {{ item[1] }}.mayPlot();
  {%- endfor %}
  return result;
}


double getMinTimeStamp(bool ofLastTimeStepOnly) {
  double result = std::numeric_limits<double>::max();
  {% for item in SOLVERS -%}
    result = std::min( result, {{ item[1] }}.getMinTimeStamp(ofLastTimeStepOnly) );
  {%- endfor %}
  return result;
}


double getMaxTimeStamp(bool ofLastTimeStepOnly) {
  double result = 0.0;
  {% for item in SOLVERS -%}
    result = std::max( result, {{ item[1] }}.getMaxTimeStamp(ofLastTimeStepOnly) );
  {%- endfor %}
  return result;
}


double getMinMeshSize() {
  double result = std::numeric_limits<double>::max();
  {% for item in SOLVERS -%}
    result = std::min( result, {{ item[1] }}.getMinMeshSize() );
  {%- endfor %}
  return result;
}


double getMaxMeshSize() {
  double result = 0.0;
  {% for item in SOLVERS -%}
    result = std::max( result, {{ item[1] }}.getMaxMeshSize() );
  {%- endfor %}
  return result;
}


double getMaxAdmissibleMeshSize() {
  double result = 0.0;
  {% for item in SOLVERS -%}
    result = std::max( result, {{ item[1] }}.MaxAdmissiblePatchH );
  {%- endfor %}
  return result;
}


double getMinAdmissibleMeshSize() {
  double result = 0.0;
  {% for item in SOLVERS -%}
    result = std::max( result, {{ item[1] }}.MinAdmissiblePatchH );
  {%- endfor %}
  return result;
}


double getMinTimeStepSize() {
  double result = std::numeric_limits<double>::max();
  {% for item in SOLVERS -%}
    result = std::min( result, {{ item[1] }}.getMinTimeStepSize() );
  {%- endfor %}
  return result;
}


double getMaxTimeStepSize() {
  double result = 0.0;
  {% for item in SOLVERS -%}
  result = std::max( result, {{ item[1] }}.getMaxTimeStepSize() );
  {%- endfor %}
  return result;
}


void startGridConstructionStep() {
  {% for item in SOLVERS -%}
  {{ item[1] }}.startGridConstructionStep();
  {%- endfor %}

  refinementControl.clear();
}


void startGridInitialisationStep() {
  {% for item in SOLVERS -%}
  {{ item[1] }}.startGridInitialisationStep();
  {%- endfor %}
}


void startTimeStep(
  double minTimeStamp,
  double maxTimeStamp,
  double minTimeStepSize,
  double maxTimeStepSize
) {
  {% for item in SOLVERS -%}
  {{ item[1] }}.startTimeStep(minTimeStamp,maxTimeStamp,minTimeStepSize,maxTimeStepSize);
  {%- endfor %}

  refinementControl.clear();
}


void startPlottingStep(
  double minTimeStamp,
  double maxTimeStamp,
  double minTimeStepSize,
  double maxTimeStepSize
) {
  {% for item in SOLVERS -%}
  {{ item[1] }}.startPlottingStep(minTimeStamp,maxTimeStamp,minTimeStepSize,maxTimeStepSize);
  {%- endfor %}
}


void finishTimeStep() {
  {% for item in SOLVERS -%}
  {{ item[1] }}.finishTimeStep();
  {%- endfor %}

  refinementControl.finishStep();
  loadBalancer.finishStep();

  #ifdef UseSmartMPI
  smartmpi::tick();
  #endif
}


void finishGridConstructionStep() {
  {% for item in SOLVERS -%}
  {{ item[1] }}.finishGridConstructionStep();
  {%- endfor %}

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
  {% for item in SOLVERS -%}
  {{ item[1] }}.finishGridInitialisationStep();
  {%- endfor %}

  loadBalancer.finishStep();
}


void finishPlottingStep() {
  {% for item in SOLVERS -%}
  {{ item[1] }}.finishPlottingStep();
  {%- endfor %}

  plotFilter.finishPlottingStep();
}


void startSimulation() {
  {% for item in PLOT_FILTER -%}
  plotFilter.addFilter(
    {{item}}
  );
  {% endfor %}
}


void finishSimulation() {
  loadBalancer.finishStep();
  refinementControl.finishStep();
}


{% for item in NAMESPACE -%}
  }

{%- endfor %}

