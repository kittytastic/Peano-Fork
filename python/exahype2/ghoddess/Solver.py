# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org
import os

import peano4
import peano4.datamodel
import peano4.output.TemplatedHeaderFile
import peano4.output.TemplatedHeaderImplementationFilePair

import exahype2.grid.AMROnPatch

from .AMRKernel         import AMRKernel
from .GenericCellKernel import GenericCellKernel
from .GenericFaceKernel import GenericFaceKernel
from .PlotInPeanoBlockFormat import PlotInPeanoBlockFormat



class Solver(object):
  """ 
  An abstract Ghoddess solver
        
  """
  def __init__(self, name, order, unknowns, dimensions):
    self._name       = name
    self._order      = order
    self._unknowns   = unknowns
    self._dimensions = dimensions
    
    #
    # The division by two is due to the triangles. Sure this formula
    # is wrong for d=3 therefore. Might even be wrong for 2d with 
    # higher orders.
    #
    number_of_unknowns_within_cell = self._get_number_of_unknowns_within_cell()
    
    #
    # Again, wrong for 3d. The factor two stems from the fact that 
    # we project the solution from left and right.
    #
    number_of_unknowns_per_face    = 2 * (order+1)
    
    #
    # We map the cell's interior to a degenerated patch of the dimensions
    # number_of_unknowns_within_cell x 1 x 1. The blockstructured toolbox
    # is written for (logically) Cartesian meshes. We kind of hijack it 
    # here by embedding 1d `patches' into the cells where we are responsible
    # for the cardinalty ourselves
    #
    self._cell_data = peano4.datamodel.Patch( (number_of_unknowns_within_cell,1,1), unknowns, self._unknown_identifier() )
    self._face_data = peano4.datamodel.Patch( (2,number_of_unknowns_per_face,1), unknowns, self._unknown_identifier() )
    
    #
    # Clarify how we merge the face data along a domain decomposition boundary
    #
    self._face_data.generator.set_merge_method_definition( peano4.toolbox.blockstructured.get_face_overlap_merge_implementation(self._face_data) )
    pass
  

  def _get_number_of_unknowns_within_cell(self):
    return (self._order+1)**self._dimensions/2
  
  
  def _unknown_identifier(self):
    return self._name+"Q"
  

  def get_name_of_global_instance(self):
    return "InstanceOf" + self._name

  
  def add_to_Peano4_datamodel( self, datamodel ):
    """
    
      Add all required data to the Peano4 project's datamodel 
      so it is properly built up
      
    """
    datamodel.add_cell(self._cell_data)
    datamodel.add_face(self._face_data)
 
 
  def add_use_data_statements_to_Peano4_solver_step(self, step):
    """
     
      Inform Peano4 step which data are to be moved around via the 
      use_cell and use_face commands.
    
    """
    step.use_cell(self._cell_data)
    step.use_face(self._face_data)

  
  def __get_default_includes(self):
    return """
#include "tarch/la/Vector.h" 

#include "peano4/utils/Globals.h"

#include "SolverRepository.h"
"""


  def get_user_includes(self):
    """
  
    Use this to add include statements to the generated C++ code.
  
    """
    return ""

  AdjustCellTemplate = ""
    
  AMRTemplate = "::exahype2::RefinementCommand::Keep;"

  BoundaryTemplate = ""

  ProjectOntoFaceTemplate = ""

  SolveRiemannTemplate = ""

  SolveCellTemplate = ""

  ProjectOntoCellTemplate = ""


  def add_actions_to_create_grid(self, step):
    d = {}
    self.__init_dictionary_with_default_parameters(d)
    self.add_entries_to_text_replacement_dictionary(d)
    
    step.add_action_set( GenericCellKernel( self._cell_data, 
      "true",
      self.AdjustCellTemplate.format(**d), 
      self.__get_default_includes() + self.get_user_includes()) 
    )
    step.add_action_set( AMRKernel( self._cell_data, 
      "true",
      self.AMRTemplate.format(**d), 
      self.__get_default_includes() + self.get_user_includes(), True ))
    pass
  
  
  def add_actions_to_plot_solution(self, step):
    d = {}
    self.__init_dictionary_with_default_parameters(d)
    self.add_entries_to_text_replacement_dictionary(d)

    step.add_action_set( PlotInPeanoBlockFormat("solution" + self._name,self._get_number_of_unknowns_within_cell(),self._unknowns, self._unknown_identifier()) )
    pass
   
 
  def add_actions_to_perform_time_step(self, step):
    d = {}
    self.__init_dictionary_with_default_parameters(d)
    self.add_entries_to_text_replacement_dictionary(d)
    
    step.add_action_set( GenericCellKernel( self._cell_data, 
      d["SOLVER_INSTANCE"] + ".startNewTimeStepOnCellAndProjectOntoFace()",
      self.AdjustCellTemplate.format(**d), 
      self.__get_default_includes() + self.get_user_includes()) 
    )

    step.add_action_set( GenericCellKernel( self._cell_data, 
      d["SOLVER_INSTANCE"] + ".startNewTimeStepOnCellAndProjectOntoFace()",
      self.ProjectOntoFaceTemplate.format(**d), 
      self.__get_default_includes() + self.get_user_includes()) 
    )

    step.add_action_set( GenericFaceKernel( self._cell_data, 
      d["SOLVER_INSTANCE"] + ".solveRiemannProblem() and not fineGridFaceLabel.getBoundary()",
      self.SolveRiemannTemplate.format(**d), 
      self.__get_default_includes() + self.get_user_includes()) 
    )

    step.add_action_set( GenericFaceKernel( self._cell_data, 
      d["SOLVER_INSTANCE"] + ".solveRiemannProblem() and fineGridFaceLabel.getBoundary()",
      self.BoundaryTemplate.format(**d), 
      self.__get_default_includes() + self.get_user_includes()) 
    )

    step.add_action_set( GenericCellKernel( self._cell_data, 
      d["SOLVER_INSTANCE"] + ".solveCellProblem()",
      self.SolveCellTemplate.format(**d), 
      self.__get_default_includes() + self.get_user_includes()) 
    )

    step.add_action_set( GenericCellKernel( self._cell_data, 
      d["SOLVER_INSTANCE"] + ".projectRiemannSolutionOntoCellAndFinishTimeStepOnCell()",
      self.ProjectOntoCellTemplate.format(**d), 
      self.__get_default_includes() + self.get_user_includes()) 
    )

    step.add_action_set( AMRKernel( self._cell_data, 
      d["SOLVER_INSTANCE"] + ".projectRiemannSolutionOntoCellAndFinishTimeStepOnCell()",
      self.AMRTemplate.format(**d), 
      self.__get_default_includes() + self.get_user_includes(), False))
    pass


  def add_entries_to_text_replacement_dictionary(self,d):
    pass  

  
  def add_implementation_files_to_project(self,namespace,output):
    """
    
      makefile is an instance of peano4.output.Makefile, so you can 
      add your files to this instance.
      
    """

    templatefile_prefix = os.path.dirname( os.path.realpath(__file__) ) + "/" + self.__class__.__name__
    
    dictionary = {}
    self.__init_dictionary_with_default_parameters(dictionary)
    self.add_entries_to_text_replacement_dictionary(dictionary)
        
    generated_solver_files = peano4.output.TemplatedHeaderImplementationFilePair(
      templatefile_prefix + ".template.h",
      templatefile_prefix + ".template.cpp",
      self._name, 
      namespace,
      ".", 
      dictionary,
      True)

    output.add( generated_solver_files )
    output.makefile.add_cpp_file( self._name + ".cpp" )


  def __init_dictionary_with_default_parameters(self,d):
    d["SOLVER_INSTANCE"]    = self.get_name_of_global_instance()
    d["UNKNOWN_IDENTIFIER"] = self._unknown_identifier()
    d["NUMBER_OF_UNKNOWNS"] = self._unknowns
 
