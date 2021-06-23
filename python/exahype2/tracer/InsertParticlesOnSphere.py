# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from peano4.solversteps.ActionSet import ActionSet

import jinja2

import peano4.datamodel.DaStGen2

import dastgen2.attributes.Integer

import numpy as np

class InsertParticlesOnSphere(ActionSet):
  def __init__(self, particle_set, r=20, theta_s = 3, phi_s = 3 ):
    """
=

    particle_set: ParticleSet
 
    r: Float
     radius coordinates for the sampled sphere

    theta_s, phi_s
     number of sample points along angular coordinates on the sphere

    """

    self.d = {}
    self.d[ "PARTICLE" ]                 = particle_set.particle_model.name
    self.d[ "PARTICLES_CONTAINER" ]      = particle_set.name
    self.d[ "R" ]                        = r
    self.d[ "THETAS" ]                   = theta_s
    self.d[ "PHIS" ]                     = phi_s

  __Template_TouchVertexFirstTime = jinja2.Template("""
  int indice={{THETAS}}*{{PHIS}};
  double Pi=3.14159265358979;
  double thata_interval=(Pi-0.2)/({{THETAS}}-1);
  double phi_interval=(2*Pi)/{{PHIS}};
  double theta_s[{{THETAS}}], phi_s[{{PHIS}}];
  for (int i=0;i<{{THETAS}};i++) {theta_s[i] =0.1+i*thata_interval;}
  for (int i=0;i<{{PHIS}};i++)   {phi_s[i]   =i*phi_interval;}
  
  double coor_s[indice][3];
  for (int i=0;i<{{THETAS}};i++)
  for (int j=0;j<{{PHIS}};j++){
    coor_s[i*{{PHIS}}+j][0]={{R}}*cos(phi_s[j])*sin(theta_s[i]);
    coor_s[i*{{PHIS}}+j][1]={{R}}*sin(phi_s[j])*sin(theta_s[i]);
    coor_s[i*{{PHIS}}+j][2]={{R}}*cos(theta_s[i]);
  }
      
  for (int i=0;i<indice;i++){
	  if ( not marker.isRefined() and 
	  (marker.x()(0)-marker.h()(0)/2.0) < coor_s[i][0] and (marker.x()(0)+marker.h()(0)/2.0) > coor_s[i][0] and
	  (marker.x()(1)-marker.h()(1)/2.0) < coor_s[i][1] and (marker.x()(1)+marker.h()(1)/2.0) > coor_s[i][1] and
	  (marker.x()(2)-marker.h()(2)/2.0) < coor_s[i][2] and (marker.x()(2)+marker.h()(2)/2.0) > coor_s[i][2]
	  )
	  {
	    globaldata::{{PARTICLE}}* p = new globaldata::{{PARTICLE}}();
	    p->setNumber(0, _spacetreeId);
	    p->setNumber(1, _particleNumberOnThisTree);
	    p->setX(0, coor_s[i][0] );		// x coordinate
	    p->setX(1, coor_s[i][1] );		// y coordinate
	    p->setX(2, coor_s[i][2] );		// z coordinate
	    p->setCutOffRadius(0.0); 
	    _particleNumberOnThisTree++;
	    fineGridVertex{{PARTICLES_CONTAINER}}.push_back( p );
	    coor_s[i][0]= 99999; coor_s[i][1]= 99999; coor_s[i][2]= 99999;
	  }
	}
""")

  def get_body_of_operation(self,operation_name):
    result = "\n"
    if operation_name==ActionSet.OPERATION_TOUCH_VERTEX_FIRST_TIME:
      result = self.__Template_TouchVertexFirstTime.render(**self.d)
    return result


  def get_body_of_getGridControlEvents(self):
    return "  return std::vector< peano4::grid::GridControlEvent >();\n"


  def get_action_set_name(self):
    return __name__.replace(".py", "").replace(".", "_")
    

  def user_should_modify_template(self):
    return False


  def get_includes(self):
    result = jinja2.Template( """
#include "tarch/multicore/Lock.h"
#include "vertexdata/{{PARTICLES_CONTAINER}}.h"
#include "globaldata/{{PARTICLE}}.h"
#include "toolbox/particles/ParticleFactory.h"
""" )
    return result.render(**self.d)


  def get_constructor_body(self):
    return """
  _particleNumberOnThisTree = 0;
  _spacetreeId              = treeNumber;
"""


  def get_attributes(self):
     return """
  int _particleNumberOnThisTree;
  int _spacetreeId;
"""
#    result = jinja2.Template( """
#  std::forward_list< globaldata::{{PARTICLE}}* >  _activeParticles;
#""")
#    return result.render(**self.d)
