#include "swe.h"
#include "exahype2/RefinementControl.h"


tarch::logging::Log   project::exahype::SWE::default_kernel::swe::_log( "project::exahype::SWE::default_kernel::swe" );




::exahype2::RefinementCommand project::exahype::SWE::default_kernel::swe::refinementCriterion(
  const double * __restrict__ Q, // Q[3+1]
  const tarch::la::Vector<Dimensions,double>&  volumeX,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t
) {
 ::exahype2::RefinementCommand result = ::exahype2::RefinementCommand::Keep;

  if(tarch::la::equals(t, 0.0)){
	  tarch::la::Vector<Dimensions,double> centre = {0.5, 0.5};
	  bool nearCentre = tarch::la::norm2(volumeX-centre)>0.19 && tarch::la::norm2(volumeX-centre)<0.21;
	  result = (nearCentre ? ::exahype2::RefinementCommand::Refine : ::exahype2::RefinementCommand::Erase);
  }
  return result;
}




void project::exahype::SWE::default_kernel::swe::initialCondition(
  double * __restrict__ Q,
  const tarch::la::Vector<Dimensions,double>&  volumeCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  bool                                         gridIsConstructred
) {
  logTraceInWith3Arguments( "initialCondition(...)", volumeCentre, volumeH, gridIsConstructred );

   tarch::la::Vector<Dimensions,double> centre = {0.5, 0.5};
  bool nearCentre = tarch::la::norm2(volumeCentre-centre)<0.20;
  // height of water
  Q[0] = 1.0;
  
  // height times velocities
  Q[1] = 0;
  Q[2] = 0;
  
  // bathimetry
  Q[3] = (nearCentre ? 0.0 : 0.1);

  logTraceOut( "initialCondition(...)" );
}





void project::exahype::SWE::default_kernel::swe::boundaryConditions(
  const double * __restrict__                  Qinside, // Qinside[3+1]
  double * __restrict__                        Qoutside, // Qoutside[3+1]
  const tarch::la::Vector<Dimensions,double>&  faceCentre,
  const tarch::la::Vector<Dimensions,double>&  volumeH,
  double                                       t,
  int                                          normal
) {
  logTraceInWith4Arguments( "boundaryConditions(...)", faceCentre, volumeH, t, normal );
   Qoutside[0] = Qinside[0];
	  Qoutside[1] = Qinside[1];
	  Qoutside[2] = Qinside[2];
	  Qoutside[3] = Qinside[3];
  logTraceOut( "boundaryConditions(...)" );
}





double ::project::exahype::SWE::default_kernel::swe::maxEigenvalue(
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




void ::project::exahype::SWE::default_kernel::swe::flux(
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




void ::project::exahype::SWE::default_kernel::swe::nonconservativeProduct(
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



















