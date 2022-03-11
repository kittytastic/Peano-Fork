#include "../../stdlibs.h"

#include "tarch/la/Vector.h"
#include "tarch/Assertions.h"
#include "tarch/logging/Log.h"
#include "tarch/la/la.h"

#include "exahype2/NonCriticalAssertions.h"
#include "swe_1_base.h"
#include "../shared.h"


void kernels::swe1::kernelLambda(tarch::la::Vector<2,double> patchCenter, tarch::la::Vector<2,double> patchSize, double t, double dt, double * Qin, double * Qout){
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
