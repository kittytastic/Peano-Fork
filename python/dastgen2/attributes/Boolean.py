# This file is part of the DaStGen2 project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from .Attribute import Attribute


class Boolean(Attribute):
  def __init__(self, name):
    Attribute.__init__(self, name)
    
  def get_methods(self,_full_qualified_class_name):
    accessor_name = self._name[:1].title() + self._name[1:]
    return [ 
      ("get" + accessor_name + "() const", "bool"),
      ("set" + accessor_name + "(bool value)", "void")
    ]

  def get_plain_C_attributes(self):
    return [ ("_" + self._name, "bool" ) ]

  def get_method_body(self,signature):
    if signature.startswith( "get" ):
      return "  return _" + self._name + ";\n"
    elif signature.startswith( "set" ):
      return "  _" + self._name + " = value;\n"
    else:
      assert(False)
    return ""
  
  def get_native_MPI_type(self):
    return [ ("MPI_CXX_BOOL", 1) ]
  
  def get_to_string(self):
    """
    
      Return string representation of attribute.

    """
    return "_" + self._name

