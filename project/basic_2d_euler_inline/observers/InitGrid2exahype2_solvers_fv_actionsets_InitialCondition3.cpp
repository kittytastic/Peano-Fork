#include "InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3.h"


tarch::logging::Log project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::_log( "project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3");





project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3(int treeNumber) {
// @todo Should be overwritten
}


project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::~InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3() {
// @todo Should be overwritten
}


std::vector< peano4::grid::GridControlEvent > project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::getGridControlEvents() const {
return std::vector< peano4::grid::GridControlEvent >();
}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::beginTraversal(
      ) {

}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::endTraversal(
      ) {

}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::createPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler_inline::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler_inline::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler_inline::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler_inline::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::destroyPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler_inline::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler_inline::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler_inline::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler_inline::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::createHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler_inline::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler_inline::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler_inline::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler_inline::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::destroyHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler_inline::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler_inline::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler_inline::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler_inline::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::touchFaceFirstTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler_inline::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler_inline::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler_inline::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler_inline::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::touchFaceLastTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler_inline::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler_inline::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler_inline::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler_inline::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::createCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::destroyCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::touchCellFirstTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

  if (not marker.willBeRefined() and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridConstruction) { 
    logTraceIn( "touchCellFirstTime(...)---InitialCondition" );
    int index = 0;
    dfor( volume, 3 ) {
      repositories::InstanceOfeuler2D.initialCondition(
        fineGridCelleuler2DQ.value + index,
        ::exahype2::getVolumeCentre( marker.x(), marker.h(), 3, volume), 
        ::exahype2::getVolumeSize( marker.h(), 3 ),
        true
      );
      index += 4 + 0;
    }
    logTraceOut( "touchCellFirstTime(...)---InitialCondition" );
  } 
}


void project::base_2d_euler_inline::observers::InitGrid2exahype2_solvers_fv_actionsets_InitialCondition3::touchCellLastTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler_inline::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler_inline::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

}


