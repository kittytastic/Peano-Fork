#include "CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1.h"


tarch::logging::Log project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::_log( "project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1");





project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1(int treeNumber) {
}


project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::~CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1() {
}


std::vector< peano4::grid::GridControlEvent > project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::getGridControlEvents() const {
return std::vector< peano4::grid::GridControlEvent >();
}


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::beginTraversal(
      ) {


}


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::endTraversal(
      ) {


}


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::createPersistentFace(
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


  logTraceInWith1Argument( "createPersistent/HangingFace(...)", marker.toString() );
      
  tarch::la::Vector<Dimensions, double> offset(DomainOffset);
  tarch::la::Vector<Dimensions, double> size(DomainSize);
  bool isBoundary = false;
  for (int d=0; d<Dimensions; d++) {{
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) );
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) + size(d) );
  }}
  fineGridFaceeuler2DFaceLabel.setBoundary( isBoundary );
  logTraceOutWith1Argument( "createPersistent/HangingFace(...)", fineGridFaceeuler2DFaceLabel.toString() );

}


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::destroyPersistentFace(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::createHangingFace(
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


  logTraceInWith1Argument( "createPersistent/HangingFace(...)", marker.toString() );
      
  tarch::la::Vector<Dimensions, double> offset(DomainOffset);
  tarch::la::Vector<Dimensions, double> size(DomainSize);
  bool isBoundary = false;
  for (int d=0; d<Dimensions; d++) {{
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) );
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) + size(d) );
  }}
  fineGridFaceeuler2DFaceLabel.setBoundary( isBoundary );
  logTraceOutWith1Argument( "createPersistent/HangingFace(...)", fineGridFaceeuler2DFaceLabel.toString() );

}


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::destroyHangingFace(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::touchFaceFirstTime(
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

  fineGridFaceeuler2DFaceLabel.setUpdated( false );

}


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::touchFaceLastTime(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::createCell(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::destroyCell(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::touchCellFirstTime(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_grid_FaceLabel1::touchCellLastTime(
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


