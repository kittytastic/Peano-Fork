# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
import peano4.solversteps.UserActionSet

from peano4.solversteps.StepToActionSet import StepToActionSet
from peano4.solversteps.StepToObserver  import StepToObserver


# 
# @todo Aufteilen in mehrere Files mit ToXXXXX wie im Model.
#

class Step:
  """
    Most generic version of a solver step. A solverstep describes what Peano4 
    should do when it runs over the grid. As users have to specify which pieces
    of data from the data model are used by the solver step, it can handle all
    the user data stack flow.
    
    This class also is responsible to generate all function signatures of all 
    the steps, observers and action sets. 
  """
  def __init__(self,name,add_user_defined_actions = True):
    """
     By default, the step generates at least one action set for the user. 
     However, you can disable this behaviour by passing False to
     add_user_defined_actions. Alternatively, use remove_all_action_sets()
     on the step.
    """
    self.name        = name
    self.cell_data   = []
    self.face_data   = []
    self.vertex_data = []
    if add_user_defined_actions:
      self.action_sets    = [ peano4.solversteps.UserActionSet( name ) ]
    else:
      self.action_sets    = []
    self.action_set_generator   = StepToActionSet(self)
    self.observer_generator  = StepToObserver(self)


  def remove_all_actions(self):
    """
     Each step holds a set of actions. They describe what the step actually
     should do whenever it loads a vertex, runs into a cell, and so forth. By
     default, the step holds one user-defined actions which means
     that a stub is generated where users can insert their functionality. You
     can remove this one (or any other one added so far) with this routine.
    """
    self.action_sets = []

  
  def add_action_set(self,action_set):
    """
     Each step holds a set of action_sets. They describe what the step actually
     should do whenever it loads a vertex, runs into a cell, and so forth. By
     default, the step holds one user-defined action_set (UserActionSet) which means
     that a stub is generated where users can insert their functionality. It is 
     important in which order you add your action_sets: The whole tree traversal 
     is a top-down/depth-first tree traversal. So all the enter, create, ...
     operations of a action_set are invoked exactly in the order you add them to 
     the step. All the delete, leave, ... operations are invokved in reversed
     order.
    """
    self.action_sets.append(action_set)

    
  def set_project(self,project):
    """
     You don't have to call this. It is automatically called once you add a step 
     to the project's steps.
    """
    self.project     = project
    
  def use_cell(self,submodel):
    self.cell_data.append(submodel)

  def use_face(self,submodel):
    self.face_data.append(submodel)

  def use_vertex(self,submodel):
    self.vertex_data.append(submodel)


  def get_vertex_operations_signature(self):
    result = ["marker", "const peano4::datamanagement::VertexMarker&" ]
    for i in self.vertex_data:
      result += ["fineGridVertex" + i.name,i.get_full_qualified_type() + "&"]
    for i in self.vertex_data:
      result += ["coarseGridVertices" + i.name, i.get_enumeration_type() + "" ]
    for i in self.face_data:
      result += ["coarseGridFaces" + i.name, i.get_enumeration_type() + "" ]
    for i in self.cell_data:
      result += ["coarseGridCell" + i.name,i.get_full_qualified_type() + "&"]
    return result

  def get_face_operations_signature(self):
    result = ["marker", "const peano4::datamanagement::FaceMarker&" ]
    for i in self.vertex_data:
      result += ["fineGridVertices" + i.name, i.get_enumeration_type() + "" ]
    for i in self.face_data:
      result += ["fineGridFace" + i.name,i.get_full_qualified_type() + "&"]
    for i in self.vertex_data:
      result += ["coarseGridVertices" + i.name, i.get_enumeration_type() + "" ]
    for i in self.face_data:
      result += ["coarseGridFaces" + i.name, i.get_enumeration_type() + "" ]
    for i in self.cell_data:
      result += ["coarseGridCell" + i.name,i.get_full_qualified_type() + "&"]
    return result


  def get_cell_operations_signature(self):
    result = ["marker", "const peano4::datamanagement::CellMarker&" ]
    for i in self.vertex_data:
      result += ["fineGridVertices" + i.name, i.get_enumeration_type() + "" ]
    for i in self.face_data:
      result += ["fineGridFaces" + i.name, i.get_enumeration_type() + "" ]
    for i in self.cell_data:
      result += ["fineGridCell" + i.name,i.get_full_qualified_type() + "&"]
    for i in self.vertex_data:
      result += ["coarseGridVertices" + i.name, i.get_enumeration_type() + "" ]
    for i in self.face_data:
      result += ["coarseGridFaces" + i.name, i.get_enumeration_type() + "" ]
    for i in self.cell_data:
      result += ["coarseGridCell" + i.name,i.get_full_qualified_type() + "&"]
    return result
      

  def get_touch_cell_signature(self):
    result = ["marker", "const peano4::datamanagement::CellMarker&" ]
    for i in self.vertex_data:
      result += ["fineGridVertices" + i.name, i.get_enumeration_type() + "" ]
    for i in self.face_data:
      result += ["fineGridFaces" + i.name, i.get_enumeration_type() + "" ]
    for i in self.cell_data:
      result += ["fineGridCell" + i.name,i.get_full_qualified_type() + "&"]
      
    for i in self.vertex_data:
      result += ["coarseGridVertices" + i.name, i.get_enumeration_type() + "" ]
    for i in self.face_data:
      result += ["coarseGridFaces" + i.name, i.get_enumeration_type() + "" ]
    for i in self.cell_data:
      result += ["coarseGridCell" + i.name,i.get_full_qualified_type() + "&"]

    return result
      

  def construct_output(self,output):
    """
    Each solver step basically gives us two big files/classes: A class which 
    handles the actual data movements, i.e. is an implementation of the tree
    visitor pattern over the Peano4 tree. The other type is an interface which 
    provides plugin points into the created data transitions from a user's 
    perspective.
    """
    
    
    included_action_sets = []
    for action_set in self.action_sets:
      full_qualified_action_set_name = self.action_set_generator.construct_output(output,action_set)
      included_action_sets.append( full_qualified_action_set_name )
    
    self.observer_generator.construct_output(output, included_action_sets)

  
  def copy_action_sets_from_other_step(self, other_step):
    self.action_sets += other_step.action_sets
    

    