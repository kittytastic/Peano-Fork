//
// ExaHyPE2 solver file
// Generated by Peano's Python API
// www.peano-framework.org
//
// This is generated. Don't change it! Every rerun of the Python API will
// overwrite your changes.
//
#ifndef {% for item in NAMESPACE -%}_{{ item }}{%- endfor %}_{{CLASSNAME}}_H_
#define {% for item in NAMESPACE -%}_{{ item }}{%- endfor %}_{{CLASSNAME}}_H_


#include "peano4/datamanagement/CellMarker.h"
#include "tarch/multicore/Tasks.h"


#include "exahype2/fv/Generic.h"
#include "exahype2/fv/Rusanov.h"
#include "exahype2/EnclaveBookkeeping.h"
#include "exahype2/EnclaveTask.h"
#include "peano4/parallel/Tasks.h"
#include "repositories/SolverRepository.h"


{{SOLVER_INCLUDES}}


#include <vector>


#ifdef UseSmartMPI
#include "smartmpi.h"
#endif


{% for item in NAMESPACE -%}
  namespace {{ item }} {

{%- endfor %}
  class {{CLASSNAME}};

{% for item in NAMESPACE -%}
  }
{%- endfor %}



/**
 * Single task that can also take multiple tasks and deploy them to the GPU
 *
 * @author ExaHyPE's code generator written by Holger Schulz and Tobias Weinzierl 
 */
{% if STATELESS_PDE_TERMS %}
class {{NAMESPACE | join("::")}}::{{CLASSNAME}}: public tarch::multicore::Task
{% else %}
class {{NAMESPACE | join("::")}}::{{CLASSNAME}}: public ::exahype2::EnclaveTask
{% endif %}
#ifdef UseSmartMPI
, public smartmpi::Task
#endif
{
  private:
    static tarch::logging::Log  _log;
    /**
     * This is a class attribute holding a unique integer per enclave task type.
     */
    static int                  _enclaveTaskTypeId;


    #ifdef UseSmartMPI
    /*
     * This uniquely identifies an enclave task. Unlike _enclaveTaskTypeId it
     * differentiates between tasks within a task type, not between task types.
     *
     * Crucially, the value of this ID is not necessarily the same as that of
     * tarch::multicore::Task::_id . That is because _id is reset each time
     * we move a task to another rank and reconstitute it there (see the constructor
     * of tarch::multicore::Task). Instead, _remoteTaskId tracks the ID of
     * the original task object (i.e. the task originally spawned and
     * only then moved). In smartmpi we need to keep track of the task's
     * ID so that it can be bookmarked correctly after being moved around.
     *
     * As such moveTask(...), sends _id if the task has not yet been
     * moved and _remoteTaskId if it has already been moved. Similarly,
     * _remoteTaskId is always sent when forwarding task outcomes since the
     * task will already have been moved.
     */
    int          _remoteTaskId = -1;
    #endif

    {% if STATELESS_PDE_TERMS %}
    static int                                _gpuEnclaveTaskId;

    const ::peano4::datamanagement::CellMarker   _marker;
    const double                                 _t;
    const double                                 _dt;
    double*                                      _reconstructedValues;

    #if Dimensions==2
    const int _destinationPatchSize = {{NUMBER_OF_VOLUMES_PER_AXIS}}*{{NUMBER_OF_VOLUMES_PER_AXIS}}*({{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}});
    const int _sourcePatchSize      = ({{NUMBER_OF_VOLUMES_PER_AXIS}}+2)*({{NUMBER_OF_VOLUMES_PER_AXIS}}+2)*({{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}});
    #elif Dimensions==3
    const int _destinationPatchSize = {{NUMBER_OF_VOLUMES_PER_AXIS}}*{{NUMBER_OF_VOLUMES_PER_AXIS}}*{{NUMBER_OF_VOLUMES_PER_AXIS}}*({{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}});
    const int _sourcePatchSize      = ({{NUMBER_OF_VOLUMES_PER_AXIS}}+2)*({{NUMBER_OF_VOLUMES_PER_AXIS}}+2)*({{NUMBER_OF_VOLUMES_PER_AXIS}}+2)*({{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}});
    #endif
    {% endif %}


  public:
    static void applyKernelToCell(
      const ::peano4::datamanagement::CellMarker& marker, 
      double                                      t,
      double                                      dt,
      double* __restrict__                        reconstructedPatch, 
      double* __restrict__                        targetPatch
    );
    
    
    {{CLASSNAME}}(
      const ::peano4::datamanagement::CellMarker& marker, 
      double                                      t,
      double                                      dt,
      double* __restrict__                        reconstructedPatch
    );

    bool isSmartMPITask() const override;

    #ifdef UseSmartMPI
    void runLocally() override;
    void moveTask(int rank, int tag, MPI_Comm communicator) override;
    void runLocallyAndSendTaskOutputToRank(int rank, int tag, MPI_Comm communicator) override;
    void forwardTaskOutputToRank(int rank, int tag, MPI_Comm communicator) override;

    static smartmpi::Task* receiveTask(int rank, int tag, MPI_Comm communicator);
    static smartmpi::Task* receiveOutcome(int rank, int tag, MPI_Comm communicator, const bool intentionToForward);
    #endif

    {% if STATELESS_PDE_TERMS %}
    bool run() override;
    bool fuse( const std::list<Task*>& otherTasks, int targetDevice=Host ) override;
    bool canFuse() const override;
    {% endif %}
};



#endif
