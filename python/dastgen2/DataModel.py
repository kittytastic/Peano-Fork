# This file is part of the DaStGen2 project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
import dastgen2
import os


class DataModel(object):
  """ 
  Represents on DaStGen2 object, i.e. one data model.
  
  full_qualified_name  Full qualified name. Please pass in in C++ convention i.e. with 
                       :: separating the namespaces.
    
  """
  def __init__(self, full_qualified_name, has_nondefault_constructor = True ):
    self._full_qualified_name = full_qualified_name
    self._attributes          = []
    self._aspects             = []
    self.has_nondefault_constructor = has_nondefault_constructor


  def set_full_qualified_name(self, full_qualified_name):
    self._full_qualified_name = full_qualified_name
    
    
  def add_attribute(self,attribute):
    self._attributes.append(attribute)


  def add_aspect(self,aspect):
    aspect.set_model(self)
    self._aspects.append(aspect)


  _Header_Template = """
//
// Generated by DaStGen2 (C) 2020 Tobias Weinzierl
//
// For DaStGen's copyright, visit www.peano-framework.org. These generated files
// however are not subject of copyright, i.e. feel free to add your copyright in 
// here
//  
#ifndef {INCLUDE_GUARD}
#define {INCLUDE_GUARD}

#include <string>
  
{ASPECT_INCLUDES}
  
{OPEN_NAMESPACES}
  struct {UNQUALIFIED_CLASS_NAME};
{CLOSE_NAMESPACES}


struct {FULL_QUALIFIED_CLASS_NAME} {{
  public:
{PUBLIC_FIELDS}

    {UNQUALIFIED_CLASS_NAME}() {{}}
    {UNQUALIFIED_CLASS_NAME}{CONSTRUCTOR_ARGUMENTS};

{METHOD_DECLARATIONS}

{ASPECT_METHOD_DECLARATIONS}
    std::string toString() const;
  
  private:
{ATTRIBUTE_DECLARATIONS}

{ASPECT_ATTRIBUTES}
    
}};

#endif
  """


  def _get_flattened_attributes(self):
    """
    
      We can hold multiple attributes and some of these attributes in 
      turn can hold multiple (plain C) attributes. This operation
      flattens this two-level hierarchy, i.e. gives back a plain list
      of C attributes.
      
    """  
    flattened_attributes = []
    for attribute in self._attributes:
      flattened_attributes           += attribute.get_plain_C_attributes()
    return flattened_attributes


  def _get_flattened_declarations(self):
    flattened_method_declarations = []
    for attribute in self._attributes:
      flattened_method_declarations  += attribute.get_methods(self._full_qualified_name)
    return flattened_method_declarations

  
  def _get_constructor_arguments(self):
    result  = "("
    for attribute in self._get_flattened_attributes():
      if attribute!=self._get_flattened_attributes()[0]:
        result += ", "
      result += attribute[1] + "  _" + attribute[0]
    result += ")"
    return result


  def write_header_file(self,full_qualified_filename):
    d = {}
    d[ "INCLUDE_GUARD" ]              = dastgen2.get_include_guard(self._full_qualified_name)
    d[ "UNQUALIFIED_CLASS_NAME" ]     = dastgen2.get_unqualified_class_name(self._full_qualified_name)
    d[ "FULL_QUALIFIED_CLASS_NAME" ]  = self._full_qualified_name
    d[ "OPEN_NAMESPACES" ]            = ""
    d[ "CLOSE_NAMESPACES" ]           = ""
    d[ "SETTER_GETTER_DECLARATIONS" ] = ""
    for i in dastgen2.get_namespaces( self._full_qualified_name ):
      d[ "OPEN_NAMESPACES" ]         += "namespace " + i + "{\n"
      d[ "CLOSE_NAMESPACES" ]        += "}\n"

    d[ "PUBLIC_FIELDS" ]              = ""
        
    for attribute in self._attributes:
      d[ "PUBLIC_FIELDS" ]           += attribute.get_public_fields()

    d[ "ATTRIBUTE_DECLARATIONS" ]     = ""
    for attribute in self._get_flattened_attributes():
      d[ "ATTRIBUTE_DECLARATIONS" ]  += "    " + attribute[1] + "   " + attribute[0] + ";\n"

    d[ "METHOD_DECLARATIONS" ]        = ""
    for method in self._get_flattened_declarations():
      d[ "METHOD_DECLARATIONS" ]     += "    " + method[1] + "   " + method[0] + ";\n"

    d[ "ASPECT_ATTRIBUTES" ]             = ""
    d[ "ASPECT_METHOD_DECLARATIONS" ]    = ""
    d[ "ASPECT_INCLUDES" ]               = ""
    for i in self._aspects:
      d[ "ASPECT_ATTRIBUTES" ]          += i.get_attributes() + "\n"
      d[ "ASPECT_METHOD_DECLARATIONS" ] += i.get_method_declarations(self._full_qualified_name) + "\n"
      d[ "ASPECT_INCLUDES" ]            += i.get_include() + "\n"
        
        
    d[ "CONSTRUCTOR_ARGUMENTS" ] = self._get_constructor_arguments()


    if full_qualified_filename.find( "/" ) != -1:
      path = full_qualified_filename[ 0 : full_qualified_filename.rfind( "/" ) ]
      if not os.path.exists(path):
        os.mkdir( path )
    with open( full_qualified_filename, "w" ) as output:
      output.write( self._Header_Template.format(**d) )


  def __generate_constructor_definition(self, output):
    output.write( self._full_qualified_name + "::" + dastgen2.get_unqualified_class_name(self._full_qualified_name) + self._get_constructor_arguments() + ":\n" )
    for attribute in self._get_flattened_attributes():
      if attribute==self._get_flattened_attributes()[0]:
        output.write( "    " )
      else:
        output.write( "  , " )
      output.write( attribute[0] + "(_" + attribute[0] + ")\n" )
    output.write( "  {}\n")

  
  def __generate_toString_definition(self, output):
      output.write("std::string " + self._full_qualified_name + "::toString() const {\n")
      output.write("  std::ostringstream out;\n")
      output.write("  out << \"(\";\n")
      for attribute in self._attributes:
          if self._attributes.index(attribute) != 0:
              output.write("""  out << ","; \n""")
          output.write("  out << \"" + attribute._name + "=\" << " + attribute.get_to_string() + ";\n")
      
      output.write("  out << \")\";\n")
      output.write("  return out.str();\n")
      output.write("}\n\n\n")
      for attribute in self._attributes:
          for method in attribute.get_methods(self._full_qualified_name):
              output.write(method[1] + "   " + self._full_qualified_name + "::" + method[0] + " {\n")
              output.write(attribute.get_method_body(method[0]))
              output.write("}\n\n\n")
      

  def write_implementation_file(self,full_qualified_filename):
    #d = {}
    #d[ "INCLUDE_GUARD" ]              = dastgen2.get_include_guard(self._full_qualified_name)
    #d[ "UNQUALIFIED_CLASS_NAME" ]     = dastgen2.get_unqualified_class_name(self._full_qualified_name)
    #d[ "FULL_QUALIFIED_CLASS_NAME" ]  = self._full_qualified_name
    #d[ "OPEN_NAMESPACES" ]            = ""
    #d[ "CLOSE_NAMESPACES" ]           = ""
    #d[ "SETTER_GETTER_DECLARATIONS" ] = ""
    #for i in dastgen2.get_namespaces( self._full_qualified_name ):

    with open( full_qualified_filename, "w" ) as output:
      output.write( "#include \"" + dastgen2.get_unqualified_class_name(self._full_qualified_name) + ".h\"\n\n\n" )

      output.write( """
#include <sstream>
#include <algorithm>



""" )

      if self.has_nondefault_constructor:
        self.__generate_constructor_definition(output)
        output.write( "\n\n\n" )
      self.__generate_toString_definition(output)
      output.write( "\n\n\n" )

      for aspect in self._aspects:
          output.write(aspect.get_implementation(self._full_qualified_name))
