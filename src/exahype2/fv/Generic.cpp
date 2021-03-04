#include "Generic.h"

#include "tarch/logging/Log.h"
#include "tarch/multicore/multicore.h"

#include "../PatchUtils.h"

#include "peano4/utils/Loop.h"

#include "exahype2/NonCriticalAssertions.h"

// This is a fantastic hack
#if defined(OpenMPGPUOffloading)
namespace std
{
#pragma omp declare target
void __throw_bad_function_call() {};
#pragma omp  end declare target
}
#endif

// This is another hack
#if defined(OpenMPGPUOffloading)
#pragma omp declare target
void abort() {};
#pragma omp  end declare target
#endif



std::string exahype2::fv::plotVolume(
  const double* __restrict__ Q,
  int    unknowns
) {
  std::string result = "(" + std::to_string(Q[0]);
  for (int i=1; i<unknowns; i++) result += "," + std::to_string(Q[i]);
  result += ")";
  return result;
}


void exahype2::fv::validatePatch (
  const double *__restrict__ Q, int unknowns,
  int auxiliaryVariables,
  int numberOfVolumesPerAxisInPatch, int haloSize,
  const std::string &location
) {
  #if PeanoDebug>1
  const int PatchSize = numberOfVolumesPerAxisInPatch+2*haloSize;
  dfor (k,PatchSize) {
    int index = peano4::utils::dLinearised(k,PatchSize) * (unknowns+auxiliaryVariables);

    // It is a diagonal entry if this counter is bigger than 1. If it equals
    // 0, it is interior. If it equals 1, then this is a face-connected halo
    // entry.
    int isDiagonal = tarch::la::count(k,0) + tarch::la::count(k,PatchSize-1);

    for (int i=0; i<unknowns+auxiliaryVariables; i++) {
      if (haloSize==0 or isDiagonal==0) {
        nonCriticalAssertion9(
          std::isfinite(Q[index+i]),
          unknowns,
          auxiliaryVariables,
          isDiagonal, haloSize,
          numberOfVolumesPerAxisInPatch, haloSize, k, i, location );

      }
    }
  }
  #endif
}


double exahype2::fv::maxEigenvalue_AoS(
  std::function< double(
    const double * __restrict__ Q,
    const tarch::la::Vector<Dimensions,double>&  faceCentre,
    const tarch::la::Vector<Dimensions,double>&  volumeH,
    double                                       t,
    double                                       dt,
    int                                          normal
  ) >   eigenvalues,
  const tarch::la::Vector<Dimensions,double>&           patchCentre,
  const tarch::la::Vector<Dimensions,double>&           patchSize,
  double                                       t,
  double                                       dt,
  int                                          numberOfVolumesPerAxisInPatch,
  int                                          unknowns,
  int                                          auxiliaryVariables,
  const double * __restrict__                  Q
) {
  double result = 0.0;

  tarch::la::Vector<Dimensions, double> volumeH = exahype2::getVolumeSize (
      patchSize, numberOfVolumesPerAxisInPatch);

  #if Dimensions==2
  #ifdef SharedOMP
  #pragma omp parallel for collapse(2) reduction(min:result)
  #endif
  for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++)
  for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++) {
    tarch::la::Vector<2, double> volumeX = patchCentre
        - 0.5 * patchSize;
    volumeX (0) += (x + 0.5) * volumeH (0);
    volumeX (1) += (y + 0.5) * volumeH (1);

    const int voxelInImage  = x
                            + y * numberOfVolumesPerAxisInPatch;

    for (int d=0; d<Dimensions; d++) {
      result = std::max(
        result,
        eigenvalues(
          Q + voxelInImage * (unknowns + auxiliaryVariables),
          volumeX, volumeH, t, dt, d
        )
      );
    }
  }
  #else
  #ifdef SharedOMP
  #pragma omp parallel for collapse(3) reduction(min:result)
  #endif
  for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++)
  for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++)
  for (int z = 0; z < numberOfVolumesPerAxisInPatch; z++) {
    tarch::la::Vector<3, double> volumeX = patchCentre
        - 0.5 * patchSize;
    volumeX (0) += (x + 0.5) * volumeH (0);
    volumeX (1) += (y + 0.5) * volumeH (1);
    volumeX (2) += (z + 0.5) * volumeH (2);

    const int voxelInImage  = x
                            + y * numberOfVolumesPerAxisInPatch
                            + z * numberOfVolumesPerAxisInPatch * numberOfVolumesPerAxisInPatch;

    for (int d=0; d<Dimensions; d++) {
      result = std::max(
        result,
        eigenvalues(
          Q + voxelInImage * (unknowns + auxiliaryVariables),
          volumeX, volumeH, t, dt, d
        )
      );
    }
  }
  #endif

  return result;
}



#if defined(OpenMPGPUOffloading)
#pragma omp declare target
#endif
void exahype2::fv::copyPatch (
  const double *__restrict__   QinWithHalo,
  double *__restrict__         QOutWithoutHalo,
  int unknowns,
  int auxiliaryVariables,
  int numberOfVolumesPerAxisInPatch,
  int haloSize
) {

  //dfor(k,numberOfVolumesPerAxisInPatch) {
  //tarch::la::Vector<Dimensions,int>   source = k + tarch::la::Vector<Dimensions,int>(haloSize);
  //int sourceSerialised      = peano4::utils::dLinearised(source,numberOfVolumesPerAxisInPatch+haloSize*2);
  //int destinationSerialised = peano4::utils::dLinearised(k,numberOfVolumesPerAxisInPatch);
  //for (int i=0; i<unknowns+auxiliaryVariables; i++) {
  //QOutWithoutHalo[destinationSerialised*(unknowns+auxiliaryVariables)+i] = QinWithHalo[sourceSerialised*(unknowns+auxiliaryVariables)+i];
  //}
  //}

#if Dimensions==2
  #ifdef SharedOMP
     #if defined(OpenMPGPUOffloading)
     #pragma omp target
     #endif
  #pragma omp parallel for collapse(3)
  #endif
  for (int y=0; y<numberOfVolumesPerAxisInPatch; y++)
  {
    for (int x=0; x<numberOfVolumesPerAxisInPatch; x++)
    {
      for (int i=0; i<unknowns+auxiliaryVariables; i++)
      {
        int sourceIndex      = (y+1)*(numberOfVolumesPerAxisInPatch+ 3*haloSize) + x - y;
        int destinationIndex = y*numberOfVolumesPerAxisInPatch + x;
        QOutWithoutHalo[destinationIndex*(unknowns+auxiliaryVariables)+i] = QinWithHalo[sourceIndex*(unknowns+auxiliaryVariables)+i];
      }
    }
  }
#else
  int sourceSerialised = (numberOfVolumesPerAxisInPatch + haloSize * 2)
      * (numberOfVolumesPerAxisInPatch + haloSize * 2)
      + numberOfVolumesPerAxisInPatch + haloSize * 2 + haloSize;



  int helper = numberOfVolumesPerAxisInPatch+haloSize*2;
  #ifdef SharedOMP
     #if defined(OpenMPGPUOffloading)
     #pragma omp target
     #endif
  #pragma omp parallel for collapse(4)
  #endif
  for (int z = 0; z < numberOfVolumesPerAxisInPatch; z++)
  {
    for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++)
    {
      for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++)
      {
        for (int i = 0; i < unknowns + auxiliaryVariables; i++)
        {
           int mydest = z*numberOfVolumesPerAxisInPatch*numberOfVolumesPerAxisInPatch + y*numberOfVolumesPerAxisInPatch + x;
           int mysrc  = z*helper*helper + y*helper + x + sourceSerialised;

           QOutWithoutHalo[mydest * (unknowns + auxiliaryVariables) + i] = QinWithHalo[mysrc * (unknowns + auxiliaryVariables) + i];
        }
      }
    }
  }
#endif
}
#if defined(OpenMPGPUOffloading)
#pragma omp end declare target
#endif


void exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS2d (
  std::function< void(
    const double *__restrict__                    QL,
    const double *__restrict__                    QR,
    const tarch::la::Vector<2, double>&           faceCentre,
    double volumeH, double t, double dt, int normal,
    double *__restrict__ FL, double *__restrict__ FR)
  > splitRiemannSolve1d,
  std::function< void(
    const double * __restrict__ Q,
    const tarch::la::Vector<2,double>&           volueCentre,
    double                                       volumeH,
    double                                       t,
    double                                       dt,
    double * __restrict__ S
  ) >   sourceTerm,
  const tarch::la::Vector<2, double>&  patchCentre,
  const tarch::la::Vector<2, double>&  patchSize,
  double t, double dt,
  int numberOfVolumesPerAxisInPatch, int unknowns, int auxiliaryVariables,
  const double *__restrict__ Qin, double *__restrict__ Qout
) {
  static tarch::logging::Log _log ("exahype2::fv");
  logTraceInWith6Arguments( "applySplit1DRiemannToPatch_Overlap1AoS2d(...)", patchCentre, patchSize, t, dt, numberOfVolumesPerAxisInPatch, unknowns );
  assertion4( dt>=0.0, patchCentre, patchSize, t, dt  );

  tarch::la::Vector<2, double> volumeH = exahype2::getVolumeSize (
      patchSize, numberOfVolumesPerAxisInPatch);

  double * numericalFluxL = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);
  double * numericalFluxR = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);

  #ifdef SharedOMP
  #pragma omp parallel for collapse(2)
  #endif
  for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++)
  for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++) {
    tarch::la::Vector<2, double> volumeX = patchCentre
        - 0.5 * patchSize;
    volumeX (0) += (x + 0.5) * volumeH (0);
    volumeX (1) += (y + 0.5) * volumeH (1);

    const int voxelInPreImage  = x+1
                               + (y+1) * (numberOfVolumesPerAxisInPatch+2);
    const int voxelInImage     = x
                               + y * numberOfVolumesPerAxisInPatch;

    sourceTerm(
      Qin + voxelInPreImage * (unknowns + auxiliaryVariables),
      volumeX, volumeH(0), t, dt,
      numericalFluxL
    );

    for (int unknown = 0; unknown < unknowns; unknown++) {
      Qout[voxelInImage * (unknowns + auxiliaryVariables) + unknown] += dt * numericalFluxL[unknown];
    }
  }

  for (int x = 0; x <= numberOfVolumesPerAxisInPatch; x++) {
    #ifdef SharedOMP
    #pragma omp parallel for
    #endif
    for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++) {
      const int leftVoxelInPreimage = x
          + (y + 1) * (2 + numberOfVolumesPerAxisInPatch);
      const int rightVoxelInPreimage = x + 1
          + (y + 1) * (2 + numberOfVolumesPerAxisInPatch);

      const int leftVoxelInImage = x - 1 + y * numberOfVolumesPerAxisInPatch;
      const int rightVoxelInImage = x + y * numberOfVolumesPerAxisInPatch;

      tarch::la::Vector<2, double> volumeX = patchCentre
          - 0.5 * patchSize;
      volumeX (0) += x * volumeH (0);
      volumeX (1) += (y + 0.5) * volumeH (1);

      splitRiemannSolve1d (
          Qin + leftVoxelInPreimage * (unknowns + auxiliaryVariables),
          Qin + rightVoxelInPreimage * (unknowns + auxiliaryVariables), volumeX,
          volumeH (0), t, dt, 0, //  last argument = normal
          numericalFluxL, numericalFluxR);

      for (int unknown = 0; unknown < unknowns; unknown++) {
        if (x > 0) {
          Qout[leftVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
              dt / volumeH (0) * numericalFluxL[unknown];
        }
        if (x < numberOfVolumesPerAxisInPatch) {
          Qout[rightVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
              dt / volumeH (0) * numericalFluxR[unknown];
        }
      }
    }
  }

  for (int y = 0; y <= numberOfVolumesPerAxisInPatch; y++) {
    #ifdef SharedOMP
    #pragma omp parallel for
    #endif
    for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++) {
      const int lowerVoxelInPreimage = x + 1
          + y * (2 + numberOfVolumesPerAxisInPatch);
      const int upperVoxelInPreimage = x + 1
          + (y + 1) * (2 + numberOfVolumesPerAxisInPatch);

      const int lowerVoxelInImage = x + (y - 1) * numberOfVolumesPerAxisInPatch;
      const int upperVoxelInImage = x + y * numberOfVolumesPerAxisInPatch;

      tarch::la::Vector<2, double> volumeX = patchCentre
          - 0.5 * patchSize;
      volumeX (0) += (x + 0.5) * volumeH (0);
      volumeX (1) += y * volumeH (1);

      splitRiemannSolve1d (
          Qin + lowerVoxelInPreimage * (unknowns + auxiliaryVariables),
          Qin + upperVoxelInPreimage * (unknowns + auxiliaryVariables), volumeX,
          volumeH (0), t, dt, 1, //  last argument = normal
          numericalFluxL, numericalFluxR);

      for (int unknown = 0; unknown < unknowns; unknown++) {
        if (y > 0) {
          Qout[lowerVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
              dt / volumeH (0) * numericalFluxL[unknown];
        }
        if (y < numberOfVolumesPerAxisInPatch) {
          Qout[upperVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
              dt / volumeH (0) * numericalFluxR[unknown];
        }
      }
    }
  }

  ::tarch::freeMemory(numericalFluxL, tarch::MemoryLocation::Heap);
  ::tarch::freeMemory(numericalFluxR, tarch::MemoryLocation::Heap);
  logTraceOut( "applySplit1DRiemannToPatch_Overlap1AoS2d(...)" );
}


void exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS3d (
  std::function<void(
    const double *__restrict__ QL,
    const double *__restrict__ QR,
         const tarch::la::Vector<3, double> &faceCentre,
         double volumeH, double t, double dt, int normal,
  double *__restrict__ FL, double *__restrict__ FR)> splitRiemannSolve1d,
  std::function< void(
    const double * __restrict__ Q,
    const tarch::la::Vector<3,double>&  volueCentre,
    double                                       volumeH,
    double                                       t,
    double                                       dt,
    double * __restrict__ S
  ) >   sourceTerm,
  const tarch::la::Vector<3, double>&   patchCentre,
  const tarch::la::Vector<3, double>&   patchSize,
  double t, double dt,
  int numberOfVolumesPerAxisInPatch, int unknowns, int auxiliaryVariables,
  const double *__restrict__ Qin,
  double *__restrict__       Qout
) {
  static tarch::logging::Log _log ("exahype2::fv");
  logTraceInWith6Arguments( "applySplit1DRiemannToPatch_Overlap1AoS3d(...)", patchCentre, patchSize, t, dt, numberOfVolumesPerAxisInPatch, unknowns );

  assertion( dt>=0.0 );

  tarch::la::Vector<3, double> volumeH = exahype2::getVolumeSize (
      patchSize, numberOfVolumesPerAxisInPatch);

  double numericalFluxL[unknowns]; // helper out variable
  double numericalFluxR[unknowns]; // helper out variable

  #ifdef SharedOMP
  #pragma omp parallel for collapse(3)
  #endif
  for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++)
  for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++)
  for (int z = 0; z < numberOfVolumesPerAxisInPatch; z++) {
    tarch::la::Vector<3, double> volumeX = patchCentre
        - 0.5 * patchSize;
    volumeX (0) += (x + 0.5) * volumeH (0);
    volumeX (1) += (y + 0.5) * volumeH (1);
    volumeX (2) += (z + 0.5) * volumeH (2);

    const int voxelInPreImage  = x+1
                               + (y+1) * (numberOfVolumesPerAxisInPatch+2)
                               + (z+1) * (numberOfVolumesPerAxisInPatch+2) * (numberOfVolumesPerAxisInPatch+2);
    const int voxelInImage     = x
                               + y * numberOfVolumesPerAxisInPatch
                               + z * numberOfVolumesPerAxisInPatch * numberOfVolumesPerAxisInPatch;

    sourceTerm(
      Qin + voxelInPreImage * (unknowns + auxiliaryVariables),
      volumeX, volumeH(0), t, dt,
      numericalFluxL
    );

    for (int unknown = 0; unknown < unknowns; unknown++) {
      Qout[voxelInImage * (unknowns + auxiliaryVariables) + unknown] += dt * numericalFluxL[unknown];
    }
  }

  for (int x = 0; x <= numberOfVolumesPerAxisInPatch; x++) {
    #ifdef SharedOMP
    #pragma omp parallel for collapse(2)
    #endif
    for (int z = 0; z < numberOfVolumesPerAxisInPatch; z++)
    for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++) {
      const int leftVoxelInPreimage = x
            + (y + 1) * (2 + numberOfVolumesPerAxisInPatch)
            + (z + 1) * (2 + numberOfVolumesPerAxisInPatch)
                * (2 + numberOfVolumesPerAxisInPatch);
      const int rightVoxelInPreimage = x + 1
            + (y + 1) * (2 + numberOfVolumesPerAxisInPatch)
            + (z + 1) * (2 + numberOfVolumesPerAxisInPatch)
                * (2 + numberOfVolumesPerAxisInPatch);

      const int leftVoxelInImage = x - 1 + y * numberOfVolumesPerAxisInPatch
            + z * numberOfVolumesPerAxisInPatch * numberOfVolumesPerAxisInPatch;
      const int rightVoxelInImage = x + y * numberOfVolumesPerAxisInPatch
            + z * numberOfVolumesPerAxisInPatch * numberOfVolumesPerAxisInPatch;

      tarch::la::Vector<3, double> volumeX = patchCentre
            - 0.5 * patchSize;
        volumeX (0) += x * volumeH (0);
        volumeX (1) += (y + 0.5) * volumeH (1);
        volumeX (2) += (z + 0.5) * volumeH (2);

      splitRiemannSolve1d (
            Qin + leftVoxelInPreimage * (unknowns + auxiliaryVariables),
            Qin + rightVoxelInPreimage * (unknowns + auxiliaryVariables),
            volumeX, volumeH (0), t, dt, 0, //  last argument = normal
            numericalFluxL, numericalFluxR);

      for (int unknown = 0; unknown < unknowns; unknown++) {
        if (x > 0) {
          Qout[leftVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
              dt / volumeH (0) * numericalFluxL[unknown];
        }
        if (x < numberOfVolumesPerAxisInPatch) {
          Qout[rightVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
              dt / volumeH (0) * numericalFluxR[unknown];
        }
      }
    }
  }

  for (int y = 0; y <= numberOfVolumesPerAxisInPatch; y++) {
    #ifdef SharedOMP
    #pragma omp parallel for collapse(2)
    #endif
    for (int z = 0; z < numberOfVolumesPerAxisInPatch; z++)
      for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++) {
        const int lowerVoxelInPreimage = x + 1
            + y * (2 + numberOfVolumesPerAxisInPatch)
            + (z + 1) * (2 + numberOfVolumesPerAxisInPatch)
                * (2 + numberOfVolumesPerAxisInPatch);
        const int upperVoxelInPreimage = x + 1
            + (y + 1) * (2 + numberOfVolumesPerAxisInPatch)
            + (z + 1) * (2 + numberOfVolumesPerAxisInPatch)
                * (2 + numberOfVolumesPerAxisInPatch);

        const int lowerVoxelInImage = x
            + (y - 1) * numberOfVolumesPerAxisInPatch
            + z * numberOfVolumesPerAxisInPatch * numberOfVolumesPerAxisInPatch;
        const int upperVoxelInImage = x + y * numberOfVolumesPerAxisInPatch
            + z * numberOfVolumesPerAxisInPatch * numberOfVolumesPerAxisInPatch;

        tarch::la::Vector<3, double> volumeX = patchCentre
            - 0.5 * patchSize;
        volumeX (0) += (x + 0.5) * volumeH (0);
        volumeX (1) += y * volumeH (1);
        volumeX (2) += (z + 0.5) * volumeH (2);

        splitRiemannSolve1d (
            Qin + lowerVoxelInPreimage * (unknowns + auxiliaryVariables),
            Qin + upperVoxelInPreimage * (unknowns + auxiliaryVariables),
            volumeX, volumeH (0), t, dt, 1, //  last argument = normal
            numericalFluxL, numericalFluxR);

        for (int unknown = 0; unknown < unknowns; unknown++) {
          if (y > 0) {
            Qout[lowerVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
                dt / volumeH (0) * numericalFluxL[unknown];
          }
          if (y < numberOfVolumesPerAxisInPatch) {
            Qout[upperVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
                dt / volumeH (0) * numericalFluxR[unknown];
          }
        }
      }
  }

  for (int z = 0; z <= numberOfVolumesPerAxisInPatch; z++) {
    #ifdef SharedOMP
    #pragma omp parallel for collapse(2)
    #endif
    for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++)
      for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++) {
        const int lowerVoxelInPreimage = x + 1
            + (y + 1) * (2 + numberOfVolumesPerAxisInPatch)
            + z * (2 + numberOfVolumesPerAxisInPatch)
                * (2 + numberOfVolumesPerAxisInPatch);
        const int upperVoxelInPreimage = x + 1
            + (y + 1) * (2 + numberOfVolumesPerAxisInPatch)
            + (z + 1) * (2 + numberOfVolumesPerAxisInPatch)
                * (2 + numberOfVolumesPerAxisInPatch);

        const int lowerVoxelInImage = x + y * numberOfVolumesPerAxisInPatch
            + (z - 1) * numberOfVolumesPerAxisInPatch
                * numberOfVolumesPerAxisInPatch;
        const int upperVoxelInImage = x + y * numberOfVolumesPerAxisInPatch
            + z * numberOfVolumesPerAxisInPatch * numberOfVolumesPerAxisInPatch;

        tarch::la::Vector<3, double> volumeX = patchCentre
            - 0.5 * patchSize;
        volumeX (0) += (x + 0.5) * volumeH (0);
        volumeX (1) += (y + 0.5) * volumeH (1);
        volumeX (2) += z * volumeH (2);

        splitRiemannSolve1d (
            Qin + lowerVoxelInPreimage * (unknowns + auxiliaryVariables),
            Qin + upperVoxelInPreimage * (unknowns + auxiliaryVariables),
            volumeX, volumeH (0), t, dt, 2, //  last argument = normal
            numericalFluxL, numericalFluxR);

        for (int unknown = 0; unknown < unknowns; unknown++) {
          if (z > 0) {
            Qout[lowerVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
                dt / volumeH (0) * numericalFluxL[unknown];
          }
          if (z < numberOfVolumesPerAxisInPatch) {
            Qout[upperVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
                dt / volumeH (0) * numericalFluxR[unknown];
          }
        }
      }
  }

  logTraceOut( "applySplit1DRiemannToPatch_Overlap1AoS3d(...)" );
}


void exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS2d_SplitLoop (
  std::function< void(
    const double *__restrict__ QL,
    const double *__restrict__ QR,
         const tarch::la::Vector<2, double> &faceCentre,
         double volumeH, double t, double dt, int normal,
  double *__restrict__ FL, double *__restrict__ FR)> splitRiemannSolve1d,
  std::function< void(
    const double * __restrict__ Q,
    const tarch::la::Vector<2,double>&  volueCentre,
    double                                       volumeH,
    double                                       t,
    double                                       dt,
    double * __restrict__ S
  ) >   sourceTerm,
  const tarch::la::Vector<2, double>&   patchCentre,
  const tarch::la::Vector<2, double>&   patchSize,
  double t, double dt,
  int numberOfVolumesPerAxisInPatch, int unknowns, int auxiliaryVariables,
  const double *__restrict__  Qin,
  double *__restrict__        Qout
) {
  static tarch::logging::Log _log ("exahype2::fv");
  logTraceInWith6Arguments( "applySplit1DRiemannToPatch_Overlap1AoS2d(...)", patchCentre, patchSize, t, dt, numberOfVolumesPerAxisInPatch, unknowns );

  tarch::la::Vector<2, double> volumeH = exahype2::getVolumeSize (
      patchSize, numberOfVolumesPerAxisInPatch);

  double * numericalFluxL = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);
  double * numericalFluxR = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);

  for (int shift = 0; shift < 2; shift++) {
#ifdef SharedOMP
#pragma omp parallel for collapse(2)
#endif
    for (int x = shift; x <= numberOfVolumesPerAxisInPatch; x += 2)
      for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++) {
        const int leftVoxelInPreimage = x
            + (y + 1) * (2 + numberOfVolumesPerAxisInPatch);
        const int rightVoxelInPreimage = x + 1
            + (y + 1) * (2 + numberOfVolumesPerAxisInPatch);

        const int leftVoxelInImage = x - 1 + y * numberOfVolumesPerAxisInPatch;
        const int rightVoxelInImage = x + y * numberOfVolumesPerAxisInPatch;

        tarch::la::Vector<2, double> volumeX = patchCentre
            - 0.5 * patchSize;
        volumeX (0) += x * volumeH (0);
        volumeX (1) += (y + 0.5) * volumeH (1);

        splitRiemannSolve1d (
            Qin + leftVoxelInPreimage * (unknowns + auxiliaryVariables),
            Qin + rightVoxelInPreimage * (unknowns + auxiliaryVariables),
            volumeX, volumeH (0), t, dt, 0, //  last argument = normal
            numericalFluxL, numericalFluxR);

        for (int unknown = 0; unknown < unknowns; unknown++) {
          if (x > 0) {
            Qout[leftVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
                dt / volumeH (0) * numericalFluxL[unknown];
          }
          if (x < numberOfVolumesPerAxisInPatch) {
            Qout[rightVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
                dt / volumeH (0) * numericalFluxR[unknown];
          }
        }
      }
  }

  for (int shift = 0; shift < 2; shift++) {
#ifdef SharedOMP
#pragma omp parallel for collapse(2)
#endif
    for (int y = shift; y <= numberOfVolumesPerAxisInPatch; y += 2)
      for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++) {
        const int lowerVoxelInPreimage = x + 1
            + y * (2 + numberOfVolumesPerAxisInPatch);
        const int upperVoxelInPreimage = x + 1
            + (y + 1) * (2 + numberOfVolumesPerAxisInPatch);

        const int lowerVoxelInImage = x
            + (y - 1) * numberOfVolumesPerAxisInPatch;
        const int upperVoxelInImage = x + y * numberOfVolumesPerAxisInPatch;

        tarch::la::Vector<2, double> volumeX = patchCentre
            - 0.5 * patchSize;
        volumeX (0) += (x + 0.5) * volumeH (0);
        volumeX (1) += y * volumeH (1);

        splitRiemannSolve1d (
            Qin + lowerVoxelInPreimage * (unknowns + auxiliaryVariables),
            Qin + upperVoxelInPreimage * (unknowns + auxiliaryVariables),
            volumeX, volumeH (0), t, dt, 1, //  last argument = normal
            numericalFluxL, numericalFluxR);

        for (int unknown = 0; unknown < unknowns; unknown++) {
          if (y > 0) {
            Qout[lowerVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
                dt / volumeH (0) * numericalFluxL[unknown];
          }
          if (y < numberOfVolumesPerAxisInPatch) {
            Qout[upperVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
                dt / volumeH (0) * numericalFluxR[unknown];
          }
        }
      }
  }

  ::tarch::freeMemory(numericalFluxL, tarch::MemoryLocation::Heap);
  ::tarch::freeMemory(numericalFluxR, tarch::MemoryLocation::Heap);
  logTraceOut( "applySplit1DRiemannToPatch_Overlap1AoS2d(...)" );
}


void exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS3d_SplitLoop (
    std::function<void(
      const double *__restrict__ QL,
      const double *__restrict__ QR,
      const tarch::la::Vector<3, double> &faceCentre,
      double volumeH, double t, double dt, int normal,
      double *__restrict__ FL, double *__restrict__ FR)> splitRiemannSolve1d,
      std::function< void(
        const double * __restrict__ Q,
        const tarch::la::Vector<3,double>&           volueCentre,
        double                                       volumeH,
        double                                       t,
        double                                       dt,
        double * __restrict__ S
      ) >   sourceTerm,
    const tarch::la::Vector<3, double>&   patchCentre,
    const tarch::la::Vector<3, double>&   patchSize,
    double t, double dt,
    int numberOfVolumesPerAxisInPatch, int unknowns, int auxiliaryVariables,
    const double *__restrict__   Qin,
    double *__restrict__         Qout
) {
  static tarch::logging::Log _log ("exahype2::fv");
  logTraceInWith6Arguments( "applySplit1DRiemannToPatch_Overlap1AoS3d(...)", patchCentre, patchSize, t, dt, numberOfVolumesPerAxisInPatch, unknowns );

  tarch::la::Vector<3, double> volumeH = exahype2::getVolumeSize (
      patchSize, numberOfVolumesPerAxisInPatch);

  double numericalFluxL[unknowns]; // helper out variable
  double numericalFluxR[unknowns]; // helper out variable

  for (int shift = 0; shift < 2; shift++) {
#ifdef SharedOMP
#pragma omp parallel for collapse(3)
#endif
    for (int x = shift; x <= numberOfVolumesPerAxisInPatch; x += 2)
      for (int z = 0; z < numberOfVolumesPerAxisInPatch; z++)
        for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++) {
          const int leftVoxelInPreimage = x
              + (y + 1) * (2 + numberOfVolumesPerAxisInPatch)
              + (z + 1) * (2 + numberOfVolumesPerAxisInPatch)
                  * (2 + numberOfVolumesPerAxisInPatch);
          const int rightVoxelInPreimage = x + 1
              + (y + 1) * (2 + numberOfVolumesPerAxisInPatch)
              + (z + 1) * (2 + numberOfVolumesPerAxisInPatch)
                  * (2 + numberOfVolumesPerAxisInPatch);

          const int leftVoxelInImage = x - 1 + y * numberOfVolumesPerAxisInPatch
              + z * numberOfVolumesPerAxisInPatch
                  * numberOfVolumesPerAxisInPatch;
          const int rightVoxelInImage = x + y * numberOfVolumesPerAxisInPatch
              + z * numberOfVolumesPerAxisInPatch
                  * numberOfVolumesPerAxisInPatch;

          tarch::la::Vector<3, double> volumeX = patchCentre
              - 0.5 * patchSize;
          volumeX (0) += x * volumeH (0);
          volumeX (1) += (y + 0.5) * volumeH (1);
          volumeX (2) += (z + 0.5) * volumeH (2);

          splitRiemannSolve1d (
              Qin + leftVoxelInPreimage * (unknowns + auxiliaryVariables),
              Qin + rightVoxelInPreimage * (unknowns + auxiliaryVariables),
              volumeX, volumeH (0), t, dt, 0, //  last argument = normal
              numericalFluxL, numericalFluxR);

          for (int unknown = 0; unknown < unknowns; unknown++) {
            if (x > 0) {
              Qout[leftVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
                  dt / volumeH (0) * numericalFluxL[unknown];
            }
            if (x < numberOfVolumesPerAxisInPatch) {
              Qout[rightVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
                  dt / volumeH (0) * numericalFluxR[unknown];
            }
          }
        }
  }

  for (int shift = 0; shift < 2; shift++) {
#ifdef SharedOMP
#pragma omp parallel for collapse(3)
#endif
    for (int y = shift; y <= numberOfVolumesPerAxisInPatch; y += 2)
      for (int z = 0; z < numberOfVolumesPerAxisInPatch; z++)
        for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++) {
          const int lowerVoxelInPreimage = x + 1
              + y * (2 + numberOfVolumesPerAxisInPatch)
              + (z + 1) * (2 + numberOfVolumesPerAxisInPatch)
                  * (2 + numberOfVolumesPerAxisInPatch);
          const int upperVoxelInPreimage = x + 1
              + (y + 1) * (2 + numberOfVolumesPerAxisInPatch)
              + (z + 1) * (2 + numberOfVolumesPerAxisInPatch)
                  * (2 + numberOfVolumesPerAxisInPatch);

          const int lowerVoxelInImage = x
              + (y - 1) * numberOfVolumesPerAxisInPatch
              + z * numberOfVolumesPerAxisInPatch
                  * numberOfVolumesPerAxisInPatch;
          const int upperVoxelInImage = x + y * numberOfVolumesPerAxisInPatch
              + z * numberOfVolumesPerAxisInPatch
                  * numberOfVolumesPerAxisInPatch;

          tarch::la::Vector<3, double> volumeX = patchCentre
              - 0.5 * patchSize;
          volumeX (0) += (x + 0.5) * volumeH (0);
          volumeX (1) += y * volumeH (1);
          volumeX (2) += (z + 0.5) * volumeH (2);

          splitRiemannSolve1d (
              Qin + lowerVoxelInPreimage * (unknowns + auxiliaryVariables),
              Qin + upperVoxelInPreimage * (unknowns + auxiliaryVariables),
              volumeX, volumeH (0), t, dt, 1, //  last argument = normal
              numericalFluxL, numericalFluxR);

          for (int unknown = 0; unknown < unknowns; unknown++) {
            if (y > 0) {
              Qout[lowerVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
                  dt / volumeH (0) * numericalFluxL[unknown];
            }
            if (y < numberOfVolumesPerAxisInPatch) {
              Qout[upperVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
                  dt / volumeH (0) * numericalFluxR[unknown];
            }
          }
        }
  }

  for (int shift = 0; shift < 2; shift++) {
#ifdef SharedOMP
#pragma omp parallel for collapse(3)
#endif
    for (int z = shift; z <= numberOfVolumesPerAxisInPatch; z += 2)
      for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++)
        for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++) {
          const int lowerVoxelInPreimage = x + 1
              + (y + 1) * (2 + numberOfVolumesPerAxisInPatch)
              + z * (2 + numberOfVolumesPerAxisInPatch)
                  * (2 + numberOfVolumesPerAxisInPatch);
          const int upperVoxelInPreimage = x + 1
              + (y + 1) * (2 + numberOfVolumesPerAxisInPatch)
              + (z + 1) * (2 + numberOfVolumesPerAxisInPatch)
                  * (2 + numberOfVolumesPerAxisInPatch);

          const int lowerVoxelInImage = x + y * numberOfVolumesPerAxisInPatch
              + (z - 1) * numberOfVolumesPerAxisInPatch
                  * numberOfVolumesPerAxisInPatch;
          const int upperVoxelInImage = x + y * numberOfVolumesPerAxisInPatch
              + z * numberOfVolumesPerAxisInPatch
                  * numberOfVolumesPerAxisInPatch;

          tarch::la::Vector<3, double> volumeX = patchCentre
              - 0.5 * patchSize;
          volumeX (0) += (x + 0.5) * volumeH (0);
          volumeX (1) += (y + 0.5) * volumeH (1);
          volumeX (2) += z * volumeH (2);

          splitRiemannSolve1d (
              Qin + lowerVoxelInPreimage * (unknowns + auxiliaryVariables),
              Qin + upperVoxelInPreimage * (unknowns + auxiliaryVariables),
              volumeX, volumeH (0), t, dt, 2, //  last argument = normal
              numericalFluxL, numericalFluxR);

          for (int unknown = 0; unknown < unknowns; unknown++) {
            if (z > 0) {
              Qout[lowerVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
                  dt / volumeH (0) * numericalFluxL[unknown];
            }
            if (z < numberOfVolumesPerAxisInPatch) {
              Qout[upperVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
                  dt / volumeH (0) * numericalFluxR[unknown];
            }
          }
        }
  }

  logTraceOut( "applySplit1DRiemannToPatch_Overlap1AoS3d(...)" );
}

