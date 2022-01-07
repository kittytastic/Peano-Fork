#include "PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4.h"


tarch::logging::Log project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::_log( "project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4");





project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4(int treeNumber) {
}


project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::~PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4() {
}


std::vector< peano4::grid::GridControlEvent > project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::getGridControlEvents() const {
  return std::vector< peano4::grid::GridControlEvent >();
}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::beginTraversal(
      ) {


}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::endTraversal(
      ) {


}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::createPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::destroyPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::createHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::destroyHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::touchFaceFirstTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::touchFaceLastTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::createCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::destroyCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::touchCellFirstTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::base_2d_euler::observers::PlotSolution2exahype2_solvers_fv_actionsets_ProjectPatchOntoFaces4::touchCellLastTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

  if ( not marker.hasBeenRefined() and not marker.willBeRefined() and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridConstruction ) {
    logTraceIn( "touchCellLastTime(...)---ProjectPatchOntoFaces" );

    for(int d=0; d<Dimensions; d++) {
      /**
       * d-loop over all dimensions except d. The vector k's entry d is set
       * to 0. We start with the left/bottom face, i.e. the one closer to the 
       * coordinate system's origin.
       */
      dfore(k,3,d,0) {
        for (int i=0; i<1; i++) {
          tarch::la::Vector<Dimensions,int> patchCell   = k;
          tarch::la::Vector<Dimensions,int> overlapCell = k;
          patchCell(d)   = i;
          overlapCell(d) = i+1;
          
          int patchCellSerialised   = peano4::utils::dLinearised(patchCell,3);
          int overlapCellSerialised = toolbox::blockstructured::serialisePatchIndexInOverlap(overlapCell,3,1,d);
          for (int j=0; j<4; j++) {
            assertion7( 
              false
              or
              fineGridCelleuler2DQ.value[patchCellSerialised*4+j]==fineGridCelleuler2DQ.value[patchCellSerialised*4+j], j,i,k,d, patchCell, overlapCell,
              marker.toString() 
            );
            fineGridFaceseuler2DQUpdate(d).value[overlapCellSerialised*4+j] = 
              fineGridCelleuler2DQ.value[patchCellSerialised*4+j];
          }
  
          patchCell(d)   = i+3-1;
          overlapCell(d) = i;
          
          patchCellSerialised   = peano4::utils::dLinearised(patchCell,3);
          overlapCellSerialised = toolbox::blockstructured::serialisePatchIndexInOverlap(overlapCell,3,1,d);
          for (int j=0; j<4; j++) {
            assertion7( 
              false
              or
              fineGridCelleuler2DQ.value[patchCellSerialised*4+j]==fineGridCelleuler2DQ.value[patchCellSerialised*4+j], j,i,k,d, patchCell, overlapCell, 
              marker.toString() 
            );
            fineGridFaceseuler2DQUpdate(d+Dimensions).value[overlapCellSerialised*4+j] = 
              fineGridCelleuler2DQ.value[patchCellSerialised*4+j];
          }
        }
      }
    }

  for (int d=0; d<Dimensions; d++) {
    fineGridFaceseuler2DFaceLabel(d).setUpdated(1,true);
    fineGridFaceseuler2DFaceLabel(d).setUpdatedTimeStamp(1,fineGridCelleuler2DCellLabel.getTimeStamp());
    fineGridFaceseuler2DFaceLabel(d+Dimensions).setUpdated(0,true);
    fineGridFaceseuler2DFaceLabel(d+Dimensions).setUpdatedTimeStamp(0,fineGridCelleuler2DCellLabel.getTimeStamp());
    logDebug( "touchCellLastTime(...)", "update fineGridFaceseuler2DFaceLabel(" << d << ")(1)" );
    logDebug( "touchCellLastTime(...)", "update fineGridFaceseuler2DFaceLabel(" << (d+Dimensions) << ")(0)" );
  }  

    logTraceOut( "touchCellLastTime(...)---ProjectPatchOntoFaces" );
  }
  else {
    logTraceInWith1Argument( "touchCellLastTime(...)---ProjectPatchOntoFaces [skip]", marker.toString() );
    logTraceOut( "touchCellLastTime(...)---ProjectPatchOntoFaces [skip]" );
  }

}


