#include "MockKernel.h"

#include "tarch/Assertions.h"
#include "tarch/logging/Log.h"

#include "exahype2/NonCriticalAssertions.h"
#include <iostream>

void exahype2::fv::ck::compliedKernel (
  const tarch::la::Vector<2, double>&  patchCentre,
  const tarch::la::Vector<2, double>&  patchSize,
  double t, double dt,
  const double *__restrict__ Qin, // length = (vol in preimage) * (num vars) -- preimage = patch with ghost values
  double *__restrict__ Qout       // length = (vol in patch)    * (num vars)
) {

    // Known from compile
    const int numberOfVolumesPerAxisInPatch = 3;
    const int unknowns=4;
    const int auxiliaryVariables=0;

    
    static tarch::logging::Log _log ("exahype2::fv");
    logTraceInWith6Arguments( "applySplit1DRiemannToPatch_Overlap1AoS2d(...)", patchCentre, patchSize, t, dt, numberOfVolumesPerAxisInPatch, unknowns );
    assertion4( dt>=0.0, patchCentre, patchSize, t, dt  ); 

    tarch::la::Vector<2, double> volumeH = exahype2::fv::ck::getVolumeSize(
      patchSize, numberOfVolumesPerAxisInPatch); // Calc h for h/w

    double * numericalFluxL = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);
    double * numericalFluxR = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);

    // --------------- Source -------------------
    for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++)
    for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++) {
        tarch::la::Vector<2, double> volumeX = patchCentre - 0.5 * patchSize; // Patch origin
        volumeX (0) += (x + 0.5) * volumeH (0); // Center volume (x,y)
        volumeX (1) += (y + 0.5) * volumeH (1); // Center volume (x,y)

        const int voxelInPreImage  = voxelPosInPreimage(x,y, numberOfVolumesPerAxisInPatch);
        const int voxelInImage     = voxelPosInImage(x, y, numberOfVolumesPerAxisInPatch);

        sourceTerm(
        Qin + voxelInPreImage * (unknowns + auxiliaryVariables), // Mem position of start of state array
        volumeX, // Center of volume
        volumeH(0), // h_x = h_y 
        t, dt,
        numericalFluxL // OUT
        );

        for (int unknown = 0; unknown < unknowns; unknown++) {
        Qout[voxelInImage * (unknowns + auxiliaryVariables) + unknown] += dt * numericalFluxL[unknown];
        }
    }

    // ------------- Flux 1 ---------------------
    // Left - Right
    for (int x = 0; x <= numberOfVolumesPerAxisInPatch; x++) {
        for (int y = 0; y < numberOfVolumesPerAxisInPatch; y++) {
            const int leftVoxelInPreimage  = voxelPosInPreimage(x-1,y,numberOfVolumesPerAxisInPatch); 
            const int rightVoxelInPreimage = voxelPosInPreimage(x,y,numberOfVolumesPerAxisInPatch);

            const int leftVoxelInImage  = voxelPosInImage(x-1, y, numberOfVolumesPerAxisInPatch);
            const int rightVoxelInImage = voxelPosInImage(x, y, numberOfVolumesPerAxisInPatch);

            tarch::la::Vector<2, double> volumeX = patchCentre - 0.5 * patchSize; // Patch origin
            volumeX (0) += x * volumeH (0); // Face between left and right volumes 
            volumeX (1) += (y + 0.5) * volumeH (1);
            
            splitRusanov1d(
                Qin + leftVoxelInPreimage * (unknowns + auxiliaryVariables),
                Qin + rightVoxelInPreimage * (unknowns + auxiliaryVariables),
                volumeX,
                volumeH (0),
                t, 
                0, //  normal
                numericalFluxL, numericalFluxR);

            for (int unknown = 0; unknown < unknowns; unknown++) {
                if (x > 0) { // Left volume is in image
                Qout[leftVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
                    dt / volumeH (0) * numericalFluxL[unknown];
                }
                if (x < numberOfVolumesPerAxisInPatch) { // Right volume is in image
                Qout[rightVoxelInImage * (unknowns + auxiliaryVariables) + unknown] +=
                    dt / volumeH (0) * numericalFluxR[unknown];
                }
            }
        }
    }

    // ------------------- Flux 2 -------------------
    // Upper
    //   |
    // Lower
    for (int y = 0; y <= numberOfVolumesPerAxisInPatch; y++) {
        for (int x = 0; x < numberOfVolumesPerAxisInPatch; x++) {
            const int lowerVoxelInPreimage = voxelPosInPreimage(x,y-1,numberOfVolumesPerAxisInPatch);
            const int upperVoxelInPreimage = voxelPosInPreimage(x,y,numberOfVolumesPerAxisInPatch);

            const int lowerVoxelInImage = voxelPosInImage(x, y-1, numberOfVolumesPerAxisInPatch);
            const int upperVoxelInImage = voxelPosInImage(x, y, numberOfVolumesPerAxisInPatch);

            tarch::la::Vector<2, double> volumeX = patchCentre - 0.5 * patchSize; // Patch origin
            volumeX (0) += (x + 0.5) * volumeH (0); // Face between upper and lower volumes
            volumeX (1) += y * volumeH (1);

            splitRusanov1d(
                Qin + lowerVoxelInPreimage * (unknowns + auxiliaryVariables),
                Qin + upperVoxelInPreimage * (unknowns + auxiliaryVariables), volumeX,
                volumeH (0), t, 
                1, // normal
                numericalFluxL, numericalFluxR);

            for (int unknown = 0; unknown < unknowns; unknown++) {
                if (y > 0) { // Lower is in image
                Qout[lowerVoxelInImage * (unknowns + auxiliaryVariables) + unknown] -=
                    dt / volumeH (0) * numericalFluxL[unknown];
                }
                if (y < numberOfVolumesPerAxisInPatch) { // Upper is in image
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
    

void exahype2::fv::ck::splitRusanov1d(
  const double * __restrict__ QL,
  const double * __restrict__ QR,
  const tarch::la::Vector<Dimensions,double>&  x,
  double                                       dx,
  double                                       t,
  int                                          normal,
  double * __restrict__ FL,
  double * __restrict__ FR
) {
    const int unknowns = 4;
    const int auxiliaryVariables =0;
  assertion(normal>=0);
  assertion(normal<Dimensions);

    
    double * fluxFL;
    double * fluxFR;
    fluxFL   = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);
    fluxFR   = ::tarch::allocateMemory(unknowns, tarch::MemoryLocation::Heap);
    for (int i=0;i<unknowns;i++) fluxFL[i]=0;
    for (int i=0;i<unknowns;i++) fluxFR[i]=0;

    flux(QL,x,dx,t,normal,fluxFL);
    flux(QR,x,dx,t,normal,fluxFR);


    double lambdaMaxL = maxEigenvalue(QL,x,dx,t,normal);
    double lambdaMaxR = maxEigenvalue(QR,x,dx,t,normal);

    nonCriticalAssertion7( lambdaMaxL>=0.0, x, dx, t, dt, normal, lambdaMaxL, lambdaMaxR );
    nonCriticalAssertion7( lambdaMaxR>=0.0, x, dx, t, dt, normal, lambdaMaxL, lambdaMaxR );

    double lambdaMax  = std::max( lambdaMaxL, lambdaMaxR );

    for (int unknown=0; unknown<unknowns; unknown++) {
        double new_flux =  0.5 * fluxFL[unknown] 
                        + 0.5 * fluxFR[unknown] 
                        - 0.5 * lambdaMax * (QR[unknown] - QL[unknown]);;
        
        FL[unknown] = new_flux; 
        FR[unknown] = new_flux; 
    }

    ::tarch::freeMemory(fluxFL,   tarch::MemoryLocation::Heap);
    ::tarch::freeMemory(fluxFR,   tarch::MemoryLocation::Heap);  
};

void exahype2::fv::ck::flux(
  const double * __restrict__ Q, // Q[4+0],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal,
  double * __restrict__ F // F[4]
)  {
  logTraceInWith4Arguments( "flux(...)", faceCentre, volumeH, t, normal );
  const double irho = 1.0/Q[0];

  // based on the assumption that the fluid is an ideal gas, gamma chosen for dry air
  const double gamma = 1.4;
  const double p = (gamma-1) * (Q[3] - 0.5*irho*(Q[1]*Q[1]+Q[2]*Q[2]));
  
  switch(normal){  
  case 0: //in x direction
	  F[0] = Q[1]; //rho
	  F[1] = irho * Q[1] * Q[1] + p; 
	  F[2] = irho * Q[1] * Q[2];
	  F[3] = irho * Q[1] *(Q[3] + p);
	  break;
  case 1: //in y direction
	  F[0] = Q[2];
	  F[1] = irho * Q[2] * Q[1];
	  F[2] = irho * Q[2] * Q[2] + p;
	  F[3] = irho * Q[2] *(Q[3] + p);
	  break;
  }  

}

double exahype2::fv::ck::maxEigenvalue(
  const double * __restrict__ Q, // Qma[4+0],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal
)  {
	
	  const double irho = 1.0/Q[0];
	  
	  // based on the assumption that the fluid is an ideal gas, gamma chosen for dry air
	  const double gamma = 1.4;  
	  const double p = (gamma-1) * (Q[3] - 0.5*irho*(Q[1]*Q[1]+Q[2]*Q[2]));
	  
	  const double c   = std::sqrt(gamma * p * irho);

	  double result = 1.0;
	  switch(normal){
	  case 0: //x
		  result = std::max( std::abs(Q[1] * irho - c), std::abs(Q[1] * irho + c) );
		  break;
	  case 1: //y
		  result = std::max( std::abs(Q[2] * irho - c), std::abs(Q[2] * irho + c) );
		  break;
	  }
	  
	  return result;

}

void exahype2::fv::ck::sourceTerm(
    const double * __restrict__                  Q,
    const tarch::la::Vector<2,double>&           volueCentre,
    double                                       volumeH,
    double                                       t,
    double                                       dt,
    double * __restrict__                        S
    ){
            std::fill_n(S,4,0.0);
}

/**
 * @brief Calculates interger position of volume in preimage
 */
inline int exahype2::fv::ck::voxelPosInPreimage(int x, int y, int numberOfVolumesPerAxisInPatch){
    return x + 1 + (y + 1) * (2 + numberOfVolumesPerAxisInPatch);
}

/**
 * @brief Calculates interger position of volume in image (aka patch)
 */
inline int exahype2::fv::ck::voxelPosInImage(int x, int y, int numberOfVolumesPerAxisInPatch){
    return x + y * numberOfVolumesPerAxisInPatch;
}



tarch::la::Vector<2,double>  exahype2::fv::ck::getVolumeSize(
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