{% include "AbstractSolverFixedTimeStepSize.template.cpp" %}



{{NAMESPACE | join("::")}}::{{CLASSNAME}}::{{CLASSNAME}}():
  _NumberOfFiniteVolumesPerAxisPerPatch( {{NUMBER_OF_VOLUMES_PER_AXIS}} ),
  _timeStamp(0.0),
  _solverState(SolverState::GridConstruction),
  _maxH({{MAX_H}}),
  _minH({{MIN_H}})
  {
}


void {{NAMESPACE | join("::")}}::{{CLASSNAME}}::startGridConstructionStep() {
  assertion( _solverState == SolverState::GridConstruction );
}


void {{NAMESPACE | join("::")}}::{{CLASSNAME}}::finishGridConstructionStep() {
}


void {{NAMESPACE | join("::")}}::{{CLASSNAME}}::startGridInitialisationStep() {
  assertion( _solverState == SolverState::GridConstruction );
  _solverState = SolverState::GridInitialisation;
  logDebug( "startGridInitialisationStep(...)", "new state is " << toString(_solverState) );
}


void {{NAMESPACE | join("::")}}::{{CLASSNAME}}::finishGridInitialisationStep() {
}


void {{NAMESPACE | join("::")}}::{{CLASSNAME}}::startTimeStep(
  double globalMinTimeStamp,
  double globalMaxTimeStamp,
  double globalMinTimeStepSize,
  double globalMaxTimeStepSize
) {
  if (
    _solverState == SolverState::GridInitialisation
  ) {
    _solverState = SolverState::PrimaryAfterGridInitialisation;
  }
  else if (
    _solverState == SolverState::Primary
    or
    _solverState == SolverState::PrimaryAfterGridInitialisation
  ) {
    _solverState = SolverState::Secondary;
  }
  else {
    _solverState = SolverState::Primary;
  }

  logDebug( "startTimeStep(...)", "new state is " << toString(_solverState) );
}


void {{NAMESPACE | join("::")}}::{{CLASSNAME}}::finishTimeStep() {
  if ( _solverState == SolverState::Secondary ) {
    _timeStamp += {{TIME_STEP_SIZE}};
  }
}


void {{NAMESPACE | join("::")}}::{{CLASSNAME}}::startPlottingStep(
  double globalMinTimeStamp,
  double globalMaxTimeStamp,
  double globalMinTimeStepSize,
  double globalMaxTimeStepSize
) {
  if ( _solverState == SolverState::GridInitialisation ) {
    _solverState = SolverState::PlottingInitialCondition;
  }
  else {
    _solverState = SolverState::Plotting;
  }
}


void {{NAMESPACE | join("::")}}::{{CLASSNAME}}::finishPlottingStep() {
}


std::string {{NAMESPACE | join("::")}}::{{CLASSNAME}}::toString(SolverState state) {
  switch (state) {
    case SolverState::GridConstruction:
      return "grid-construction";
    case SolverState::GridInitialisation:
      return "grid-initialisation";
    case SolverState::Primary:
      return "primary";
    case SolverState::Secondary:
      return "secondary";
    case SolverState::PlottingInitialCondition:
      return "plotting-initial-condition";
    case SolverState::PrimaryAfterGridInitialisation:
      return "primary-after-grid-initialisation";
    case SolverState::Plotting:
      return "plotting";
  }
  return "<undef>";
}


{% if EIGENVALUES_IMPLEMENTATION!="<user-defined>" %}
double {{NAMESPACE | join("::")}}::{{CLASSNAME}}::maxEigenvalue(
  const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal
) {
  {{EIGENVALUES_IMPLEMENTATION}}
}
{% endif %}


{% if FLUX_IMPLEMENTATION!="<none>" %}
{% if FLUX_IMPLEMENTATION!="<user-defined>" %}
void {{NAMESPACE | join("::")}}::{{CLASSNAME}}::flux(
 const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
 const tarch::la::Vector<Dimensions,double>&  faceCentre,
 const tarch::la::Vector<Dimensions,double>&  volumeH,
 double                                       t,
 int                                          normal,
 double * __restrict__ F // F[{{NUMBER_OF_UNKNOWNS}}]
) {
  {{FLUX_IMPLEMENTATION}}
}
{% endif %}
{% endif %}


{% if NCP_IMPLEMENTATION!="<none>" %}
{% if NCP_IMPLEMENTATION!="<user-defined>" %}
void {{NAMESPACE | join("::")}}::{{CLASSNAME}}::nonconservativeProduct(
  const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  const double * __restrict__             deltaQ, // [{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal,
  double * __restrict__ BgradQ // BgradQ[{{NUMBER_OF_UNKNOWNS}}]
) {
  {{NCP_IMPLEMENTATION}}
}
{% endif %}
{% endif %}
