# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org

from .AbstractFVActionSet import AbstractFVActionSet

import peano4
import jinja2

class AdaptivityCriterion(AbstractFVActionSet):
  """
  
  The action set to realise AMR
  
  AMR is a multistep process in ExaHyPE. Most of the relevant documentation 
  on it is documented in the class exahype2::RefinementControl. As it is a 
  multistep algorithm, it is also clear even observers that do not want AMR
  have to include this action set - though with a context-specific choice 
  of boolean flags.
  
  There are different phases in ExaHyPE: grid generation (either with 
  refinement or without), initialisation, plotting and time stepping. It 
  depends on your solver in which time stepping to use AMR, but the there
  are some things to take into account:
  
  - The grid creation does already create all volumetric data as we have to
    evaluate the refinement criteria. There is however no need to manage all
    face data et al in this step, as we have a dedicated init sweep after 
    the grid generation has terminated.
  - The plotting usually has to implement AMR as we have a multi-stage 
    adaptive refinement. It might not re-evalutae the AMR again, as the 
    solution is not changed.
  
  """
  
  
  TemplateAMR = """  
  logTraceInWith2Arguments( "touchCellFirstTime(...)", marker.willBeRefined(), marker.hasBeenRefined() );

  ::exahype2::RefinementCommand refinementCriterion = ::exahype2::getDefaultRefinementCommand();

  if ( 
    not marker.willBeRefined() 
    and
    tarch::la::equals(repositories::{{SOLVER_INSTANCE}}.getMinTimeStamp(),0.0)  
    and
    tarch::la::greater( tarch::la::max( marker.h() ), repositories::{{SOLVER_INSTANCE}}.MaxAdmissiblePatchH) 
  ) {
    refinementCriterion = ::exahype2::RefinementCommand::Refine;
  } 
  else if ( 
    {{PREDICATE}}
    and
    not marker.willBeRefined() 
    and
    tarch::la::greater( tarch::la::max( marker.h() ), repositories::{{SOLVER_INSTANCE}}.MaxAdmissiblePatchH) 
  ) {
    refinementCriterion = ::exahype2::RefinementCommand::Refine;
  } 
  else if ( not marker.willBeRefined() and tarch::la::equals(repositories::{{SOLVER_INSTANCE}}.getMinTimeStamp(),0.0)  ) { 
    int index = 0;
    dfor( volume, {{NUMBER_OF_VOLUMES_PER_AXIS}} ) {
        refinementCriterion = refinementCriterion and repositories::{{SOLVER_INSTANCE}}.refinementCriterion(
          fineGridCell{{UNKNOWN_IDENTIFIER}}.value + index,
          ::exahype2::getVolumeCentre( marker.x(), marker.h(), {{NUMBER_OF_VOLUMES_PER_AXIS}}, volume), 
          ::exahype2::getVolumeSize( marker.h(), {{NUMBER_OF_VOLUMES_PER_AXIS}} ),
          0.0
        );
        index += {{NUMBER_OF_UNKNOWNS}} + {{NUMBER_OF_AUXILIARY_VARIABLES}};
    }
     
    if (refinementCriterion==::exahype2::RefinementCommand::Refine and tarch::la::max( marker.h() ) < repositories::{{SOLVER_INSTANCE}}.MinAdmissiblePatchH ) {
      refinementCriterion = ::exahype2::RefinementCommand::Keep;
    } 
    else if (refinementCriterion==::exahype2::RefinementCommand::Erase ) {
      logDebug( "touchCellFirstTime(...)", "drop coarsen instructions, as we are in initial grid setup phase" );
      refinementCriterion = ::exahype2::RefinementCommand::Keep;
    } 
  }
  else if ( 
    {{PREDICATE}}
    and
    fineGridCell{{CELL_LABEL_NAME}}.getHasUpdated()
  ) { 
    int index = 0;
    dfor( volume, {{NUMBER_OF_VOLUMES_PER_AXIS}} ) {
        refinementCriterion = refinementCriterion and repositories::{{SOLVER_INSTANCE}}.refinementCriterion(
          fineGridCell{{UNKNOWN_IDENTIFIER}}.value + index,
          ::exahype2::getVolumeCentre( marker.x(), marker.h(), {{NUMBER_OF_VOLUMES_PER_AXIS}}, volume), 
          ::exahype2::getVolumeSize( marker.h(), {{NUMBER_OF_VOLUMES_PER_AXIS}} ),
          repositories::{{SOLVER_INSTANCE}}.getMinTimeStamp()
        );
        index += {{NUMBER_OF_UNKNOWNS}} + {{NUMBER_OF_AUXILIARY_VARIABLES}};
    }
     
    if (refinementCriterion==::exahype2::RefinementCommand::Refine and tarch::la::max( marker.h() ) < repositories::{{SOLVER_INSTANCE}}.MinAdmissiblePatchH ) {
      refinementCriterion = ::exahype2::RefinementCommand::Keep;
    } 
    else if (refinementCriterion==::exahype2::RefinementCommand::Erase and 3.0* tarch::la::max( marker.h() ) > repositories::{{SOLVER_INSTANCE}}.MaxAdmissiblePatchH ) {
      refinementCriterion = ::exahype2::RefinementCommand::Keep;
    } 
  }
  else {
    refinementCriterion = ::exahype2::RefinementCommand::Keep;
  }
    
  _localRefinementControl.addCommand( marker.x(), marker.h(), refinementCriterion, {{EVENT_LIFETIME}} );
  logTraceOutWith1Argument( "touchCellFirstTime(...)", toString(refinementCriterion) );
  """
  
    
  def __init__(self, solver, guard, build_up_new_refinement_instructions, implement_previous_refinement_instructions, event_lifetime=1):
    """
    
    guard: C++ expression which evaluates to true or false
      A per cell decision whether we should study a cell or not.
    
    build_up_new_refinement_instructions: Boolean
      See remarks on multistep realisation of AMR in C++ class 
      exahype2::RefinementControl.
        
    implement_previous_refinement_instructions: Boolean
      See remarks on multistep realisation of AMR in C++ class 
      exahype2::RefinementControl.
      
    event_lifetime: Int
      See setter below
    
    """
    AbstractFVActionSet.__init__(self,solver)
    self.guard                                       = guard
    self._build_up_new_refinement_instructions       = build_up_new_refinement_instructions
    self._implement_previous_refinement_instructions = implement_previous_refinement_instructions
    self._event_lifetime                             = event_lifetime

  
  def get_body_of_getGridControlEvents(self):
    if self._implement_previous_refinement_instructions:
      return """
    return repositories::refinementControl.getGridControlEvents();
""" 
    else:
      return """
    return std::vector< peano4::grid::GridControlEvent >();
"""      


  def get_body_of_operation(self,operation_name):
    result = ""
    if self._build_up_new_refinement_instructions and operation_name==peano4.solversteps.ActionSet.OPERATION_BEGIN_TRAVERSAL:
      result = """
  _localRefinementControl.clear();
"""

    if self._build_up_new_refinement_instructions and operation_name==peano4.solversteps.ActionSet.OPERATION_END_TRAVERSAL:
      result = """
  repositories::refinementControl.merge( _localRefinementControl );
"""
    
    if self._build_up_new_refinement_instructions and operation_name==peano4.solversteps.ActionSet.OPERATION_TOUCH_CELL_LAST_TIME:
      d = {}
      if self._solver._patch.dim[0] != self._solver._patch.dim[1]:
        raise Exception( "Error: Can only handle square patches." )
      
      d[ "CELL_LABEL_NAME" ]    = self._solver._cell_label.name
      d[ "UNKNOWNS" ]           = str(self._solver._patch.no_of_unknowns)
      d[ "DOFS_PER_AXIS" ]      = str(self._solver._patch.dim[0])
      d[ "NUMBER_OF_DOUBLE_VALUES_IN_ORIGINAL_PATCH_2D" ] = str(self._solver._patch.no_of_unknowns * self._solver._patch.dim[0] * self._solver._patch.dim[0])
      d[ "NUMBER_OF_DOUBLE_VALUES_IN_ORIGINAL_PATCH_3D" ] = str(self._solver._patch.no_of_unknowns * self._solver._patch.dim[0] * self._solver._patch.dim[0] * self._solver._patch.dim[0])
      d[ "CELL_ACCESSOR" ]                                = "fineGridCell" + self._solver._patch.name
      d[ "PREDICATE" ]          = "not marker.willBeRefined() and not marker.hasBeenRefined() and " + self.guard
      d[ "EVENT_LIFETIME"]      = self._event_lifetime
      self._solver._init_dictionary_with_default_parameters(d)
      self._solver.add_entries_to_text_replacement_dictionary(d)      
      result = jinja2.Template( self.TemplateAMR ).render(**d)

    return result

  
  def set_event_lifetime(self,value):
    """
    
     By default, a refinement/coarsening event is only alive for one grid sweep. 
     After that one, the set of refine/coarsen commands is reset and we start
     again. If you work with local time stepping, subcycling, multiphysics codes,
     you might want to keep an event for more steps. In this case, you have to 
     invoke this setter.
     
    """
    self._event_lifetime = value

  def get_attributes(self):
    return """
    ::exahype2::RefinementControl         _localRefinementControl;
"""


  def get_action_set_name(self):
    return __name__.replace(".py", "").replace(".", "_")
