# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org
import os

import peano4
import peano4.datamodel

import peano4.output.Jinja2TemplatedHeaderFile
import peano4.output.Jinja2TemplatedHeaderImplementationFilePair

import exahype2.grid.AMROnPatch

import jinja2
import math

from abc import abstractmethod


from enum import IntEnum


class Polynomials(IntEnum):
  """
  
   Superclass has to be IntEnum, as I use this one within Jinja2 templates
   where I struggled to compare against enum variants. I however can always
   compare against integers.
  
  """
  Gauss_Legendre = 0,
  Gauss_Lobatto = 1
  


class ADERDG(object):
  """ 
    An abstract ADER-DG solver

    Our ADER-DG solver hijacks the patch-based data structures. Topologically,
    this makes sense, as the Cartesian mesh is just distorted - depending on 
    whether you use Gauss-Lobatto or Gauss-Legendre nodes. A big semantic 
    difference can be found for the overlaps: We use an overlap of two but the 
    layer closer to the actual patch hosts a nodal representation of the 
    solution. The outer ghost layer holds a nodel representation of the solution
    gradient along the boundary.
    
    Further to the width of the overlaps, our face data always is space-time.
    For a global time stepping, this is not required, as we can directly apply
    the space-time integral. For all other routines, it is essential.
    
    We use two overlaps: one with gradient and solution, and one with the 
    outcome of the Riemann solve.
  
  
    Parallelisation:

    @todo Has to be updated
        
    I do equip both Q and NewQ with proper merge routines. However, all merge guards
    are unset by default. If you need some data exchange, you have to activate
    them manually.
  
  
    Attributes:

    @todo Has to be updated
      
    The guard variables are used within the templates and switch them on/off. By 
    default, they all are true, i.e. the actions are triggered in every grid 
    traversal an action in theory could be active.
  
  
    plot_description: string
      The description I use when I plot. By default, it is empty, but 
      some solvers add a string here that explains which entry of the 
      tuple represents which data.   
  
  """
  def __init__(self, name, order, unknowns, auxiliary_variables, polynomials, min_h, max_h, plot_grid_properties):
    """
  name: string
     A unique name for the solver. This one will be used for all generated 
     classes. Also the C++ object instance later on will incorporate this 
     name.
     
  order: int
     Order of the chosen polynomials.
     
  unknowns: int
     Number of unknowns per Finite Volume voxel.
     
  auxiliary_variables: int 
     Number of auxiliary variables per Finite Volume voxel. Eventually, both
     unknowns and auxiliary_variables are merged into one big vector if we 
     work with AoS. But the solver has to be able to distinguish them, as 
     only the unknowns are subject to a hyperbolic formulation.
     
  polynomials: Polynomials
     Type of polynomials used within the cell.
  
  min_h: double
  
  max_h: double
  
  plot_grid_properties: Boolean
     Clarifies whether a dump of the data should be enriched with grid info
     (such as enclave status flags), too.
 
    """
    if order<=0:
      raise Exception( "Order has to be positive. Order 0 is a Finite Volume scheme. Use FV solver instead")
    
    self._name                    = name
    self._patch                   = peano4.datamodel.Patch( (order,order,order),     unknowns+auxiliary_variables, self._unknown_identifier() )
    self._patch_new               = peano4.datamodel.Patch( (order,order,order),     unknowns+auxiliary_variables, self._unknown_identifier() + "New" )
    self._spacetime_patch_overlap = peano4.datamodel.Patch( (2*(order),order,order), unknowns+auxiliary_variables, self._unknown_identifier() + "SolutionExtrapolation" )
    self._Riemann_result          = peano4.datamodel.Patch( (2,order,order),         unknowns+auxiliary_variables, self._unknown_identifier() + "RiemannSolveResult" )
    
    #self._patch_overlap.generator.merge_method_definition     = peano4.toolbox.blockstructured.get_face_overlap_merge_implementation(self._patch_overlap)
    #self._patch_overlap_new.generator.merge_method_definition = peano4.toolbox.blockstructured.get_face_overlap_merge_implementation(self._patch_overlap)
    
    self._spacetime_patch_overlap.generator.includes     += """
#include "peano4/utils/Loop.h"
#include "observers/SolverRepository.h" 
"""
    self._Riemann_result.generator.includes += """
#include "peano4/utils/Loop.h"
#include "observers/SolverRepository.h" 
"""
   
    self._guard_copy_new_face_data_into_face_data  = self._predicate_face_carrying_data()
    self._guard_adjust_cell                        = self._predicate_cell_carrying_data()
    self._guard_AMR                                = self._predicate_cell_carrying_data()
    self._guard_project_patch_onto_faces           = self._predicate_cell_carrying_data()
    self._guard_update_cell                        = self._predicate_cell_carrying_data()
    self._guard_handle_boundary                    = self._predicate_boundary_face_carrying_data()

    self._order                = order
    self._min_h                = min_h
    self._max_h                = max_h 
    self._plot_grid_properties = plot_grid_properties
    
    self._unknowns             = unknowns
    self._auxiliary_variables  = auxiliary_variables
    
    #
    # All order 3. @todo Dominic your scripts. 
    #
    self._quadrature_points_over_unit_interval = [
      -1.0/5.0*math.sqrt(15) * 0.5 + 0.5,
       0                      + 0.5, 
       1.0/5.0*math.sqrt(15) * 0.5 + 0.5,
    ]
    self._quadrature_weights_over_unit_interval = [
       5.0/9.0,
       8.0/9.0, 
       5.0/9.0
    ]
    
    if min_h>max_h:
       print( "Error: min_h (" + str(min_h) + ") is bigger than max_h (" + str(max_h) + ")" )

    self._template_adjust_cell     = jinja2.Template( "" )
    self._template_AMR             = jinja2.Template( "" )
    self._template_handle_boundary = jinja2.Template( "" )
    self._template_update_cell     = jinja2.Template( "" )

    self._reconstructed_array_memory_location=peano4.toolbox.blockstructured.ReconstructedArrayMemoryLocation.CallStack
    
    self._spacetime_patch_overlap.generator.send_condition               = "false"
    self._spacetime_patch_overlap.generator.receive_and_merge_condition  = "false"

    self._Riemann_result.generator.send_condition               = "false"
    self._Riemann_result.generator.receive_and_merge_condition  = "false"

    self.plot_description = ""
    self.plot_metadata    = ""
    pass

  
  def _predicate_face_carrying_data(self):
    return "not marker.isRefined()"


  def _predicate_boundary_face_carrying_data(self):
    return "not marker.isRefined() and fineGridFaceLabel.getBoundary()"


  def _predicate_cell_carrying_data(self):
    return "not marker.isRefined()"
  
  
  def _unknown_identifier(self):
    return self._name+"Q"
  

  def get_name_of_global_instance(self):
    return "InstanceOf" + self._name

  
  def add_to_Peano4_datamodel( self, datamodel ):
    """
    
      Add all required data to the Peano4 project's datamodel 
      so it is properly built up
      
    """
    datamodel.add_cell(self._patch)
    datamodel.add_face(self._spacetime_patch_overlap)
    datamodel.add_face(self._Riemann_result)
 
 
  def add_use_data_statements_to_Peano4_solver_step(self, step):
    """
      Tell Peano what data to move around
      
      Inform Peano4 step which data are to be moved around via the 
      use_cell and use_face commands. This operation is generic from
      ExaHyPE's point of view, i.e. I use it for all grid sweep types. 
    
    """
    step.use_cell(self._patch)
    step.use_face(self._spacetime_patch_overlap)
    step.use_face(self._Riemann_result)

  
  def _get_default_includes(self):
    return """
#include "tarch/la/Vector.h" 

#include "peano4/utils/Globals.h"
#include "peano4/utils/Loop.h"

#include "SolverRepository.h"

#include "exahype2/PatchUtils.h"
#include "exahype2/fv/BoundaryConditions.h"
"""


  @abstractmethod
  def get_user_includes(self):
    """
  
    Use this to add include statements to the generated C++ code. Is there for
    subclasses to hook in.
  
    """
    return ""
  
  
  def add_actions_to_init_grid(self, step):
    d = {}
    self._init_dictionary_with_default_parameters(d)
    self.add_entries_to_text_replacement_dictionary(d)

    #step.add_action_set( peano4.toolbox.blockstructured.ApplyFunctorOnPatch(
    #  self._patch,self._template_adjust_cell.render(**d),
    #  self._guard_adjust_cell,
    #  self._get_default_includes() + self.get_user_includes()
    #))
    #step.add_action_set( peano4.toolbox.blockstructured.ProjectPatchOntoFaces(
    #  self._patch,
    #  self._patch_overlap_new,
    #  self._guard_project_patch_onto_faces, 
    #  self._get_default_includes() + self.get_user_includes()
    #))
    #step.add_action_set( peano4.toolbox.blockstructured.BackupPatchOverlap(
    #  self._patch_overlap_new,
    #  self._patch_overlap,
    #  False,
    #  self._guard_copy_new_face_data_into_face_data,
    #  self._get_default_includes() + self.get_user_includes()
    #))

    
  def add_actions_to_create_grid(self, step, evaluate_refinement_criterion):
    d = {}
    self._init_dictionary_with_default_parameters(d)
    self.add_entries_to_text_replacement_dictionary(d)
    d["IS_GRID_CREATION"] = "true"
    
    #step.add_action_set( peano4.toolbox.blockstructured.ApplyFunctorOnPatch(
    #  self._patch,self._template_adjust_cell.render(**d),
    #  self._guard_adjust_cell,
    #  self._get_default_includes() + self.get_user_includes()
    #))
    #if evaluate_refinement_criterion:
    #  step.add_action_set( exahype2.grid.AMROnPatch(
    #    self._patch,self._template_AMR.render(**d),
    #    "not marker.isRefined()", 
    #    self._get_default_includes() + self.get_user_includes()
    #  ))
    pass
  
  
  def set_plot_description(self,description,meta_data = ""):
    """
    
    description: String
       Use this one to set a description within the output patch file that tells
       the vis solver what the semantics of the entries are. Typically, I use 
       a comma-separated list here.
    
    meta_data: String
       Arbitrary text. 
    
    """
    self.plot_description = description
    self.plot_metadata    = meta_data

    
  
  def add_actions_to_plot_solution(self, step):
    d = {}
    self._init_dictionary_with_default_parameters(d)
    self.add_entries_to_text_replacement_dictionary(d)
    
    mapping = []    
    for z in self._quadrature_points_over_unit_interval:
      for y in self._quadrature_points_over_unit_interval:
        for x in self._quadrature_points_over_unit_interval:
          mapping.append( (x,y,z) )
    
    step.add_action_set( peano4.toolbox.blockstructured.PlotPatchesInPeanoBlockFormat( 
      filename="solution-" + self._name,         
      patch=self._patch,     
      dataset_name=self._unknown_identifier(), 
      description=self.plot_description,
      metadata=self.plot_metadata,
      mapping=mapping,
      plot_cell_data=False
    ))
    #step.add_action_set( peano4.toolbox.blockstructured.PlotPatchesInPeanoBlockFormat( filename="updated-solution-" + self._name, patch=self._patch_new, dataset_name=self._unknown_identifier(), description=self.plot_description ) )
    #self._patch                   = peano4.datamodel.Patch( (order+1,order+1,order+1),     unknowns+auxiliary_variables, self._unknown_identifier() )
    #self._patch                   = peano4.datamodel.Patch( (order+1,order+1,order+1),     unknowns+auxiliary_variables, self._unknown_identifier() + "New" )

    if self._plot_grid_properties:    
      step.add_action_set( peano4.toolbox.PlotGridInPeanoBlockFormat( "grid-" + self._name,None ))

    pass
   
 
  def add_actions_to_perform_time_step(self, step):
    d = {}
    self._init_dictionary_with_default_parameters(d)
    self.add_entries_to_text_replacement_dictionary(d)
    d["IS_GRID_CREATION"] = "false"


    #step.add_action_set( peano4.toolbox.blockstructured.ReconstructPatchAndApplyFunctor(
    #  self._patch,
    #  self._patch_overlap,
    #  self._template_update_cell.render(**d),
    #  self._template_handle_boundary.render(**d),
    #  self._guard_update_cell,
    #  self._guard_handle_boundary,
    #  self._get_default_includes() + self.get_user_includes() + """#include "exahype2/NonCriticalAssertions.h" 
    #      self._reconstructed_array_memory_location
    #)) 
    #step.add_action_set( peano4.toolbox.blockstructured.ProjectPatchOntoFaces(
    #  self._patch,
    #  self._patch_overlap_new,
    #  self._guard_project_patch_onto_faces,
    #  self._get_default_includes() + self.get_user_includes()
    #))
    #step.add_action_set( peano4.toolbox.blockstructured.ApplyFunctorOnPatch(
    #  self._patch,self._template_adjust_cell.render(**d),
    #  self._guard_adjust_cell,
    #  self._get_default_includes() + self.get_user_includes()
    #))
    #step.add_action_set( exahype2.grid.AMROnPatch(
    #  self._patch,self._template_AMR.render(**d),  
    #  self._guard_AMR,
    #  self._get_default_includes() + self.get_user_includes()
    #))
    #step.add_action_set( peano4.toolbox.blockstructured.BackupPatchOverlap(
    #  self._patch_overlap_new,
    #  self._patch_overlap,
    #  False,
    #  self._guard_copy_new_face_data_into_face_data,
    #  self._get_default_includes() + self.get_user_includes()
    #))
    pass


  @abstractmethod
  def add_entries_to_text_replacement_dictionary(self,d):
    pass  

  
  def add_implementation_files_to_project(self,namespace,output):
    """
    
     The ExaHyPE2 project will call this operation when it sets 
     up the overall environment.
     
     
     
     output: peano4.output.Output
      
    """

    templatefile_prefix = os.path.dirname( os.path.realpath(__file__) ) + "/" + self.__class__.__name__
    
    abstractHeaderDictionary = {}
    implementationDictionary = {}
    self._init_dictionary_with_default_parameters(abstractHeaderDictionary)
    self._init_dictionary_with_default_parameters(implementationDictionary)
    self.add_entries_to_text_replacement_dictionary(abstractHeaderDictionary)
    self.add_entries_to_text_replacement_dictionary(implementationDictionary)
        
    generated_abstract_header_file = peano4.output.Jinja2TemplatedHeaderImplementationFilePair(
      templatefile_prefix + "Abstract.template.h",
      templatefile_prefix + "Abstract.template.cpp",
      "Abstract" + self._name, 
      namespace,
      ".", 
      abstractHeaderDictionary,
      True)
    generated_solver_files = peano4.output.Jinja2TemplatedHeaderImplementationFilePair(
      templatefile_prefix + ".template.h",
      templatefile_prefix + ".template.cpp",
      self._name, 
      namespace,
      ".", 
      implementationDictionary,
      False)

    output.add( generated_abstract_header_file )
    output.add( generated_solver_files )
    output.makefile.add_cpp_file( "Abstract" + self._name + ".cpp" )
    output.makefile.add_cpp_file( self._name + ".cpp" )


  def _init_dictionary_with_default_parameters(self,d):
    """
    
    """
    #d["NUMBER_OF_VOLUMES_PER_AXIS"]     = self._patch.dim[0]
    #d["HALO_SIZE"]                      = int(self._patch_overlap.dim[0]/2)
    d["SOLVER_INSTANCE"]                = self.get_name_of_global_instance()
    d["SOLVER_NAME"]                    = self._name
    d["UNKNOWN_IDENTIFIER"]             = self._unknown_identifier()
    d["NUMBER_OF_UNKNOWNS"]             = self._unknowns
    d["NUMBER_OF_AUXILIARY_VARIABLES"]  = self._auxiliary_variables
        
    d["ORDER"]                          = self._order

    d["QUADRATURE_POINTS"]              = self._quadrature_points_over_unit_interval
    d["QUADRATURE_WEIGHTS"]             = self._quadrature_weights_over_unit_interval
        
    #if self._patch_overlap.dim[0]/2!=1:
    #  print( "ERROR: Finite Volume solver currently supports only a halo size of 1")
    #d[ "ASSERTION_WITH_1_ARGUMENTS" ] = "nonCriticalAssertion1"
    #d[ "ASSERTION_WITH_2_ARGUMENTS" ] = "nonCriticalAssertion2"
    #d[ "ASSERTION_WITH_3_ARGUMENTS" ] = "nonCriticalAssertion3"
    #d[ "ASSERTION_WITH_4_ARGUMENTS" ] = "nonCriticalAssertion4"
    #d[ "ASSERTION_WITH_5_ARGUMENTS" ] = "nonCriticalAssertion5"
    #d[ "ASSERTION_WITH_6_ARGUMENTS" ] = "nonCriticalAssertion6"
    d[ "MAX_H"] = self._min_h
    d[ "MIN_H"] = self._max_h
 
