# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from .Helper import Overwrite
from .Helper import writeFile


import os
import re
from gi._gi import BaseInfo


class Observer(object):
  default_overwrite = True
  
  
  def __init__(self,classname,namespace,subdirectory,included_mappings,vertices,faces,cells):
    """
      Included mappings is a list of qualified mappings which are used
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

    for vertex in vertices:
      self.d[ "ATTRIBUTES" ] += "   peano4::stacks::STDVectorStack<"
      self.d[ "ATTRIBUTES" ] += vertex.get_enumeration_type()
      self.d[ "ATTRIBUTES" ] += "   _"
      self.d[ "ATTRIBUTES" ] += vertex.get_logical_type_name()
      self.d[ "ATTRIBUTES" ] += "CallStack; \n"

    for face in faces:
      self.d[ "ATTRIBUTES" ] += "   peano4::stacks::STDVectorStack<"
      self.d[ "ATTRIBUTES" ] += face.get_enumeration_type()
      self.d[ "ATTRIBUTES" ] += ">   _"
      self.d[ "ATTRIBUTES" ] += face.get_logical_type_name()
      self.d[ "ATTRIBUTES" ] += "CallStack; \n"

    #for cell in cells:
    #  self.d[ "ATTRIBUTES" ] += "   "
    #  self.d[ "ATTRIBUTES" ] += cell.generator.get_stack_container()
    #  self.d[ "ATTRIBUTES" ] += "   _"
    #  self.d[ "ATTRIBUTES" ] += cell.get_logical_type_name()
    #  self.d[ "ATTRIBUTES" ] += "CallStack; \n"
    self.d[ "MAPPING_SIGNATURE_FINE_GRID_CELL_ARGUMENTS" ]       = ""
    self.d[ "MAPPING_SIGNATURE_COARSE_GRID_CELL_ARGUMENTS" ]     = ""
    for cell in cells:
      self.d[ "MAPPING_SIGNATURE_FINE_GRID_CELL_ARGUMENTS" ]   += ",DataRepository::_" + cell.get_logical_type_name() + "Stack[ DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack) ].top(0)";
      self.d[ "MAPPING_SIGNATURE_COARSE_GRID_CELL_ARGUMENTS" ] += ",DataRepository::_" + cell.get_logical_type_name() + "Stack[ DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack) ].top(1)";
     
    self.d[ "MAPPING_SIGNATURE_FINE_GRID_FACES_ARGUMENTS" ]      = ""
    self.d[ "MAPPING_SIGNATURE_COARSE_GRID_FACES_ARGUMENTS" ]    = ""
    for face in faces:
      self.d[ "MAPPING_SIGNATURE_FINE_GRID_FACES_ARGUMENTS" ]   += ",_" + face.get_logical_type_name() + "CallStack.top(0)"
      self.d[ "MAPPING_SIGNATURE_COARSE_GRID_FACES_ARGUMENTS" ] += ",_" + face.get_logical_type_name() + "CallStack.top(1)"
      
    self.d[ "MAPPING_SIGNATURE_FINE_GRID_VERTICES_ARGUMENTS" ]   = ""
    self.d[ "MAPPING_SIGNATURE_COARSE_GRID_VERTICES_ARGUMENTS" ] = ""
    for vertex in vertices:
      self.d[ "MAPPING_SIGNATURE_FINE_GRID_VERTICES_ARGUMENTS" ]   = ",_" + vertex.get_logical_type_name() + "CallStack.top(0)"
      self.d[ "MAPPING_SIGNATURE_COARSE_GRID_VERTICES_ARGUMENTS" ] = ",_" + vertex.get_logical_type_name() + "CallStack.top(1)"
      


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


  TemplateClone = """
  
peano4::grid::TraversalObserver* {FULL_QUALIFIED_CLASSNAME}::clone(int spacetreeId) {{
  return new {CLASSNAME}(spacetreeId);
}}
  
  """


  TemplateBeginTraversal = """
  
void {FULL_QUALIFIED_CLASSNAME}::beginTraversal( const tarch::la::Vector<Dimensions,double>&  x, const tarch::la::Vector<Dimensions,double>&  h ) {{
  //
  // Invoke beginTraversal() on the mappings
  //
{MAPPING_BEGIN_TRAVERSAL_CALLS}

  //
  // Befill call stack with dummies which represent level -1 such that we can 
  // call standard mapping routines on level 0 with parents.
  //
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
      self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "  DataRepository::_" + cell.get_logical_type_name() + "Stack[ DataRepository::DataKey(_spacetreeId,outStack) ].push( " + cell.get_full_qualified_type() + "() );\n"
      pass

    for face in self.faces:
      #self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "  _faces" + face + "CallStack.push(DataRepository::Faces" + face + "(x,h));\n"
      pass

    for vertex in self.vertices:
      #self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "  _vertices" + vertex + "CallStack.push(DataRepository::Vertices" + vertex + "(x,h));\n"
      pass

    output_file.write( self.TemplateBeginTraversal.format(**self.d) )


  TemplateEndTraversal = """
  
void {FULL_QUALIFIED_CLASSNAME}::endTraversal( const tarch::la::Vector<Dimensions,double>&  x, const tarch::la::Vector<Dimensions,double>&  h ) {{
{MAPPING_END_TRAVERSAL_CALLS}
  int inStack = peano4::grid::PeanoCurve::CallStack;
{FINAL_POP_FROM_INPUT_STREAMS}
}}
  
  """

    
  def __generate_endTraversal(self,output_file):
    self.d[ "MAPPING_END_TRAVERSAL_CALLS" ]                = ""
    for mapping in self.included_mappings:
      self.d[ "MAPPING_END_TRAVERSAL_CALLS" ]  += "  _mapping"
      self.d[ "MAPPING_END_TRAVERSAL_CALLS" ]  += str( self.included_mappings.index(mapping) )
      self.d[ "MAPPING_END_TRAVERSAL_CALLS" ]  += ".endTraversal();\n"

    self.d[ "FINAL_POP_FROM_INPUT_STREAMS" ]    = ""
    for cell in self.cells:
      #self.d[ "FINAL_POP_FROM_INPUT_STREAMS" ]    += "  DataRepository::_CellData" + cell + "[ DataRepository::DataKey(_spacetreeId,inStack) ].pop();\n"
      pass

    for face in self.faces:
      #self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "  _faces" + cell + "CallStack.pop();\n"
      pass

    for vertex in self.vertices:
      #self.d[ "INITIAL_PUSH_TO_OUTPUT_STREAMS" ]    += "  _vertices" + vertex + "CallStack.pop();\n"
      pass
    
    output_file.write( self.TemplateEndTraversal.format(**self.d) )
    

  def __format_template_per_mapping(self,output_file,template,reverse_order=False):
    """
     Takes the specified template file, iterates over self.mappings and pastes
     the template into the output file once per mapping. Per mapping, the dictionary's
     entries are updated. Otherwise, the dictionary remains unchanged.
    """ 
    local_mappings = [x for x in self.included_mappings]
    if reverse_order:
      local_mappings.reverse()
        
    for mapping in local_mappings:
      self.d[ "ACTIVE_MAPPING" ]  = "_mapping" + str( self.included_mappings.index(mapping) )
      self.d[ "ACTIVE_MAPPING_FULL_QUALIFIED_NAME" ]  = mapping
      output_file.write( template.format(**self.d) )
        

  TemplateGetGridControlEvents_Prologue = """
  
std::vector< peano4::grid::GridControlEvent > {FULL_QUALIFIED_CLASSNAME}::getGridControlEvents() {{
  std::vector< peano4::grid::GridControlEvent > result;
"""

  TemplateGetGridControlEvents_MappingCall = """
  {{
    const std::vector< peano4::grid::GridControlEvent > mappingResult = {ACTIVE_MAPPING}.getGridControlEvents();
    result.insert(result.begin(),mappingResult.begin(),mappingResult.end());
  }}
"""        

  
  TemplateGetGridControlEvents_Epilogue = """
  return result;
}}
  
"""
  
        
  def __generate_getGridControlEvents(self,output_file):
    output_file.write( self.TemplateGetGridControlEvents_Prologue.format(**self.d) )
    self.__format_template_per_mapping(output_file,self.TemplateGetGridControlEvents_MappingCall)
    output_file.write( self.TemplateGetGridControlEvents_Epilogue.format(**self.d) )


  def __generate_clone(self,output_file):
    output_file.write( self.TemplateClone.format(**self.d) )


  TemplateEnterCell_Prologue = """  
void {FULL_QUALIFIED_CLASSNAME}::enterCell( const peano4::grid::GridTraversalEvent&  event ) {{
  logTraceInWith1Argument( "enterCell(peano4::grid::GridTraversalEvent)", event.toString() );
"""


  TemplateEnterCell_FaceLoad = """  
  // Handle face {name}
  {enumeration_type}     fineGridFaces{name}(event.getX(),event.getH());
  {enumeration_type}     coarseGridFaces{name}(event.getX(),event.getH());
  // @todo Die Enumeratoren muessen jetzt gleich auch auf den Call-Stack, sonst gehen die Zugriffslisten net in den Events 
  {{
//    DataRepository::{logical_type_name}Stack::PushBlockVertexStackView faceView = DataRepository::_FaceData{name}[ DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack) ].pushBlock(Dimensions*2);
  }}
"""


  TemplateEnterCell_CellLoad_Prologue = """  
  // Handle cell {name}
  {{
    const int inCellStack  = event.getCellData();
    const int outCellStack = peano4::grid::PeanoCurve::CallStack;
    logDebug("enterCell(peano4::grid::GridTraversalEvent)", "cell " << inCellStack << "->pos-" << outCellStack );

    {full_qualified_type} data;
    if (inCellStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity) {{
      data = DataRepository::_{logical_type_name}Stack[ DataRepository::DataKey(_spacetreeId,inCellStack) ].pop();
    }}
    DataRepository::_{logical_type_name}Stack[ DataRepository::DataKey(_spacetreeId,outCellStack) ].push(data);
  }}
"""

  TemplateEnterCell_CellLoad_MappingCall = """  
  if (event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity) {{
    const peano4::datamanagement::CellMarker marker( event );
    {ACTIVE_MAPPING}.createCell(
         event.getX()
        ,event.getH()
         {MAPPING_SIGNATURE_FINE_GRID_VERTICES_ARGUMENTS}
         {MAPPING_SIGNATURE_FINE_GRID_FACES_ARGUMENTS}
        ,DataRepository::_{logical_type_name}Stack[ DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack) ].top(0)
         {MAPPING_SIGNATURE_COARSE_GRID_VERTICES_ARGUMENTS}
         {MAPPING_SIGNATURE_COARSE_GRID_FACES_ARGUMENTS}
         {MAPPING_SIGNATURE_COARSE_GRID_CELL_ARGUMENTS}
        ,marker
    );
  }}
"""


  TemplateEnterCell_MappingCall = """  
  {{
    peano4::datamanagement::CellMarker marker(event.getIsRefined(),false);
    {ACTIVE_MAPPING}.touchCellFirstTime(
      event.getX(), event.getH()
       {MAPPING_SIGNATURE_FINE_GRID_VERTICES_ARGUMENTS}
       {MAPPING_SIGNATURE_FINE_GRID_FACES_ARGUMENTS}
       {MAPPING_SIGNATURE_FINE_GRID_CELL_ARGUMENTS}
       {MAPPING_SIGNATURE_COARSE_GRID_VERTICES_ARGUMENTS}
       {MAPPING_SIGNATURE_COARSE_GRID_FACES_ARGUMENTS}
       {MAPPING_SIGNATURE_COARSE_GRID_CELL_ARGUMENTS}
      ,marker
    );
  }}
"""



  TemplateEnterCell_Epilogue = """  
  logTraceOut( "enterCell(peano4::grid::GridTraversalEvent)" );
}}
"""

  
  def __generate_enterCell(self,output_file):
    """
      Generates enter cell
    """
    output_file.write( self.TemplateEnterCell_Prologue.format(**self.d) )
          
    # @todo Das ist noch net fertig
    for vertices in self.vertices:
      #output_file.write( self.TemplateEnterCell_FaceLoad.format(**self.d) )
      pass

    for face in self.faces:
      self.d[ "name" ]                 = face.name
      self.d[ "enumeration_type" ]     = face.get_enumeration_type()
      self.d[ "logical_type_name" ]    = face.get_logical_type_name()
      self.d[ "full_qualified_type" ]  = face.get_full_qualified_type()
      output_file.write( self.TemplateEnterCell_FaceLoad.format(**self.d) )

    for cell in self.cells:
      self.d[ "name" ]                 = cell.name
      #self.d[ "enumeration_type" ]     = cell.get_enumeration_type()
      self.d[ "logical_type_name" ]    = cell.get_logical_type_name()
      self.d[ "full_qualified_type" ]  = cell.get_full_qualified_type()
      output_file.write( self.TemplateEnterCell_CellLoad_Prologue.format(**self.d) )
      self.__format_template_per_mapping(output_file, self.TemplateEnterCell_CellLoad_MappingCall, False)


    self.__format_template_per_mapping(output_file, self.TemplateEnterCell_MappingCall, False)
    output_file.write( self.TemplateEnterCell_Epilogue.format(**self.d) )


  TemplateLeaveCell_Prologue = """  
void {FULL_QUALIFIED_CLASSNAME}::leaveCell( const peano4::grid::GridTraversalEvent&  event ) {{
  logTraceInWith1Argument( "leaveCell(peano4::grid::GridTraversalEvent)", event.toString() );
"""


  TemplateLeaveCell_CellStore_MappingCall = """  
  if (event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity) {{
    {ACTIVE_MAPPING}.destroyCell(
         event.getX()
        ,event.getH()
        {MAPPING_SIGNATURE_FINE_GRID_VERTICES_ARGUMENTS}
        {MAPPING_SIGNATURE_FINE_GRID_FACES_ARGUMENTS}
        ,DataRepository::_{logical_type_name}Stack[ DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack) ].top(0)
        {MAPPING_SIGNATURE_COARSE_GRID_VERTICES_ARGUMENTS}
        {MAPPING_SIGNATURE_COARSE_GRID_FACES_ARGUMENTS}
        {MAPPING_SIGNATURE_COARSE_GRID_CELL_ARGUMENTS}
    );
  }}
"""


  TemplateLeaveCell_CellStore_Epilogue = """  
  // Handle cell {name}
  {{
    const int inCellStack   = peano4::grid::PeanoCurve::CallStack;
    const int outCellStack  = event.getCellData();
    logDebug("leaveCell(peano4::grid::GridTraversalEvent)", "cell " << inCellStack << "->pos-" << outCellStack );

    {full_qualified_type} data = DataRepository::_{logical_type_name}Stack[ DataRepository::DataKey(_spacetreeId,inCellStack) ].pop();
    if (outCellStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity) {{
      DataRepository::_{logical_type_name}Stack[ DataRepository::DataKey(_spacetreeId,outCellStack) ].push(data);
    }}
  }}
"""


  TemplateLeaveCell_MappingCall = """  
  {{
    peano4::datamanagement::CellMarker marker(event.getIsRefined(),false);
    {ACTIVE_MAPPING}.touchCellLastTime(
      event.getX(), event.getH(),
      {MAPPING_SIGNATURE_FINE_GRID_VERTICES_ARGUMENTS}
      {MAPPING_SIGNATURE_FINE_GRID_FACES_ARGUMENTS}
      {MAPPING_SIGNATURE_FINE_GRID_CELL_ARGUMENTS}
      {MAPPING_SIGNATURE_COARSE_GRID_VERTICES_ARGUMENTS}
      {MAPPING_SIGNATURE_COARSE_GRID_FACES_ARGUMENTS}
      {MAPPING_SIGNATURE_COARSE_GRID_CELL_ARGUMENTS}
      marker
    );
  }}
"""



  TemplateLeaveCell_Epilogue = """  
  logTraceOut( "leaveCell(peano4::grid::GridTraversalEvent)" );
}}
"""


  def __generate_leaveCell(self,output_file):
    """
      Generates enter cell
    """
    output_file.write( self.TemplateLeaveCell_Prologue.format(**self.d) )
          
    for cell in self.cells:
      self.d[ "name" ]                 = cell.name
      #self.d[ "enumeration_type" ]     = cell.get_enumeration_type()
      self.d[ "logical_type_name" ]    = cell.get_logical_type_name()
      self.d[ "full_qualified_type" ]  = cell.get_full_qualified_type()
      self.__format_template_per_mapping(output_file, self.TemplateLeaveCell_CellStore_MappingCall, False)
      output_file.write( self.TemplateLeaveCell_CellStore_Epilogue.format(**self.d) )

    for face in self.faces:
      self.d[ "name" ]                 = face.name
      self.d[ "enumeration_type" ]     = face.get_enumeration_type()
      self.d[ "logical_type_name" ]    = face.get_logical_type_name()
      self.d[ "full_qualified_type" ]  = face.get_full_qualified_type()
      pass
      #output_file.write( self.TemplateEnterCell_FaceLoad.format(**self.d) )
        
    for vertices in self.vertices:
      #output_file.write( self.TemplateEnterCell_FaceLoad.format(**self.d) )
      pass

    output_file.write( self.TemplateLeaveCell_Epilogue.format(**self.d) )


  TemplateImplementationFilePrologue = """
#include "{CLASSNAME}.h"
#include "DataRepository.h"
#include "peano4/grid/PeanoCurve.h"



tarch::logging::Log {FULL_QUALIFIED_CLASSNAME}::_log( "{FULL_QUALIFIED_CLASSNAME}" );

"""


  def __generate_implementation(self,overwrite,full_qualified_filename):
    if writeFile(overwrite,self.default_overwrite,full_qualified_filename):
      print( "write " + full_qualified_filename )
      output_file = open( full_qualified_filename, "w" )
      output_file.write( self.TemplateImplementationFilePrologue.format(**self.d) )
      
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

