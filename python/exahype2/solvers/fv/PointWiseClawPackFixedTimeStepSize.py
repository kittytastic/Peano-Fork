# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org
from .FV                       import FV
 
from .PDETerms import PDETerms

import peano4
import exahype2

import jinja2

from peano4.toolbox.blockstructured.ReconstructPatchAndApplyFunctor import ReconstructPatchAndApplyFunctor



class UpdateCell(ReconstructPatchAndApplyFunctor):
  RiemannCallOverPatch = """
    {% if USE_SPLIT_LOOP %}
    #if Dimensions==2
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS2d_SplitLoop(
    #else
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS3d_SplitLoop(
    #endif
    {% else %}
    #if Dimensions==2
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS2d(
    #else
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS3d(
    #endif
    {% endif %}
      [&](
        const double * __restrict__                  QL,
        const double * __restrict__                  QR,
        const tarch::la::Vector<Dimensions,double>&  x,
        double                                       dx,
        double                                       t,
        double                                       dt,
        int                                          normal,
        double                                       FL[],
        double                                       FR[]
      ) -> void {
        double wave[{{NUMBER_OF_UNKNOWNS}}][{{NUMBER_OF_UNKNOWNS}}]; 
        double speed[{{NUMBER_OF_UNKNOWNS}}]; 

        int num_eqn   = {{NUMBER_OF_UNKNOWNS}};
        int num_aux   = {{NUMBER_OF_AUXILIARY_VARIABLES}};
        int num_waves = {{NUMBER_OF_UNKNOWNS}}; 

        {{CLAWPACK_RIEMANN_SOLVER}}_(
          {%if DISCRIMINATE_NORMAL %}
            &normal,
          {% endif %}   
          &num_eqn,
          &num_aux,
          &num_waves, 
          QL,                                 // double* q_l 
          QR,                                 // double* q_r
          QL+{{NUMBER_OF_UNKNOWNS}},          // double* aux_l
          QR+{{NUMBER_OF_UNKNOWNS}},          // double* aux_r
          wave,
          speed,
          FL,                                 // double* amdq
          FR                                  // double* apdq
        );

        for (int i=0; i<{{NUMBER_OF_UNKNOWNS}}; i++) {
          FL[i] = -FL[i];
        }
      },
      marker.x(),
      marker.h(),
      {{TIME_STAMP}},
      {{TIME_STEP_SIZE}},
      {{NUMBER_OF_VOLUMES_PER_AXIS}},
      {{NUMBER_OF_UNKNOWNS}},
      {{NUMBER_OF_AUXILIARY_VARIABLES}},
      reconstructedPatch,
      originalPatch
    );
  """ 


  def __init__(self,solver):
    d = {}
    solver._init_dictionary_with_default_parameters(d)
    solver.add_entries_to_text_replacement_dictionary(d)   
    d[ "USE_SPLIT_LOOP" ] = solver._use_split_loop

    ReconstructPatchAndApplyFunctor.__init__(self,
      solver._patch,
      solver._patch_overlap,
      jinja2.Template( self.RiemannCallOverPatch ).render(**d),
      solver._reconstructed_array_memory_location,
      "not marker.isRefined()"
    )
    
    self._solver = solver
  
  
  def get_includes(self):
    return """
#include "exahype2/fv/BoundaryConditions.h"
""" + self._solver._get_default_includes() + self._solver.get_user_includes() 



#! =====================================================
#subroutine rp1_ptwise(num_eqn, num_aux, num_waves, q_l, q_r, aux_l, aux_r,    &
#                       wave, s, amdq, apdq)
#! =====================================================###

#!     # Pointwise Riemann solver for the acoustics equations in 1d, with
#!     #  variable coefficients (heterogeneous media)

#! waves:     2
#! equations: 2
#! aux fields: 2


class PointWiseClawPackFixedTimeStepSize(  FV ):
  """
  
    Very simple solver that can use ClawPack's point-wise Riemann solver.
  

   The actual call of the Riemann solver has to be a simple function call
   which has the following variables available. The FL and FR is the only
   out array. All the other data are in.
   
      double QL[],
      double QR[],
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       dx,
      double                                       t,
      double                                       dt,
      int                                          normal,
      int                                          unknowns,
      int                                          auxiliaryVariables,
      double                                       FL[],
      double                                       FR[]
      
   My generic kernel requires FR and FL along the normal of the respective
   cell you look at F. That is, I need -FR compared to what ClawPack gives 
   me. Quick trial and error with the acoustics equations tells you that
   it indeed has to be -FR and not -FL.
   
   There's also the opportunity to misuse a degenerated 1d Riemann solver, i.e.
   a solver specified over a 1d array as point-wise solver.  
      
  """
  
  

  
  def __init__(self, name, patch_size, unknowns, auxiliary_variables, min_h, max_h, time_step_size, clawpack_Riemann_solver, Riemann_solver_implementation_files = [], plot_grid_properties=False, kernel_implementation = None, discriminate_normal=False):
    """
    
      Instantiate a generic FV scheme with an overlap of 1.
      
      
      Riemann_solver_implementation_files: list of strings
        These are the Fortran files the code should add to the compile.
        
        
      is_degenerated_1d_solver: Boolean
        I prefer ClawPack solvers which are written point-wisely. Alternatively, I 
        can misuse 1d solvers.  
      
    """
    FV.__init__(self, name, patch_size, 1, unknowns, auxiliary_variables, min_h, max_h, plot_grid_properties)
    
    self._time_step_size = time_step_size
    
    self._boundary_conditions_implementation  = PDETerms.User_Defined_Implementation
    self._refinement_criterion_implementation = PDETerms.Empty_Implementation
    self._initial_conditions_implementation   = PDETerms.User_Defined_Implementation

    self.clawpack_Riemann_solver             = clawpack_Riemann_solver 
    self.Riemann_solver_implementation_files = Riemann_solver_implementation_files
    
    self._discriminate_normal = discriminate_normal
    
    self._reconstructed_array_memory_location = peano4.toolbox.blockstructured.ReconstructedArrayMemoryLocation.CallStack
    self._use_split_loop                      = False

    self._patch_overlap.generator.store_persistent_condition   = self._store_face_data_default_predicate()
    self._patch_overlap.generator.load_persistent_condition    = self._load_face_data_default_predicate()

    self._patch_overlap.generator.send_condition               = "true"
    self._patch_overlap.generator.receive_and_merge_condition  = "true"

    self.set_implementation()


  def set_implementation(self,
    boundary_conditions=None,refinement_criterion=None,initial_conditions=None,
    memory_location         = None,
    use_split_loop          = False
  ):
    """
    
      Pass in None if you don't want to overwrite any default.
      
    """
    if boundary_conditions!=None:
      self._boundary_conditions_implementation        = boundary_conditions
    if refinement_criterion!=None:
      self._refinement_criterion_implementation       = refinement_criterion
    if initial_conditions!=None: 
      self._initial_conditions_implementation         = initial_conditions

    if memory_location!=None:
      self._reconstructed_array_memory_location = memory_location
    if use_split_loop!=None:
      self._use_split_loop = use_split_loop

    if self._reconstructed_array_memory_location==peano4.toolbox.blockstructured.ReconstructedArrayMemoryLocation.HeapThroughTarchWithoutDelete or \
       self._reconstructed_array_memory_location==peano4.toolbox.blockstructured.ReconstructedArrayMemoryLocation.HeapWithoutDelete or \
       self._reconstructed_array_memory_location==peano4.toolbox.blockstructured.ReconstructedArrayMemoryLocation.AcceleratorWithoutDelete:
      raise Exception( "memory mode without appropriate delete chosen, i.e. this will lead to a memory leak" )

    self._action_set_update_cell = UpdateCell(self)


  
  def add_entries_to_text_replacement_dictionary(self,d):
    """
     
     d: Dictionary of string to string
        in/out argument
    
    """
    d[ "TIME_STEP_SIZE" ]                = self._time_step_size
    d[ "TIME_STAMP" ]                    = "repositories::"+d[ "SOLVER_INSTANCE" ] + ".getMinTimeStamp()"
    
    d[ "CLAWPACK_RIEMANN_SOLVER"]        = self.clawpack_Riemann_solver

    d[ "BOUNDARY_CONDITIONS_IMPLEMENTATION"]  = self._boundary_conditions_implementation
    d[ "REFINEMENT_CRITERION_IMPLEMENTATION"] = self._refinement_criterion_implementation
    d[ "INITIAL_CONDITIONS_IMPLEMENTATION"]   = self._initial_conditions_implementation
    d[ "DISCRIMINATE_NORMAL"] = self._discriminate_normal

  
  def get_user_includes(self):
    return """
#include "exahype2/fv/Generic.h"
"""    
  
  
  def add_implementation_files_to_project(self,namespace,output):
    """
    
      Invoke add_implementation_files_to_project() of superclass and
      then add all the Fortran files to the makefile.
      
    """
    FV.add_implementation_files_to_project(self,namespace,output)
    for f in self.Riemann_solver_implementation_files:
      output.makefile.add_Fortran_file(f)
  
    
