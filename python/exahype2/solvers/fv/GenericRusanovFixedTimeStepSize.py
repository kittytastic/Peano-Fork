# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org
from .FV                       import FV
 
from .PDETerms import PDETerms

import peano4
import exahype2

import jinja2

from peano4.toolbox.blockstructured.ReconstructPatchAndApplyFunctor import ReconstructPatchAndApplyFunctor



class UpdateCell(ReconstructPatchAndApplyFunctor):
  """
  
    This is the straightforward implementation.
    
  """
  CellUpdateImplementation_NestedLoop = """
    #if Dimensions==2
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS2d
    #else
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS3d
    #endif
  """


  CellUpdateImplementation_SplitLoop = """
    #if Dimensions==2
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS2d_SplitLoop
    #else
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS3d_SplitLoop
    #endif
  """
  
  RusanovCallWithFlux = """
      [&](
        double                                       QL[],
        double                                       QR[],
        const tarch::la::Vector<Dimensions,double>&  x,
        double                                       dx,
        double                                       t,
        double                                       dt,
        int                                          normal,
        double                                       FL[],
        double                                       FR[]
      ) -> void {
        ::exahype2::fv::splitRusanov1d(
          [] (
            double                                       Q[],
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double                                       F[]
          ) -> void {
            {{SOLVER_INSTANCE}}.flux( Q, faceCentre, volumeH, t, normal, F );
          },
          [] (
            double                                       Q[],
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal
          ) -> double {
            return {{SOLVER_INSTANCE}}.maxEigenvalue( Q, faceCentre, volumeH, t, normal);
          },
          QL, QR, x, dx, t, dt, normal,
          {{NUMBER_OF_UNKNOWNS}},
          {{NUMBER_OF_AUXILIARY_VARIABLES}},
          FL,FR
        );
      },
"""


  """
  
    Flux is empty here.
    
  """
  RusanovCallWithNCP = """
      [&](
        double                                       QL[],
        double                                       QR[],
        const tarch::la::Vector<Dimensions,double>&  x,
        double                                       dx,
        double                                       t,
        double                                       dt,
        int                                          normal,
        double                                       FL[],
        double                                       FR[]
      ) -> void {
        ::exahype2::fv::splitRusanov1d(
          [] (
           double * __restrict__ Q,
           const tarch::la::Vector<Dimensions,double>&  faceCentre,
           const tarch::la::Vector<Dimensions,double>&  volumeH,
           double                                       t,
           double                                       dt,
           int                                          normal,
           double * __restrict__                        F
          ) -> void {
            for (int i=0; i<{{NUMBER_OF_UNKNOWNS}}; i++) F[i] = 0.0;
          },
          [] (
            double                                       Q[],
            double                                       gradQ[][Dimensions],
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double                                       BgradQ[]
          ) -> void {
            {{SOLVER_INSTANCE}}.nonconservativeProduct( Q, gradQ, faceCentre, volumeH, t, normal, BgradQ );
          },
          [] (
            double                                       Q[],
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal
          ) -> double {
            return {{SOLVER_INSTANCE}}.maxEigenvalue( Q, faceCentre, volumeH, t, normal);
          },
          QL, QR, x, dx, t, dt, normal,
          {{NUMBER_OF_UNKNOWNS}},
          {{NUMBER_OF_AUXILIARY_VARIABLES}},
          FL,FR
        );
      },
"""


  """
  
    Combination of the two previous ones.
    
  """
  RusanovCallWithFluxAndNCP = """
      [&](
        double                                       QL[],
        double                                       QR[],
        const tarch::la::Vector<Dimensions,double>&  x,
        double                                       dx,
        double                                       t,
        double                                       dt,
        int                                          normal,
        double                                       FL[],
        double                                       FR[]
      ) -> void {
        ::exahype2::fv::splitRusanov1d(
          [] (
           double * __restrict__ Q,
           const tarch::la::Vector<Dimensions,double>&  faceCentre,
           const tarch::la::Vector<Dimensions,double>&  volumeH,
           double                                       t,
           double                                       dt,
           int                                          normal,
           double * __restrict__                        F
          ) -> void {
            {{SOLVER_INSTANCE}}.flux( Q, faceCentre, volumeH, t, normal, F );
          },
          [] (
            double                                       Q[],
            double                                       gradQ[][Dimensions],
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double                                       BgradQ[]
          ) -> void {
            {{SOLVER_INSTANCE}}.nonconservativeProduct( Q, gradQ, faceCentre, volumeH, t, normal, BgradQ );
          },
          [] (
            double                                       Q[],
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal
          ) -> double {
            return {{SOLVER_INSTANCE}}.maxEigenvalue( Q, faceCentre, volumeH, t, normal);
          },
          QL, QR, x, dx, t, dt, normal,
          {{NUMBER_OF_UNKNOWNS}},
          {{NUMBER_OF_AUXILIARY_VARIABLES}},
          FL,FR
        );
      },
"""


 
  FunctionCallArguments = """
      marker.x(),
      marker.h(),
      {{TIME_STAMP}},
      {{TIME_STEP_SIZE}},
      {{NUMBER_OF_VOLUMES_PER_AXIS}},
      {{NUMBER_OF_UNKNOWNS}},
      {{NUMBER_OF_AUXILIARY_VARIABLES}},
      reconstructedPatch,
      originalPatch
  """ 


  def __init__(self,solver):
    if solver._use_split_loop:
      loop_body = self.CellUpdateImplementation_SplitLoop
    else:
      loop_body = self.CellUpdateImplementation_NestedLoop
    
    loop_body += "("
    
    if solver._flux_implementation!=PDETerms.None_Implementation   and solver._ncp_implementation==PDETerms.None_Implementation:
      loop_body += self.RusanovCallWithFlux
    elif solver._flux_implementation==PDETerms.None_Implementation and solver._ncp_implementation!=PDETerms.None_Implementation:
      loop_body += self.RusanovCallWithNCP
    elif solver._flux_implementation!=PDETerms.None_Implementation and solver._ncp_implementation!=PDETerms.None_Implementation:
      loop_body += self.RusanovCallWithFluxAndNCP
    
    loop_body += self.FunctionCallArguments
    loop_body += ");"
    
    d = {}
    solver._init_dictionary_with_default_parameters(d)
    solver.add_entries_to_text_replacement_dictionary(d)      

    ReconstructPatchAndApplyFunctor.__init__(self,
      solver._patch,
      solver._patch_overlap,
      jinja2.Template( loop_body ).render(**d),
      solver._reconstructed_array_memory_location,
      "not marker.isRefined()"
    )
    
    self._solver = solver
  
  
  def get_includes(self):
    return """
#include "exahype2/fv/BoundaryConditions.h"
""" + self._solver._get_default_includes() + self._solver.get_user_includes() 
  




class GenericRusanovFixedTimeStepSize( FV ):
  """
  
    Probably the simplest solver you could think off. There's a few
    interesting things to try out with this one nevertheless: You 
    can inject symbolic flux/pde term implementations, or you can 
    alter the implementation variant of the cell update kernel. The
    latter can be combined with different dynamic memory allocation 
    schemes and thus offers quite some opportunities to tweak and 
    tune things. 
  
  """
    

  def __init__(self, name, patch_size, unknowns, auxiliary_variables, min_h, max_h, time_step_size, flux=PDETerms.User_Defined_Implementation, ncp=None, plot_grid_properties=False):
    """

      Instantiate a generic FV scheme with an overlap of 1.

    """
    FV.__init__(self, name, patch_size, 1, unknowns, auxiliary_variables, min_h, max_h, plot_grid_properties)

    self._time_step_size = time_step_size

    self._flux_implementation                 = PDETerms.None_Implementation
    self._ncp_implementation                  = PDETerms.None_Implementation
    self._eigenvalues_implementation          = PDETerms.User_Defined_Implementation
    self._boundary_conditions_implementation  = PDETerms.User_Defined_Implementation
    self._refinement_criterion_implementation = PDETerms.Empty_Implementation
    self._initial_conditions_implementation   = PDETerms.User_Defined_Implementation

    self._patch_overlap.generator.send_condition               = "not marker.isRefined() and observers::" + self.get_name_of_global_instance() + ".getSolverState()!=" + self._name + "::SolverState::GridConstruction"
    self._patch_overlap.generator.receive_and_merge_condition  = "not marker.isRefined() and " \
      "observers::" + self.get_name_of_global_instance() + ".getSolverState()!=" + self._name + "::SolverState::GridConstruction and " + \
      "observers::" + self.get_name_of_global_instance() + ".getSolverState()!=" + self._name + "::SolverState::GridInitialisation"

    self._reconstructed_array_memory_location = peano4.toolbox.blockstructured.ReconstructedArrayMemoryLocation.CallStack
    self._use_split_loop                      = False

    self._patch_overlap.generator.store_persistent_condition   = "true"
    self._patch_overlap.generator.load_persistent_condition    = "true"

    self._patch_overlap.generator.send_condition               = "true"
    self._patch_overlap.generator.receive_and_merge_condition  = "true"
    
    #self._patch_overlap_new.generator.store_persistent_condition   = "true"
    #self._patch_overlap_new.generator.load_persistent_condition    = "true"

    self.set_implementation(flux=flux,ncp=ncp)


  def set_implementation(self,
    flux=None,ncp=None,eigenvalues=None,boundary_conditions=None,refinement_criterion=None,initial_conditions=None,
    memory_location         = peano4.toolbox.blockstructured.ReconstructedArrayMemoryLocation.CallStack,
    use_split_loop          = False
  ):
    """
      If you pass in User_Defined, then the generator will create C++ stubs 
      that you have to befill manually. If you pass in None_Implementation, it 
      will create nop, i.e. no implementation or defaults. Any other string
      is copied 1:1 into the implementation. If you pass in None, then the 
      set value so far won't be overwritten.
      
      Please note that not all options are supported by all solvers. You 
      cannot set ncp and fluxes for the ClawPack Riemann solvers, e.g.
    """
    if flux!=None:
      self._flux_implementation                       = flux
    if ncp!=None:
      self._ncp_implementation                        = ncp
    if eigenvalues!=None:    
      self._eigenvalues_implementation                = eigenvalues
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
     
      
  def get_user_includes(self):
    return """
#include "exahype2/fv/Generic.h"
#include "exahype2/fv/Rusanov.h"
"""    
    
  
  def add_entries_to_text_replacement_dictionary(self,d):
    """
     
     d: Dictionary of string to string
        in/out argument
    
    """
    d[ "TIME_STEP_SIZE" ]               = self._time_step_size
    d[ "TIME_STAMP" ]                   = d[ "SOLVER_INSTANCE" ] + ".getMinTimeStamp()"
    
    d[ "FLUX_IMPLEMENTATION"]                 = self._flux_implementation
    d[ "NCP_IMPLEMENTATION"]                  = self._ncp_implementation
    d[ "EIGENVALUES_IMPLEMENTATION"]          = self._eigenvalues_implementation
    d[ "BOUNDARY_CONDITIONS_IMPLEMENTATION"]  = self._boundary_conditions_implementation
    d[ "REFINEMENT_CRITERION_IMPLEMENTATION"] = self._refinement_criterion_implementation
    d[ "INITIAL_CONDITIONS_IMPLEMENTATION"]   = self._initial_conditions_implementation

