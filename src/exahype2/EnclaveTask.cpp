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
  _outputValues = tarch::multicore::allocateMemory( _numberOfResultValues, tarch::multicore::MemoryLocation::Heap );

  ::exahype2::fv::validatePatch(
    _inputValues,
    64,
    0,
    6,
    1,
    std::string(__FILE__) + ": " + std::to_string(__LINE__)
  ); // previous time step has to be valid

  _functor(_inputValues,_outputValues,_marker);
  tarch::multicore::freeMemory(_inputValues,tarch::multicore::MemoryLocation::Heap );

  ::exahype2::fv::validatePatch(
		  _outputValues,
    64,
    0,
    6,
    0,
    std::string(__FILE__) + ": " + std::to_string(__LINE__)
  ); // previous time step has to be valid

  EnclaveBookkeeping::getInstance().finishedTask(getTaskId(),_numberOfResultValues,_outputValues);
  logTraceOut( "run()" );
  return false;
}


void exahype2::EnclaveTask::prefetch() {
  logTraceIn( "prefetch()" );
  logTraceOut( "prefetch()" );
}


