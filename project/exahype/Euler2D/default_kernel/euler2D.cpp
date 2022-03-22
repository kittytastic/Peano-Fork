#include "euler2D.h"
#include "exahype2/RefinementControl.h"


tarch::logging::Log   project::exahype::Euler2D::default_kernel::euler2D::_log( "project::exahype::Euler2D::default_kernel::euler2D" );







void project::exahype::Euler2D::default_kernel::euler2D::initialCondition(
  double * __restrict__ Q,
  const tarch::la::Vector<Dimensions,double>&  volumeCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  bool                                         gridIsConstructred
) {
  logTraceInWith3Arguments( "initialCondition(...)", volumeCentre, volumeH, gridIsConstructred );

	Q[0] = 0.1;  // rho
	Q[1] = 0.0;    // momentum in x direction
	Q[2] = 0.0;    // momentum in y direction
  
  logTraceOut( "initialCondition(...)" );
}





void project::exahype::Euler2D::default_kernel::euler2D::boundaryConditions(
  const double * __restrict__                  Qinside, // Qinside[4+0]
  double * __restrict__                        Qoutside, // Qoutside[4+0]
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal
) {
  logTraceInWith4Arguments( "boundaryConditions(...)", faceCentre, volumeH, t, normal );
 Qoutside[0] = Qinside[0]; //density
  Qoutside[1] = 0;			//velocity in x direction
  Qoutside[2] = 0;			//velocity in y direction
  Qoutside[3] = 0;			//Energy
  logTraceOut( "boundaryConditions(...)" );
}





double ::project::exahype::Euler2D::default_kernel::euler2D::maxEigenvalue(
  const double * __restrict__ Q, // Q[4+0],
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
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




void ::project::exahype::Euler2D::default_kernel::euler2D::flux(
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
  logTraceOut( "flux(...)" );
}






















