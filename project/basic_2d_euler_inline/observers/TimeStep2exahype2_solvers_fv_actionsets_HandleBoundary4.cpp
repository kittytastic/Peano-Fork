#include "TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4.h"


tarch::logging::Log project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::_log( "project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4");





project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4(int treeNumber) {
// @todo Should be overwritten
}


project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::~TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4() {
// @todo Should be overwritten
}


std::vector< peano4::grid::GridControlEvent > project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::getGridControlEvents() const {
return std::vector< peano4::grid::GridControlEvent >();
}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::beginTraversal(
      ) {

}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::endTraversal(
      ) {

}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::createPersistentFace(
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


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::destroyPersistentFace(
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


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::createHangingFace(
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


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::destroyHangingFace(
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


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::touchFaceFirstTime(
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

    if (
      not marker.willBeRefined() and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridConstruction
      and
      not repositories::InstanceOfeuler2D.PeriodicBC[marker.getSelectedFaceNumber()%Dimensions]
      and
      not marker.hasBeenRefined() 
      and 
      fineGridFaceeuler2DFaceLabel.getBoundary()
    ) {
      logTraceInWith3Arguments( "touchFaceFirstTime(...)", fineGridFaceeuler2DFaceLabel.toString(), (repositories::InstanceOfeuler2D.PeriodicBC[marker.getSelectedFaceNumber()%Dimensions]), marker.toString() );
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
          repositories::InstanceOfeuler2D.boundaryConditions( Qinside, Qoutside, faceCentre, volumeH, t, normal );
        },  
        marker.x(),
        marker.h(),
        fineGridFaceeuler2DFaceLabel.getNewTimeStamp(marker.getSelectedFaceNumber()<Dimensions ? 1 : 0),
        repositories::InstanceOfeuler2D.getMinTimeStepSize(),
        3,
        4+0,
        marker.getSelectedFaceNumber(),
        fineGridFaceeuler2DQNew.value
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
          repositories::InstanceOfeuler2D.boundaryConditions( Qinside, Qoutside, faceCentre, volumeH, t, normal );
        },  
        marker.x(),
        marker.h(),
        fineGridFaceeuler2DFaceLabel.getOldTimeStamp(marker.getSelectedFaceNumber()<Dimensions ? 1 : 0),
        repositories::InstanceOfeuler2D.getMinTimeStepSize(),
        3,
        4+0,
        marker.getSelectedFaceNumber(),
        fineGridFaceeuler2DQOld.value
      );
      
      bool isLeftEntryOutside = marker.getSelectedFaceNumber() < Dimensions;
      double innerTimeStamp;
      
      innerTimeStamp = fineGridFaceeuler2DFaceLabel.getUpdatedTimeStamp( isLeftEntryOutside ? 1 : 0 );
      fineGridFaceeuler2DFaceLabel.setUpdatedTimeStamp( isLeftEntryOutside ? 0 : 1, innerTimeStamp );
      
      innerTimeStamp = fineGridFaceeuler2DFaceLabel.getNewTimeStamp( isLeftEntryOutside ? 1 : 0 );
      fineGridFaceeuler2DFaceLabel.setNewTimeStamp( isLeftEntryOutside ? 0 : 1, innerTimeStamp );

      innerTimeStamp = fineGridFaceeuler2DFaceLabel.getOldTimeStamp( isLeftEntryOutside ? 1 : 0 );
      fineGridFaceeuler2DFaceLabel.setOldTimeStamp( isLeftEntryOutside ? 0 : 1, innerTimeStamp );

      logTraceOut( "touchFaceFirstTime(...)" );
    }
    else {
      logDebug( "touchFaceFirstTime(...)", "skip face " << marker.toString() );
    }
}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::touchFaceLastTime(
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


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::createCell(
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


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::destroyCell(
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


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::touchCellFirstTime(
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


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_HandleBoundary4::touchCellLastTime(
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


