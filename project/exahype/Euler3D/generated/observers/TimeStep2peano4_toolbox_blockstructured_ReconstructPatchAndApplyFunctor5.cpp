#include "TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5.h"
#include "../euler3d.g.h"

tarch::logging::Log project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::_log( "project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5");





project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5(int treeNumber) {
  _treeNumber = treeNumber;
}


project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::~TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5() {
// @todo Should be overwritten
}


std::vector< peano4::grid::GridControlEvent > project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::getGridControlEvents() const {
return std::vector< peano4::grid::GridControlEvent >();
}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::beginTraversal(
      ) {


}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::endTraversal(
      ) {


}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::Euler3D::generated::facedata::euler3DQOld& fineGridFaceeuler3DQOld,
      project::exahype::Euler3D::generated::facedata::euler3DQNew& fineGridFaceeuler3DQNew,
      project::exahype::Euler3D::generated::facedata::euler3DQUpdate& fineGridFaceeuler3DQUpdate,
      project::exahype::Euler3D::generated::facedata::euler3DFaceLabel& fineGridFaceeuler3DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> coarseGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> coarseGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> coarseGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> coarseGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& coarseGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& coarseGridCelleuler3DCellLabel) {


}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::Euler3D::generated::facedata::euler3DQOld& fineGridFaceeuler3DQOld,
      project::exahype::Euler3D::generated::facedata::euler3DQNew& fineGridFaceeuler3DQNew,
      project::exahype::Euler3D::generated::facedata::euler3DQUpdate& fineGridFaceeuler3DQUpdate,
      project::exahype::Euler3D::generated::facedata::euler3DFaceLabel& fineGridFaceeuler3DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> coarseGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> coarseGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> coarseGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> coarseGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& coarseGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& coarseGridCelleuler3DCellLabel) {


}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::Euler3D::generated::facedata::euler3DQOld& fineGridFaceeuler3DQOld,
      project::exahype::Euler3D::generated::facedata::euler3DQNew& fineGridFaceeuler3DQNew,
      project::exahype::Euler3D::generated::facedata::euler3DQUpdate& fineGridFaceeuler3DQUpdate,
      project::exahype::Euler3D::generated::facedata::euler3DFaceLabel& fineGridFaceeuler3DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> coarseGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> coarseGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> coarseGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> coarseGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& coarseGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& coarseGridCelleuler3DCellLabel) {


}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::Euler3D::generated::facedata::euler3DQOld& fineGridFaceeuler3DQOld,
      project::exahype::Euler3D::generated::facedata::euler3DQNew& fineGridFaceeuler3DQNew,
      project::exahype::Euler3D::generated::facedata::euler3DQUpdate& fineGridFaceeuler3DQUpdate,
      project::exahype::Euler3D::generated::facedata::euler3DFaceLabel& fineGridFaceeuler3DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> coarseGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> coarseGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> coarseGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> coarseGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& coarseGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& coarseGridCelleuler3DCellLabel) {


}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchFaceFirstTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::Euler3D::generated::facedata::euler3DQOld& fineGridFaceeuler3DQOld,
      project::exahype::Euler3D::generated::facedata::euler3DQNew& fineGridFaceeuler3DQNew,
      project::exahype::Euler3D::generated::facedata::euler3DQUpdate& fineGridFaceeuler3DQUpdate,
      project::exahype::Euler3D::generated::facedata::euler3DFaceLabel& fineGridFaceeuler3DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> coarseGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> coarseGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> coarseGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> coarseGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& coarseGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& coarseGridCelleuler3DCellLabel) {


}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchFaceLastTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::Euler3D::generated::facedata::euler3DQOld& fineGridFaceeuler3DQOld,
      project::exahype::Euler3D::generated::facedata::euler3DQNew& fineGridFaceeuler3DQNew,
      project::exahype::Euler3D::generated::facedata::euler3DQUpdate& fineGridFaceeuler3DQUpdate,
      project::exahype::Euler3D::generated::facedata::euler3DFaceLabel& fineGridFaceeuler3DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> coarseGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> coarseGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> coarseGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> coarseGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& coarseGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& coarseGridCelleuler3DCellLabel) {


}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> fineGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> fineGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> fineGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> fineGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& fineGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& fineGridCelleuler3DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> coarseGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> coarseGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> coarseGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> coarseGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& coarseGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& coarseGridCelleuler3DCellLabel) {


}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> fineGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> fineGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> fineGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> fineGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& fineGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& fineGridCelleuler3DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> coarseGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> coarseGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> coarseGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> coarseGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& coarseGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& coarseGridCelleuler3DCellLabel) {


}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchCellFirstTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> fineGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> fineGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> fineGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> fineGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& fineGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& fineGridCelleuler3DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> coarseGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> coarseGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> coarseGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> coarseGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& coarseGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& coarseGridCelleuler3DCellLabel) {

  fineGridCelleuler3DCellLabel.setHasUpdated(false);

  auto serialisePatchIndex = [](tarch::la::Vector<Dimensions,int> overlapCell, int normal) {
    int base   = 1;
    int result = 0;
    for (int d=0; d<Dimensions; d++) {
      result += overlapCell(d) * base;
      if (d==normal) {
        base *= 1.0*2;
      }
      else {
        base *= 3;
      }
    }
    return result;
  };
  
  if (not marker.willBeRefined() and not marker.hasBeenRefined()) {
    logTraceInWith1Argument( "touchCellFirstTime(...)", marker.toString() );

    
    #if Dimensions==2
    double reconstructedPatch[125];
    #elif Dimensions==3
    double reconstructedPatch[625];
    #endif


    //
    // Loop over original patch (k) and copy stuff over.
    //
    dfor(sourceCell,3) {
      tarch::la::Vector<Dimensions,int> destinationCell = sourceCell + tarch::la::Vector<Dimensions,int>(1.0);
      int sourceCellSerialised       = peano4::utils::dLinearised(sourceCell,3);
      int destinationCellSerialised  = peano4::utils::dLinearised(destinationCell,3 + 2*1.0);
      for (int j=0; j<5; j++) {
        reconstructedPatch[destinationCellSerialised*5+j] = fineGridCelleuler3DQ.value[ sourceCellSerialised*5+j ];
        nonCriticalAssertion4( reconstructedPatch[destinationCellSerialised*5+j]==reconstructedPatch[destinationCellSerialised*5+j], sourceCell, j, _treeNumber, marker.toString() );
      }
    }

    //
    // Bring in the auxiliary patches, i.e. befill halo
    //
    for(int d=0; d<Dimensions; d++) {
      logTraceInWith1Argument( "touchCellFirstTime(...)::loopOverFace", d );
      //
      // d-loop over all dimensions except d. The vector k's entry d is set
      // to 0. We start with the left/bottom face, i.e. the one closer to the 
      // coordinate system's origin.
      //
      dfore(k,3,d,0) {
        for (int i=0; i<1.0; i++) {
          tarch::la::Vector<Dimensions,int> destinationCell = k + tarch::la::Vector<Dimensions,int>(1.0);
          tarch::la::Vector<Dimensions,int> sourceCell      = k;
          destinationCell(d) = i;
          sourceCell(d)      = i;
          
          int destinationCellSerialised   = peano4::utils::dLinearised(destinationCell,3 + 2*1.0);
          int sourceCellSerialised        = serialisePatchIndex(sourceCell,d);

          for (int j=0; j<5; j++) {
            reconstructedPatch[ destinationCellSerialised*5+j ] = fineGridFaceseuler3DQNew(d).value[ sourceCellSerialised*5+j ];
            assertion7( 
              true or 
              reconstructedPatch[ destinationCellSerialised*5+j ]==reconstructedPatch[ destinationCellSerialised*5+j ], 
              sourceCell, destinationCell, j, d, marker.toString(), _treeNumber, marker.toString()
            );
          }

          destinationCell(d) = i+3+1.0;
          sourceCell(d)      = i+1.0;

          destinationCellSerialised   = peano4::utils::dLinearised(destinationCell,3 + 2*1.0);
          sourceCellSerialised        = serialisePatchIndex(sourceCell,d);
          for (int j=0; j<5; j++) {
            reconstructedPatch[ destinationCellSerialised*5+j ] = fineGridFaceseuler3DQNew(d+Dimensions).value[ sourceCellSerialised*5+j ];
            assertion7( 
              true or 
              reconstructedPatch[ destinationCellSerialised*5+j ]==reconstructedPatch[ destinationCellSerialised*5+j ], 
              sourceCell, destinationCell, j, d, marker.toString(), _treeNumber, marker.toString()
            );
          }
        }
      }
      logTraceOut( "touchCellFirstTime(...)::loopOverFace" );
    }

    double* targetPatch = fineGridCelleuler3DQ.value;
    
    double cellTimeStepSize = -1.0;
    double cellTimeStamp    = -1.0;
     
    
    
  cellTimeStepSize = repositories::InstanceOfeuler3D.getTimeStepSize();
  cellTimeStamp    = fineGridCelleuler3DCellLabel.getTimeStamp();
    
    assertion2( tarch::la::greaterEquals( cellTimeStepSize, 0.0 ), cellTimeStepSize, cellTimeStamp );
    assertion2( tarch::la::greaterEquals( cellTimeStamp, 0.0 ), cellTimeStepSize, cellTimeStamp );

    const double usedTimeStepSize = cellTimeStepSize;

    ::exahype2::fv::validatePatch(
        reconstructedPatch,
        5,
        0,
        3,
        1, // halo
        std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): " + marker.toString()
    ); // previous time step has to be valid
  
    ::exahype2::fv::copyPatch(
        reconstructedPatch,
        targetPatch,
        5,
        0,
        3,
        1 // halo size
    );


    kernels::euler3d2::PatchUpdate(
      cellTimeStamp,
      cellTimeStepSize,
      marker.x()(0),
      marker.x()(1),
      marker.x()(2),
      marker.h()(0),
      marker.h()(1),
      marker.h()(2),
      reconstructedPatch,
      targetPatch
    );
  
        
    fineGridCelleuler3DCellLabel.setTimeStamp(cellTimeStamp + usedTimeStepSize);
    fineGridCelleuler3DCellLabel.setTimeStepSize(cellTimeStepSize);
    fineGridCelleuler3DCellLabel.setHasUpdated(true);
    
    repositories::InstanceOfeuler3D.update(cellTimeStepSize, cellTimeStamp + usedTimeStepSize, marker.h()(0) );

    ::exahype2::fv::validatePatch(
        targetPatch,
        5,
        0,
        3,
        0, // halo
        std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): " + marker.toString()
    ); // outcome has to be valid
  
    
    

    logTraceOut( "touchCellFirstTime(...)" );
  }

  else if (not marker.willBeRefined() and not marker.hasBeenRefined()) {
    double cellTimeStepSize = -1.0;
    double cellTimeStamp    = -1.0;
     
    
  cellTimeStepSize = repositories::InstanceOfeuler3D.getTimeStepSize();
  cellTimeStamp    = fineGridCelleuler3DCellLabel.getTimeStamp();
    
    assertion2( tarch::la::greaterEquals( cellTimeStepSize, 0.0 ), cellTimeStepSize, cellTimeStamp );
    assertion2( tarch::la::greaterEquals( cellTimeStamp, 0.0 ), cellTimeStepSize, cellTimeStamp );

    repositories::InstanceOfeuler3D.update(0.0, cellTimeStamp, marker.h()(0) );
  }

}


void project::exahype::Euler3D::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchCellLastTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> fineGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> fineGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> fineGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> fineGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& fineGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& fineGridCelleuler3DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQOld> coarseGridFaceseuler3DQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQNew> coarseGridFaceseuler3DQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DQUpdate> coarseGridFaceseuler3DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::Euler3D::generated::facedata::euler3DFaceLabel> coarseGridFaceseuler3DFaceLabel,
      project::exahype::Euler3D::generated::celldata::euler3DQ& coarseGridCelleuler3DQ,
      project::exahype::Euler3D::generated::celldata::euler3DCellLabel& coarseGridCelleuler3DCellLabel) {


}


