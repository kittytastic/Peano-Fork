#include "TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0.h"


tarch::logging::Log project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::_log( "project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0");





project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0(int treeNumber) {
}


project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::~TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0() {
}


std::vector< peano4::grid::GridControlEvent > project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::getGridControlEvents() const {
  return std::vector< peano4::grid::GridControlEvent >();
}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::beginTraversal(
      ) {


}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::endTraversal(
      ) {


}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::createPersistentFace(
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

  logTraceInWith1Argument( "createPersistentFace(...)", marker.toString() );
    ::toolbox::blockstructured::interpolateHaloLayer_AoS_linear_precomputed_operators<3>(
      marker,
      3,
      1,
      4,
      fineGridFaceeuler2DQOld.value,
      coarseGridFaceseuler2DQOld(marker.getSelectedFaceNumber()).value,
      coarseGridCelleuler2DQ.value
    );
    ::toolbox::blockstructured::interpolateHaloLayer_AoS_linear_precomputed_operators<3>(
      marker,
      3,
      1,
      4,
      fineGridFaceeuler2DQNew.value,
      coarseGridFaceseuler2DQNew(marker.getSelectedFaceNumber()).value,
      coarseGridCelleuler2DQ.value
    );
    // It is important that we clear the halo layer. If we have two layers of 
    // AMR, the finest one will restrict into QUpdate (so it has to be properly
    // initialised as 0).
    ::toolbox::blockstructured::clearHaloLayerAoS(
      marker,
      3,
      1,
      4,
      fineGridFaceeuler2DQUpdate.value
    );
    const int leftRightEntry = marker.getSelectedFaceNumber()<Dimensions ? 0 : 1;
    fineGridFaceeuler2DFaceLabel.setNewTimeStamp(coarseGridCelleuler2DCellLabel.getTimeStamp());
    fineGridFaceeuler2DFaceLabel.setOldTimeStamp(coarseGridCelleuler2DCellLabel.getTimeStamp());
  logTraceOutWith1Argument( "createPersistentFace(...)", marker.toString() );
}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::destroyPersistentFace(
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

  logTraceIn( "destroyPersistentFace(...)" );
  
  if ( not marker.isInteriorFaceWithinPatch() ) {
  ::toolbox::blockstructured::restrictHaloLayer_AoS_averaging(
      marker,
      3,
      1,
      4,
      fineGridFaceeuler2DQUpdate.value,
      coarseGridFaceseuler2DQUpdate(marker.getSelectedFaceNumber()).value
  );
 
  // Copy over updated data. This is inaccurate, as we should restrict the updated
  // and the old value separatedly. But the restriction accumulates data in the 
  // coarse level, so we'd have to clear it beforehand. However, we cannot clear
  // it as we need for the BCs and an interpolation. So I accept that I introduce
  // an error here.
  #if Dimensions==2
  constexpr int NumberOfBytes = 3*2*1*4*sizeof(double);
  #else
  constexpr int NumberOfBytes = 3*3*2*1*4*sizeof(double);
  #endif
  std::memcpy( 
    coarseGridFaceseuler2DQNew(marker.getSelectedFaceNumber()).value, 
    fineGridFaceeuler2DQNew.value,
    NumberOfBytes
  );
  std::memcpy( 
    coarseGridFaceseuler2DQOld(marker.getSelectedFaceNumber()).value, 
    fineGridFaceeuler2DQOld.value,
    NumberOfBytes
  );

  // A coarse face might have been non-persistent before. So it might
  // not carry a valid boundary flag, and we have to re-analyse it and
  // set it accordingly.    
  tarch::la::Vector<Dimensions, double> offset(DomainOffset);
  tarch::la::Vector<Dimensions, double> size(DomainSize);
  bool isBoundary = false;
  for (int d=0; d<Dimensions; d++) {
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) );
    isBoundary |= tarch::la::equals( marker.x()(d), offset(d) + size(d) );
  }
  coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).setBoundary( isBoundary );

  // left and right
  for (int i=0; i<2; i++) {
    double newTimeStamp     = std::max( coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).getNewTimeStamp(     i ), fineGridFaceeuler2DFaceLabel.getNewTimeStamp( i ));
    double oldTimeStamp     = std::max( coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).getOldTimeStamp(     i ), fineGridFaceeuler2DFaceLabel.getOldTimeStamp( i ));
    double updatedTimeStamp = std::max( coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).getUpdatedTimeStamp( i ), fineGridFaceeuler2DFaceLabel.getUpdatedTimeStamp( i ));
    coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).setUpdated(         i,true);
    coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).setNewTimeStamp(    i,newTimeStamp);
    coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).setOldTimeStamp(    i,oldTimeStamp);
    coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).setUpdatedTimeStamp(i,updatedTimeStamp);
  }
  }
  logTraceOut( "destroyPersistentFace(...)" );
}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::createHangingFace(
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
  repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridInitialisation
 ) {
    logTraceInWith1Argument( "createHangingFace(...)", marker.toString() );
    ::toolbox::blockstructured::interpolateHaloLayer_AoS_linear_precomputed_operators<3>(
      marker,
      3,
      1,
      4,
      fineGridFaceeuler2DQOld.value,
      coarseGridFaceseuler2DQOld(marker.getSelectedFaceNumber()).value
    );
    ::toolbox::blockstructured::interpolateHaloLayer_AoS_linear_precomputed_operators<3>(
      marker,
      3,
      1,
      4,
      fineGridFaceeuler2DQNew.value,
      coarseGridFaceseuler2DQNew(marker.getSelectedFaceNumber()).value
    );
    // It is important that we clear the halo layer. If we have two layers of 
    // AMR, the finest one will restrict into QUpdate (so it has to be properly
    // initialised as 0).
    ::toolbox::blockstructured::clearHaloLayerAoS(
      marker,
      3,
      1,
      4,
      fineGridFaceeuler2DQUpdate.value
    );
    const int leftRightEntry = marker.getSelectedFaceNumber()<Dimensions ? 0 : 1;
    fineGridFaceeuler2DFaceLabel.setNewTimeStamp(leftRightEntry,coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).getNewTimeStamp(leftRightEntry));
    fineGridFaceeuler2DFaceLabel.setOldTimeStamp(leftRightEntry,coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).getOldTimeStamp(leftRightEntry));
    
    
    logTraceOut( "createHangingFace(...)" );
  }
  else {
    logDebug( "createHangingFace(...)", "skip interpolation for " << marker.toString() << " as interpolation guard did not yield true" );
  }
}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::destroyHangingFace(
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

  if ( true ) {
    logTraceInWith4Arguments( "destroyHangingFace(...)", "fineGridFaceeuler2DQUpdate", "coarseGridFaceseuler2DQUpdate", marker.getSelectedFaceNumber(), marker.toString() );
    ::toolbox::blockstructured::restrictInnerHalfOfHaloLayer_AoS_averaging(
      marker,
      3,
      1,
      4,
      fineGridFaceeuler2DQUpdate.value,
      coarseGridFaceseuler2DQUpdate(marker.getSelectedFaceNumber()).value
    );

  bool isLeftEntryOnCoarseFaceLabel = marker.getSelectedFaceNumber() >= Dimensions;
  double newTimeStamp = std::max( coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).getUpdatedTimeStamp( isLeftEntryOnCoarseFaceLabel ? 0 : 1 ), fineGridFaceeuler2DFaceLabel.getUpdatedTimeStamp( isLeftEntryOnCoarseFaceLabel ? 0 : 1 ));
  coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).setUpdated( isLeftEntryOnCoarseFaceLabel ? 0 : 1,true);
  coarseGridFaceseuler2DFaceLabel(marker.getSelectedFaceNumber()).setUpdatedTimeStamp( isLeftEntryOnCoarseFaceLabel ? 0 : 1,newTimeStamp);
    

    logTraceOut( "destroyHangingFace(...)" );
  }
}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::touchFaceFirstTime(
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

  if ( true ) {
    logTraceInWith2Arguments( "touchFaceFirstTime(...)", marker.toString(), "clear halo layer fineGridFaceeuler2DQUpdate" );
    
    ::toolbox::blockstructured::clearHaloLayerAoS(
      marker,
      3,
      1,
      4,
      fineGridFaceeuler2DQUpdate.value
    );

    logTraceOut( "touchFaceFirstTime(...)" );
  }
}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::touchFaceLastTime(
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


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::createCell(
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

  logTraceIn( "createCell(...)" );
  ::toolbox::blockstructured::interpolateCell_AoS_linear_precomputed_operators<3>(
      marker,
      3,
      4,
      fineGridCelleuler2DQ.value,
      coarseGridCelleuler2DQ.value
  );
    
::exahype2::fv::validatePatch(
    fineGridCelleuler2DQ.value,
    4,
    0, // auxiliary values. Not known here
    3,
    0, // no halo
    std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): " + marker.toString()
  ); 

  fineGridCelleuler2DCellLabel.setTimeStamp( coarseGridCelleuler2DCellLabel.getTimeStamp() );
  fineGridCelleuler2DCellLabel.setTimeStepSize( coarseGridCelleuler2DCellLabel.getTimeStepSize() );   
  logTraceOut( "createCell(...)" );
}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::destroyCell(
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

  logTraceInWith1Argument( "destroyCell(...)", marker.toString() );
  ::toolbox::blockstructured::restrictCell_AoS_averaging(
      marker,
      3,
      4,
      fineGridCelleuler2DQ.value,
      coarseGridCelleuler2DQ.value
  );
    
  ::exahype2::fv::validatePatch(
    fineGridCelleuler2DQ.value,
    4,
    0, // auxiliary values. Not known here
    3,
    0, // no halo
    std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): " + marker.toString()
  ); 
  
  coarseGridCelleuler2DCellLabel.setTimeStamp( fineGridCelleuler2DCellLabel.getTimeStamp() );
  coarseGridCelleuler2DCellLabel.setTimeStepSize( fineGridCelleuler2DCellLabel.getTimeStepSize() );
  logTraceOut( "destroyCell(...)" );
}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::touchCellFirstTime(
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

  if ( marker.hasBeenRefined() and not marker.willBeRefined() ) {
    logTraceInWith2Arguments( "touchCellFirstTime(...)", marker.toString(), "clear cell fineGridCelleuler2DQ" );
    
    ::toolbox::blockstructured::clearCell(
      marker,
      3,
      4,
      fineGridCelleuler2DQ.value
    );

    logTraceOut( "touchCellFirstTime(...)" );
  }
}


void project::base_2d_euler_inline::observers::TimeStep2exahype2_solvers_fv_actionsets_DynamicAMR0::touchCellLastTime(
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


