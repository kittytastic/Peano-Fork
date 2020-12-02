#include "InitGrid2exahype2_grid_SetLabels3.h"


tarch::logging::Log examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::_log( "examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3");





examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::InitGrid2exahype2_grid_SetLabels3(int treeNumber) {
}


examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::~InitGrid2exahype2_grid_SetLabels3() {
}


std::vector< peano4::grid::GridControlEvent > examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::getGridControlEvents() const {
return std::vector< peano4::grid::GridControlEvent >();
}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::beginTraversal(
      ) {


}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::endTraversal(
      ) {


}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::createPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::swe::facedata::SWEQ& fineGridFaceSWEQ,
      examples::exahype2::swe::facedata::SWEQNew& fineGridFaceSWEQNew,
      examples::exahype2::swe::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> coarseGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> coarseGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& coarseGridCellSWEQ) {


  tarch::la::Vector<Dimensions, double> offset(DomainOffset);
  tarch::la::Vector<Dimensions, double> size(DomainSize);
  bool isBoundary = false;
  for (int d=0; d<Dimensions; d++) {{
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) );
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) + size(d) );
  }}
  fineGridFaceLabel.setBoundary( isBoundary );

}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::destroyPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::swe::facedata::SWEQ& fineGridFaceSWEQ,
      examples::exahype2::swe::facedata::SWEQNew& fineGridFaceSWEQNew,
      examples::exahype2::swe::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> coarseGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> coarseGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& coarseGridCellSWEQ) {


}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::createHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::swe::facedata::SWEQ& fineGridFaceSWEQ,
      examples::exahype2::swe::facedata::SWEQNew& fineGridFaceSWEQNew,
      examples::exahype2::swe::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> coarseGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> coarseGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& coarseGridCellSWEQ) {


  tarch::la::Vector<Dimensions, double> offset(DomainOffset);
  tarch::la::Vector<Dimensions, double> size(DomainSize);
  bool isBoundary = false;
  for (int d=0; d<Dimensions; d++) {{
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) );
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) + size(d) );
  }}
  fineGridFaceLabel.setBoundary( isBoundary );

}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::destroyHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::swe::facedata::SWEQ& fineGridFaceSWEQ,
      examples::exahype2::swe::facedata::SWEQNew& fineGridFaceSWEQNew,
      examples::exahype2::swe::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> coarseGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> coarseGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& coarseGridCellSWEQ) {


}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::touchFaceFirstTime(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::swe::facedata::SWEQ& fineGridFaceSWEQ,
      examples::exahype2::swe::facedata::SWEQNew& fineGridFaceSWEQNew,
      examples::exahype2::swe::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> coarseGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> coarseGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& coarseGridCellSWEQ) {


}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::touchFaceLastTime(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::swe::facedata::SWEQ& fineGridFaceSWEQ,
      examples::exahype2::swe::facedata::SWEQNew& fineGridFaceSWEQNew,
      examples::exahype2::swe::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> coarseGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> coarseGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& coarseGridCellSWEQ) {


}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::createCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> fineGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> fineGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> fineGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& fineGridCellSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> coarseGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> coarseGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& coarseGridCellSWEQ) {


}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::destroyCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> fineGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> fineGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> fineGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& fineGridCellSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> coarseGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> coarseGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& coarseGridCellSWEQ) {


}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::touchCellFirstTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> fineGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> fineGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> fineGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& fineGridCellSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> coarseGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> coarseGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& coarseGridCellSWEQ) {


}


void examples::exahype2::swe::observers::InitGrid2exahype2_grid_SetLabels3::touchCellLastTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> fineGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> fineGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> fineGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& fineGridCellSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ> coarseGridFacesSWEQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew> coarseGridFacesSWEQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::swe::celldata::SWEQ& coarseGridCellSWEQ) {


}


