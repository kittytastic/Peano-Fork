#include "CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3.h"


tarch::logging::Log project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::_log( "project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3");





project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3(int treeNumber) {
// @todo Should be overwritten
}


project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::~CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3() {
// @todo Should be overwritten
}


std::vector< peano4::grid::GridControlEvent > project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::getGridControlEvents() const {

    return repositories::refinementControl.getGridControlEvents();
}


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::beginTraversal(
      ) {

  _localRefinementControl.clear();

}


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::endTraversal(
      ) {

  repositories::refinementControl.merge( _localRefinementControl );

}


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::createPersistentFace(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::destroyPersistentFace(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::createHangingFace(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::destroyHangingFace(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::touchFaceFirstTime(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::touchFaceLastTime(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::createCell(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::destroyCell(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::touchCellFirstTime(
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


void project::base_2d_euler::observers::CreateGridButPostponeRefinement2exahype2_solvers_fv_actionsets_AdaptivityCriterion3::touchCellLastTime(
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
  
  logTraceInWith2Arguments( "touchCellFirstTime(...)", marker.willBeRefined(), marker.hasBeenRefined() );

  ::exahype2::RefinementCommand refinementCriterion = ::exahype2::getDefaultRefinementCommand();

  if ( 
    not marker.willBeRefined() 
    and
    tarch::la::equals(repositories::InstanceOfeuler2D.getMinTimeStamp(),0.0)  
    and
    tarch::la::greater( tarch::la::max( marker.h() ), repositories::InstanceOfeuler2D.MaxAdmissiblePatchH) 
  ) {
    refinementCriterion = ::exahype2::RefinementCommand::Refine;
  } 
  else if ( 
    not marker.willBeRefined() and not marker.hasBeenRefined() and not marker.willBeRefined() and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridConstruction
    and
    not marker.willBeRefined() 
    and
    tarch::la::greater( tarch::la::max( marker.h() ), repositories::InstanceOfeuler2D.MaxAdmissiblePatchH) 
  ) {
    refinementCriterion = ::exahype2::RefinementCommand::Refine;
  } 
  else if ( not marker.willBeRefined() and tarch::la::equals(repositories::InstanceOfeuler2D.getMinTimeStamp(),0.0)  ) { 
    int index = 0;
    dfor( volume, 3 ) {
        refinementCriterion = refinementCriterion and repositories::InstanceOfeuler2D.refinementCriterion(
          fineGridCelleuler2DQ.value + index,
          ::exahype2::getVolumeCentre( marker.x(), marker.h(), 3, volume), 
          ::exahype2::getVolumeSize( marker.h(), 3 ),
          0.0
        );
        index += 4 + 0;
    }
     
    if (refinementCriterion==::exahype2::RefinementCommand::Refine and tarch::la::max( marker.h() ) < repositories::InstanceOfeuler2D.MinAdmissiblePatchH ) {
      refinementCriterion = ::exahype2::RefinementCommand::Keep;
    } 
    else if (refinementCriterion==::exahype2::RefinementCommand::Erase ) {
      logDebug( "touchCellFirstTime(...)", "drop coarsen instructions, as we are in initial grid setup phase" );
      refinementCriterion = ::exahype2::RefinementCommand::Keep;
    } 
  }
  else if ( 
    not marker.willBeRefined() and not marker.hasBeenRefined() and not marker.willBeRefined() and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridConstruction
    and
    fineGridCelleuler2DCellLabel.getHasUpdated()
  ) { 
    int index = 0;
    dfor( volume, 3 ) {
        refinementCriterion = refinementCriterion and repositories::InstanceOfeuler2D.refinementCriterion(
          fineGridCelleuler2DQ.value + index,
          ::exahype2::getVolumeCentre( marker.x(), marker.h(), 3, volume), 
          ::exahype2::getVolumeSize( marker.h(), 3 ),
          repositories::InstanceOfeuler2D.getMinTimeStamp()
        );
        index += 4 + 0;
    }
     
    if (refinementCriterion==::exahype2::RefinementCommand::Refine and tarch::la::max( marker.h() ) < repositories::InstanceOfeuler2D.MinAdmissiblePatchH ) {
      refinementCriterion = ::exahype2::RefinementCommand::Keep;
    } 
    else if (refinementCriterion==::exahype2::RefinementCommand::Erase and 3.0* tarch::la::max( marker.h() ) > repositories::InstanceOfeuler2D.MaxAdmissiblePatchH ) {
      refinementCriterion = ::exahype2::RefinementCommand::Keep;
    } 
  }
  else {
    refinementCriterion = ::exahype2::RefinementCommand::Keep;
  }
    
  _localRefinementControl.addCommand( marker.x(), marker.h(), refinementCriterion, 1 );
  logTraceOutWith1Argument( "touchCellFirstTime(...)", toString(refinementCriterion) );
  
}


