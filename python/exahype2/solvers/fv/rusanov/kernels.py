# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org
from exahype2.solvers.fv.PDETerms  import PDETerms

import jinja2

from exahype2.solvers.fv.kernels import create_empty_source_term_kernel
from exahype2.solvers.fv.kernels import create_user_defined_source_term_kernel
from dis import dis
    
    
def create_compute_time_step_size_for_fixed_time_stepping_with_subcycling( time_step_size, solver_name, remove_accumulation_errors=True ):
  result = """
  // The fixed solver's _timeStepSize scales with min volume h, i.e. it is 
  // always chosen such that the finest grid does something meaningful.
  cellTimeStepSize = repositories::{{SOLVER_INSTANCE}}.getMinPatchSize(false)>0.0 ?
    repositories::{{SOLVER_INSTANCE}}.getTimeStepSize() * marker.h()(0) / repositories::{{SOLVER_INSTANCE}}.getMinPatchSize(false) :
    0.0;
  cellTimeStamp    = fineGridCell{{SOLVER_NAME}}CellLabel.getTimeStamp();  
"""  

  if remove_accumulation_errors:
    result += """
  cellTimeStepSize = ::exahype2::removeTimeStepAccumulationErrorsFromCell( fineGridCell""" + solver_name + """CellLabel, fineGridFaces""" + solver_name + """FaceLabel, cellTimeStepSize);
"""

  return result


def create_compute_time_step_size_kernel_for_adaptive_time_stepping_with_subcycling( solver_name, remove_accumulation_errors=True ):
  result = """
  // The fixed solver's _timeStepSize scales with min volume h, i.e. it is 
  // always chosen such that the finest grid does something meaningful.
  cellTimeStepSize = repositories::{{SOLVER_INSTANCE}}.getMinPatchSize(false)>0.0 ?
    repositories::{{SOLVER_INSTANCE}}.getAdmissibleTimeStepSize() * marker.h()(0) / repositories::{{SOLVER_INSTANCE}}.getMinPatchSize(false) :
    0.0;
  cellTimeStamp    = fineGridCell{{SOLVER_NAME}}CellLabel.getTimeStamp();  
"""  

  if remove_accumulation_errors:
    result += """
  cellTimeStepSize = ::exahype2::removeTimeStepAccumulationErrorsFromCell( fineGridCell""" + solver_name + """CellLabel, fineGridFaces""" + solver_name + """FaceLabel, cellTimeStepSize);
"""

  return result


def create_compute_time_step_size_kernel_for_local_time_stepping( solver_name, time_step_relaxation ):
  result = """
  cellTimeStepSize = fineGridCell{{SOLVER_NAME}}CellLabel.getTimeStepSize();  
  cellTimeStamp    = fineGridCell{{SOLVER_NAME}}CellLabel.getTimeStamp();  

  cellTimeStepSize = ::exahype2::removeTimeStepAccumulationErrorsFromCell( fineGridCell""" + solver_name + """CellLabel, fineGridFaces""" + solver_name + """FaceLabel, cellTimeStepSize);
"""

  return result


def create_compute_time_step_size_kernel_for_adaptive_time_stepping():
  return """
  cellTimeStepSize = repositories::{{SOLVER_INSTANCE}}.getAdmissibleTimeStepSize();
  cellTimeStamp    = fineGridCell{{SOLVER_NAME}}CellLabel.getTimeStamp();
"""


def create_postprocess_updated_patch_for_local_time_stepping(time_step_relaxation, avoid_staircase_effect, discretisation_steps):
  """
  
  :: Zero eigenvalues
  
  If you solve non-linear problems, cells can have a zero eigenvalue. It means that 
  nothing happens within this cell. There are two options on the table: You can take
  the biggest global eigenvalue and march forward using this value. In ExaHyPE 2, 
  this yields a staircase effect if you have larger, regular region, then we have 
  something similar to many stencil codes which then update the cells in the middle
  again, and then those in the middle again, and so forth.
  
  We can avoid this by making a cell march if an only if one neighbour has advanced.
  In this case large global areas where nothing happens lag behind. 
  
  
  avoid_staircase_effect: Boolean
  
  """
  if discretisation_steps<=1.0:
    raise Exception( "invalid discretisation step size for local time step (val=" + str(discretisation_steps) + ")" )

  determine_eigenvalue = """
    double maxEigenvalue = ::exahype2::fv::maxEigenvalue_AoS(
      [] (
        const double * __restrict__                  Q,
        const tarch::la::Vector<Dimensions,double>&  faceCentre,
        const tarch::la::Vector<Dimensions,double>&  volumeH,
        double                                       t,
        double                                       dt,
        int                                          normal
      ) -> double {
        return repositories::{{SOLVER_INSTANCE}}.maxEigenvalue( Q, faceCentre, volumeH, t, normal);
      },
      marker.x(),
      marker.h(),
      fineGridCell{{SOLVER_NAME}}CellLabel.getTimeStamp(),
      fineGridCell{{SOLVER_NAME}}CellLabel.getTimeStepSize(),
      {{NUMBER_OF_VOLUMES_PER_AXIS}},
      {{NUMBER_OF_UNKNOWNS}},
      {{NUMBER_OF_AUXILIARY_VARIABLES}},
      targetPatch
    );
    repositories::{{SOLVER_INSTANCE}}.setMaxEigenvalue( maxEigenvalue );  
"""

  if avoid_staircase_effect:
    compute_time_step_sizes = """    
    double newTimeStepSize = 0.0;
    //const double minGlobalTimeStepSize = repositories::{{SOLVER_INSTANCE}}.getMaxEigenvalue()>0.0 ? """ + str(time_step_relaxation) + """ * repositories::{{SOLVER_INSTANCE}}.getMinVolumeSize(false) / repositories::{{SOLVER_INSTANCE}}.getMaxEigenvalue() : 0.0;
    const double minGlobalTimeStepSize = repositories::{{SOLVER_INSTANCE}}.getMinTimeStepSize()<std::numeric_limits<double>::max() ? repositories::{{SOLVER_INSTANCE}}.getMinTimeStepSize() : 0.0;
    const double maxGlobalTimeStepSize = repositories::{{SOLVER_INSTANCE}}.getMaxEigenvalue()>0.0 ? """ + str(time_step_relaxation) + """ * repositories::{{SOLVER_INSTANCE}}.getMaxVolumeSize(false) / repositories::{{SOLVER_INSTANCE}}.getMaxEigenvalue() : 0.0;
    if ( tarch::la::greater( maxEigenvalue,0.0) ) {
      newTimeStepSize = ::exahype2::discretiseAndTruncateTimeStepSizes(
        """ + str(time_step_relaxation) + """ * marker.h()(0) / {{NUMBER_OF_VOLUMES_PER_AXIS}} / maxEigenvalue,
        minGlobalTimeStepSize,
        maxGlobalTimeStepSize,
        """ + str(discretisation_steps) + """
      );
    }
    else {
      const double minTimeStampOfNeighbours = ::exahype2::getMinTimeStampOfNeighboursAhead(fineGridCell{{SOLVER_NAME}}CellLabel, fineGridFaces{{SOLVER_NAME}}FaceLabel);

      newTimeStepSize = minTimeStampOfNeighbours - fineGridCell{{SOLVER_NAME}}CellLabel.getTimeStamp();
    }
"""    
  else:
    compute_time_step_sizes = """    
    double       newTimeStepSize       = 0.0;
    //const double minGlobalTimeStepSize = repositories::{{SOLVER_INSTANCE}}.getMaxEigenvalue()>0.0 ? """ + str(time_step_relaxation) + """ * repositories::{{SOLVER_INSTANCE}}.getMinVolumeSize(false) / repositories::{{SOLVER_INSTANCE}}.getMaxEigenvalue() : 0.0;
    const double minGlobalTimeStepSize = repositories::{{SOLVER_INSTANCE}}.getMinTimeStepSize()<std::numeric_limits<double>::max() ? repositories::{{SOLVER_INSTANCE}}.getMinTimeStepSize() : 0.0;
    const double maxGlobalTimeStepSize = repositories::{{SOLVER_INSTANCE}}.getMaxEigenvalue()>0.0 ? """ + str(time_step_relaxation) + """ * repositories::{{SOLVER_INSTANCE}}.getMaxVolumeSize(false) / repositories::{{SOLVER_INSTANCE}}.getMaxEigenvalue() : 0.0;
    if ( tarch::la::greater( maxEigenvalue,0.0) ) {
      newTimeStepSize = ::exahype2::discretiseAndTruncateTimeStepSizes(
        """ + str(time_step_relaxation) + """ * marker.h()(0) / {{NUMBER_OF_VOLUMES_PER_AXIS}} / maxEigenvalue,
        minGlobalTimeStepSize,
        maxGlobalTimeStepSize,
        """ + str(discretisation_steps) + """
      );
    }
    else if ( tarch::la::greater( repositories::{{SOLVER_INSTANCE}}.getMaxEigenvalue(),0.0) ) {
      newTimeStepSize = minGlobalTimeStepSize;
    }
"""    
   
    
  set_time_step_size = """    
    if ( tarch::la::equals(newTimeStepSize,0.0) ) {
      logDebug( "touchCellFirstTime(...)", "can't do a time step on cell " << marker.toString() << " as global max eigenvalue=" << repositories::{{SOLVER_INSTANCE}}.getMaxEigenvalue() );
      fineGridCell{{SOLVER_NAME}}CellLabel.setTimeStepSize(0.0);    
    }
    else {
      fineGridCell{{SOLVER_NAME}}CellLabel.setTimeStepSize(newTimeStepSize);    
    }
"""

  return determine_eigenvalue + compute_time_step_sizes + set_time_step_size
    
    
def create_postprocess_updated_patch_for_adaptive_time_stepping():
  return """
    const double maxEigenvalue = ::exahype2::fv::maxEigenvalue_AoS(
      [] (
        const double * __restrict__                  Q,
        const tarch::la::Vector<Dimensions,double>&  faceCentre,
        const tarch::la::Vector<Dimensions,double>&  volumeH,
        double                                       t,
        double                                       dt,
        int                                          normal
      ) -> double {
        return repositories::{{SOLVER_INSTANCE}}.maxEigenvalue( Q, faceCentre, volumeH, t, normal);
      },
      marker.x(),
      marker.h(),
      cellTimeStamp,
      cellTimeStepSize,
      {{NUMBER_OF_VOLUMES_PER_AXIS}},
      {{NUMBER_OF_UNKNOWNS}},
      {{NUMBER_OF_AUXILIARY_VARIABLES}},
      targetPatch
    );
    
    repositories::{{SOLVER_INSTANCE}}.setMaxEigenvalue( maxEigenvalue );  
"""


def create_constructor_implementation_for_adaptive_time_stepping():
  return "_admissibleTimeStepSize = 0.0;"


def create_constructor_implementation_for_local_time_stepping():
  return "_maxEigenvalue = std::numeric_limits<double>::max();"
  

def create_abstract_solver_user_declarations_for_adaptive_time_stepping():
  return """
private:
  double _maxEigenvalue;
  double _admissibleTimeStepSize;
public:
  void setMaxEigenvalue( double eigenvalue );  
  /**
   * @return Admissible time step size for the current sweep, i.e. 
   *         return _admissibleTimeStepSize. This value always refers
   *         to the minimum mesh volume size. If you use subcycling,
   *         you have to scale it for cells that are not on the finest
   *         mesh resolution. 
   */
  double getAdmissibleTimeStepSize() const;  
    """  
    
    
def create_abstract_solver_user_declarations_for_local_time_stepping():
  return """
private:
  double _maxEigenvalue;
  double _maxEigenvalueOfPreviousSweep;
public:
  /**
   * @return Minimum non-zero eigenvalue. Keep in mind that the per-cell 
   *         eigenvalues can become zero for some non-linear problems (if 
   *         nothing happens), so it is important to neglect those when we
   *         take the minimum.
   */
  double getMaxEigenvalue() const;  

  void setMaxEigenvalue( double eigenvalue );
    """  
    
    
def create_abstract_solver_user_definitions_for_adaptive_time_stepping():
  return """
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::setMaxEigenvalue( double eigenvalue ) {
  if ( tarch::la::greater( eigenvalue, 0.0 ) ) {
    tarch::multicore::Lock lock(_semaphore);
    _maxEigenvalue = std::max(_maxEigenvalue,eigenvalue);
  }
}    


double {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::getAdmissibleTimeStepSize() const {
  return _admissibleTimeStepSize;
}
    """  
    
    
def create_abstract_solver_user_definitions_for_local_time_stepping():
  return """
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::setMaxEigenvalue( double eigenvalue ) {
  if ( tarch::la::greater( eigenvalue, 0.0 ) ) {
    tarch::multicore::Lock lock(_semaphore);
    _maxEigenvalue = std::max(_maxEigenvalue,eigenvalue);
  }
}    


double {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::getMaxEigenvalue() const {
  return _maxEigenvalueOfPreviousSweep;
}
    """  


def create_finish_time_step_implementation_for_local_time_stepping():
  """
  
  This routine is inserted after we have reduced all global quantities. These
  are the quantities with the postfix ThisTimeStep.
  
  """ 
  return """
  #ifdef Parallel
  double newMaxEigenvalue = _maxEigenvalue;
  tarch::mpi::Rank::getInstance().allReduce(
        &newMaxEigenvalue,
        &_maxEigenvalue,
        1,
        MPI_DOUBLE,
        MPI_MAX, 
        [&]() -> void { tarch::services::ServiceRepository::getInstance().receiveDanglingMessages(); }
        );
  #endif
  
  if ( _solverState == SolverState::Secondary ) {
    _maxEigenvalueOfPreviousSweep = _maxEigenvalue;
  }
"""
    
    
def create_finish_time_step_implementation_for_adaptive_time_stepping(time_step_relaxation):
  """
  
  This routine is inserted after we have reduced all global quantities. These
  are the quantities with the postfix ThisTimeStep.
  
  """ 
  return """
  #ifdef Parallel
  double newMaxEigenvalue = _maxEigenvalue;
  tarch::mpi::Rank::getInstance().allReduce(
        &newMaxEigenvalue,
        &_maxEigenvalue,
        1,
        MPI_DOUBLE,
        MPI_MAX, 
        [&]() -> void { tarch::services::ServiceRepository::getInstance().receiveDanglingMessages(); }
        );
  #endif

  if ( tarch::la::smaller(_maxEigenvalue, 0.0 ) ) {
    ::exahype2::triggerNonCriticalAssertion( __FILE__, __LINE__, "_maxEigenvalue>=0", "invalid max eigenvalue: " + std::to_string(_maxEigenvalue) );
    // keep time step size invariant
    // _admissibleTimeStepSize = _admissibleTimeStepSize;
  }
  else if ( tarch::la::equals(_maxEigenvalue, 0.0 ) ) {
    logWarning( "finishTimeStep(...)", "maximum eigenvalue approaches 0.0. For nonlinear PDEs, this often means the PDE becomes stationary. It could also be a bug however" ); 
    _admissibleTimeStepSize = 0.0;
  }
  else {
    const double minVolumeSize = _minVolumeHThisTimeStep;
    _admissibleTimeStepSize = """ + str(time_step_relaxation) + """ * minVolumeSize / _maxEigenvalue;
    if ( std::isnan(_admissibleTimeStepSize) or std::isinf(_admissibleTimeStepSize) ) {
      ::exahype2::triggerNonCriticalAssertion( __FILE__, __LINE__, "_admissibleTimeStepSize>0", "invalid (NaN of inf) time step size: " + std::to_string(_admissibleTimeStepSize) );
    }
    if (tarch::la::smallerEquals(_admissibleTimeStepSize,0.0,1e-10) ) {
      logWarning( "finishTimeStep(...)", "degenerated time step size of " << std::to_string(_admissibleTimeStepSize) << ". Problem might be extremely stiff (and can't be solved) or there could be a bug (h_volume=" << minVolumeSize << ")" );
    }
  }
"""


def create_source_term_kernel_for_Rusanov(source_term_implementation):
  if source_term_implementation==PDETerms.None_Implementation:
    return create_empty_source_term_kernel()
  else:
    return create_user_defined_source_term_kernel()
  
    
def create_fused_compute_Riemann_kernel_for_Rusanov(flux_implementation, ncp_implementation, source_term_implementation):
  Template = jinja2.Template( """
#if Dimensions==2
::exahype2::fv::Fusanov_2D
#elif Dimensions==3
::exahype2::fv::Fusanov_3D
#endif
  <{{NUMBER_OF_VOLUMES_PER_AXIS}},{{NUMBER_OF_UNKNOWNS}},{{NUMBER_OF_AUXILIARY_VARIABLES}},{{SOLVER_NAME}},{{SKIP_FLUX}},{{SKIP_NCP}},{{SKIP_SOURCE_TERM}}>
""", undefined=jinja2.DebugUndefined)
  
  d= {}
  if flux_implementation==PDETerms.None_Implementation or flux_implementation==PDETerms.Empty_Implementation:
    d[ "SKIP_FLUX"] = "true"
  else:
    d[ "SKIP_FLUX"] = "false"
  if ncp_implementation==PDETerms.None_Implementation or ncp_implementation==PDETerms.Empty_Implementation:
    d[ "SKIP_NCP"]  = "true"
  else:
    d[ "SKIP_NCP"] = "false"
  if source_term_implementation==PDETerms.None_Implementation or source_term_implementation==PDETerms.Empty_Implementation:
    d[ "SKIP_SOURCE_TERM"]  = "true"
  else:
    d[ "SKIP_SOURCE_TERM"] = "false"
  return Template.render(**d)
    
    
def create_compute_Riemann_kernel_for_Rusanov(flux_implementation, ncp_implementation):
  Template = jinja2.Template( """
        ::exahype2::fv::splitRusanov1d(
          [] (
            const double * __restrict__                  Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double                                       F[]
          ) -> void {
            {% if FLUX_IMPLEMENTATION=="<none>" %}
            std::fill_n(F,{{NUMBER_OF_UNKNOWNS}},0.0);
            {% else %}
            repositories::{{SOLVER_INSTANCE}}.flux( Q, faceCentre, volumeH, t, normal, F );
            {% endif %}
          },
          [] (
            const double * __restrict__                  Q,
            const double * __restrict__                  deltaQ,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double                                       BgradQ[]
          ) -> void {
            {% if NCP_IMPLEMENTATION!="<none>" %}
            repositories::{{SOLVER_INSTANCE}}.nonconservativeProduct( Q, deltaQ, faceCentre, volumeH, t, normal, BgradQ );
            {% else %}
            std::fill_n(BgradQ,{{NUMBER_OF_UNKNOWNS}},0.0);
            {% endif %}
          },
          [] (
            const double * __restrict__                  Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal
          ) -> double {
            return repositories::{{SOLVER_INSTANCE}}.maxEigenvalue( Q, faceCentre, volumeH, t, normal);
          },
          QL, QR, x, dx, t, dt, normal,
          {{NUMBER_OF_UNKNOWNS}},
          {{NUMBER_OF_AUXILIARY_VARIABLES}},
          FL,FR,
          {% if FLUX_IMPLEMENTATION=="<none>" %}
          true,
          {% else %}
          false,
          {% endif %}
          {% if NCP_IMPLEMENTATION=="<none>" %}
          true
          {% else %}
          false
          {% endif %}
        );
""", undefined=jinja2.DebugUndefined)
  
  d= {}
  d[ "FLUX_IMPLEMENTATION"]                 = flux_implementation
  d[ "NCP_IMPLEMENTATION"]                  = ncp_implementation
  return Template.render(**d)


def create_abstract_solver_declarations(flux_implementation, ncp_implementation, eigenvalues_implementation, source_term_implementation, stateless_pde_terms):
  Template = jinja2.Template( """
  public:
    {% if EIGENVALUES_IMPLEMENTATION=="<none>" %}
    #error eigenvalue implementation cannot be none
    {% endif %}
    
    {% if EIGENVALUES_IMPLEMENTATION!="<user-defined>" and STATELESS_PDE_TERMS %}
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
    static double maxEigenvalue(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      Offloadable
    );
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
    {% endif %}
    
    /**
     * Determine max eigenvalue over Jacobian in a given point with solution values
     * (states) Q. All parameters are in.
     *
     * @return Max eigenvalue. Result has to be positive, so we are actually speaking
     *   about the maximum absolute eigenvalue.
     */
    virtual double maxEigenvalue(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal
    ) {% if EIGENVALUES_IMPLEMENTATION=="<user-defined>" %}= 0{% else %} final{% endif %};


    {% if FLUX_IMPLEMENTATION!="<user-defined>" and STATELESS_PDE_TERMS %}
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
    static void flux(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__                        F, // F[{{NUMBER_OF_UNKNOWNS}}]
      Offloadable
    );
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
    {% endif %}
    
    {% if FLUX_IMPLEMENTATION!="<none>" %}
    virtual void flux(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__ F // F[{{NUMBER_OF_UNKNOWNS}}]
    ) {% if FLUX_IMPLEMENTATION=="<user-defined>" %}=0{% else %} final {% endif %};
    {% endif %}


    {% if NCP_IMPLEMENTATION!="<user-defined>" and STATELESS_PDE_TERMS %}
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
    static void nonconservativeProduct(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const double * __restrict__             deltaQ, // [{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__                        BgradQ, // BgradQ[{{NUMBER_OF_UNKNOWNS}}]
      Offloadable
    );
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
    {% endif %}
    
    {% if NCP_IMPLEMENTATION!="<none>" %}
    virtual void nonconservativeProduct(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const double * __restrict__             deltaQ, // [{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__ BgradQ // BgradQ[{{NUMBER_OF_UNKNOWNS}}]
    ) {% if NCP_IMPLEMENTATION=="<user-defined>" %}=0{% endif %};
    {% endif %}
    

    {% if SOURCE_TERM_IMPLEMENTATION!="<user-defined>" and STATELESS_PDE_TERMS %}
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
    static void sourceTerm(
      const double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      double                                       dt,
      double * __restrict__ S,
      Offloadable
    );
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
    {% endif %}
    
    {% if SOURCE_TERM_IMPLEMENTATION!="<none>" %}
    virtual void sourceTerm(
      const double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      double                                       dt,
      double * __restrict__ S
    ) {% if SOURCE_TERM_IMPLEMENTATION=="<user-defined>" %}= 0{% else %} final {% endif %};
    {% endif %}

""", undefined=jinja2.DebugUndefined)

  d= {}
  d[ "FLUX_IMPLEMENTATION"]                 = flux_implementation
  d[ "NCP_IMPLEMENTATION"]                  = ncp_implementation
  d[ "EIGENVALUES_IMPLEMENTATION"]          = eigenvalues_implementation
  d[ "SOURCE_TERM_IMPLEMENTATION"]          = source_term_implementation
  d[ "STATELESS_PDE_TERMS"]                             = stateless_pde_terms
  return Template.render(**d)


def create_abstract_solver_definitions(flux_implementation, ncp_implementation, eigenvalues_implementation, source_term_implementation, stateless_pde_terms):
  Template = jinja2.Template( """
{% if EIGENVALUES_IMPLEMENTATION!="<user-defined>" and EIGENVALUES_IMPLEMENTATION!="<none>" %}
double {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::maxEigenvalue(
  const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal
) {
  {{EIGENVALUES_IMPLEMENTATION}}
}
{% endif %}


{% if FLUX_IMPLEMENTATION!="<none>" and FLUX_IMPLEMENTATION!="<user-defined>" %}
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::flux(
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


{% if NCP_IMPLEMENTATION!="<none>" and NCP_IMPLEMENTATION!="<user-defined>" %}
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::nonconservativeProduct(
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


{% if SOURCE_TERM_IMPLEMENTATION!="<user-defined>" and SOURCE_TERM_IMPLEMENTATION!="<none>" %}
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::sourceTerm(
  const double * __restrict__                  Q,
  const tarch::la::Vector<Dimensions,double>&  volumeCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  double                                       dt,
  double * __restrict__                        S
) {
  {% if SOURCE_TERM_IMPLEMENTATION!="<empty>" %}
  {{SOURCE_TERM_IMPLEMENTATION}}
  {% else %}
  std::fill_n(S,{{NUMBER_OF_UNKNOWNS}},0.0);
  {% endif %}
}
{% endif %}



{% if EIGENVALUES_IMPLEMENTATION!="<user-defined>" and STATELESS_PDE_TERMS %}
#if defined(OpenMPGPUOffloading)
#pragma omp declare target
#endif
double {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::maxEigenvalue(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      Offloadable
) {
  {{EIGENVALUES_IMPLEMENTATION}};
}
#if defined(OpenMPGPUOffloading)
#pragma omp end declare target
#endif
{% endif %}


{% if FLUX_IMPLEMENTATION!="<user-defined>" and STATELESS_PDE_TERMS %}
#if defined(OpenMPGPUOffloading)
#pragma omp declare target
#endif
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::flux(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__                        F, // F[{{NUMBER_OF_UNKNOWNS}}]
      Offloadable
) {
  {% if FLUX_IMPLEMENTATION=="<none>" %}
  abort();
  {% else %}
  {{FLUX_IMPLEMENTATION}}
  {% endif %}
}
#if defined(OpenMPGPUOffloading)
#pragma omp end declare target
#endif
{% endif %}


{% if NCP_IMPLEMENTATION!="<user-defined>" and STATELESS_PDE_TERMS %}
#if defined(OpenMPGPUOffloading)
#pragma omp declare target
#endif
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::nonconservativeProduct(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const double * __restrict__             deltaQ, // [{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__                        BgradQ, // BgradQ[{{NUMBER_OF_UNKNOWNS}}]
      Offloadable
) {
  {% if NCP_IMPLEMENTATION=="<none>" %}
  abort();
  {% else %}
  {{NCP_IMPLEMENTATION}}
  {% endif %}
}
#if defined(OpenMPGPUOffloading)
#pragma omp end declare target
#endif
{% endif %}


{% if SOURCE_TERM_IMPLEMENTATION!="<user-defined>" and STATELESS_PDE_TERMS %}
#if defined(OpenMPGPUOffloading)
#pragma omp declare target
#endif
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::sourceTerm(
      const double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      double                                       dt,
      double * __restrict__ S,
      Offloadable
) {
  {% if SOURCE_TERM_IMPLEMENTATION=="<none>" %}
  abort();
  {% else %}
  {{SOURCE_TERM_IMPLEMENTATION}}
  {% endif %}
}
#if defined(OpenMPGPUOffloading)
#pragma omp end declare target
#endif
{% endif %}
""", undefined=jinja2.DebugUndefined)

  d= {}
  d[ "FLUX_IMPLEMENTATION"]                 = flux_implementation
  d[ "NCP_IMPLEMENTATION"]                  = ncp_implementation
  d[ "EIGENVALUES_IMPLEMENTATION"]          = eigenvalues_implementation
  d[ "SOURCE_TERM_IMPLEMENTATION"]          = source_term_implementation
  d[ "STATELESS_PDE_TERMS"]                             = stateless_pde_terms  
  return Template.render(**d)


def create_solver_declarations(flux_implementation, ncp_implementation, eigenvalues_implementation, source_term_implementation, stateless_pde_terms):
  Template = jinja2.Template( """
  public:
    {% if SOURCE_TERM_IMPLEMENTATION=="<user-defined>" %}
    void sourceTerm(
      const double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      double                                       dt,
      double * __restrict__ S
    ) override;
    {% endif %}

    {% if EIGENVALUES_IMPLEMENTATION=="<user-defined>" %}
    /**
     * Determine max eigenvalue over Jacobian in a given point with solution values
     * (states) Q. All parameters are in.
     *
     * @return Max eigenvalue. Result has to be positive, so we are actually speaking
     *   about the maximum absolute eigenvalue.
     */
    virtual double maxEigenvalue(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal
    ) override;
    {% endif %}


    {% if FLUX_IMPLEMENTATION=="<user-defined>" %}
    virtual void flux(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__ F // F[{{NUMBER_OF_UNKNOWNS}}]
    ) override;
    {% endif %}
     
     
    {% if NCP_IMPLEMENTATION=="<user-defined>" %}
    virtual void nonconservativeProduct(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const double * __restrict__             deltaQ, // [{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__ BgradQ // BgradQ[{{NUMBER_OF_UNKNOWNS}}]
    ) override;
    {% endif %}
    
   
    {% if STATELESS_PDE_TERMS  and SOURCE_TERM_IMPLEMENTATION=="<user-defined>" %}
    // The GPU offloading requires static functions, we do the
    // TBB trick of overloading static functions with an enum
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
     static void sourceTerm(
       const double * __restrict__ Q,
       const tarch::la::Vector<Dimensions,double>&  volumeCentre,
       const tarch::la::Vector<Dimensions,double>&  volumeH,
       double                                       t,
       double                                       dt,
       double * __restrict__ S,
       Offloadable
     );
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
    {% endif %}


    {% if EIGENVALUES_IMPLEMENTATION=="<user-defined>" and STATELESS_PDE_TERMS %}
    /**
     * Determine max eigenvalue over Jacobian in a given point with solution values
     * (states) Q. All parameters are in.
     *
     * @return Max eigenvalue. Result has to be positive, so we are actually speaking
     *   about the maximum absolute eigenvalue.
     */
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
    static double maxEigenvalue(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      Offloadable
    );
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
    {% endif %}


    {% if STATELESS_PDE_TERMS  and FLUX_IMPLEMENTATION=="<user-defined>" %}
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
    static void flux(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__                        F, // F[{{NUMBER_OF_UNKNOWNS}}]
      Offloadable
    );
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
    {% endif %}
     
   
    {% if STATELESS_PDE_TERMS  and NCP_IMPLEMENTATION=="<user-defined>" %}
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
    static void nonconservativeProduct(
      const double * __restrict__                  Q,         // Q[5+0],
      const double * __restrict__                  deltaQ,    // [5+0]
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__                        BgradQ,     // BgradQ[5]
      Offloadable
    );
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
    {% endif %}    
""", undefined=jinja2.DebugUndefined)
  d= {}
  d[ "FLUX_IMPLEMENTATION"]                 = flux_implementation
  d[ "NCP_IMPLEMENTATION"]                  = ncp_implementation
  d[ "EIGENVALUES_IMPLEMENTATION"]          = eigenvalues_implementation
  d[ "SOURCE_TERM_IMPLEMENTATION"]          = source_term_implementation
  d[ "STATELESS_PDE_TERMS"]                             = stateless_pde_terms  
  return Template.render(**d)


def create_solver_definitions(flux_implementation, ncp_implementation, eigenvalues_implementation, source_term_implementation, stateless_pde_terms):
  Template = jinja2.Template( """
{% if EIGENVALUES_IMPLEMENTATION=="<user-defined>" %}
double {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::maxEigenvalue(
  const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal
)  {
  logTraceInWith4Arguments( "maxEigenvalue(...)", faceCentre, volumeH, t, normal );
  // @todo implement
  logTraceOut( "maxEigenvalue(...)" );
}
{% endif %}


{% if FLUX_IMPLEMENTATION=="<user-defined>" %}
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::flux(
  const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal,
  double * __restrict__ F // F[{{NUMBER_OF_UNKNOWNS}}]
)  {
  logTraceInWith4Arguments( "flux(...)", faceCentre, volumeH, t, normal );
  // @todo implement
  logTraceOut( "flux(...)" );
}
{% endif %}


{% if NCP_IMPLEMENTATION=="<user-defined>" %}
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::nonconservativeProduct(
  const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  const double * __restrict__             deltaQ, // [{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal,
  double * __restrict__ BgradQ // BgradQ[{{NUMBER_OF_UNKNOWNS}}]
)  {
  logTraceInWith4Arguments( "nonconservativeProduct(...)", faceCentre, volumeH, t, normal );
  // @todo implement
  logTraceOut( "nonconservativeProduct(...)" );
}
{% endif %}


{% if SOURCE_TERM_IMPLEMENTATION=="<user-defined>" %}
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::sourceTerm(
  const double * __restrict__                  Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
  const tarch::la::Vector<Dimensions,double>&  volumeX,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  double                                       dt,
  double * __restrict__                        S  // S[{{NUMBER_OF_UNKNOWNS}}
) {
  logTraceInWith4Arguments( "sourceTerm(...)", volumeX, volumeH, t, dt );
  // @todo implement
  logTraceOut( "sourceTerm(...)" );
}
{% endif %}





{% if EIGENVALUES_IMPLEMENTATION=="<user-defined>" and STATELESS_PDE_TERMS %}
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
double {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::maxEigenvalue(
  const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal,
  Offloadable
)  {
  // @todo implement
}
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
{% endif %}


{% if FLUX_IMPLEMENTATION=="<user-defined>" and STATELESS_PDE_TERMS %}
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::flux(
  const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal,
  double * __restrict__ F,
  Offloadable
)  {
  // @todo implement
}
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
{% endif %}


{% if NCP_IMPLEMENTATION=="<user-defined>" and STATELESS_PDE_TERMS %}
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::nonconservativeProduct(
  const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
  const double * __restrict__             deltaQ, // [{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal,
  double * __restrict__ BgradQ,
  Offloadable
)  {
  // @todo implement
}
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
{% endif %}



{% if SOURCE_TERM_IMPLEMENTATION=="<user-defined>" and STATELESS_PDE_TERMS %}
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
void {{FULL_QUALIFIED_NAMESPACE}}::{{CLASSNAME}}::sourceTerm(
  const double * __restrict__ Q,
  const tarch::la::Vector<Dimensions,double>&  volumeCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  double                                       dt,
  double * __restrict__ S,
  Offloadable
) {
  // @todo implement
}
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
{% endif %}


""", undefined=jinja2.DebugUndefined)
  d= {}
  d[ "FLUX_IMPLEMENTATION"]                 = flux_implementation
  d[ "NCP_IMPLEMENTATION"]                  = ncp_implementation
  d[ "EIGENVALUES_IMPLEMENTATION"]          = eigenvalues_implementation
  d[ "SOURCE_TERM_IMPLEMENTATION"]          = source_term_implementation
  d[ "STATELESS_PDE_TERMS"]                             = stateless_pde_terms  
  return Template.render(**d)


