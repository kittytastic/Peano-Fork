#include "EnclaveTask.h"
#include "EnclaveBookkeeping.h"

#include "tarch/multicore/Core.h"

#include "exahype2/fv/Generic.h"


tarch::logging::Log  exahype2::EnclaveTask::_log( "exahype2::EnclaveTask" );


exahype2::EnclaveTask::EnclaveTask(
  const ::peano4::datamanagement::CellMarker&    marker,
  double*                                        inputValues,
  int                                            numberOfResultValues,
  std::function< void(double* input, double* output, const ::peano4::datamanagement::CellMarker& marker) >                        functor
):
  tarch::multicore::Task(tarch::multicore::reserveTaskNumber(),tarch::multicore::Task::DefaultPriority),
  _marker(marker),
  _inputValues(inputValues),
  _outputValues(nullptr),
  _numberOfResultValues(numberOfResultValues),
  _functor(functor) {
  logTraceIn( "EnclaveTask(...)" );
  logTraceOut( "EnclaveTask(...)" );
}


bool exahype2::EnclaveTask::run() {
  logTraceIn( "run()" );
  _outputValues = tarch::allocateMemory( _numberOfResultValues, tarch::MemoryLocation::Heap );

  _functor(_inputValues,_outputValues,_marker);
  tarch::freeMemory(_inputValues,tarch::MemoryLocation::Heap );

  EnclaveBookkeeping::getInstance().finishedTask(getTaskId(),_numberOfResultValues,_outputValues);
  logTraceOut( "run()" );
  return false;
}


void exahype2::EnclaveTask::prefetch() {
  logTraceIn( "prefetch()" );
  logTraceOut( "prefetch()" );
}

