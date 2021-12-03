#include "TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1.h"


tarch::logging::Log project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::_log( "project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1");





project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1(int treeNumber) {
// @todo Should be overwritten
}


project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::~TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1() {
// @todo Should be overwritten
}


std::vector< peano4::grid::GridControlEvent > project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::getGridControlEvents() const {
return std::vector< peano4::grid::GridControlEvent >();
}


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::beginTraversal(
      ) {

}


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::endTraversal(
      ) {

}


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::createPersistentFace(
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


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::destroyPersistentFace(
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


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::createHangingFace(
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


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::destroyHangingFace(
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


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::touchFaceFirstTime(
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


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::touchFaceLastTime(
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

    if ( not marker.willBeRefined() and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridConstruction ) {
      logTraceInWith2Arguments( "touchFaceLastTime(...)---RollOverUpdatedFace", fineGridFaceeuler2DFaceLabel.toString(), marker.toString() );
      
      const int normal = marker.getSelectedFaceNumber() % Dimensions;
      // Left half
      if (fineGridFaceeuler2DFaceLabel.getUpdated(0)) {
        logTraceIn( "touchFaceLastTime(...)---RollOverUpdatedFace (roll over updated left half of face)"  );
        dfore(k,3,normal,0) {
          for (int i=0; i<1; i++) {
            tarch::la::Vector<Dimensions,int> overlapCell = k;
            overlapCell(normal) = i;
            const int index = toolbox::blockstructured::serialisePatchIndexInOverlap(overlapCell,3,1,normal);
            logDebug( "touchFaceLastTime(...)", "normal=" << normal << ",fineGridFaceeuler2DQNew[" << index << "]->fineGridFaceeuler2DQOld[" << index << "]" );
            logDebug( "touchFaceLastTime(...)", "normal=" << normal << ",fineGridFaceeuler2DQUpdate[" << index << "]->fineGridFaceeuler2DQNew[" << index << "]" );
            for (int j=0; j<4; j++) {
              fineGridFaceeuler2DQOld.value[index*4+j] = fineGridFaceeuler2DQNew.value[index*4+j]; 
              fineGridFaceeuler2DQNew.value[index*4+j] = fineGridFaceeuler2DQUpdate.value[index*4+j]; 
            }
          }
        }
        
        fineGridFaceeuler2DFaceLabel.setOldTimeStamp(0, fineGridFaceeuler2DFaceLabel.getNewTimeStamp(0) );
        fineGridFaceeuler2DFaceLabel.setNewTimeStamp(0, fineGridFaceeuler2DFaceLabel.getUpdatedTimeStamp(0) );
        
        logTraceOut( "touchFaceLastTime(...)---RollOverUpdatedFace (roll over updated left part of face)"  );
      }
      else {
        logTraceIn( "touchFaceLastTime(...)---RollOverUpdatedFace (skip left part of face)"  );
        logTraceOut( "touchFaceLastTime(...)---RollOverUpdatedFace (skip left part of face)"  );
      }
      
      // Right half
      if (fineGridFaceeuler2DFaceLabel.getUpdated(1)) {
        logTraceIn( "touchFaceLastTime(...)---RollOverUpdatedFace (roll over updated right part of face)"  );
        dfore(k,3,normal,0) {
          for (int i=1; i<2*1; i++) {
            tarch::la::Vector<Dimensions,int> overlapCell = k;
            overlapCell(normal) = i;
            const int index = toolbox::blockstructured::serialisePatchIndexInOverlap(overlapCell,3,1,normal);
            logDebug( "touchFaceLastTime(...)", "normal=" << normal << ",fineGridFaceeuler2DQNew[" << index << "]->fineGridFaceeuler2DQOld[" << index << "]" );
            logDebug( "touchFaceLastTime(...)", "normal=" << normal << ",fineGridFaceeuler2DQUpdate[" << index << "]->fineGridFaceeuler2DQNew[" << index << "]" );
            for (int j=0; j<4; j++) {
              fineGridFaceeuler2DQOld.value[index*4+j] = fineGridFaceeuler2DQNew.value[index*4+j]; 
              fineGridFaceeuler2DQNew.value[index*4+j] = fineGridFaceeuler2DQUpdate.value[index*4+j]; 
            }
          }
        }
        
        fineGridFaceeuler2DFaceLabel.setOldTimeStamp(1, fineGridFaceeuler2DFaceLabel.getNewTimeStamp(1) );
        fineGridFaceeuler2DFaceLabel.setNewTimeStamp(1, fineGridFaceeuler2DFaceLabel.getUpdatedTimeStamp(1) );
        
        logTraceOut( "touchFaceLastTime(...)---RollOverUpdatedFace (roll over updated right part of face)"  );
      }
      else {
        logTraceIn( "touchFaceLastTime(...)---RollOverUpdatedFace (skip right part of face)"  );
        logTraceOut( "touchFaceLastTime(...)---RollOverUpdatedFace (skip right part of face)"  );
      }
      
      int index = 0;
      logTraceOut( "touchFaceLastTime(...)---RollOverUpdatedFace" );
    }
}


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::createCell(
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


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::destroyCell(
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


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::touchCellFirstTime(
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


void project::base_2d_euler::observers::TimeStep2exahype2_solvers_fv_actionsets_RollOverUpdatedFace1::touchCellLastTime(
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


