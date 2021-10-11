# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from peano4.solversteps.ActionSet import ActionSet

import peano4.toolbox.particles

import jinja2



class DumpTrajectoryIntoDatabase(peano4.solversteps.ActionSet):
  def __init__(self, particle_set, solver, filename, number_of_entries_between_two_db_flushes=65536, data_delta_between_two_snapsots=1e-8, position_delta_between_two_snapsots=1e-8, output_precision=8):
    """
     
    data_delta_between_two_snapsots: Float
     A particle is dumped into the database if it has switched the domain 
     partition or its position has changed more then delta_between_two_snapshots. 
     See toolbox::particles::TrajectoryDatabase::getAction() for a description 
     how the C++ code interprets this threshold, but it is usually the max norm
     that is used here. If you set it to a very small number, you'll get a lot 
     of entries in your database. 
     
    position_delta_between_two_snapsots: Float
     Similar to data_delta_between_two_snapsots but this time it is not the
     difference in the data that triggers a dump into the database, but a change
     of position. Obviously, these things can be totally independent (and also can
     be combined), as particles that move with the domain might not change their 
     value, as theyare tracer, while stationary seismograms usually do not change
     their position at all.
     
    number_of_entries_between_two_db_flushes: Int
      Number of entries that we dump into the database before it is flushed the next
      time. Set it to max of an integer or zero to disable on-the-fly dumps. In this
      case, the database is only flushed when the simulation terminates. So, the
      thresholds data_delta_between_two_snapsots and position_delta_between_two_snapsots
      determine how often entries and up in the database, and number_of_entries_between_two_db_flushes
      determines how often this database is written into a file.
     
    """
    self.d = {}
    self.d[ "PARTICLE" ]                 = particle_set.particle_model.name
    self.d[ "PARTICLES_CONTAINER" ]      = particle_set.name
    self.d[ "DATA_DELTA" ]               = data_delta_between_two_snapsots
    self.d[ "POSITION_DELTA" ]           = position_delta_between_two_snapsots
    self.d[ "OUTPUT_PRECISION"]          = output_precision
    self.d[ "FILENAME" ]                 = filename
    self.d[ "SOLVER_NAME" ]              = solver._name
    self.d[ "SOLVER_INSTANCE" ]          = solver.get_name_of_global_instance()

    self.number_of_entries_between_two_db_flushes = number_of_entries_between_two_db_flushes

  __Template_TouchCellLastTime = jinja2.Template("""
if ( not marker.isRefined() and fineGridCell{{SOLVER_NAME}}CellLabel.getHasUpdated() ) {
  for (int i=0; i<TwoPowerD; i++) {
    for (auto& p: fineGridVertices{{PARTICLES_CONTAINER}}(i) ) {
      if (
        p->getParallelState()==globaldata::{{PARTICLE}}::ParallelState::Local
        and
        marker.isContained( p->getX() )
      ) {
        _database.addParticleSnapshot( 
          p->getNumber(0), 
          p->getNumber(1),
          fineGridCell{{SOLVER_NAME}}CellLabel.getTimeStamp(),
          p->getX(),
          p->getData().size(),
          p->getData().data()
        );
      }
    }
  }
}
""")
  

  def get_body_of_operation(self,operation_name):
    result = ""
    if operation_name==ActionSet.OPERATION_TOUCH_CELL_LAST_TIME:
      result = self.__Template_TouchCellLastTime.render(**self.d)
    return result


  def get_action_set_name(self):
    return __name__.replace(".py", "").replace(".", "_")
    

  def user_should_modify_template(self):
    return False


  def get_constructor_body(self):
    template = jinja2.Template("""
  _database.setOutputFileName( "{{FILENAME}}" );
  _database.setOutputPrecision( {{OUTPUT_PRECISION}} );
  _database.setDataDeltaBetweenTwoSnapshots( {{DATA_DELTA}} );
  _database.setPositionDeltaBetweenTwoSnapshots( {{POSITION_DELTA}} );
""")
    return template.render(**self.d)


  def get_includes(self):
    result = jinja2.Template( """
#include "toolbox/particles/TrajectoryDatabase.h"
#include "vertexdata/{{PARTICLES_CONTAINER}}.h"
#include "globaldata/{{PARTICLE}}.h"
#include "peano4/parallel/Node.h"
#include "repositories/SolverRepository.h"
""" )
    return result.render(**self.d)
    

  def get_attributes(self):
    return """
    static toolbox::particles::TrajectoryDatabase  _database;
"""

  def get_static_initialisations(self,full_qualified_classname):
    return """
toolbox::particles::TrajectoryDatabase  """ + full_qualified_classname + """::_database( """ + str(self.number_of_entries_between_two_db_flushes) + """);
"""

