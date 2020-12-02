#include "TimeStep2exahype2_grid_SetLabels7.h"


tarch::logging::Log examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::_log( "examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7");





examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::TimeStep2exahype2_grid_SetLabels7(int treeNumber) {
}


examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::~TimeStep2exahype2_grid_SetLabels7() {
}


std::vector< peano4::grid::GridControlEvent > examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::getGridControlEvents() const {
return std::vector< peano4::grid::GridControlEvent >();
}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::beginTraversal(
      ) {


}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::endTraversal(
      ) {


}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::createPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::euler::facedata::EulerQ& fineGridFaceEulerQ,
      examples::exahype2::euler::facedata::EulerQNew& fineGridFaceEulerQNew,
      examples::exahype2::euler::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> coarseGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> coarseGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& coarseGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& coarseGridCellEulerCellSemaphoreLabel) {


  tarch::la::Vector<Dimensions, double> offset(DomainOffset);
  tarch::la::Vector<Dimensions, double> size(DomainSize);
  bool isBoundary = false;
  for (int d=0; d<Dimensions; d++) {{
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) );
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) + size(d) );
  }}
  fineGridFaceLabel.setBoundary( isBoundary );

}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::destroyPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::euler::facedata::EulerQ& fineGridFaceEulerQ,
      examples::exahype2::euler::facedata::EulerQNew& fineGridFaceEulerQNew,
      examples::exahype2::euler::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> coarseGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> coarseGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& coarseGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& coarseGridCellEulerCellSemaphoreLabel) {


}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::createHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::euler::facedata::EulerQ& fineGridFaceEulerQ,
      examples::exahype2::euler::facedata::EulerQNew& fineGridFaceEulerQNew,
      examples::exahype2::euler::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> coarseGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> coarseGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& coarseGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& coarseGridCellEulerCellSemaphoreLabel) {


  tarch::la::Vector<Dimensions, double> offset(DomainOffset);
  tarch::la::Vector<Dimensions, double> size(DomainSize);
  bool isBoundary = false;
  for (int d=0; d<Dimensions; d++) {{
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) );
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) + size(d) );
  }}
  fineGridFaceLabel.setBoundary( isBoundary );

}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::destroyHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::euler::facedata::EulerQ& fineGridFaceEulerQ,
      examples::exahype2::euler::facedata::EulerQNew& fineGridFaceEulerQNew,
      examples::exahype2::euler::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> coarseGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> coarseGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& coarseGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& coarseGridCellEulerCellSemaphoreLabel) {


}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::touchFaceFirstTime(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::euler::facedata::EulerQ& fineGridFaceEulerQ,
      examples::exahype2::euler::facedata::EulerQNew& fineGridFaceEulerQNew,
      examples::exahype2::euler::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> coarseGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> coarseGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& coarseGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& coarseGridCellEulerCellSemaphoreLabel) {


}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::touchFaceLastTime(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::euler::facedata::EulerQ& fineGridFaceEulerQ,
      examples::exahype2::euler::facedata::EulerQNew& fineGridFaceEulerQNew,
      examples::exahype2::euler::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> coarseGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> coarseGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& coarseGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& coarseGridCellEulerCellSemaphoreLabel) {


}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::createCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> fineGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> fineGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> fineGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& fineGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& fineGridCellEulerCellSemaphoreLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> coarseGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> coarseGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& coarseGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& coarseGridCellEulerCellSemaphoreLabel) {


}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::destroyCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> fineGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> fineGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> fineGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& fineGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& fineGridCellEulerCellSemaphoreLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> coarseGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> coarseGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& coarseGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& coarseGridCellEulerCellSemaphoreLabel) {


}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::touchCellFirstTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> fineGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> fineGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> fineGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& fineGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& fineGridCellEulerCellSemaphoreLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> coarseGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> coarseGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& coarseGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& coarseGridCellEulerCellSemaphoreLabel) {


}


void examples::exahype2::euler::observers::TimeStep2exahype2_grid_SetLabels7::touchCellLastTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> fineGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> fineGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> fineGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& fineGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& fineGridCellEulerCellSemaphoreLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQ> coarseGridFacesEulerQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::EulerQNew> coarseGridFacesEulerQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::euler::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::euler::celldata::EulerQ& coarseGridCellEulerQ,
      examples::exahype2::euler::celldata::EulerCellSemaphoreLabel& coarseGridCellEulerCellSemaphoreLabel) {


}


