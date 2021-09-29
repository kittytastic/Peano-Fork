//
// ExaHyPE2 solver file
// Generated by Peano's Python API
// www.peano-framework.org
//
// This is generated. If you change fundamental properties, you will have to
// generate this file. Backup your manual changes before you do so.
//
#ifndef {% for item in NAMESPACE -%}_{{ item }}{%- endfor %}_{{CLASSNAME}}_H_
#define {% for item in NAMESPACE -%}_{{ item }}{%- endfor %}_{{CLASSNAME}}_H_



#include "toolbox/loadbalancing/NoLoadBalancing.h"

{% if LOAD_BALANCER!="" -%}
#include "{{LOAD_BALANCER | replace('::', '/') }}.h"
{% endif -%}

#include "exahype2/RefinementControl.h"
#include "exahype2/PlotFilter.h"
#include "peano4/grid/GridStatistics.h"


{% for item in SOLVERS -%}
#include "{{ item[0] }}.h"
{%- endfor %}


{% for item in NAMESPACE -%}
  namespace {{ item }} {
{%- endfor %}

  {% for item in SOLVERS -%}
  extern {{ item[0] }}  {{ item[1] }};
  {%- endfor %}


  extern ::exahype2::RefinementControl  refinementControl;
  extern ::exahype2::PlotFilter         plotFilter;

  {% if LOAD_BALANCER!="" -%}
  extern {{LOAD_BALANCER}}              loadBalancer;
  {% else -%}
  extern toolbox::loadbalancing::NoLoadBalancing  loadBalancer;
  {% endif -%}

  extern peano4::grid::GridStatistics   gridStatisticsAfterGridConstruction;


  /**
   * Return the global min time stamp over all solvers.
   *
   * There are two different flavours of a minimal time stamp: On the one hand,
   * there's a global minimum time stamp over all solvers. This might not
   * be the min time stamp after the last update. If you have local time
   * stepping, then some cells might just have done a tiny time step,
   * whereas the big cells still span a large time span. Hence, no the other
   * hand, there's also a (time-)local time stamp.
   */
  double getMinTimeStamp(bool ofLastTimeStepOnly = false);
  double getMaxTimeStamp(bool ofLastTimeStepOnly = false);
  double getMinTimeStepSize();
  double getMaxTimeStepSize();
  double getMinMeshSize();
  double getMaxMeshSize();

  double getMaxAdmissibleMeshSize();
  double getMinAdmissibleMeshSize();

  void startGridConstructionStep();
  void startGridInitialisationStep();

  void startTimeStep(
    double globalMinTimeStamp,
    double globalMaxTimeStamp,
    double globalMinTimeStepSize,
    double globalMaxTimeStepSize
  );

  void startPlottingStep(
    double globalMinTimeStamp,
    double globalMaxTimeStamp,
    double globalMinTimeStepSize,
    double globalMaxTimeStepSize
  );

  void finishGridConstructionStep();
  void finishGridInitialisationStep();
  void finishTimeStep();
  void finishPlottingStep();

  void startSimulation();
  void finishSimulation();

{% for item in NAMESPACE -%}
  }
{%- endfor %}


#endif
