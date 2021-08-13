#include "Interpolation.h"
#include "Enumeration.h"

#include "peano4/utils/Loop.h"
#include "tarch/la/DynamicMatrix.h"


namespace {
  tarch::logging::Log _log( "toolbox::blockstructured" );
}


tarch::la::DynamicMatrix  toolbox::blockstructured::internal::create1dLinearInterpolation(int numberOfDoFsPerAxisInPatch, int number, int where, int repeat) {
    tarch::la::DynamicMatrix P1d(3,3,{
      {1.0/3.0, 2.0/3.0,     0.0},
      {    0.0, 3.0/3.0,     0.0},
      {    0.0, 2.0/3.0, 1.0/3.0}
    });
    P1d.replicateRows( numberOfDoFsPerAxisInPatch, 1 );
    P1d.removeColumn(0);
    P1d.removeColumn(numberOfDoFsPerAxisInPatch);

  /*
   * See comments on missing diagonal element
   * ========================================
    P1d(0,0) =  2.0/3.0 + 1.0/3.0 * 2.0;
    P1d(0,1) = -1.0/3.0;
    P1d(numberOfDoFsPerAxisInPatch*3-1,numberOfDoFsPerAxisInPatch-1) =  2.0/3.0 + 1.0/3.0 * 2.0;
    P1d(numberOfDoFsPerAxisInPatch*3-1,numberOfDoFsPerAxisInPatch-2) = -1.0/3.0;
  */

    P1d(0,0) =  1.0;
    P1d(0,1) =  0.0;
    P1d(numberOfDoFsPerAxisInPatch*3-1,numberOfDoFsPerAxisInPatch-1) =  1.0;
    P1d(numberOfDoFsPerAxisInPatch*3-1,numberOfDoFsPerAxisInPatch-2) =  0.0;

    if (where!=-1) {
      #if Dimensions==3
      tarch::la::DynamicMatrix P( P1d, P1d, false);
      P.insertColumns(number,where,repeat);
      P.insertRows(number,where,repeat);
      return P;
      #else
      P1d.insertColumns(number,where,repeat);
      P1d.insertRows(number,where,repeat);
      return P1d;
      #endif
    }
    else return P1d;
}


void toolbox::blockstructured::internal::clearHalfOfHaloLayerAoS(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  bool                                      clearInnerPart,
  double*                                   value
) {
  const int normal = marker.getSelectedFaceNumber() % Dimensions;
  const bool left  = (marker.getSelectedFaceNumber() < Dimensions) xor clearInnerPart;

  // clear fine grid data structure
  dfore(k,numberOfDoFsPerAxisInPatch,normal,0) {
    for (int i=0; i<overlap; i++) {
      tarch::la::Vector<Dimensions,int> targetCell = k;
      targetCell(normal)  = left ? i : i + overlap;
      int targetCellSerialised = serialisePatchIndexInOverlap(
        targetCell,
        numberOfDoFsPerAxisInPatch,
        overlap,
        normal
      );
      assertion(targetCellSerialised>=0);
      for (int j=0; j<unknowns; j++) {
        value[targetCellSerialised*unknowns+j] = 0.0;
      }
    }
  }
}


void toolbox::blockstructured::clearHaloLayerAoS(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  double*                                   value
) {
  const int normal = marker.getSelectedFaceNumber() % Dimensions;

  // clear fine grid data structure
  dfore(k,numberOfDoFsPerAxisInPatch,normal,0) {
    for (int i=0; i<overlap*2; i++) {
      tarch::la::Vector<Dimensions,int> targetCell = k;
      targetCell(normal)  = i;
      int targetCellSerialised = serialisePatchIndexInOverlap(
        targetCell,
        numberOfDoFsPerAxisInPatch,
        overlap,
        normal
      );
      assertion(targetCellSerialised>=0);
      for (int j=0; j<unknowns; j++) {
        value[targetCellSerialised*unknowns+j] = 0.0;
      }
    }
  }
}


void toolbox::blockstructured::internal::projectHaloLayers_AoS(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  std::function<void(
      tarch::la::Vector<Dimensions,int> coarseVolumeNumber,
      tarch::la::Vector<Dimensions,int> fineVolumeNumber,
      tarch::la::Vector<Dimensions,double> coarseVolumeCentre,
      tarch::la::Vector<Dimensions,double> fineVolumeCentre,
      double courseVolumeH,
      double fineVolumeH
  )> update,
  bool mapInnerHalfOfHalo
) {
  logTraceInWith4Arguments( "projectHaloLayers_AoS(...)", marker.toString(), numberOfDoFsPerAxisInPatch, overlap, mapInnerHalfOfHalo );

  const int  normal              = marker.getSelectedFaceNumber() % Dimensions;
  const bool pickLeftHalfOfHalo  = (marker.getSelectedFaceNumber() < Dimensions) xor mapInnerHalfOfHalo;

  const double volumeHCoarse = marker.h()(0) / static_cast<double>(numberOfDoFsPerAxisInPatch) * 3.0;
  const double volumeHFine   = marker.h()(0) / static_cast<double>(numberOfDoFsPerAxisInPatch);

  tarch::la::Vector<Dimensions,double> leftBottomCornerOfHaloFine   = marker.x();
  tarch::la::Vector<Dimensions,double> leftBottomCornerOfHaloCoarse = marker.x();
  for (int d=0; d<Dimensions; d++) {
    if (d==normal) {
      leftBottomCornerOfHaloFine(d)   -= static_cast<double>(overlap) * volumeHFine;
      leftBottomCornerOfHaloCoarse(d) -= static_cast<double>(overlap) * volumeHCoarse;
    }
    else {
      leftBottomCornerOfHaloFine(d)   = marker.x()(d)-marker.h()(d)/2.0;
      leftBottomCornerOfHaloCoarse(d) = leftBottomCornerOfHaloFine(d)-marker.getRelativePositionWithinFatherCell()(d)*marker.h()(d);
    }
  }

  dfore(kCoarse,numberOfDoFsPerAxisInPatch,normal,0) {
    dfore(kFine,numberOfDoFsPerAxisInPatch,normal,0) {
      for (int iCoarse=0; iCoarse<overlap; iCoarse++)
      for (int iFine=0;   iFine<overlap;   iFine++) {
        tarch::la::Vector<Dimensions,int> coarseVolume = kCoarse;
        tarch::la::Vector<Dimensions,int> fineVolume   = kFine;
        coarseVolume(normal) += pickLeftHalfOfHalo ? iCoarse : iCoarse+overlap;
        fineVolume(normal)   += pickLeftHalfOfHalo ? iFine   : iFine+overlap;

        tarch::la::Vector<Dimensions,double> volumeXCoarse = leftBottomCornerOfHaloCoarse
          + volumeHCoarse * tarch::la::convertScalar<double>(coarseVolume)
          + 0.5 * tarch::la::Vector<Dimensions,double>(volumeHCoarse);
        tarch::la::Vector<Dimensions,double> volumeXFine = leftBottomCornerOfHaloFine
          + volumeHFine * tarch::la::convertScalar<double>(fineVolume)
          + 0.5 * tarch::la::Vector<Dimensions,double>(volumeHFine);

        update(
          coarseVolume,
          fineVolume,
          volumeXCoarse,
          volumeXFine,
          volumeHCoarse,
          volumeHFine
        );
      }
    }
  }

  logTraceOut( "projectHaloLayers_AoS(...)" );
}


void toolbox::blockstructured::interpolateHaloLayer_AoS_piecewise_constant(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues
) {
  interpolateOntoOuterHalfOfHaloLayer_AoS_piecewise_constant(marker,numberOfDoFsPerAxisInPatch,overlap,unknowns,fineGridValues,coarseGridValues,false);
  interpolateOntoOuterHalfOfHaloLayer_AoS_piecewise_constant(marker,numberOfDoFsPerAxisInPatch,overlap,unknowns,fineGridValues,coarseGridValues,true);
}


void toolbox::blockstructured::interpolateOntoOuterHalfOfHaloLayer_AoS_piecewise_constant(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues,
  bool                                      swapInsideOutside
) {
  logTraceInWith6Arguments( "interpolateOntoOuterHalfOfHaloLayer_AoS_piecewise_constant(...)", marker.toString(), numberOfDoFsPerAxisInPatch, overlap, unknowns, fineGridValues, coarseGridValues );

  const int  normal              = marker.getSelectedFaceNumber() % Dimensions;

  internal::projectHaloLayers_AoS(
    marker,
    numberOfDoFsPerAxisInPatch,
    overlap,
    [&](
      tarch::la::Vector<Dimensions,int>    coarseVolume,
      tarch::la::Vector<Dimensions,int>    fineVolume,
      tarch::la::Vector<Dimensions,double> coarseVolumeCentre,
      tarch::la::Vector<Dimensions,double> fineVolumeCentre,
      double coarseVolumeH,
      double fineVolumeH
    ) -> void {
      // This is where the magic happens
      bool fineGridXIsWithinSupportOfCoarseVolume = tarch::la::normMax(
        coarseVolumeCentre - fineVolumeCentre
      ) < coarseVolumeH/2.0;
      if (fineGridXIsWithinSupportOfCoarseVolume) {
        int coarseVolumeLinearised = serialisePatchIndexInOverlap(
          coarseVolume,
          numberOfDoFsPerAxisInPatch, overlap, normal
          );
        int fineVolumeLinearised = serialisePatchIndexInOverlap(
          fineVolume,
          numberOfDoFsPerAxisInPatch, overlap, normal
          );
        logDebug(
          "interpolateOntoOuterHalfOfHaloLayer_AoS_piecewise_constant(...)",
          coarseVolume << "->" << fineVolume << " i.e. " << coarseVolumeLinearised << "->" << fineVolumeLinearised <<
          " (normal=" << normal << ",restrict=" << fineGridXIsWithinSupportOfCoarseVolume <<
          ",fine-x=" << fineVolumeCentre << ",coarse-x=" << coarseVolumeCentre <<
          ",coarse-h=" << coarseVolumeH << ",fine-h=" << fineVolumeH <<
          ",first-value-fine=" << fineGridValues[fineVolumeLinearised*unknowns] <<
          ",first-value-coarse=" << coarseGridValues[coarseVolumeLinearised*unknowns] <<
          ")"
        );
        for (int j=0; j<unknowns; j++) {
          fineGridValues[fineVolumeLinearised*unknowns+j] = coarseGridValues[coarseVolumeLinearised*unknowns+j];
        }
      }
    },
    swapInsideOutside // mapOuterCoarseGridHaloOntoInnerFineGridHalo
  );

  logTraceOut( "interpolateOntoOuterHalfOfHaloLayer_AoS_piecewise_constant(...)" );
}


void toolbox::blockstructured::internal::projectCells_AoS(
  const peano4::datamanagement::CellMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  std::function<void(
    tarch::la::Vector<Dimensions,int> coarseVolume,
    tarch::la::Vector<Dimensions,int> fineVolume,
    tarch::la::Vector<Dimensions,double> coarseVolumeCentre,
    tarch::la::Vector<Dimensions,double> fineVolumeCentre,
    double coarseVolumeH,
    double fineVolumeH
  )> update
) {
  logTraceInWith2Arguments( "projectCells_AoS(...)", marker.toString(), numberOfDoFsPerAxisInPatch );

  const double volumeHCoarse = marker.h()(0) / static_cast<double>(numberOfDoFsPerAxisInPatch) * 3.0;
  const double volumeHFine   = marker.h()(0) / static_cast<double>(numberOfDoFsPerAxisInPatch);

  tarch::la::Vector<Dimensions,double> leftBottomOfFineCell   = marker.getOffset();
  tarch::la::Vector<Dimensions,double> leftBottomOfCoarseCell = marker.getOffset() - tarch::la::multiplyComponents( marker.h(), tarch::la::convertScalar<double>(marker.getRelativePositionWithinFatherCell()) );

  dfor(kCoarse,numberOfDoFsPerAxisInPatch) {
    dfor(kFine,numberOfDoFsPerAxisInPatch) {
      tarch::la::Vector<Dimensions,double> volumeXCoarse = leftBottomOfCoarseCell
          + volumeHCoarse * tarch::la::convertScalar<double>(kCoarse)
          + 0.5 * tarch::la::Vector<Dimensions,double>(volumeHCoarse);
      tarch::la::Vector<Dimensions,double> volumeXFine = leftBottomOfFineCell
          + volumeHFine * tarch::la::convertScalar<double>(kFine)
          + 0.5 * tarch::la::Vector<Dimensions,double>(volumeHFine);

      update(
        kCoarse,
        kFine,
        volumeXCoarse,
        volumeXFine,
        volumeHCoarse,
        volumeHFine
      );
    }
  }

  logTraceOut( "projectCells_AoS(...)" );
}


void toolbox::blockstructured::interpolateCell_AoS_piecewise_constant(
  const peano4::datamanagement::CellMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues
) {
  internal::projectCells_AoS(
    marker,
    numberOfDoFsPerAxisInPatch,
    [&](
      tarch::la::Vector<Dimensions,int> coarseVolume,
      tarch::la::Vector<Dimensions,int> fineVolume,
      tarch::la::Vector<Dimensions,double> coarseVolumeCentre,
      tarch::la::Vector<Dimensions,double> fineVolumeCentre,
      double coarseVolumeH,
      double fineVolumeH
    ) -> void {
      int coarseVolumeLinearised = peano4::utils::dLinearised( coarseVolume, numberOfDoFsPerAxisInPatch );
      int fineVolumeLinearised   = peano4::utils::dLinearised( fineVolume, numberOfDoFsPerAxisInPatch );
      for (int j=0; j<unknowns; j++) {
        fineGridValues[coarseVolumeLinearised*unknowns+j] = coarseGridValues[fineVolumeLinearised*unknowns+j];
      }
    }
  );
}


void toolbox::blockstructured::restrictOntoOuterHalfOfHaloLayer_AoS_averaging(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues,
  bool                                      swapInsideOutside
) {
  logTraceInWith6Arguments( "restrictOntoOuterHalfOfHaloLayer_AoS_averaging(...)", marker.toString(), numberOfDoFsPerAxisInPatch, overlap, unknowns, fineGridValues, coarseGridValues );

  const int  normal          = marker.getSelectedFaceNumber() % Dimensions;
  double scaleFineGridVolume = std::pow(3.0,-static_cast<double>(Dimensions-1));

  logDebug( "restrictOntoOuterHalfOfHaloLayer_AoS_averaging(...)", "fineGridValues=" << fineGridValues << ",coarseGridValues=" << coarseGridValues );
  internal::projectHaloLayers_AoS(
    marker,
    numberOfDoFsPerAxisInPatch,
    overlap,
    [&](
      tarch::la::Vector<Dimensions,int>    coarseVolume,
      tarch::la::Vector<Dimensions,int>    fineVolume,
      tarch::la::Vector<Dimensions,double> coarseVolumeCentre,
      tarch::la::Vector<Dimensions,double> fineVolumeCentre,
      double coarseVolumeH,
      double fineVolumeH
    ) -> void {
      // This is where the magic happens
      double distance = tarch::la::normMax( coarseVolumeCentre - fineVolumeCentre );
      bool fineGridXIsWithinSupportOfCoarseVolume = distance < coarseVolumeH/2.0;
      if (fineGridXIsWithinSupportOfCoarseVolume) {
        int coarseVolumeLinearised = serialisePatchIndexInOverlap(
          coarseVolume,
          numberOfDoFsPerAxisInPatch, overlap, normal
          );
        int fineVolumeLinearised = serialisePatchIndexInOverlap(
          fineVolume,
          numberOfDoFsPerAxisInPatch, overlap, normal
          );
        for (int j=0; j<unknowns; j++) {
          assertion5(coarseGridValues[coarseVolumeLinearised*unknowns+j]==coarseGridValues[coarseVolumeLinearised*unknowns+j], coarseVolume, fineVolume, coarseVolumeCentre, fineVolumeCentre, marker.toString());
          assertion5(fineGridValues[fineVolumeLinearised*unknowns+j]==fineGridValues[fineVolumeLinearised*unknowns+j],         coarseVolume, fineVolume, coarseVolumeCentre, fineVolumeCentre, marker.toString());
          coarseGridValues[coarseVolumeLinearised*unknowns+j] += scaleFineGridVolume * fineGridValues[fineVolumeLinearised*unknowns+j];
        }
        logDebug(
          "restrictOntoOuterHalfOfHaloLayer_AoS_averaging(...)",
          fineVolume << "->" << coarseVolume << " i.e. " << fineVolumeLinearised << "->" << coarseVolumeLinearised <<
          " (normal=" << normal << ",restrict=" << fineGridXIsWithinSupportOfCoarseVolume <<
          ",fine-x=" << fineVolumeCentre << ",coarse-x=" << coarseVolumeCentre <<
          ",coarse-h=" << coarseVolumeH << ",fine-h=" << fineVolumeH << ",d=" << distance <<
          ",first-value-fine=" << fineGridValues[fineVolumeLinearised*unknowns] <<
          ",first-value-coarse=" << coarseGridValues[coarseVolumeLinearised*unknowns] <<
          ",fine-add=" << (&fineGridValues[fineVolumeLinearised*unknowns]) <<
          ",coarse-add=" << (&coarseGridValues[coarseVolumeLinearised*unknowns]) <<
          ")"
        );
      }
    },
    not swapInsideOutside // mapOuterCoarseGridHaloOntoInnerFineGridHalo
  );

  logTraceOut( "restrictOntoOuterHalfOfHaloLayer_AoS_averaging(...)" );
}


void toolbox::blockstructured::restrictHaloLayer_AoS_averaging(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues
) {
  restrictOntoOuterHalfOfHaloLayer_AoS_averaging( marker, numberOfDoFsPerAxisInPatch, overlap, unknowns, fineGridValues, coarseGridValues, false );
  restrictOntoOuterHalfOfHaloLayer_AoS_averaging( marker, numberOfDoFsPerAxisInPatch, overlap, unknowns, fineGridValues, coarseGridValues, true );
}


void toolbox::blockstructured::restrictCell_AoS_averaging(
  const peano4::datamanagement::CellMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues
) {
  double scaleFineGridVolume = std::pow(3.0,-static_cast<double>(Dimensions-1));
  internal::projectCells_AoS(
    marker,
    numberOfDoFsPerAxisInPatch,
    [&](
      tarch::la::Vector<Dimensions,int> coarseVolume,
      tarch::la::Vector<Dimensions,int> fineVolume,
      tarch::la::Vector<Dimensions,double> coarseVolumeCentre,
      tarch::la::Vector<Dimensions,double> fineVolumeCentre,
      double coarseVolumeH,
      double fineVolumeH
    ) -> void {
      int coarseVolumeLinearised = peano4::utils::dLinearised( coarseVolume, numberOfDoFsPerAxisInPatch );
      int fineVolumeLinearised   = peano4::utils::dLinearised( fineVolume, numberOfDoFsPerAxisInPatch );
      for (int j=0; j<unknowns; j++) {
        coarseGridValues[coarseVolumeLinearised*unknowns+j] += scaleFineGridVolume * fineGridValues[fineVolumeLinearised*unknowns+j];
      }
    }
  );
}


void toolbox::blockstructured::interpolateOntoOuterHalfOfHaloLayer_AoS_linear(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues,
  bool                                      swapInsideOutside
) {
  assertion(overlap==1);

  const int  normal                        = marker.getSelectedFaceNumber() % Dimensions;
  const bool pickLeftHalfOfHaloOnFineGrid  = (marker.getSelectedFaceNumber() < Dimensions) xor swapInsideOutside;

  #if Dimensions==2
  if ( normal==0 and pickLeftHalfOfHaloOnFineGrid ) {
    tarch::la::DynamicMatrix P( internal::create1dLinearInterpolation(numberOfDoFsPerAxisInPatch,1,1,1) );
    int matrixRowBlock = marker.getRelativePositionWithinFatherCell()(1);
    P.batchedMultiplyAoS(
      fineGridValues, // image
      coarseGridValues,  // preimage
      unknowns,          // batch size, i.e. how often to apply it in one AoS rush
      numberOfDoFsPerAxisInPatch*2, // result size, i.e. size of image
      matrixRowBlock * numberOfDoFsPerAxisInPatch * 2
    );
  }
  else if ( normal==0 and not pickLeftHalfOfHaloOnFineGrid ) {
    tarch::la::DynamicMatrix P( internal::create1dLinearInterpolation(numberOfDoFsPerAxisInPatch,1,0,1) );
    int matrixRowBlock = marker.getRelativePositionWithinFatherCell()(1);
    P.batchedMultiplyAoS(
      fineGridValues, // image
      coarseGridValues,  // preimage
      unknowns,          // batch size, i.e. how often to apply it in one AoS rush
      numberOfDoFsPerAxisInPatch*2, // result size, i.e. size of image
      matrixRowBlock * numberOfDoFsPerAxisInPatch * 2
    );
  }
  else if (normal==1 and pickLeftHalfOfHaloOnFineGrid ) {
    tarch::la::DynamicMatrix P( internal::create1dLinearInterpolation(numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch) );
    int matrixRowBlock = marker.getRelativePositionWithinFatherCell()(0);
    P.batchedMultiplyAoS(
      fineGridValues, // image
      coarseGridValues,  // preimage
      unknowns,          // batch size, i.e. how often to apply it in one AoS rush
      numberOfDoFsPerAxisInPatch*2, // result size, i.e. size of image
      matrixRowBlock * numberOfDoFsPerAxisInPatch * 2
    );
  }
  else if (normal==1 and not pickLeftHalfOfHaloOnFineGrid ) {
    tarch::la::DynamicMatrix P( internal::create1dLinearInterpolation(numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch,0,numberOfDoFsPerAxisInPatch) );
    int matrixRowBlock = marker.getRelativePositionWithinFatherCell()(0);
    P.batchedMultiplyAoS(
      fineGridValues, // image
      coarseGridValues,  // preimage
      unknowns,          // batch size, i.e. how often to apply it in one AoS rush
      numberOfDoFsPerAxisInPatch*2, // result size, i.e. size of image
      matrixRowBlock * numberOfDoFsPerAxisInPatch * 2
    );
  }
  #elif Dimensions==3
  if ( normal==0 and pickLeftHalfOfHaloOnFineGrid ) {
    tarch::la::DynamicMatrix P( internal::create1dLinearInterpolation(numberOfDoFsPerAxisInPatch,1,1,1) );
    int matrixRowBlock = marker.getRelativePositionWithinFatherCell()(1) + marker.getRelativePositionWithinFatherCell()(2)*3;
    P.batchedMultiplyAoS(
      fineGridValues, // image
      coarseGridValues,  // preimage
      unknowns,          // batch size, i.e. how often to apply it in one AoS rush
      numberOfDoFsPerAxisInPatch*numberOfDoFsPerAxisInPatch*2, // result size, i.e. size of image
      matrixRowBlock * numberOfDoFsPerAxisInPatch * numberOfDoFsPerAxisInPatch * 2
    );
  }
  else if ( normal==0 and not pickLeftHalfOfHaloOnFineGrid ) {
    tarch::la::DynamicMatrix P( internal::create1dLinearInterpolation(numberOfDoFsPerAxisInPatch,1,0,1) );
    int matrixRowBlock = marker.getRelativePositionWithinFatherCell()(1) + marker.getRelativePositionWithinFatherCell()(2)*3;
    P.batchedMultiplyAoS(
      fineGridValues, // image
      coarseGridValues,  // preimage
      unknowns,          // batch size, i.e. how often to apply it in one AoS rush
      numberOfDoFsPerAxisInPatch*numberOfDoFsPerAxisInPatch*2, // result size, i.e. size of image
      matrixRowBlock * numberOfDoFsPerAxisInPatch * numberOfDoFsPerAxisInPatch * 2
    );
  }
  else if (normal==1 and pickLeftHalfOfHaloOnFineGrid ) {
    tarch::la::DynamicMatrix P( internal::create1dLinearInterpolation(numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch) );
    int matrixRowBlock = marker.getRelativePositionWithinFatherCell()(0) + marker.getRelativePositionWithinFatherCell()(2)*3;
    P.batchedMultiplyAoS(
      fineGridValues, // image
      coarseGridValues,  // preimage
      unknowns,          // batch size, i.e. how often to apply it in one AoS rush
      numberOfDoFsPerAxisInPatch*numberOfDoFsPerAxisInPatch*2, // result size, i.e. size of image
      matrixRowBlock * numberOfDoFsPerAxisInPatch * numberOfDoFsPerAxisInPatch * 2
    );
  }
  else if (normal==1 and not pickLeftHalfOfHaloOnFineGrid ) {
    tarch::la::DynamicMatrix P( internal::create1dLinearInterpolation(numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch,0,numberOfDoFsPerAxisInPatch) );
    int matrixRowBlock = marker.getRelativePositionWithinFatherCell()(0) + marker.getRelativePositionWithinFatherCell()(2)*3;
    P.batchedMultiplyAoS(
      fineGridValues, // image
      coarseGridValues,  // preimage
      unknowns,          // batch size, i.e. how often to apply it in one AoS rush
      numberOfDoFsPerAxisInPatch*numberOfDoFsPerAxisInPatch*2, // result size, i.e. size of image
      matrixRowBlock * numberOfDoFsPerAxisInPatch * numberOfDoFsPerAxisInPatch * 2
    );
  }
  else if (normal==2 and pickLeftHalfOfHaloOnFineGrid ) {
    tarch::la::DynamicMatrix P( internal::create1dLinearInterpolation(numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch*numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch*numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch*numberOfDoFsPerAxisInPatch) );
    int matrixRowBlock = marker.getRelativePositionWithinFatherCell()(0) + marker.getRelativePositionWithinFatherCell()(1)*3;
    P.batchedMultiplyAoS(
      fineGridValues, // image
      coarseGridValues,  // preimage
      unknowns,          // batch size, i.e. how often to apply it in one AoS rush
      numberOfDoFsPerAxisInPatch*numberOfDoFsPerAxisInPatch*2, // result size, i.e. size of image
      matrixRowBlock * numberOfDoFsPerAxisInPatch * numberOfDoFsPerAxisInPatch * 2
    );
  }
  else if (normal==2 and not pickLeftHalfOfHaloOnFineGrid ) {
    tarch::la::DynamicMatrix P( internal::create1dLinearInterpolation(numberOfDoFsPerAxisInPatch,numberOfDoFsPerAxisInPatch*numberOfDoFsPerAxisInPatch,0,numberOfDoFsPerAxisInPatch*numberOfDoFsPerAxisInPatch) );
    int matrixRowBlock = marker.getRelativePositionWithinFatherCell()(0) + marker.getRelativePositionWithinFatherCell()(1)*3;
    P.batchedMultiplyAoS(
      fineGridValues, // image
      coarseGridValues,  // preimage
      unknowns,          // batch size, i.e. how often to apply it in one AoS rush
      numberOfDoFsPerAxisInPatch*numberOfDoFsPerAxisInPatch*2, // result size, i.e. size of image
      matrixRowBlock * numberOfDoFsPerAxisInPatch * numberOfDoFsPerAxisInPatch * 2
    );
  }
  #endif
}


void toolbox::blockstructured::interpolateHaloLayer_AoS_linear(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues
) {
  interpolateOntoOuterHalfOfHaloLayer_AoS_linear(marker,numberOfDoFsPerAxisInPatch,overlap,unknowns,fineGridValues,coarseGridValues,false);
  interpolateOntoOuterHalfOfHaloLayer_AoS_linear(marker,numberOfDoFsPerAxisInPatch,overlap,unknowns,fineGridValues,coarseGridValues,true);
}


void toolbox::blockstructured::interpolateCell_AoS_linear(
  const peano4::datamanagement::CellMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues
) {
  toolbox::blockstructured::interpolateCell_AoS_piecewise_constant(
    marker,
    numberOfDoFsPerAxisInPatch,
    unknowns,
    fineGridValues,
    coarseGridValues
  );
}


void toolbox::blockstructured::interpolateOntoOuterHalfOfHaloLayer_AoS_outflow(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues,
  bool                                      swapInsideOutside
) {
  assertionEquals(overlap,1);

  interpolateOntoOuterHalfOfHaloLayer_AoS_linear(
    marker, numberOfDoFsPerAxisInPatch, overlap, unknowns, fineGridValues, coarseGridValues,
    not swapInsideOutside
  );

  const int  normal                        = marker.getSelectedFaceNumber() % Dimensions;
  const bool pickLeftHalfOfHaloOnFineGrid  = (marker.getSelectedFaceNumber() < Dimensions) xor swapInsideOutside;

  dfore(fineVolumeOutside,numberOfDoFsPerAxisInPatch,normal,pickLeftHalfOfHaloOnFineGrid ? 0 : 1) {
    tarch::la::Vector<Dimensions,int>    fineVolumeInside = fineVolumeOutside;
    fineVolumeInside(normal) = pickLeftHalfOfHaloOnFineGrid ? 1 : 0;

    int fineVolumeOutsideLinearised = serialisePatchIndexInOverlap(
      fineVolumeOutside,
      numberOfDoFsPerAxisInPatch, overlap, normal
      );
    int fineVolumeInsideLinearised = serialisePatchIndexInOverlap(
      fineVolumeInside,
      numberOfDoFsPerAxisInPatch, overlap, normal
      );

    for (int j=0; j<unknowns; j++) {
      fineGridValues[fineVolumeOutsideLinearised*unknowns+j] = fineGridValues[fineVolumeInsideLinearised*unknowns+j];
    }
  }
}


void toolbox::blockstructured::interpolateHaloLayer_AoS_outflow(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues
) {
  interpolateOntoOuterHalfOfHaloLayer_AoS_linear(marker,numberOfDoFsPerAxisInPatch,overlap,unknowns,fineGridValues,coarseGridValues,false);
  interpolateOntoOuterHalfOfHaloLayer_AoS_linear(marker,numberOfDoFsPerAxisInPatch,overlap,unknowns,fineGridValues,coarseGridValues,true);
}


void toolbox::blockstructured::interpolateCell_AoS_outflow(
  const peano4::datamanagement::CellMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues
) {
  toolbox::blockstructured::interpolateCell_AoS_piecewise_constant(
    marker,
    numberOfDoFsPerAxisInPatch,
    unknowns,
    fineGridValues,
    coarseGridValues
  );
}


void toolbox::blockstructured::restrictOntoOuterHalfOfHaloLayer_AoS_inject(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues,
  bool                                      swapInsideOutside
) {
  logTraceInWith6Arguments( "restrictOntoOuterHalfOfHaloLayer_AoS_inject(...)", marker.toString(), numberOfDoFsPerAxisInPatch, overlap, unknowns, fineGridValues, coarseGridValues );

  const int  normal                        = marker.getSelectedFaceNumber() % Dimensions;
  const bool pickLeftHalfOfHaloOnFineGrid  = (marker.getSelectedFaceNumber() >= Dimensions) xor swapInsideOutside;

  dfore(kFine,numberOfDoFsPerAxisInPatch,normal,0) {
    tarch::la::Vector<Dimensions,int>    fineVolume                = kFine;
    tarch::la::Vector<Dimensions,int>    fineVolumeAlongCoarseFace = kFine;

    bool restrictThisVolume = true;
    for (int d=0; d<Dimensions; d++) {
      if (d!=normal) {
        fineVolumeAlongCoarseFace(d)+=marker.getRelativePositionWithinFatherCell()(d)*numberOfDoFsPerAxisInPatch;

        restrictThisVolume &= (fineVolumeAlongCoarseFace(d)%3)==1;
      }
    }

    if (restrictThisVolume) {
      tarch::la::Vector<Dimensions,int>    coarseVolume = fineVolumeAlongCoarseFace/3;

      assertion(overlap==1);
    //for (int iFine=0;   iFine<overlap;   iFine+=3) {
      const int iFine=0;
      fineVolume(normal)   = pickLeftHalfOfHaloOnFineGrid ? iFine : iFine + overlap;
      coarseVolume(normal) = pickLeftHalfOfHaloOnFineGrid ? iFine : iFine + overlap;

      int coarseVolumeLinearised = serialisePatchIndexInOverlap(
        coarseVolume,
        numberOfDoFsPerAxisInPatch, overlap, normal
        );
      int fineVolumeLinearised = serialisePatchIndexInOverlap(
        fineVolume,
        numberOfDoFsPerAxisInPatch, overlap, normal
        );
      for (int j=0; j<unknowns; j++) {
        assertion3(coarseGridValues[coarseVolumeLinearised*unknowns+j]==coarseGridValues[coarseVolumeLinearised*unknowns+j], coarseVolume, fineVolume, marker.toString());
        assertion3(fineGridValues[fineVolumeLinearised*unknowns+j]==fineGridValues[fineVolumeLinearised*unknowns+j],         coarseVolume, fineVolume, marker.toString());
        coarseGridValues[coarseVolumeLinearised*unknowns+j] = fineGridValues[fineVolumeLinearised*unknowns+j];
      }
    }
  }

  logTraceOut( "restrictOntoOuterHalfOfHaloLayer_AoS_restrict(...)" );
}


void toolbox::blockstructured::restrictHaloLayer_AoS_inject(
  const peano4::datamanagement::FaceMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       overlap,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues
) {
  restrictOntoOuterHalfOfHaloLayer_AoS_inject( marker, numberOfDoFsPerAxisInPatch, overlap, unknowns, fineGridValues, coarseGridValues, false );
  restrictOntoOuterHalfOfHaloLayer_AoS_inject( marker, numberOfDoFsPerAxisInPatch, overlap, unknowns, fineGridValues, coarseGridValues, true );
}


void toolbox::blockstructured::restrictCell_AoS_inject(
  const peano4::datamanagement::CellMarker& marker,
  int                                       numberOfDoFsPerAxisInPatch,
  int                                       unknowns,
  double*                                   fineGridValues,
  double*                                   coarseGridValues
) {
  dfor(fineVolume,numberOfDoFsPerAxisInPatch) {
    tarch::la::Vector<Dimensions,int>   fineVolumeWithintCoarsePatch = (fineVolume + marker.getRelativePositionWithinFatherCell() * numberOfDoFsPerAxisInPatch);
    tarch::la::Vector<Dimensions,int>   coarseVolume;

    bool restrictThisVolume = true;
    for (int d=0; d<Dimensions; d++) {
      restrictThisVolume &= (fineVolumeWithintCoarsePatch(d)%3)==1;
      coarseVolume(d) = fineVolumeWithintCoarsePatch(3)/3;
    }

    if (restrictThisVolume) {
      int coarseVolumeLinearised = peano4::utils::dLinearised( coarseVolume, numberOfDoFsPerAxisInPatch );
      int fineVolumeLinearised   = peano4::utils::dLinearised( fineVolume, numberOfDoFsPerAxisInPatch );
      for (int j=0; j<unknowns; j++) {
        assertion3(coarseGridValues[coarseVolumeLinearised*unknowns+j]==coarseGridValues[coarseVolumeLinearised*unknowns+j], coarseVolume, fineVolume, marker.toString());
        assertion3(fineGridValues[fineVolumeLinearised*unknowns+j]==fineGridValues[fineVolumeLinearised*unknowns+j],         coarseVolume, fineVolume, marker.toString());
        coarseGridValues[coarseVolumeLinearised*unknowns+j] = fineGridValues[fineVolumeLinearised*unknowns+j];
      }
    }
  }
}
