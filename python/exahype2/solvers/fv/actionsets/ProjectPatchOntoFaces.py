# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org
import peano4
import jinja2


import peano4.toolbox.blockstructured.ProjectPatchOntoFaces


class ProjectPatchOntoFaces( peano4.toolbox.blockstructured.ProjectPatchOntoFaces ):
  """
  
   This class is very similar to peano4.toolbox.blockstructured.ProjectPatchOntoFaces, 
   but there are some delicate differences.
   
  """
  def __init__(self,solver, predicate):
    peano4.toolbox.blockstructured.ProjectPatchOntoFaces.__init__(self,solver._patch,solver._patch_overlap_update,predicate,solver._get_default_includes() + solver.get_user_includes(), True)

    self.d[ "FACE_METADATA_ACCESSOR" ] = "fineGridFaces"  + solver._face_label.name
    self.d[ "CELL_METADATA_ACCESSOR" ] = "fineGridCell""" + solver._cell_label.name

    self.__Template_TouchCellLastTime_Core += """
  for (int d=0; d<Dimensions; d++) {{
    {FACE_METADATA_ACCESSOR}(d).setUpdated(1,true);
    {FACE_METADATA_ACCESSOR}(d).setUpdatedTimeStamp(1,{CELL_METADATA_ACCESSOR}.getTimeStamp());
    {FACE_METADATA_ACCESSOR}(d+Dimensions).setUpdated(0,true);
    {FACE_METADATA_ACCESSOR}(d+Dimensions).setUpdatedTimeStamp(0,{CELL_METADATA_ACCESSOR}.getTimeStamp());
    logDebug( "touchCellLastTime(...)", "update {FACE_METADATA_ACCESSOR}(" << d << ")(1)" );
    logDebug( "touchCellLastTime(...)", "update {FACE_METADATA_ACCESSOR}(" << (d+Dimensions) << ")(0)" );
  }}  
"""


  def get_action_set_name(self):
    return __name__.replace(".py", "").replace(".", "_")


  #def get_body_of_operation(self,operation_name):
  #  result = peano4.toolbox.blockstructured.ProjectPatchOntoFaces.get_body_of_operation(self,operation_name)
    
    #if operation_name==peano4.solversteps.ActionSet.OPERATION_TOUCH_FACE_FIRST_TIME:
    #  #self._solver._init_dictionary_with_default_parameters(self.d)
    #  #self._solver.add_entries_to_text_replacement_dictionary(self.d)
    #  result = jinja2.Template(self._Template_TouchFaceFirstTime).render(**self.d)
    #  pass 

  #  return result

#  def get_includes(self):
#    return """
##include "peano4/utils/Loop.h"
#""" + self.additional_includes
