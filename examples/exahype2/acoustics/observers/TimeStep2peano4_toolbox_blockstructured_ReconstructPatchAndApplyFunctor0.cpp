#include "TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0.h"


tarch::logging::Log examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::_log( "examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0");





examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0(int treeNumber) {
  _treeNumber = treeNumber;
}


examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::~TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0() {
}


std::vector< peano4::grid::GridControlEvent > examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::getGridControlEvents() const {
  return std::vector< peano4::grid::GridControlEvent >();
}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::beginTraversal(
      ) {


}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::endTraversal(
      ) {


}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::createPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::acoustics::facedata::AcousticsQ& fineGridFaceAcousticsQ,
      examples::exahype2::acoustics::facedata::AcousticsQNew& fineGridFaceAcousticsQNew,
      examples::exahype2::acoustics::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> coarseGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> coarseGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& coarseGridCellAcousticsQ) {


}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::destroyPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::acoustics::facedata::AcousticsQ& fineGridFaceAcousticsQ,
      examples::exahype2::acoustics::facedata::AcousticsQNew& fineGridFaceAcousticsQNew,
      examples::exahype2::acoustics::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> coarseGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> coarseGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& coarseGridCellAcousticsQ) {


}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::createHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::acoustics::facedata::AcousticsQ& fineGridFaceAcousticsQ,
      examples::exahype2::acoustics::facedata::AcousticsQNew& fineGridFaceAcousticsQNew,
      examples::exahype2::acoustics::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> coarseGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> coarseGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& coarseGridCellAcousticsQ) {


}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::destroyHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::acoustics::facedata::AcousticsQ& fineGridFaceAcousticsQ,
      examples::exahype2::acoustics::facedata::AcousticsQNew& fineGridFaceAcousticsQNew,
      examples::exahype2::acoustics::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> coarseGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> coarseGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& coarseGridCellAcousticsQ) {


}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::touchFaceFirstTime(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::acoustics::facedata::AcousticsQ& fineGridFaceAcousticsQ,
      examples::exahype2::acoustics::facedata::AcousticsQNew& fineGridFaceAcousticsQNew,
      examples::exahype2::acoustics::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> coarseGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> coarseGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& coarseGridCellAcousticsQ) {

  if ( not marker.isRefined() and fineGridFaceLabel.getBoundary() ) {
    logTraceInWith2Arguments( "touchFaceFirstTime(...)", marker.toString(), marker.isLocal() );
    
    logDebug( "touchFaceFirstTime(...)", "label=" << fineGridFaceLabel.toString() );
    ::exahype2::fv::applyBoundaryConditions(
      [&](
        double                                       Qinside[],
        double                                       Qoutside[],
        const tarch::la::Vector<Dimensions,double>&  faceCentre,
        const tarch::la::Vector<Dimensions,double>&  volumeH,
        double                                       t,
        double                                       dt,
        int                                          normal
      ) -> void {
        InstanceOfAcoustics.boundaryConditions( Qinside, Qoutside, faceCentre, volumeH, t, normal );
      },
      marker.x(),
      marker.h(),
      InstanceOfAcoustics.getMinTimeStamp(),
      0.0001,
      11,
      2+2,
      marker.getSelectedFaceNumber(),
      fineGridFaceAcousticsQ.value
    );
    logTraceOut( "touchFaceFirstTime(...)" );
  }

}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::touchFaceLastTime(
      const peano4::datamanagement::FaceMarker& marker,
      examples::exahype2::acoustics::facedata::AcousticsQ& fineGridFaceAcousticsQ,
      examples::exahype2::acoustics::facedata::AcousticsQNew& fineGridFaceAcousticsQNew,
      examples::exahype2::acoustics::facedata::Label& fineGridFaceLabel,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> coarseGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> coarseGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& coarseGridCellAcousticsQ) {


}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::createCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> fineGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> fineGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> fineGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& fineGridCellAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> coarseGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> coarseGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& coarseGridCellAcousticsQ) {


}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::destroyCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> fineGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> fineGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> fineGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& fineGridCellAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> coarseGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> coarseGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& coarseGridCellAcousticsQ) {


}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::touchCellFirstTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> fineGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> fineGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> fineGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& fineGridCellAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> coarseGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> coarseGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& coarseGridCellAcousticsQ) {

  auto serialisePatchIndex = [](tarch::la::Vector<Dimensions,int> overlapCell, int normal) {
    int base   = 1;
    int result = 0;
    for (int d=0; d<Dimensions; d++) {
      result += overlapCell(d) * base;
      if (d==normal) {
        base *= 1*2;
      }
      else {
        base *= 11;
      }
    }
    return result;
  };

  if (not marker.isRefined()) {
    logTraceInWith1Argument( "touchCellFirstTime(...)", marker.toString() );

    
    double* reconstructedPatch;
    #if Dimensions==2
    reconstructedPatch = ::tarch::multicore::allocateMemory(676, ::tarch::multicore::MemoryLocation::Heap);
    #elif Dimensions==3
    reconstructedPatch = ::tarch::multicore::allocateMemory(8788, ::tarch::multicore::MemoryLocation::Heap);
    #endif


    //
    // Loop over original patch (k) and copy stuff over.
    //
    dfor(sourceCell,11) {
      tarch::la::Vector<Dimensions,int> destinationCell = sourceCell + tarch::la::Vector<Dimensions,int>(1);
      int sourceCellSerialised       = peano4::utils::dLinearised(sourceCell,11);
      int destinationCellSerialised  = peano4::utils::dLinearised(destinationCell,11 + 2*1);
      for (int j=0; j<4; j++) {
        reconstructedPatch[destinationCellSerialised*4+j] = fineGridCellAcousticsQ.value[ sourceCellSerialised*4+j ];
        assertion3( reconstructedPatch[destinationCellSerialised*4+j]==reconstructedPatch[destinationCellSerialised*4+j], sourceCell, j, _treeNumber );
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
      dfore(k,11,d,0) {
        for (int i=0; i<1; i++) {
          tarch::la::Vector<Dimensions,int> destinationCell = k + tarch::la::Vector<Dimensions,int>(1);
          tarch::la::Vector<Dimensions,int> sourceCell      = k;
          destinationCell(d) = i;
          sourceCell(d)      = i;
          
          int destinationCellSerialised   = peano4::utils::dLinearised(destinationCell,11 + 2*1);
          int sourceCellSerialised        = serialisePatchIndex(sourceCell,d);

          for (int j=0; j<4; j++) {
            reconstructedPatch[ destinationCellSerialised*4+j ] = fineGridFacesAcousticsQ(d).value[ sourceCellSerialised*4+j ];
            assertion6( 
              reconstructedPatch[ destinationCellSerialised*4+j ]==reconstructedPatch[ destinationCellSerialised*4+j ], 
              sourceCell, destinationCell, j, d, marker.toString(), _treeNumber 
            );
          }

          destinationCell(d) = i+11+1;
          sourceCell(d)      = i+1;

          destinationCellSerialised   = peano4::utils::dLinearised(destinationCell,11 + 2*1);
          sourceCellSerialised        = serialisePatchIndex(sourceCell,d);
          for (int j=0; j<4; j++) {
            reconstructedPatch[ destinationCellSerialised*4+j ] = fineGridFacesAcousticsQ(d+Dimensions).value[ sourceCellSerialised*4+j ];
            assertion6( 
              reconstructedPatch[ destinationCellSerialised*4+j ]==reconstructedPatch[ destinationCellSerialised*4+j ], 
              sourceCell, destinationCell, j, d, marker.toString(), _treeNumber
            );
          }
        }
      }
      logTraceOut( "touchCellFirstTime(...)::loopOverFace" );
    }

    double* originalPatch = fineGridCellAcousticsQ.value;
    
    #if Dimensions==2
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS2d(
    #else
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS3d(
    #endif
  
      [&](
        double                                       QL[],
        double                                       QR[],
        const tarch::la::Vector<Dimensions,double>&  x,
        double                                       dx,
        double                                       t,
        double                                       dt,
        int                                          normal,
        double                                       FL[],
        double                                       FR[]
      ) -> void {
        
    double wave[2]; 
    double speed[2]; 

    int num_eqn   = 2;
    int num_aux   = 2;
    int num_waves = 2; 

    rp1_ptwise_(
      &num_eqn,
      &num_aux,
      &num_waves, 
      QL,                                 // double* q_l 
      QR,                                 // double* q_r
      QL+2,          // double* aux_l
      QR+2,          // double* aux_r
      wave,
      speed,
      FL,                                 // double* amdq
      FR                                  // double* apdq
    );

    for (int i=0; i<2; i++) {
      FR[i] = -FR[i];
    }
    

      },
      marker.x(),
      marker.h(),
      InstanceOfAcoustics.getMinTimeStamp(),
      0.0001,
      11,
      2,
      2,
      reconstructedPatch,
      originalPatch
  );
    
    
    
    ::tarch::multicore::freeMemory(reconstructedPatch, tarch::multicore::MemoryLocation::Heap );

    
    
    logTraceOut( "touchCellFirstTime(...)" );
  }

}


void examples::exahype2::acoustics::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0::touchCellLastTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> fineGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> fineGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> fineGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& fineGridCellAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQ> coarseGridFacesAcousticsQ,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::AcousticsQNew> coarseGridFacesAcousticsQNew,
      peano4::datamanagement::FaceEnumerator<examples::exahype2::acoustics::facedata::Label> coarseGridFacesLabel,
      examples::exahype2::acoustics::celldata::AcousticsQ& coarseGridCellAcousticsQ) {


}


