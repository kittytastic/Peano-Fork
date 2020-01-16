# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from peano4.solversteps.Mapping import Mapping


# @todo getter einfuehren, so dass man sieht was gen Observer geht und was net
# @todo Konstanten fuer ops

class PlotPatchesInPeanoBlockFormat(Mapping):
  """
  Very simple plotter that should be used in combination with Patches.
  At the moment, I only support plain double patches, i.e. you have to 
  use the default source code generator for your stuff.
  """
  
  
  def __init__(self,filename,patch):
    self.d = {}
    self.d[ "FILENAME" ]           = filename
    self.d[ "UNKNOWNS" ]           = str(patch.no_of_unknowns)
    
    #self.dim       = dim
    #self.no_of_unknowns = no_of_unknowns

  __Template_Constructor = """
  static int counter = 0;
  static tarch::multicore::BooleanSemaphore booleanSemaphore;
  tarch::multicore::Lock lock(booleanSemaphore);
    
  _writer      = nullptr;
  _dataWriter  = nullptr;
  _treeNumber  = treeNumber;

  // An MPI lock (critical section) would be important!
    
  if (_treeNumber>=0) {{
    const bool newFile = tarch::mpi::Rank::getInstance().isGlobalMaster() and _counter==0;
    logDebug( "PlotGrid2PlotGridInPeanoBlockFormat1()", "created tree instance for " << treeNumber << ". Create new file=" << newFile);
    _writer = new tarch::plotter::griddata::blockstructured::PeanoTextPatchFileWriter(
      Dimensions,"{FILENAME}", not newFile
    );
    _dataWriter = _writer->createCellDataWriter( "cell-marker", 1, {UNKNOWNS} );
    _counter = counter;
    counter++;
  }}
"""


  def get_constructor_body(self):
    return self.__Template_Constructor.format(**self.d)


  __Template_Destructor = """
  if (_dataWriter!=nullptr) {{
    _dataWriter->close();

    std::ostringstream filename;
    filename << "{FILENAME}" << "-tree-" << _treeNumber << "-" << _counter;
    _writer->writeToFile( filename.str() );

    delete _dataWriter;
    delete _writer;

    _dataWriter = nullptr;
    _writer     = nullptr;
  }}
"""

    
  def get_destructor_body(self):
    return self.__Template_Destructor.format(**self.d)


  def get_body_of_getGridControlEvents(self):
    return "  return std::vector< peano4::grid::GridControlEvent >();\n" 


  def get_mapping_name(self):
    return "PlotPatchesInPeanoBlockFormat"


  def user_should_modify_template(self):
    return False


  __Template_TouchCellFirstTime = """ 
  int vertexIndices[TwoPowerD];

  int indices = _writer->plotPatch(
    center - h * 0.5,
    h
  );

  assertion( _dataWriter!=nullptr );
  // @todo Use marker data here
 _dataWriter->plotCell(indices,1.0);
"""


  def get_body_of_operation(self,operation_name):
    result = "\n"
    if operation_name==Mapping.OPERATION_TOUCH_CELL_FIRST_TIME:
      result = self.__Template_TouchCellFirstTime.format(**self.d) 
    return result


  def get_attributes(self):
    return """
    int                _treeNumber;
    int                _counter;

    tarch::plotter::griddata::blockstructured::PeanoTextPatchFileWriter*                  _writer;
    tarch::plotter::griddata::blockstructured::PeanoTextPatchFileWriter::CellDataWriter*  _dataWriter;
"""


  def get_includes(self):
    return """
#include "tarch/plotter/griddata/blockstructured/PeanoTextPatchFileWriter.h"
#include "tarch/multicore/BooleanSemaphore.h"
#include "tarch/multicore/Lock.h"
#include "tarch/mpi/Rank.h"
"""
