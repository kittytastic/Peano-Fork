# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from .Mapping import Mapping


class UserMapping(Mapping):
  def __init__(self):
    pass


  def get_constructor_body(self):
    return "// @todo Please implement\n"


  def get_body_of_getGridControlEvents(self):
    return "// @todo Please implement\nreturn std::vector< peano4::grid::GridControlEvent >();\n" 


  def get_body_of_operation(self,operation_name):
    return "// @todo Please implement\n"


  def get_mapping_name(self):
    """
     Returns a description (word) for the mapping which is also used as class name
     for the generated type. As a consequence, the result should be one word (if 
     possible) and uppercase. Also, every subclass should overwrite this routine.
    """
    return "UserCode"
