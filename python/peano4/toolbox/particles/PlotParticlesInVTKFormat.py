# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from peano4.solversteps.ActionSet import ActionSet


import jinja2


class PlotParticlesInVTKFormat(ActionSet):
  NoMetaFile = "no-meta-file"
  CountTimeSteps = "count-time-steps"

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
  def __init__(self,filename,particle_set,time_stamp_evaluation=NoMetaFile,additional_includes=""):
    """
      Plot only the grid structure

      :Attibutes:

      filename: String
         Name of the output file.

      particle: ParticleSet
         I take this as particle set and I assume that it yields a C++
         container which I can traverse.
         
      time_stamp_evaluation: String yielding a C++ double
         Pass in something negative if want to disable the met file feature
         where multiple particle snapshots are organised as one video/collection.

    """
    self.d = {}
    self.d[ "FILENAME" ]                           = filename
    self.d[ "PARTICLE" ]                           = particle_set.particle_model.name
    self.d[ "PARTICLES_CONTAINER" ]                = particle_set.name
    self.d[ "WRITE_BINARY" ]                       = "false"
    self.d[ "ATTRIBUTE_WRITER_NULL_INITIALISERS" ] = ""
    self.d[ "ATTRIBUTE_WRITER_CLOSES" ]            = ""
    self.d[ "ATTRIBUTE_WRITER_DELETES" ]           = ""
    self.d[ "ATTRIBUTE_WRITER_INITIALISERS" ]      = ""
    self.d[ "ATTRIBUTE_WRITER_PLOT_CALLS" ]        = ""
    self.d[ "TIMESTAMP" ]                          = time_stamp_evaluation
    
    self._attributes_to_plot = []
    
    self.additional_includes                       = additional_includes
    

  __Template_Constructor = jinja2.Template("""
  _writer             = nullptr;
  _positionWriter     = nullptr;
  _cutOffWriter       = nullptr;
  _associationWriter  = nullptr;
  {{ATTRIBUTE_WRITER_NULL_INITIALISERS}}
  _treeNumber         = treeNumber;

  // An MPI lock (critical section) would be important!

  logDebug( "PlotGrid2PlotGridInPeanoBlockFormat1()", "created tree instance for " << treeNumber );
""")


  def add_attribute_to_plot(self, attribute, cardinality=1):
      self._attributes_to_plot.append(attribute)
      writer_name = f"{attribute.get_to_string()}Writer"
      delim = "\n  "
      name_no_underscore = attribute.get_to_string()[1:]
      accessor_name = name_no_underscore[0].title() + name_no_underscore[1:]

      self.d[ "ATTRIBUTE_WRITER_NULL_INITIALISERS" ] += f"{delim}{writer_name} = nullptr;"
      self.d[ "ATTRIBUTE_WRITER_CLOSES" ]            += f"{delim}{writer_name}->close();"
      self.d[ "ATTRIBUTE_WRITER_DELETES" ]           += f"{delim}delete {writer_name};"
      self.d[ "ATTRIBUTE_WRITER_INITIALISERS" ]      += f"{delim}{writer_name} = _writer->createPointDataWriter( \"{name_no_underscore}\", {cardinality} );"
      if writer_name=="_dataWriter":
        self.d[ "ATTRIBUTE_WRITER_PLOT_CALLS" ]        += f"{delim}  _dataWriter->plot(particleNumber,p->getData().data(),{cardinality});" 
      else:
        self.d[ "ATTRIBUTE_WRITER_PLOT_CALLS" ]        += f"{delim}  {writer_name}->plot(particleNumber,p->get{accessor_name}());"

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
    if (
      p->getParallelState()==globaldata::{{PARTICLE}}::ParallelState::Local
    ) {
      int particleNumber = _writer->plotPoint(p->getX());
      _positionWriter->plot(particleNumber,p->getX());
      _cutOffWriter->plot(particleNumber,p->getCutOffRadius());
      _associationWriter->plot(particleNumber,marker.x()-p->getX());
      {{ATTRIBUTE_WRITER_PLOT_CALLS}}
    }
  }
""")


  __Template_BeginTraversal = jinja2.Template("""
  tarch::mpi::Lock lock( _semaphore );
  
  static int counter = -1;
  counter++;

  std::ostringstream snapshotFileName;
  snapshotFileName << "{{FILENAME}}-" << counter;

  if (tarch::mpi::Rank::getInstance().getNumberOfRanks()>0 ) {
    snapshotFileName << "-rank-" << tarch::mpi::Rank::getInstance().getRank();
  }
  
  {% if TIMESTAMP==\"""" + NoMetaFile + """\" %}
  _writer = new tarch::plotter::pointdata::vtk::VTKWriter(
    false, snapshotFileName.str(), "{{FILENAME}}",
    tarch::plotter::PVDTimeSeriesWriter::IndexFileMode::NoIndexFile,
    0.0
  );
  {% elif TIMESTAMP==\"""" + CountTimeSteps + """\" %}
  static int timeStep = -1;
  timeStep++;
  _writer = new tarch::plotter::pointdata::vtk::VTKWriter(
    false, snapshotFileName.str(), "{{FILENAME}}",
    tarch::plotter::PVDTimeSeriesWriter::IndexFileMode::AppendNewData,
    timeStep
  );
  {% else %}
  _writer = new tarch::plotter::pointdata::vtk::VTKWriter(
    false, snapshotFileName.str(), "{{FILENAME}}",
    tarch::plotter::PVDTimeSeriesWriter::IndexFileMode::AppendNewData,
    {{TIMESTAMP}}
  );    
  {% endif %}
      
  _positionWriter    = _writer->createPointDataWriter( "x", 3 );
  _cutOffWriter      = _writer->createPointDataWriter( "cut-off-radius", 1 );
  _associationWriter = _writer->createPointDataWriter( "association", 3 );
  {{ATTRIBUTE_WRITER_INITIALISERS}}
""")


  __Template_EndTraversal = jinja2.Template("""
  assertion(_positionWriter!=nullptr);

  _positionWriter->close();
  _cutOffWriter->close();
  _associationWriter->close();
  {{ATTRIBUTE_WRITER_CLOSES}}
  _writer->writeToFile();

  delete _positionWriter;
  delete _cutOffWriter;
  delete _associationWriter;
  {{ATTRIBUTE_WRITER_DELETES}}
  delete _writer;

  _positionWriter    = nullptr;
  _cutOffWriter      = nullptr;
  _associationWriter = nullptr;
  {{ATTRIBUTE_WRITER_NULL_INITIALISERS}}
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


  def _get_attribute_writer_declarations(self):
      delim = "\n    "
      datatype = "tarch::plotter::pointdata::PointWriter::PointDataWriter*"
      return delim.join(f"{datatype}  {attr.get_to_string()}Writer;"
                          for attr in self._attributes_to_plot)


  def get_attributes(self):
    return f"""
    static tarch::mpi::BooleanSemaphore                                              _semaphore;
    
    int                _treeNumber;

    tarch::plotter::pointdata::vtk::VTKWriter*                _writer;
    tarch::plotter::pointdata::PointWriter::PointDataWriter*  _positionWriter;
    tarch::plotter::pointdata::PointWriter::PointDataWriter*  _cutOffWriter;
    tarch::plotter::pointdata::PointWriter::PointDataWriter*  _associationWriter;
    {self._get_attribute_writer_declarations()}
"""


  def get_includes(self):
    return """
#include "tarch/plotter/pointdata/vtk/VTKWriter.h"
#include "tarch/multicore/Lock.h"
#include "tarch/multicore/BooleanSemaphore.h"
#include "tarch/mpi/Lock.h"
#include "tarch/mpi/BooleanSemaphore.h"
#include "peano4/parallel/SpacetreeSet.h"
#include "../vertexdata/""" + self.d["PARTICLES_CONTAINER"] + """.h"
#include "../globaldata/""" + self.d["PARTICLE"] + """.h"
""" + self.additional_includes



  def get_static_initialisations(self,full_qualified_classname):
    return """
tarch::mpi::BooleanSemaphore  """ + full_qualified_classname + "::_semaphore(\"""" + full_qualified_classname + """\");
"""
    
