#include "../../stdlibs.h"

#include "tarch/la/Vector.h"
#include "tarch/Assertions.h"
#include "tarch/logging/Log.h"
#include "tarch/la/la.h"

#include "exahype2/NonCriticalAssertions.h"
#include "kernel_1_base.h"
#include "../shared.h"


void kernels::k1::kernelLambda(tarch::la::Vector<2,double> patchCenter, tarch::la::Vector<2,double> patchSize, double t, double dt, double * Qin, double * Qout){
    const int Dimensions = 2; 
   kernels::shared::dim2::applySplit1DRiemannToPatch_Overlap1AoS2d(
    
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
          
       kernels::shared::dim2::splitRusanov1d(
          [] (
            const double * __restrict__                  Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double                                       F[]
          ) -> void {
            
           kernels::k1::flux( Q, faceCentre, volumeH, t, normal, F );
            
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
            
           std::fill_n(BgradQ,4,0.0);
            
          },
          [] (
            const double * __restrict__                  Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal
          ) -> double {
            return kernels::k1::maxEigenvalue( Q, faceCentre, volumeH, t, normal);
          },
          QL, QR, x, dx, t, dt, normal,
          4,
          0,
          FL,FR,
          
          false,
          
          
          true
          
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
          
  std::fill_n(S,4,0.0);
        },
        patchCenter,
        patchSize,
        t,
        dt,
        3,
        4,
        0,
        Qin,
        Qout
    );
}


double kernels::k1::maxEigenvalue(
  const double * __restrict__ Q, // Q[4+0],
  const tarch::la::Vector<2,double>&  faceCentre,
  const tarch::la::Vector<2,double>&  volumeH,
  double                                       t,
  int                                          normal
)  {
  logTraceInWith4Arguments( "maxEigenvalue(...)", faceCentre, volumeH, t, normal );
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
  logTraceOut( "maxEigenvalue(...)" );
}




void kernels::k1::flux(
  const double * __restrict__ Q, // Q[4+0],
  const tarch::la::Vector<2,double>&  faceCentre,
  const tarch::la::Vector<2,double>&  volumeH,
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
  logTraceOut( "flux(...)" );
}
