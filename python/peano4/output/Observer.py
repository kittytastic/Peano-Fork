# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from .Helper import Overwrite
from .Helper import writeFile


#
# @todo Work directly against model and use its generator field plus the getters in there to construct stack accesses
#


import os
import re


class Observer(object):
  default_overwrite = True
  
  
  def __init__(self,classname,namespace,subdirectory,included_mappings,vertices,faces,cells):
    """
      Included mappings is a list of qualified mappings which are used
      
      vertices is a list of names. They are not qualified
      faces is a list of names. They are not qualified
      cells is a list of names. They are not qualified
    """
    self.classname    = classname
    self.namespace    = namespace
    self.subdirectory = subdirectory 
    
    self.included_mappings = included_mappings
    self.vertices          = vertices
    self.faces             = faces
    self.cells             = cells
    
    self.d = {}
    self.d[ "OPEN_NAMESPACE" ]           = ""
    self.d[ "CLOSE_NAMESPACE" ]          = ""
    self.d[ "FULL_QUALIFIED_CLASSNAME" ] = ""
    for i in namespace:
      self.d[ "OPEN_NAMESPACE" ]           += "namespace " + i + "{\n"
      self.d[ "CLOSE_NAMESPACE" ]          += "}\n"
      self.d[ "FULL_QUALIFIED_CLASSNAME" ] += i + "::"
    self.d[ "CLASSNAME" ]                 = classname
    self.d[ "FULL_QUALIFIED_CLASSNAME" ] += classname
    self.d[ "INCLUDE_GUARD" ]             = "_" + self.d[ "FULL_QUALIFIED_CLASSNAME" ].replace( "::", "_" ).upper() + "_H_"
    self.d[ "INCLUDES" ]                  = ""
    self.d[ "ATTRIBUTES" ]                = ""

    for mapping in self.included_mappings:
      self.d[ "INCLUDES" ] += "#include \""
      self.d[ "INCLUDES" ] += mapping.replace( "::", "/" )
      self.d[ "INCLUDES" ] += ".h\"\n"
      self.d[ "ATTRIBUTES" ] += mapping
      self.d[ "ATTRIBUTES" ] += "   _mapping"
      self.d[ "ATTRIBUTES" ] += str( self.included_mappings.index(mapping) )
      self.d[ "ATTRIBUTES" ] += "; \n"



  def __generate_header(self,overwrite,full_qualified_filename):
    if writeFile(overwrite,self.default_overwrite,full_qualified_filename):
      print( "write " + full_qualified_filename )
      template_file = os.path.realpath(__file__).replace( ".pyc", ".h.template" ).replace( ".py", ".h.template" )
      with open( os.path.realpath(template_file), "r" ) as input:
        template = input.read()
      with open( full_qualified_filename, "w" ) as output:
        output.write( template.format(**self.d) )



  TemplateConstructor = """
  
{FULL_QUALIFIED_CLASSNAME}::{CLASSNAME}(int spacetreeId):
  _spacetreeId( spacetreeId ) {MAPPING_INITIALISATION_LIST}
{{
}}
  

  """


  def __generate_constructor(self,output_file):
    #
    # Constructor
    #
    self.d[ "MAPPING_INITIALISATION_LIST" ]                = ""
    for mapping in self.included_mappings:
      self.d[ "MAPPING_INITIALISATION_LIST" ]  += ", _mapping"
      self.d[ "MAPPING_INITIALISATION_LIST" ]  += str( self.included_mappings.index(mapping) )
      self.d[ "MAPPING_INITIALISATION_LIST" ]  += "(spacetreeId)"
    output_file.write( self.TemplateConstructor.format(**self.d) )


  TemplateEndTraversal = """
  
void {FULL_QUALIFIED_CLASSNAME}::endTraversal( const tarch::la::Vector<Dimensions,double>&  x, const tarch::la::Vector<Dimensions,double>&  h ) {{
{MAPPING_END_TRAVERSAL_CALLS}
}}
  
  """


  TemplateClone = """
  
peano4::grid::TraversalObserver* {FULL_QUALIFIED_CLASSNAME}::clone(int spacetreeId) {{
  return new {CLASSNAME}(spacetreeId);
}}
  
  """


  TemplateGetGridControlEvents = """
  
std::vector< peano4::grid::GridControlEvent > {FULL_QUALIFIED_CLASSNAME}::getGridControlEvents() {{
  std::vector< peano4::grid::GridControlEvent > result;

{MAPPING_GET_GRID_CONTROL_EVENT_CALLS}
        
  return result;
}}
  
  """
  

  TemplateBeginTraversal = """
  
void {FULL_QUALIFIED_CLASSNAME}::beginTraversal( const tarch::la::Vector<Dimensions,double>&  x, const tarch::la::Vector<Dimensions,double>&  h ) {{
{MAPPING_BEGIN_TRAVERSAL_CALLS}

  int outStack = peano4::grid::PeanoCurve::CallStack;

{INITIAL_PUSH_TO_OUTPUT_STREAMS}
}}
  
  """

    
  def __generate_beginTraversal(self,output_file):
    self.d[ "MAPPING_BEGIN_TRAVERSAL_CALLS" ]     = ""
    for mapping in self.included_mappings:
      self.d[ "MAPPING_BEGIN_TRAVERSAL_CALLS" ]  += "  _mapping"
      self.d[ "MAPPING_BEGIN_TRAVERSAL_CALLS" ]  += str( self.included_mappings.index(mapping) )
      self.d[ "MAPPING_BEGIN_TRAVERSAL_CALLS" ]  += ".beginTraversal();\n"
      
    self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    = ""
    for cell in self.cells:
      self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "  DataRepository::_CellData" + cell + "[ DataRepository::DataKey(_spacetreeId,outStack) ].push( celldata::" + cell + "() );\n"

    self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "  for (int i=0; i<TwoTimesD; i++) {;\n"
    for cell in self.faces:
      self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "    DataRepository::_FaceData" + cell + "[ DataRepository::DataKey(_spacetreeId,outStack) ].push( facedata::" + cell + "() );\n"
    self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "  };\n"
    
    self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "  for (int i=0; i<TwoPowerD; i++) {;\n"
    for cell in self.vertices:
      self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "    DataRepository::_VertexData" + cell + "[ DataRepository::DataKey(_spacetreeId,outStack) ].push( vertexdata::" + cell + "() );\n"
    self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "  };\n"

    output_file.write( self.TemplateBeginTraversal.format(**self.d) )

    
  def __generate_endTraversal(self,output_file):
    self.d[ "MAPPING_END_TRAVERSAL_CALLS" ]                = ""
    for mapping in self.included_mappings:
      self.d[ "MAPPING_END_TRAVERSAL_CALLS" ]  += "  _mapping"
      self.d[ "MAPPING_END_TRAVERSAL_CALLS" ]  += str( self.included_mappings.index(mapping) )
      self.d[ "MAPPING_END_TRAVERSAL_CALLS" ]  += ".endTraversal();\n"
    output_file.write( self.TemplateEndTraversal.format(**self.d) )
    
    
  def __generate_getGridControlEvents(self,output_file):
    #    //const std::vector< peano4::grid::GridControlEvent > userData = _mapping.getGridControlEvents();
    #//result.insert(result.begin(),userData.begin(),userData.end());
    self.d[ "MAPPING_GET_GRID_CONTROL_EVENT_CALLS" ]                = ""
    for mapping in self.included_mappings:
      self.d[ "MAPPING_GET_GRID_CONTROL_EVENT_CALLS" ]  += "  const std::vector< peano4::grid::GridControlEvent > result"
      self.d[ "MAPPING_GET_GRID_CONTROL_EVENT_CALLS" ]  += str( self.included_mappings.index(mapping) )
      self.d[ "MAPPING_GET_GRID_CONTROL_EVENT_CALLS" ]  += " = _mapping"
      self.d[ "MAPPING_GET_GRID_CONTROL_EVENT_CALLS" ]  += str( self.included_mappings.index(mapping) )
      self.d[ "MAPPING_GET_GRID_CONTROL_EVENT_CALLS" ]  += ".getGridControlEvents();\n"
      self.d[ "MAPPING_GET_GRID_CONTROL_EVENT_CALLS" ]  += "  result.insert( result.begin(), result"
      self.d[ "MAPPING_GET_GRID_CONTROL_EVENT_CALLS" ]  += str( self.included_mappings.index(mapping) )
      self.d[ "MAPPING_GET_GRID_CONTROL_EVENT_CALLS" ]  += ".begin(), result"
      self.d[ "MAPPING_GET_GRID_CONTROL_EVENT_CALLS" ]  += str( self.included_mappings.index(mapping) )
      self.d[ "MAPPING_GET_GRID_CONTROL_EVENT_CALLS" ]  += ".end() );\n"
    output_file.write( self.TemplateGetGridControlEvents.format(**self.d) )


  def __generate_clone(self,output_file):
    output_file.write( self.TemplateClone.format(**self.d) )


  def __generate_enterCell(self,output_file):
    output_file.write( "void " + self.d[ "FULL_QUALIFIED_CLASSNAME" ] + "::enterCell( const peano4::grid::GridTraversalEvent&  event ) { \n" )
    output_file.write( "}\n\n\n" )



  def __generate_leaveCell(self,output_file):
    output_file.write( "void " + self.d[ "FULL_QUALIFIED_CLASSNAME" ] + "::leaveCell( const peano4::grid::GridTraversalEvent&  event ) { \n" )
    output_file.write( "}\n\n\n" )
    
    #if writeFile(overwrite,self.default_overwrite,full_qualified_filename):
    #  print( "write " + full_qualified_filename )
    #  output_file = open( full_qualified_filename, "w" )
    #  output_file.write( "#include \"" + self.d[ "CLASSNAME" ] + ".h\"\n\n\n" )
    # 
    #  self.__generate_implementation_glue_code(output_file)


  def __generate_implementation(self,overwrite,full_qualified_filename):
    if writeFile(overwrite,self.default_overwrite,full_qualified_filename):
      print( "write " + full_qualified_filename )
      output_file = open( full_qualified_filename, "w" )
      output_file.write( "#include \"" + self.d[ "CLASSNAME" ] + ".h\"\n\n\n" )
      output_file.write( """#include "DataRepository.h"\n""" )
      output_file.write( """#include "peano4/grid/PeanoCurve.h"\n""" )
      
      self.__generate_constructor(output_file)
      self.__generate_clone(output_file)
      self.__generate_getGridControlEvents(output_file)
      self.__generate_beginTraversal(output_file)
      self.__generate_endTraversal(output_file)
      self.__generate_enterCell(output_file)
      self.__generate_leaveCell(output_file)


  def get_header_file_name(self):
    return self.subdirectory + "/" + self.classname + ".h"


  def get_cpp_file_name(self):
    return self.subdirectory + "/" + self.classname + ".cpp"


  def generate(self,overwrite,directory):
    if not os.path.exists( directory + "/" + self.subdirectory ):
      os.mkdir(directory + "/" + self.subdirectory)
    
    header_filename = directory + "/" + self.get_header_file_name()
    cpp_filename    = directory + "/" + self.get_cpp_file_name()
    
    self.__generate_header(overwrite,header_filename)
    self.__generate_implementation(overwrite,cpp_filename)

