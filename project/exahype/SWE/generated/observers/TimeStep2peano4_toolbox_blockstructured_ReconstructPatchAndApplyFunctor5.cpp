#include "TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5.h"


tarch::logging::Log project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::_log( "project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5");





project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5(int treeNumber) {
  _treeNumber = treeNumber;
}


project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::~TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5() {
// @todo Should be overwritten
}


std::vector< peano4::grid::GridControlEvent > project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::getGridControlEvents() const {
return std::vector< peano4::grid::GridControlEvent >();
}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::beginTraversal(
      ) {


}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::endTraversal(
      ) {


}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::SWE::generated::facedata::sweQOld& fineGridFacesweQOld,
      project::exahype::SWE::generated::facedata::sweQNew& fineGridFacesweQNew,
      project::exahype::SWE::generated::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::exahype::SWE::generated::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& coarseGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::SWE::generated::facedata::sweQOld& fineGridFacesweQOld,
      project::exahype::SWE::generated::facedata::sweQNew& fineGridFacesweQNew,
      project::exahype::SWE::generated::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::exahype::SWE::generated::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& coarseGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::SWE::generated::facedata::sweQOld& fineGridFacesweQOld,
      project::exahype::SWE::generated::facedata::sweQNew& fineGridFacesweQNew,
      project::exahype::SWE::generated::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::exahype::SWE::generated::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& coarseGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::SWE::generated::facedata::sweQOld& fineGridFacesweQOld,
      project::exahype::SWE::generated::facedata::sweQNew& fineGridFacesweQNew,
      project::exahype::SWE::generated::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::exahype::SWE::generated::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& coarseGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchFaceFirstTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::SWE::generated::facedata::sweQOld& fineGridFacesweQOld,
      project::exahype::SWE::generated::facedata::sweQNew& fineGridFacesweQNew,
      project::exahype::SWE::generated::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::exahype::SWE::generated::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& coarseGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchFaceLastTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::exahype::SWE::generated::facedata::sweQOld& fineGridFacesweQOld,
      project::exahype::SWE::generated::facedata::sweQNew& fineGridFacesweQNew,
      project::exahype::SWE::generated::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::exahype::SWE::generated::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& coarseGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> fineGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> fineGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> fineGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> fineGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& fineGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& fineGridCellsweCellLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& coarseGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> fineGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> fineGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> fineGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> fineGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& fineGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& fineGridCellsweCellLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& coarseGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchCellFirstTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> fineGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> fineGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> fineGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> fineGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& fineGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& fineGridCellsweCellLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& coarseGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& coarseGridCellsweCellLabel) {

  fineGridCellsweCellLabel.setHasUpdated(false);

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
    double reconstructedPatch[100];
    #elif Dimensions==3
    double reconstructedPatch[500];
    #endif


    //
    // Loop over original patch (k) and copy stuff over.
    //
    dfor(sourceCell,3) {
      tarch::la::Vector<Dimensions,int> destinationCell = sourceCell + tarch::la::Vector<Dimensions,int>(1.0);
      int sourceCellSerialised       = peano4::utils::dLinearised(sourceCell,3);
      int destinationCellSerialised  = peano4::utils::dLinearised(destinationCell,3 + 2*1.0);
      for (int j=0; j<4; j++) {
        reconstructedPatch[destinationCellSerialised*4+j] = fineGridCellsweQ.value[ sourceCellSerialised*4+j ];
        nonCriticalAssertion4( reconstructedPatch[destinationCellSerialised*4+j]==reconstructedPatch[destinationCellSerialised*4+j], sourceCell, j, _treeNumber, marker.toString() );
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

          for (int j=0; j<4; j++) {
            reconstructedPatch[ destinationCellSerialised*4+j ] = fineGridFacessweQNew(d).value[ sourceCellSerialised*4+j ];
            assertion7( 
              true or 
              reconstructedPatch[ destinationCellSerialised*4+j ]==reconstructedPatch[ destinationCellSerialised*4+j ], 
              sourceCell, destinationCell, j, d, marker.toString(), _treeNumber, marker.toString()
            );
          }

          destinationCell(d) = i+3+1.0;
          sourceCell(d)      = i+1.0;

          destinationCellSerialised   = peano4::utils::dLinearised(destinationCell,3 + 2*1.0);
          sourceCellSerialised        = serialisePatchIndex(sourceCell,d);
          for (int j=0; j<4; j++) {
            reconstructedPatch[ destinationCellSerialised*4+j ] = fineGridFacessweQNew(d+Dimensions).value[ sourceCellSerialised*4+j ];
            assertion7( 
              true or 
              reconstructedPatch[ destinationCellSerialised*4+j ]==reconstructedPatch[ destinationCellSerialised*4+j ], 
              sourceCell, destinationCell, j, d, marker.toString(), _treeNumber, marker.toString()
            );
          }
        }
      }
      logTraceOut( "touchCellFirstTime(...)::loopOverFace" );
    }

    double* targetPatch = fineGridCellsweQ.value;
    
    double cellTimeStepSize = -1.0;
    double cellTimeStamp    = -1.0;
     
    
    
  cellTimeStepSize = repositories::InstanceOfswe.getAdmissibleTimeStepSize();
  cellTimeStamp    = fineGridCellsweCellLabel.getTimeStamp();
    
    assertion2( tarch::la::greaterEquals( cellTimeStepSize, 0.0 ), cellTimeStepSize, cellTimeStamp );
    assertion2( tarch::la::greaterEquals( cellTimeStamp, 0.0 ), cellTimeStepSize, cellTimeStamp );

    const double usedTimeStepSize = cellTimeStepSize;

    ::exahype2::fv::validatePatch(
        reconstructedPatch,
        3,
        1,
        3,
        1, // halo
        std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): " + marker.toString()
    ); // previous time step has to be valid
  
    ::exahype2::fv::copyPatch(
        reconstructedPatch,
        targetPatch,
        3,
        1,
        3,
        1 // halo size
    );

    
    #if Dimensions==2
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS2d(
    #else
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS3d(
    #endif
    
        [&](
          const double * __restrict__                  QL,
          const double * __restrict__                  QR,
          const tarch::la::Vector<Dimensions,double>&  x,
          double                                       dx,
          double                                       t,
          double                                       dt,
          int                                          normal,
          double                                       FL[],
          double                                       FR[]
        ) -> void {
          
        ::exahype2::fv::splitRusanov1d(
          [] (
            const double * __restrict__                  Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double                                       F[]
          ) -> void {
            
            repositories::InstanceOfswe.flux( Q, faceCentre, volumeH, t, normal, F );
            
          },
          [] (
            const double * __restrict__                  Q,
            const double * __restrict__                  deltaQ,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double                                       BgradQ[]
          ) -> void {
            
            repositories::InstanceOfswe.nonconservativeProduct( Q, deltaQ, faceCentre, volumeH, t, normal, BgradQ );
            
          },
          [] (
            const double * __restrict__                  Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal
          ) -> double {
            return repositories::InstanceOfswe.maxEigenvalue( Q, faceCentre, volumeH, t, normal);
          },
          QL, QR, x, dx, t, dt, normal,
          3,
          1,
          FL,FR,
          
          false,
          
          
          false
          
        );
        },
        [&](
          const double * __restrict__                  Q,
          const tarch::la::Vector<Dimensions,double>&  x,
          double                                       dx,
          double                                       t,
          double                                       dt,
          double * __restrict__                        S
        ) -> void {
          
  std::fill_n(S,3,0.0);
        },
        marker.x(),
        marker.h(),
        cellTimeStamp,
        cellTimeStepSize,
        3,
        3,
        1,
        reconstructedPatch,
        targetPatch
    );
  
    
    const double maxEigenvalue = ::exahype2::fv::maxEigenvalue_AoS(
      [] (
        const double * __restrict__                  Q,
        const tarch::la::Vector<Dimensions,double>&  faceCentre,
        const tarch::la::Vector<Dimensions,double>&  volumeH,
        double                                       t,
        double                                       dt,
        int                                          normal
      ) -> double {
        return repositories::InstanceOfswe.maxEigenvalue( Q, faceCentre, volumeH, t, normal);
      },
      marker.x(),
      marker.h(),
      cellTimeStamp,
      cellTimeStepSize,
      3,
      3,
      1,
      targetPatch
    );
    
    repositories::InstanceOfswe.setMaxEigenvalue( maxEigenvalue );  
    
    fineGridCellsweCellLabel.setTimeStamp(cellTimeStamp + usedTimeStepSize);
    fineGridCellsweCellLabel.setTimeStepSize(cellTimeStepSize);
    fineGridCellsweCellLabel.setHasUpdated(true);
    
    repositories::InstanceOfswe.update(cellTimeStepSize, cellTimeStamp + usedTimeStepSize, marker.h()(0) );

    ::exahype2::fv::validatePatch(
        targetPatch,
        3,
        1,
        3,
        0, // halo
        std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): " + marker.toString()
    ); // outcome has to be valid
  
    
    

    logTraceOut( "touchCellFirstTime(...)" );
  }

  else if (not marker.willBeRefined() and not marker.hasBeenRefined()) {
    double cellTimeStepSize = -1.0;
    double cellTimeStamp    = -1.0;
     
    
  cellTimeStepSize = repositories::InstanceOfswe.getAdmissibleTimeStepSize();
  cellTimeStamp    = fineGridCellsweCellLabel.getTimeStamp();
    
    assertion2( tarch::la::greaterEquals( cellTimeStepSize, 0.0 ), cellTimeStepSize, cellTimeStamp );
    assertion2( tarch::la::greaterEquals( cellTimeStamp, 0.0 ), cellTimeStepSize, cellTimeStamp );

    repositories::InstanceOfswe.update(0.0, cellTimeStamp, marker.h()(0) );
  }

}


void project::exahype::SWE::generated::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchCellLastTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> fineGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> fineGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> fineGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> fineGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& fineGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& fineGridCellsweCellLabel,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::exahype::SWE::generated::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::exahype::SWE::generated::celldata::sweQ& coarseGridCellsweQ,
      project::exahype::SWE::generated::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


