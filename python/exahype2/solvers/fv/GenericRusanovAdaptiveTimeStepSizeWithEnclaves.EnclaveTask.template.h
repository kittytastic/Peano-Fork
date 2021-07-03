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
class {{NAMESPACE | join("::")}}::{{CLASSNAME}}: public ::exahype2::EnclaveTask
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
    int          _remoteTaskId;
    #endif
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

    static smartmpi::Task* receiveTask(int rank, int tag, MPI_Comm communicator);
    static smartmpi::Task* receiveOutcome(int rank, int tag, MPI_Comm communicator);
    #endif
};



#endif
