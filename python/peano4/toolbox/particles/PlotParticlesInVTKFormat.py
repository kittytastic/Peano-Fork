# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from peano4.solversteps.ActionSet import ActionSet


import jinja2


   


class PlotParticlesInVTKFormat(ActionSet):
  """
  
   By default, I plot the point particles (obviously) and drop their
   coordinates as vector, too. I also plot the cut-off radius which 
   is a simple scalar. I often use it to colour-code or as radius 
   of the rendered sphere. 
   
   Finally, I do render the associativity. This is one vector per 
   point that points towards the vertex the object belongs to. To
   visualise it, add a Glyph filter and select association as 
   orientation array. Make association also the scale array and 
   scale by magnitude.
   
  """
  def __init__(self,filename,particle_set):
    """
      Plot only the grid structure
      
      :Attibutes:
      
      filename: String
         Name of the output file.
         
      particle: ParticleSet
         I take this as particle set and I assume that it yields a C++ 
         container which I can traverse.
          
    """
    self.d = {}
    self.d[ "FILENAME" ]            = filename
    self.d[ "PARTICLE" ]            = particle_set.particle_model.name
    self.d[ "PARTICLES_CONTAINER" ] = particle_set.name
    self.d[ "WRITE_BINARY" ]        = "false"

  __Template_Constructor = jinja2.Template("""
  _writer             = nullptr;
  _positionWriter     = nullptr;
  _cutOffWriter       = nullptr;
  _associationWriter  = nullptr;
  _treeNumber         = treeNumber;

  // An MPI lock (critical section) would be important!
    
  logDebug( "PlotGrid2PlotGridInPeanoBlockFormat1()", "created tree instance for " << treeNumber );
""")


  def get_constructor_body(self):
    return self.__Template_Constructor.render(**self.d)

    
  def get_destructor_body(self):
    return ""


  def get_body_of_getGridControlEvents(self):
    return "  return std::vector< peano4::grid::GridControlEvent >();\n" 


  def get_action_set_name(self):
    return __name__.replace(".py", "").replace(".", "_")


  def user_should_modify_template(self):
    return False

  __Template_TouchVertexFirstTime = jinja2.Template(""" 
  assertion( _positionWriter!=nullptr );
  for (auto& p: fineGridVertex{{PARTICLES_CONTAINER}}) {
    int particleNumber = _writer->plotPoint(p->getX());
    _positionWriter->plot(particleNumber,p->getX());
    _cutOffWriter->plot(particleNumber,p->getCutOffRadius());
    _associationWriter->plot(particleNumber,marker.x()-p->getX());
  }
""")


  __Template_BeginTraversal = jinja2.Template("""
  static int rankLocalCounter = 0;
  static tarch::mpi::BooleanSemaphore booleanSemaphore("{{FILENAME}}");
  static bool calledBefore = false;
  
  int counter;
  {
    tarch::mpi::Lock lock(booleanSemaphore);
    counter = rankLocalCounter;
    rankLocalCounter++;
  }
  std::ostringstream snapshotFileName;
  snapshotFileName << "{{FILENAME}}" << "-tree-" << _treeNumber << "-" << counter;
  
  // This stuff only ensures that the overview file remains correct. The 
  // sync and add of the individual dumps is then managed within the actual
  // plotter files.
  if ( _treeNumber==0 and not calledBefore ) {
    calledBefore = true;
    _writer     = new tarch::plotter::pointdata::vtk::VTKWriter({{WRITE_BINARY}}, snapshotFileName.str(), "{{FILENAME}}",tarch::plotter::PVDTimeSeriesWriter::IndexFileMode::CreateNew);
    ::peano4::parallel::SpacetreeSet::getInstance().orderedBarrier("{{FILENAME}}");
  }
  else if ( _treeNumber==0 ) {
    _writer     = new tarch::plotter::pointdata::vtk::VTKWriter({{WRITE_BINARY}}, snapshotFileName.str(), "{{FILENAME}}",tarch::plotter::PVDTimeSeriesWriter::IndexFileMode::AppendNewDataSet);
    ::peano4::parallel::SpacetreeSet::getInstance().orderedBarrier("{{FILENAME}}");
  }
  else {
    ::peano4::parallel::SpacetreeSet::getInstance().orderedBarrier("{{FILENAME}}");
    _writer     = new tarch::plotter::pointdata::vtk::VTKWriter({{WRITE_BINARY}}, snapshotFileName.str(), "{{FILENAME}}",tarch::plotter::PVDTimeSeriesWriter::IndexFileMode::AppendNewData);
  }

  _positionWriter    = _writer->createPointDataWriter( "x", 3 );
  _cutOffWriter      = _writer->createPointDataWriter( "cut-off-radius", 1 );
  _associationWriter = _writer->createPointDataWriter( "association", 3 );
""")


  __Template_EndTraversal = jinja2.Template("""
  assertion(_positionWriter!=nullptr);
 
  _positionWriter->close();
  _cutOffWriter->close();
  _associationWriter->close();
  _writer->writeToFile();
  
  delete _positionWriter;
  delete _cutOffWriter;
  delete _associationWriter;
  delete _writer;

  _positionWriter    = nullptr;
  _cutOffWriter      = nullptr;
  _associationWriter = nullptr;
  _writer            = nullptr;
""")

  def get_body_of_operation(self,operation_name):
    result = "\n"
    if operation_name==ActionSet.OPERATION_TOUCH_VERTEX_FIRST_TIME:
      result = self.__Template_TouchVertexFirstTime.render(**self.d) 
    if operation_name==ActionSet.OPERATION_BEGIN_TRAVERSAL:
      result = self.__Template_BeginTraversal.render(**self.d)             
    if operation_name==ActionSet.OPERATION_END_TRAVERSAL:
      result = self.__Template_EndTraversal.render(**self.d)             
    return result


  def get_attributes(self):
    return """
    int                _treeNumber;

    tarch::plotter::pointdata::vtk::VTKWriter*                _writer;
    tarch::plotter::pointdata::PointWriter::PointDataWriter*  _positionWriter;
    tarch::plotter::pointdata::PointWriter::PointDataWriter*  _cutOffWriter;
    tarch::plotter::pointdata::PointWriter::PointDataWriter*  _associationWriter;
"""


  def get_includes(self):
    return """
#include "tarch/plotter/pointdata/vtk/VTKWriter.h"
#include "tarch/multicore/Lock.h"
#include "tarch/multicore/BooleanSemaphore.h"
#include "tarch/mpi/Lock.h"
#include "peano4/parallel/SpacetreeSet.h"
#include "../vertexdata/""" + self.d["PARTICLES_CONTAINER"] + """.h"
#include "../globaldata/""" + self.d["PARTICLE"] + """.h"
"""
