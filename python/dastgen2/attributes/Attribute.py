# This file is part of the DaStGen2 project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
import abc


class Attribute(object):
  """
  
   Represents one attribute 
   
  """
  def __init__(self, name):
    self._name = name

  @abc.abstractmethod
  def get_methods(self):
    """
      
      Return sequence of methods that are defined for this attribute. Each
      entry is a tuple. Its first entry is the signature of the function 
      (not including the semicolon), the second entry is the return type.
      
    """
    return 

  @abc.abstractmethod
  def get_plain_C_attributes(self):
    """
    
      Return list of tuples. The first tuple entry always is the name, 
      the second one the type. Type has to be plain C.
      
    """
    return


  @abc.abstractmethod
  def get_method_body(self,signature):
    """
     
      I hand in the method signature (see get_methods()) and wanna get 
      the whole implementation.
      
    """
    return


  @abc.abstractmethod
  def get_native_MPI_type(self):
    """
     
      Return native (built-in) MPI datatype. Return None if there's no 
      direct mapping. The actual result is not a string only,m 
      
    """
    return 


  @abc.abstractmethod
  def get_to_string(self):
    """
    
      Return string representation of attribute. Should be something
      that can be streamed via << into a sstream. So the result has 
      to be of type string.

    """
    return
