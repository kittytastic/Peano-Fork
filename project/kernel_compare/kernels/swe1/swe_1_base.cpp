#include "../../stdlibs.h"

#include "tarch/la/Vector.h"
#include "tarch/Assertions.h"
#include "tarch/logging/Log.h"
#include "tarch/la/la.h"

#include "exahype2/NonCriticalAssertions.h"
#include "swe_1_base.h"


void kernels::swe1::kernelLambda(tarch::la::Vector<2,double> patchCenter, tarch::la::Vector<2,double> patchSize, double t, double dt, double * Qin, double * Qout){
    const int Dimensions = 2; 
    kernels::swe1::applySplit1DRiemannToPatch_Overlap1AoS2d(
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
          
        kernels::swe1::splitRusanov1d(
          [] (
            const double * __restrict__                  Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double                                       F[]
          ) -> void {
            
            kernels::swe1::flux( Q, faceCentre, volumeH, t, normal, F );
            
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
            
            kernels::swe1::nonconservativeProduct( Q, deltaQ, faceCentre, volumeH, t, normal, BgradQ );
            
          },
          [] (
            const double * __restrict__                  Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal
          ) -> double {
            return kernels::swe1::maxEigenvalue( Q, faceCentre, volumeH, t, normal);
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
        patchCenter,
        patchSize,
        t,
        dt,
        3,
        3,
        1,
        Qin,
        Qout
    );
   
}

void kernels::swe1::applySplit1DRiemannToPatch_Overlap1AoS2d (
  std::function< void(
    const double *__restrict__                    QL,
    const double *__restrict__                    QR,
    const tarch::la::Vector<2, double>&           faceCentre,
    double volumeH, double t, double dt, int normal,
    double *__restrict__ FL, double *__restrict__ FR)
  > splitRiemannSolve1d,
  std::function< void(
    const double * __restrict__ Q,
    const tarch::la::Vector<2,double>&           volumeCentre,
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

  tarch::la::Vector<2, double> volumeH = getVolumeSize (
      patchSize, numberOfVolumesPerAxisInPatch);

  double * numericalFluxL = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);
  double * numericalFluxR = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);

  #ifdef SharedOMP
  //#pragma omp parallel for collapse(2)
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
      nonCriticalAssertion7(
        not std::isnan( Qout[voxelInImage * (unknowns + auxiliaryVariables) + unknown] ),
        unknown, x, y, patchCentre, patchSize, t, dt
      );
    }
  }

  for (int x = 0; x <= numberOfVolumesPerAxisInPatch; x++) {
    #ifdef SharedOMP
    //#pragma omp parallel for
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
          nonCriticalAssertion7(
            not std::isnan( Qout[leftVoxelInImage * (unknowns + auxiliaryVariables) + unknown] ),
            unknown, x, y, patchCentre, patchSize, t, dt
          );
        }
        if (x < numberOfVolumesPerAxisInPatch) {
          Qout[rightVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
              dt / volumeH (0) * numericalFluxR[unknown];
          nonCriticalAssertion7(
            not std::isnan( Qout[rightVoxelInImage * (unknowns + auxiliaryVariables) + unknown] ),
            unknown, x, y, patchCentre, patchSize, t, dt
          );
        }
      }
    }
    
  }

  for (int y = 0; y <= numberOfVolumesPerAxisInPatch; y++) {
    #ifdef SharedOMP
    //#pragma omp parallel for
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
          nonCriticalAssertion7(
            not std::isnan( Qout[lowerVoxelInImage * (unknowns + auxiliaryVariables) + unknown] ),
            unknown, x, y, patchCentre, patchSize, t, dt
          );
        }
        if (y < numberOfVolumesPerAxisInPatch) {
          Qout[upperVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
              dt / volumeH (0) * numericalFluxR[unknown];
          nonCriticalAssertion7(
            not std::isnan( Qout[upperVoxelInImage * (unknowns + auxiliaryVariables) + unknown] ),
            unknown, x, y, patchCentre, patchSize, t, dt
          );
        }
      }
    }
  }

  ::tarch::freeMemory(numericalFluxL, tarch::MemoryLocation::Heap);
  ::tarch::freeMemory(numericalFluxR, tarch::MemoryLocation::Heap);
  logTraceOut( "applySplit1DRiemannToPatch_Overlap1AoS2d(...)" );
}


void kernels::swe1::splitRusanov1d(
   std::function< void(
    const double * __restrict__ Q,
    const tarch::la::Vector<Dimensions,double>&  faceCentre,
    const tarch::la::Vector<Dimensions,double>&  volumeH,
    double                                       t,
    double                                       dt,
    int                                          normal,
    double * __restrict__ F
  ) >   flux,
  std::function< void(
    const double * __restrict__                  Q,
    const double * __restrict__                  deltaQ,
    const tarch::la::Vector<Dimensions,double>&  faceCentre,
    const tarch::la::Vector<Dimensions,double>&  volumeH,
    double                                       t,
    double                                       dt,
    int                                          normal,
    double * __restrict__ BgradQ
  ) >   nonconservativeProduct,
  std::function< double(
    const double * __restrict__ Q,
    const tarch::la::Vector<Dimensions,double>&  faceCentre,
    const tarch::la::Vector<Dimensions,double>&  volumeH,
    double                                       t,
    double                                       dt,
    int                                          normal
  ) >   maxEigenvalue,
  const double * __restrict__ QL,
  const double * __restrict__ QR,
  const tarch::la::Vector<Dimensions,double>&  x,
  double                                       dx,
  double                                       t,
  double                                       dt,
  int                                          normal,
  int                                          unknowns,
  int                                          auxiliaryVariables,
  double * __restrict__ FL,
  double * __restrict__ FR,
  bool skipFluxEvaluation,
  bool skipNCPEvaluation
) {
  assertion(normal>=0);
  assertion(normal<Dimensions);

  double * fluxFL;
  double * fluxFR;
  double * fluxNCP;

  double * Qaverage;
  double * deltaQ;

  if (not skipFluxEvaluation) {
    fluxFL   = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);
    fluxFR   = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);
    for (int i=0;i<unknowns;i++) fluxFL[i]=0;
    for (int i=0;i<unknowns;i++) fluxFR[i]=0;

    flux(QL,x,dx,t,dt,normal,fluxFL);
    flux(QR,x,dx,t,dt,normal,fluxFR);
  }

  if (not skipNCPEvaluation) {
    fluxNCP  = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);
    Qaverage = ::tarch::allocateMemory(unknowns+auxiliaryVariables, tarch::MemoryLocation::Heap);
    deltaQ   = ::tarch::allocateMemory(unknowns+auxiliaryVariables, tarch::MemoryLocation::Heap);

    for (int unknown=0; unknown<unknowns+auxiliaryVariables; unknown++) {
      Qaverage[unknown] = 0.5 * QL[unknown] + 0.5 * QR[unknown];
      deltaQ[unknown]   = QR[unknown] - QL[unknown];
    }
    nonconservativeProduct(Qaverage,deltaQ,x,dx,t,dt,normal,fluxNCP);
  }

  double lambdaMaxL = maxEigenvalue(QL,x,dx,t,dt,normal);
  double lambdaMaxR = maxEigenvalue(QR,x,dx,t,dt,normal);

  nonCriticalAssertion7( lambdaMaxL>=0.0, x, dx, t, dt, normal, lambdaMaxL, lambdaMaxR );
  nonCriticalAssertion7( lambdaMaxR>=0.0, x, dx, t, dt, normal, lambdaMaxL, lambdaMaxR );

  double lambdaMax  = std::max( lambdaMaxL, lambdaMaxR );

  for (int unknown=0; unknown<unknowns; unknown++) {
    FL[unknown] = - 0.5 * lambdaMax * (QR[unknown] - QL[unknown]);
    FR[unknown] = - 0.5 * lambdaMax * (QR[unknown] - QL[unknown]);
    if (not skipFluxEvaluation) {
      FL[unknown] += 0.5 * fluxFL[unknown] + 0.5 * fluxFR[unknown];
      FR[unknown] += 0.5 * fluxFL[unknown] + 0.5 * fluxFR[unknown];
    }
    if (not skipNCPEvaluation) {
      FL[unknown] += + 0.5 * fluxNCP[unknown];
      FR[unknown] += - 0.5 * fluxNCP[unknown];
      nonCriticalAssertion7( fluxNCP[unknown]==fluxNCP[unknown], x, dx, t, dt, normal, lambdaMaxL, lambdaMaxR );
    }
  }

  if (not skipFluxEvaluation) {
    ::tarch::freeMemory(fluxFL,   tarch::MemoryLocation::Heap);
    ::tarch::freeMemory(fluxFR,   tarch::MemoryLocation::Heap);
  }
  if (not skipNCPEvaluation) {
    ::tarch::freeMemory(fluxNCP,  tarch::MemoryLocation::Heap);
    ::tarch::freeMemory(Qaverage, tarch::MemoryLocation::Heap);
    ::tarch::freeMemory(deltaQ,   tarch::MemoryLocation::Heap);
  }
};

tarch::la::Vector<2,double>  kernels::swe1::getVolumeSize(
  const tarch::la::Vector<2,double>&  h,
  int                                 numberOfVolumesPerAxisInPatch
) {
  tarch::la::Vector<2,double> volumeSize;

  for (int d=0; d<2; d++) {
    assertion2( numberOfVolumesPerAxisInPatch>=1, h, numberOfVolumesPerAxisInPatch );
    volumeSize(d) = h(d)/numberOfVolumesPerAxisInPatch;
  }

  return volumeSize;
}


double kernels::swe1::maxEigenvalue(
  const double * __restrict__ Q, // Q[3+1],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal
)  {
  logTraceInWith4Arguments( "maxEigenvalue(...)", faceCentre, volumeH, t, normal );
  double result = 1.0;
	  double ih = 1/Q[0];
	  double g = 9.81;
	  double c = std::sqrt( g * (Q[0]+Q[3]) );
	  double u = 0.0;
	  
	  switch(normal){
	  case 0: //x
		  u = ih * Q[1];
		  result = std::max(u-c, u+c);
		  break;
	  case 1: //y
		  u = ih * Q[2];
		  result = std::max(u-c, u+c);
		  break;
	  }
	  
	  return result;
  logTraceOut( "maxEigenvalue(...)" );
}




void kernels::swe1::flux(
  const double * __restrict__ Q, // Q[3+1],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal,
  double * __restrict__ F // F[3]
)  {
  logTraceInWith4Arguments( "flux(...)", faceCentre, volumeH, t, normal );
  double ih = 1.0/Q[0];
	  
	  switch(normal){
	  case 0:
		  F[0] = Q[1];
		  F[1] = ih * Q[1] * Q[1];
		  F[2] = ih * Q[1] * Q[2];
		  break;
	  case 1:
		  F[0] = Q[2];
		  F[1] = ih * Q[2] * Q[1];
		  F[2] = ih * Q[2] * Q[2];
		  break;
	  }
  logTraceOut( "flux(...)" );
}




void kernels::swe1::nonconservativeProduct(
  const double * __restrict__ Q, // Q[3+1],
  const double * __restrict__             deltaQ, // [3+1]
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal,
  double * __restrict__ BgradQ // BgradQ[3]
)  {
  logTraceInWith4Arguments( "nonconservativeProduct(...)", faceCentre, volumeH, t, normal );
  double g = 9.81;
	  
	  switch(normal){
	  case 0: //x
		  BgradQ[0] = 0.0;
		  BgradQ[1] = g * Q[0] * (deltaQ[0] + deltaQ[3]);
		  BgradQ[2] = 0.0;
		  break;
	  case 1: //y
		  BgradQ[0] = 0.0;
		  BgradQ[1] = 0.0;
		  BgradQ[2] = g * Q[0] * (deltaQ[0] + deltaQ[3]);
		  break;
	  }
  logTraceOut( "nonconservativeProduct(...)" );
}
