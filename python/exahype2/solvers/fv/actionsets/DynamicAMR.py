# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org

# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org
import peano4
import jinja2


import peano4.toolbox.blockstructured.DynamicAMR                 


class DynamicAMR( peano4.toolbox.blockstructured.DynamicAMR ):
  """
  
   The ExaHyPE 2 Finite Volume handling of (dynamically) adaptive meshes
   
   This class is basically a plain copy of the DynamicAMR action set
   from the toolbox. However, we have to ensure that we also set the
   update markers appropriately such that restricted data are taken 
   into account. This action set thus has to be studied in combination 
   with the ProjectPatchOntoFaces action set which is very similar and
   also enriches the toolbox version by this marker aspect.
  
  """
    #
    # Don't interpolate in initialisation. If you have a parallel run with AMR, then some 
    # boundary data has not been received yet and your face data thus is not initialised 
    # at all.
    #
  def __init__(self,solver):
    peano4.toolbox.blockstructured.DynamicAMR.__init__(self,      
      patch = solver._patch,
      patch_overlap_interpolation = solver._patch_overlap_old,
      patch_overlap_restriction   = solver._patch_overlap_update,
      interpolate_guard           = """
  repositories::""" + solver.get_name_of_global_instance() + """.getSolverState()!=""" + solver._name + """::SolverState::GridInitialisation
""",
      additional_includes         = """
#include "../repositories/SolverRepository.h"
"""      
)
    self.__Template_DestroyHangingFace_Core += """
  bool isLeftEntryOnCoarseFaceLabel = marker.getSelectedFaceNumber() >= Dimensions;
  coarseGridFaces""" + solver._face_label.name + """(marker.getSelectedFaceNumber()).setUpdated( isLeftEntryOnCoarseFaceLabel ? 0 : 1,true);
"""

    self.__Template_CreateHangingFace_Core = """
    ::toolbox::blockstructured::interpolateOntoOuterHalfOfHaloLayer_AoS_{{INTERPOLATION_SCHEME}}(
      marker,
      {{DOFS_PER_AXIS}},
      {{OVERLAP}},
      {{UNKNOWNS}},
      fineGridFace""" + solver._name + """QOld.value,
      coarseGridFaces""" + solver._name + """QOld(marker.getSelectedFaceNumber()).value
    );
    ::toolbox::blockstructured::interpolateOntoOuterHalfOfHaloLayer_AoS_{{INTERPOLATION_SCHEME}}(
      marker,
      {{DOFS_PER_AXIS}},
      {{OVERLAP}},
      {{UNKNOWNS}},
      fineGridFace""" + solver._name + """QNew.value,
      coarseGridFaces""" + solver._name + """QNew(marker.getSelectedFaceNumber()).value
    );
"""
    

    # @todo Interpolate

  def get_action_set_name(self):
    return __name__.replace(".py", "").replace(".", "_")

