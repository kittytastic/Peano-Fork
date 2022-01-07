#include <algorithm>


#include "Abstracteuler2D.h"
#include "Constants.h"


#include "tarch/multicore/Lock.h"
#include "exahype2/NonCriticalAssertions.h"


tarch::logging::Log   project::base_2d_euler_inline::Abstracteuler2D::Abstracteuler2D::_log( "project::base_2d_euler_inline::Abstracteuler2D::Abstracteuler2D" );

std::bitset<Dimensions> project::base_2d_euler_inline::Abstracteuler2D::Abstracteuler2D::PeriodicBC = project::base_2d_euler_inline::PeriodicBC;


project::base_2d_euler_inline::Abstracteuler2D::Abstracteuler2D():
  _solverState(SolverState::GridConstruction),
  _minTimeStamp(0.0),
  _maxTimeStamp(0.0),
  _minTimeStampThisTimeStep(0.0),
  _maxTimeStampThisTimeStep(0.0),
  _minVolumeH(0.0),
  _maxVolumeH(0.0),
  _minVolumeHThisTimeStep(0.0),
  _maxVolumeHThisTimeStep(0.0),
  _minTimeStepSize(0.0),
  _maxTimeStepSize(0.0),
  _minTimeStepSizeThisTimeStep(0.0),
  _maxTimeStepSizeThisTimeStep(0.0),
  _patchUpdates(0) {
  
}


double project::base_2d_euler_inline::Abstracteuler2D::getMaxMeshSize() const {
  return getMaxPatchSize();
}


double project::base_2d_euler_inline::Abstracteuler2D::getMinMeshSize() const {
  return getMinPatchSize();
}


double project::base_2d_euler_inline::Abstracteuler2D::getMinPatchSize(bool ofCurrentlyRunningGridSweep) const {
  return getMinVolumeSize(ofCurrentlyRunningGridSweep) * NumberOfFiniteVolumesPerAxisPerPatch;
}


double project::base_2d_euler_inline::Abstracteuler2D::getMaxPatchSize(bool ofCurrentlyRunningGridSweep) const {
  return getMaxVolumeSize(ofCurrentlyRunningGridSweep) * NumberOfFiniteVolumesPerAxisPerPatch;
}


double project::base_2d_euler_inline::Abstracteuler2D::getMinVolumeSize(bool ofCurrentlyRunningGridSweep) const {
  return ofCurrentlyRunningGridSweep ? _minVolumeHThisTimeStep : _minVolumeH;
}


double project::base_2d_euler_inline::Abstracteuler2D::getMaxVolumeSize(bool ofCurrentlyRunningGridSweep) const {
  return ofCurrentlyRunningGridSweep ? _maxVolumeHThisTimeStep : _maxVolumeH;
}


double project::base_2d_euler_inline::Abstracteuler2D::getMinTimeStamp(bool ofCurrentlyRunningGridSweep) const {
  return ofCurrentlyRunningGridSweep ? _minTimeStampThisTimeStep : _minTimeStamp;
}


double project::base_2d_euler_inline::Abstracteuler2D::getMaxTimeStamp(bool ofCurrentlyRunningGridSweep) const {
  return ofCurrentlyRunningGridSweep ? _maxTimeStampThisTimeStep : _maxTimeStamp;
}


double project::base_2d_euler_inline::Abstracteuler2D::getMinTimeStepSize() const {
  return _minTimeStepSize;
}


double project::base_2d_euler_inline::Abstracteuler2D::getMaxTimeStepSize() const {
  return _maxTimeStepSize;
}


void project::base_2d_euler_inline::Abstracteuler2D::update(double timeStepSize, double timeStamp, double patchSize) {
  tarch::multicore::Lock lock(_semaphore);

  if ( tarch::la::greater(timeStepSize,0.0) ) {
    assertion1(timeStepSize<std::numeric_limits<double>::max()/10.0,timeStepSize);
    assertion1(timeStepSize>=0.0,timeStepSize);
    _minTimeStepSizeThisTimeStep = std::min(timeStepSize,_minTimeStepSizeThisTimeStep);
    _maxTimeStepSizeThisTimeStep = std::max(timeStepSize,_maxTimeStepSizeThisTimeStep);
    assertion2(_minTimeStepSizeThisTimeStep<=_maxTimeStepSizeThisTimeStep, _minTimeStepSizeThisTimeStep, _maxTimeStepSizeThisTimeStep );

    _patchUpdates++;

    _localMinTimeStampThisTimeStep = std::min(_localMinTimeStampThisTimeStep, timeStamp);
    _localMaxTimeStampThisTimeStep = std::max(_localMaxTimeStampThisTimeStep, timeStamp);
  }

  assertion1(timeStamp<std::numeric_limits<double>::max()/10.0,timeStamp);
  assertion1(timeStamp>=0.0,timeStamp);
  _maxTimeStampThisTimeStep = std::max(timeStamp,_maxTimeStampThisTimeStep);
  _minTimeStampThisTimeStep = std::min(timeStamp,_minTimeStampThisTimeStep);
  assertion6( tarch::la::smallerEquals(_minTimeStamp,_maxTimeStampThisTimeStep), _minTimeStamp, _minTimeStampThisTimeStep, _maxTimeStampThisTimeStep, timeStepSize, timeStamp, patchSize );

  assertion1(patchSize<std::numeric_limits<double>::max()/10.0,patchSize);
  assertion1(patchSize>0.0,patchSize);
  _maxVolumeHThisTimeStep = std::max(_maxVolumeHThisTimeStep,patchSize / NumberOfFiniteVolumesPerAxisPerPatch);
  _minVolumeHThisTimeStep = std::min(_minVolumeHThisTimeStep,patchSize / NumberOfFiniteVolumesPerAxisPerPatch);
}


project::base_2d_euler_inline::Abstracteuler2D::SolverState project::base_2d_euler_inline::Abstracteuler2D::getSolverState() const {
  return _solverState;
}



::exahype2::RefinementCommand project::base_2d_euler_inline::Abstracteuler2D::refinementCriterion(
  const double * __restrict__ Q, // Q[4+0],
  const tarch::la::Vector<Dimensions,double>&  volumeCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t
) {
  
  ::exahype2::RefinementCommand result = ::exahype2::RefinementCommand::Keep;


  return result;
  
}









void project::base_2d_euler_inline::Abstracteuler2D::startGridConstructionStep() {
  assertion( _solverState == SolverState::GridConstruction );
}


void project::base_2d_euler_inline::Abstracteuler2D::finishGridConstructionStep() {
}


void project::base_2d_euler_inline::Abstracteuler2D::startGridInitialisationStep() {
  _solverState = SolverState::GridInitialisation;
}


void project::base_2d_euler_inline::Abstracteuler2D::finishGridInitialisationStep() {
}


void project::base_2d_euler_inline::Abstracteuler2D::startTimeStep(
  double globalMinTimeStamp,
  double globalMaxTimeStamp,
  double globalMinTimeStepSize,
  double globalMaxTimeStepSize
) {
  
  if (
    tarch::mpi::Rank::getInstance().isGlobalMaster() 
    and
    _maxVolumeH>0.0
  ) {
    logInfo( "step()", "Solver euler2D:" );
    logInfo( "step()", "t       = " << _minTimeStampThisTimeStep );
    logInfo( "step()", "dt      = " << getTimeStepSize() );
    logInfo( "step()", "h_{min} = " << _minVolumeHThisTimeStep << " (volume size)");
    logInfo( "step()", "h_{max} = " << _maxVolumeHThisTimeStep << " (volume size)" );
  }

  if ( _solverState==SolverState::GridInitialisation ) {
    _solverState     = SolverState::TimeStepAfterGridInitialisation;
  }
  else {
    assertion( _solverState!=SolverState::GridConstruction );
    _solverState     = SolverState::TimeStep;
  }

  _minTimeStamp = _minTimeStampThisTimeStep;
  _maxTimeStamp = _maxTimeStampThisTimeStep;

  _minTimeStampThisTimeStep = std::numeric_limits<double>::max();
  _maxTimeStampThisTimeStep = std::numeric_limits<double>::min();

  _minTimeStepSize = _minTimeStepSizeThisTimeStep;
  _maxTimeStepSize = _maxTimeStepSizeThisTimeStep;

  _minTimeStepSizeThisTimeStep = std::numeric_limits<double>::max();
  _maxTimeStepSizeThisTimeStep = std::numeric_limits<double>::min();

  _minVolumeH = _minVolumeHThisTimeStep;
  _maxVolumeH = _maxVolumeHThisTimeStep;

  _maxVolumeHThisTimeStep      = 0.0;
  _minVolumeHThisTimeStep      = std::numeric_limits<double>::max();

  _localMinTimeStampThisTimeStep = std::numeric_limits<double>::max();
  _localMaxTimeStampThisTimeStep = std::numeric_limits<double>::min();

  _patchUpdates    = 0;
}


void project::base_2d_euler_inline::Abstracteuler2D::finishTimeStep() {
  #ifdef Parallel
  double newMinTimeStamp = _minTimeStampThisTimeStep;
  double newMaxTimeStamp = _maxTimeStampThisTimeStep;
  double newMinVolumeH   = _minVolumeHThisTimeStep;
  double newMaxVolumeH   = _maxVolumeHThisTimeStep;
  double newMinTimeStepSize = _minTimeStepSizeThisTimeStep;
  double newMaxTimeStepSize = _maxTimeStepSizeThisTimeStep;

  double newLocalMinTimeStamp = _localMinTimeStampThisTimeStep;
  double newLocalMaxTimeStamp = _localMaxTimeStampThisTimeStep;

  tarch::mpi::Rank::getInstance().allReduce(
      &newMinTimeStamp,
      &_minTimeStampThisTimeStep,
      1, MPI_DOUBLE,
      MPI_MIN,
      [&]() -> void { tarch::services::ServiceRepository::getInstance().receiveDanglingMessages(); }
      );
  tarch::mpi::Rank::getInstance().allReduce(
      &newMaxTimeStamp,
      &_maxTimeStampThisTimeStep,
      1, MPI_DOUBLE,
      MPI_MAX,
      [&]() -> void { tarch::services::ServiceRepository::getInstance().receiveDanglingMessages(); }
      );

  tarch::mpi::Rank::getInstance().allReduce(
      &newMinVolumeH,
      &_minVolumeHThisTimeStep,
      1, MPI_DOUBLE,
      MPI_MIN,
      [&]() -> void { tarch::services::ServiceRepository::getInstance().receiveDanglingMessages(); }
      );
  tarch::mpi::Rank::getInstance().allReduce(
      &newMaxVolumeH,
      &_maxVolumeHThisTimeStep,
      1, MPI_DOUBLE,
      MPI_MAX,
      [&]() -> void { tarch::services::ServiceRepository::getInstance().receiveDanglingMessages(); }
      );

  tarch::mpi::Rank::getInstance().allReduce(
      &newMinTimeStepSize,
      &_minTimeStepSizeThisTimeStep,
      1, MPI_DOUBLE,
      MPI_MIN,
      [&]() -> void { tarch::services::ServiceRepository::getInstance().receiveDanglingMessages(); }
      );
  tarch::mpi::Rank::getInstance().allReduce(
      &newMaxTimeStepSize,
      &_maxTimeStepSizeThisTimeStep,
      1, MPI_DOUBLE,
      MPI_MAX,
      [&]() -> void { tarch::services::ServiceRepository::getInstance().receiveDanglingMessages(); }
      );

  tarch::mpi::Rank::getInstance().allReduce(
      &newLocalMinTimeStamp,
      &_localMinTimeStampThisTimeStep,
      1, MPI_DOUBLE,
      MPI_MIN,
      [&]() -> void { tarch::services::ServiceRepository::getInstance().receiveDanglingMessages(); }
      );
  tarch::mpi::Rank::getInstance().allReduce(
      &newLocalMaxTimeStamp,
      &_localMaxTimeStampThisTimeStep,
      1, MPI_DOUBLE,
      MPI_MAX,
      [&]() -> void { tarch::services::ServiceRepository::getInstance().receiveDanglingMessages(); }
      );
  #endif

  if ( _minTimeStampThisTimeStep>=std::numeric_limits<double>::max()/10.0) {
    _minTimeStampThisTimeStep = 0.0;
  }
  if ( _maxTimeStampThisTimeStep>=std::numeric_limits<double>::max()/10.0 ) {
    _maxTimeStampThisTimeStep = 0.0;
  }

  
  assertion( _minVolumeH >= 0.0 );
  assertion( MaxAdmissibleVolumeH > 0.0 );
  assertion2( _minVolumeH <= MaxAdmissibleVolumeH, _minVolumeH, MaxAdmissibleVolumeH );
  _timeStepSize  = 0.001 * _minVolumeH / MaxAdmissibleVolumeH;
}


void project::base_2d_euler_inline::Abstracteuler2D::startPlottingStep(
  double globalMinTimeStamp,
  double globalMaxTimeStamp,
  double globalMinTimeStepSize,
  double globalMaxTimeStepSize
) {
  if ( _solverState== SolverState::GridInitialisation) {
    _solverState = SolverState::PlottingAfterGridInitialisation;
  }
  else {
    _solverState = SolverState::Plotting;
  }
}


void project::base_2d_euler_inline::Abstracteuler2D::finishPlottingStep() {
}


std::string project::base_2d_euler_inline::Abstracteuler2D::toString(SolverState state) {
  switch (state) {
    case SolverState::GridConstruction:
      return "grid-construction";
    case SolverState::GridInitialisation:
      return "grid-initialisation";
    case SolverState::TimeStep:
      return "time-step";
    case SolverState::Plotting:
      return "plotting";
    case SolverState::TimeStepAfterGridInitialisation:
      return "time-step-after-grid-initialisation";
    case SolverState::PlottingAfterGridInitialisation:
      return "plotting-after-grid-initialisation";
  }
  return "<undef>";
}


bool project::base_2d_euler_inline::Abstracteuler2D::mayPlot() const {
  return true;
}


bool project::base_2d_euler_inline::Abstracteuler2D::isFirstGridSweepOfTimeStep() const {
  return true;
}


























double ::project::base_2d_euler_inline::Abstracteuler2D::getTimeStepSize() const {
  return _timeStepSize;
}
    