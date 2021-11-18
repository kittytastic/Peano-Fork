# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org

from .AbstractFVActionSet import AbstractFVActionSet

import peano4
import jinja2

class HandleBoundary(AbstractFVActionSet):
  """
  
    The global periodic boundary conditions are set in the Constants.h. 
    
    There is no need to update QOld along the faces. QOld is always rolled
    over from QNew, i.e. we may assume it is already set correctly. It is 
    not correctly set in the very first time step (after InitGrid, we haven't
    yet set QOld), so apply the boundary conditions here would even confuse
    the assertions.
   
  """
  TemplateHandleBoundary = """
    if (
      {{PREDICATE}}
      and
      not repositories::{{SOLVER_INSTANCE}}.PeriodicBC[marker.getSelectedFaceNumber()%Dimensions]
      and
      not marker.hasBeenRefined() 
      and 
      fineGridFace{{SOLVER_NAME}}FaceLabel.getBoundary()
    ) {
      logTraceInWith3Arguments( "touchFaceFirstTime(...)", fineGridFace{{SOLVER_NAME}}FaceLabel.toString(), (repositories::{{SOLVER_INSTANCE}}.PeriodicBC[marker.getSelectedFaceNumber()%Dimensions]), marker.toString() );
      ::exahype2::fv::applyBoundaryConditions(
        [&](
          const double * __restrict__                  Qinside,
          double * __restrict__                        Qoutside,
          const tarch::la::Vector<Dimensions,double>&  faceCentre,
          const tarch::la::Vector<Dimensions,double>&  volumeH,
          double                                       t,
          double                                       dt,
          int                                          normal
        ) -> void {
          repositories::{{SOLVER_INSTANCE}}.boundaryConditions( Qinside, Qoutside, faceCentre, volumeH, t, normal );
        },  
        marker.x(),
        marker.h(),
        {{FACE_METADATA_ACCESSOR}}.getNewTimeStamp(marker.getSelectedFaceNumber()<Dimensions ? 1 : 0),
        repositories::{{SOLVER_INSTANCE}}.getMinTimeStepSize(),
        {{NUMBER_OF_VOLUMES_PER_AXIS}},
        {{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}},
        marker.getSelectedFaceNumber(),
        fineGridFace{{UNKNOWN_IDENTIFIER}}New.value
      );
      ::exahype2::fv::applyBoundaryConditions(
        [&](
          const double * __restrict__                  Qinside,
          double * __restrict__                        Qoutside,
          const tarch::la::Vector<Dimensions,double>&  faceCentre,
          const tarch::la::Vector<Dimensions,double>&  volumeH,
          double                                       t,
          double                                       dt,
          int                                          normal
        ) -> void {
          repositories::{{SOLVER_INSTANCE}}.boundaryConditions( Qinside, Qoutside, faceCentre, volumeH, t, normal );
        },  
        marker.x(),
        marker.h(),
        {{FACE_METADATA_ACCESSOR}}.getOldTimeStamp(marker.getSelectedFaceNumber()<Dimensions ? 1 : 0),
        repositories::{{SOLVER_INSTANCE}}.getMinTimeStepSize(),
        {{NUMBER_OF_VOLUMES_PER_AXIS}},
        {{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}},
        marker.getSelectedFaceNumber(),
        fineGridFace{{UNKNOWN_IDENTIFIER}}Old.value
      );
      
      bool isLeftEntryOutside = marker.getSelectedFaceNumber() < Dimensions;
      double innerTimeStamp;
      
      innerTimeStamp = {{FACE_METADATA_ACCESSOR}}.getUpdatedTimeStamp( isLeftEntryOutside ? 1 : 0 );
      {{FACE_METADATA_ACCESSOR}}.setUpdatedTimeStamp( isLeftEntryOutside ? 0 : 1, innerTimeStamp );
      
      innerTimeStamp = {{FACE_METADATA_ACCESSOR}}.getNewTimeStamp( isLeftEntryOutside ? 1 : 0 );
      {{FACE_METADATA_ACCESSOR}}.setNewTimeStamp( isLeftEntryOutside ? 0 : 1, innerTimeStamp );

      innerTimeStamp = {{FACE_METADATA_ACCESSOR}}.getOldTimeStamp( isLeftEntryOutside ? 1 : 0 );
      {{FACE_METADATA_ACCESSOR}}.setOldTimeStamp( isLeftEntryOutside ? 0 : 1, innerTimeStamp );

      logTraceOut( "touchFaceFirstTime(...)" );
    }
    else {
      logDebug( "touchFaceFirstTime(...)", "skip face " << marker.toString() );
    }
"""

  def __init__(self,solver,guard):
    AbstractFVActionSet.__init__(self,solver)
    self.guard = guard


  def get_body_of_operation(self,operation_name):
    result = ""
    if operation_name==peano4.solversteps.ActionSet.OPERATION_TOUCH_FACE_FIRST_TIME:
      self.d = {}
      self._solver._init_dictionary_with_default_parameters(self.d)
      self._solver.add_entries_to_text_replacement_dictionary(self.d)
      self.d[ "PREDICATE" ] = self.guard      
      self.d[ "FACE_METADATA_ACCESSOR" ] = "fineGridFace"  + self._solver._face_label.name
      result = jinja2.Template(self.TemplateHandleBoundary).render(**self.d)
      pass 
    return result


  def get_includes(self):
    return """
#include "exahype2/PatchUtils.h"
#include "exahype2/fv/BoundaryConditions.h"
""" + AbstractFVActionSet.get_includes(self) 


  def get_action_set_name(self):
    return __name__.replace(".py", "").replace(".", "_")
