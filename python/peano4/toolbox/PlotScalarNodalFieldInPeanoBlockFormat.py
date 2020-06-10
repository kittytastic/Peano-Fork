# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from peano4.solversteps.ActionSet import ActionSet



class PlotScalarNodalFieldInPeanoBlockFormat(ActionSet):
  def __init__(self,filename,vertex_unknown,getter):
    """
      Plot only the grid structure
      
      filename         Name of the output file
      vertex_unknown   The object you have associated with a vertex and that you want to print
      getter           Getter acting on the vertex. Could be something alike getU() for example.
                       If there's no getter but you want to directly access the data, remove 
                       any brackets from the passed string.
    """
    self.d = {}
    self.d[ "FILENAME" ]            = filename
    self.d[ "VERTEX_UNKNOWN_NAME" ] = vertex_unknown.name
    self.d[ "GETTER" ]              = getter
        

  __Template_Constructor = """
  _writer      = nullptr;
  _dataWriter  = nullptr;
  _treeNumber  = treeNumber;

  // An MPI lock (critical section) would be important!
    
  logDebug( "PlotGrid2PlotGridInPeanoBlockFormat1()", "created tree instance for " << treeNumber );
"""


  def get_constructor_body(self):
    return self.__Template_Constructor.format(**self.d)


  __Template_Destructor = """
  static int rankLocalCounter = 0;
  static tarch::multicore::BooleanSemaphore booleanSemaphore;
  
  if (_dataWriter!=nullptr and _treeNumber>=0) {{
    _dataWriter->close();

    int counter;
    {{
      tarch::multicore::Lock lock(booleanSemaphore);
      counter = rankLocalCounter;
      rankLocalCounter++;
    }}

    std::ostringstream filename;
    filename << "{FILENAME}" << "-tree-" << _treeNumber << "-" << counter;
    _writer->writeToFile( filename.str() );
  }}
  
  delete _dataWriter;
  delete _writer;

  _dataWriter = nullptr;
  _writer     = nullptr;
"""

    
  def get_destructor_body(self):
    return self.__Template_Destructor.format(**self.d)


  def get_body_of_getGridControlEvents(self):
    return "  return std::vector< peano4::grid::GridControlEvent >();\n" 


  def get_action_set_name(self):
    return __name__.replace(".py", "").replace(".", "_")


  def user_should_modify_template(self):
    return False


  __Template_TouchCellFirstTime = """ 
  int vertexIndices[TwoPowerD];

  int patchIndex = _writer->plotPatch(
    marker.x()-0.5 * marker.h(),
    marker.h()
  );

  assertion( _dataWriter!=nullptr );
  int vertexIndex  = _dataWriter->getFirstVertexWithinPatch(patchIndex);
  dfor2(k)
    auto data = fineGridVertices{VERTEX_UNKNOWN_NAME}(kScalar).{GETTER};
    _dataWriter->plotVertex( vertexIndex, data );
    vertexIndex++;
  enddforx
"""


  __Template_BeginTraversal = """
  static bool calledBefore = false;
  if ( _treeNumber==0 and not calledBefore ) {{
    calledBefore = true;
    _writer = new tarch::plotter::griddata::blockstructured::PeanoTextPatchFileWriter(
      Dimensions,"{FILENAME}",
      tarch::plotter::griddata::blockstructured::PeanoTextPatchFileWriter::IndexFileMode::CreateNew
    );
    tarch::mpi::Rank::getInstance().barrier();
  }}
  else if ( _treeNumber==0 ) {{
    _writer = new tarch::plotter::griddata::blockstructured::PeanoTextPatchFileWriter(
      Dimensions,"{FILENAME}",
      tarch::plotter::griddata::blockstructured::PeanoTextPatchFileWriter::IndexFileMode::AppendNewDataSet
    );
    tarch::mpi::Rank::getInstance().barrier();
  }}
  else {{
    tarch::mpi::Rank::getInstance().barrier();
    static tarch::mpi::BooleanSemaphore globalSempahore( "{FILENAME}" );
    tarch::mpi::Lock lock(globalSempahore);
    _writer = new tarch::plotter::griddata::blockstructured::PeanoTextPatchFileWriter(
      Dimensions,"{FILENAME}",
      tarch::plotter::griddata::blockstructured::PeanoTextPatchFileWriter::IndexFileMode::DontChange
    );
  }}  
  
  
  _dataWriter = _writer->createVertexDataWriter( "{VERTEX_UNKNOWN_NAME}", 2, 1 );
"""


  def get_body_of_operation(self,operation_name):
    result = "\n"
    if operation_name==ActionSet.OPERATION_TOUCH_CELL_FIRST_TIME:
      result = self.__Template_TouchCellFirstTime.format(**self.d) 
    if operation_name==ActionSet.OPERATION_BEGIN_TRAVERSAL:
      result = self.__Template_BeginTraversal.format(**self.d)             
    return result


  def get_attributes(self):
    return """
    int                _treeNumber;

    tarch::plotter::griddata::blockstructured::PeanoTextPatchFileWriter*                    _writer;
    tarch::plotter::griddata::blockstructured::PeanoTextPatchFileWriter::VertexDataWriter*  _dataWriter;
"""


  def get_includes(self):
    return """
#include "tarch/plotter/griddata/blockstructured/PeanoTextPatchFileWriter.h"
#include "tarch/mpi/Lock.h"
#include "tarch/multicore/Lock.h"
#include "tarch/multicore/BooleanSemaphore.h"
#include "peano4/utils/Loop.h"
"""
