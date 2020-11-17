#include "{{CLASSNAME}}.h"
#include "exahype2/RefinementControl.h"


tarch::logging::Log   {% for item in NAMESPACE -%}{{ item }}::{%- endfor %}{{CLASSNAME}}::_log( "{% for item in NAMESPACE -%}{{ item }}::{%- endfor %}{{CLASSNAME}}" );



{% if REFINEMENT_CRITERION_IMPLEMENTATION=="<user-defined>" %}
::exahype2::RefinementCommand {% for item in NAMESPACE -%}{{ item }}::{%- endfor %}{{CLASSNAME}}::refinementCriterion(
  double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
  const tarch::la::Vector<Dimensions,double>&  volumeX,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t
) {
  logTraceInWith3Arguments( "refinementCriterion(...)", volumeX, volumeH, t );
  ::exahype2::RefinementCommand result = ::exahype2::RefinementCommand::Keep;

  if ( tarch::la::smallerEquals(_maxH,_NumberOfFiniteVolumesPerAxisPerPatch*tarch::la::max(volumeH)) ) {
    result = ::exahype2::RefinementCommand::Refine;
  }

  logTraceOutWith1Argument( "refinementCriterion(...)", ::toString(result) );
  return result;
}
{% endif %}


{% if INITIAL_CONDITIONS_IMPLEMENTATION=="<user-defined>" %}
void {% for item in NAMESPACE -%}{{ item }}::{%- endfor %}{{CLASSNAME}}::adjustSolution(
  double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  const tarch::la::Vector<Dimensions,double>&  volumeX,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t
) {
  logTraceInWith3Arguments( "adjustSolution(...)", volumeX, volumeH, t );
  if (tarch::la::equals(t,0.0) ) {
    // initial conditions
  }
  else {
    // other stuff
  }
  logTraceOut( "adjustSolution(...)" );
}
{% endif %}


{% if EIGENVALUES_IMPLEMENTATION=="<user-defined>" %}
#if defined(GPUOffloading)
#pragma omp declare target
#endif
double {% for item in NAMESPACE -%}{{ item }}::{%- endfor %}{{CLASSNAME}}::maxEigenvalue(
  double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal
) {
  // @todo implement
  return 0.0;
}
#if defined(GPUOffloading)
#pragma omp end declare target
#endif
{% endif %}


{% if BOUNDARY_CONDITIONS_IMPLEMENTATION=="<user-defined>" %}
void {% for item in NAMESPACE -%}{{ item }}::{%- endfor %}{{CLASSNAME}}::boundaryConditions(
  double * __restrict__ Qinside, // Qinside[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
  double * __restrict__ Qoutside, // Qoutside[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal
) {
  logTraceInWith4Arguments( "boundaryConditions(...)", faceCentre, volumeH, t, normal );
  // @todo implement
  logTraceOut( "boundaryConditions(...)" );
}
{% endif %}

{% if FLUX_IMPLEMENTATION=="<user-defined>" %}
#if defined(GPUOffloading)
#pragma omp declare target
#endif
void {% for item in NAMESPACE -%}{{ item }}::{%- endfor %}{{CLASSNAME}}::flux(
 double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
 const tarch::la::Vector<Dimensions,double>&  faceCentre,
 const tarch::la::Vector<Dimensions,double>&  volumeH,
 double                                       t,
 int                                          normal,
 double * __restrict__ F // F[{{NUMBER_OF_UNKNOWNS}}]
) {
  // @todo implement
}
#if defined(GPUOffloading)
#pragma omp end declare target
#endif
{% endif %}


{% if NCP_IMPLEMENTATION=="<user-defined>" %}
#if defined(GPUOffloading)
#pragma omp declare target
#endif
void {% for item in NAMESPACE -%}{{ item }}::{%- endfor %}{{CLASSNAME}}::nonconservativeProduct(
  double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  double                                       gradQ[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}][Dimensions],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal,
  double * __restrict__ BgradQ // BgradQ[{{NUMBER_OF_UNKNOWNS}}]
) {
  // @todo implement
}
#if defined(GPUOffloading)
#pragma omp end declare target
#endif
{% endif %}
