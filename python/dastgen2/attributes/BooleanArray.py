# This file is part of the DaStGen2 project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from .Boolean import Boolean


class BooleanArray(Boolean):
  def __init__(self, name, cardinality):
    Boolean.__init__(self, name)
    self._cardinality = cardinality
    
  def get_methods(self,_full_qualified_class_name):
    accessor_name = self._name[:1].title() + self._name[1:]
    return [ 
      ("get" + accessor_name + "() const", "std::bitset<" + self._cardinality + ">"),
      ("set" + accessor_name + "(const std::bitset<" + self._cardinality + ">&  value)", "void"),
      ("get" + accessor_name + "(int index) const", "bool"),
      ("set" + accessor_name + "(int index, bool value)", "void"),
      ("flip" + accessor_name + "(int index)", "void"),
    ]

  def get_plain_C_attributes(self):
    return [ ("_" + self._name, "std::bitset<" + self._cardinality + ">" ) ]

  def get_first_plain_C_attribute(self):
    return [ ("_" + self._name , "double" ) ]

  def get_method_body(self,signature):
    if signature.startswith( "flip" ) and  "index" in signature:
      return "  _" + self._name + ".flip(index);\n"
    elif signature.startswith( "get" ) and  "index" in signature:
      return "  return _" + self._name + "[index];\n"
    elif signature.startswith( "set" ) and  "index" in signature:
      return "  _" + self._name + "[index] = value;\n"
    elif signature.startswith( "get" ):
      return "  return _" + self._name + ";\n"
    elif signature.startswith( "set" ):
      return "  _" + self._name + " = value;\n"
    else:
      assert(False)
    return ""
  
  def get_native_MPI_type(self):
    return [ ("MPI_UNSIGNED_LONG", 1 ) ]
      
  
  def get_to_string(self):
    """
    
      Return string representation of attribute.

    """
    return "_" + self._name

