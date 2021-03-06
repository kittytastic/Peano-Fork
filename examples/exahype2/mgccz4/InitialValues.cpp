#include "InitialValues.h"
#include "Properties.h"

/**
 *  *  * This file is automatically created by Peano. I need it to interact with
 *   *   * the Python API, i.e. to read out data set there.
 *    *    */
#include "Constants.h"

#include "tarch/la/Vector.h"

#include "peano4/utils/Globals.h"

#include <stdio.h>
#include <string.h>



void examples::exahype2::mgccz4::gaugeWave(
  double * __restrict__ Q, // Q[64+0],
  const tarch::la::Vector<Dimensions,double>&  x,
  double t
) {
  constexpr int nVars = 64;
  constexpr double pi = M_PI;
  constexpr double peak_number = 2.0;
  constexpr double ICA = 0.1; ///< Amplitude of the wave 
  double HH     = 1.0 - ICA*sin( peak_number*pi*( x[0] - t));
  double dxH    = -peak_number*pi*ICA*cos( peak_number * pi*(x[0] - t));
  double dxphi  = - pow(HH,(-7.0/6.0))*dxH/6.0;
  double phi    = pow(( 1.0 / HH),(1.0/6.0));
  double Kxx    = - 0.5*peak_number*pi*ICA*cos( peak_number * pi*(x[0] - t))/sqrt( 1.0 - ICA*sin( peak_number*pi*( x[0] - t))  );
  double traceK = Kxx/HH;
  memset(Q, .0, nVars*sizeof(double));
  Q[0]  = phi*phi*HH ;					//\tilde(\gamma)_xx
  Q[3]  = phi*phi  ;					//\tilde(\gamma)_yy
  Q[5]  = phi*phi                            ;		//\tilde(\gamma)_zz
  Q[6]  = phi*phi*(Kxx - 1.0/3.0*traceK*HH ) ;		//\tilde(A)_xx
  Q[9] =  phi*phi*(0.0 - 1.0/3.0*traceK*1.0) ;		//\tilde(A)_yy
  Q[11] = phi*phi*(0.0 - 1.0/3.0*traceK*1.0) ;		//\tilde(A)_zz
  Q[16] = log(sqrt(HH));				//ln(\alpha)
  Q[13] = 2.0/(3.0*pow(HH,(5.0/3.0)))*dxH        ;	//\hat(\Gamma)^x
  Q[23] = 1.0/(2.0*HH)*dxH               ;		//A_x
  Q[35] = pow(HH,(-1.0/3.0))*dxH/3.0         ;		//D_xxx
  Q[38] = phi*dxphi                     ;		//D_xyy
  Q[40] = phi*dxphi                    ;		//D_xzz
  Q[53] = traceK;					//K
  Q[54] = log(phi);					//ln(\phi)
  Q[55] = dxphi/phi;					//P_x
  Q[59] = HH;
  Q[60] = 2.0*Kxx;
  Q[61] = dxH;
}

void examples::exahype2::mgccz4::linearWave(
  double * __restrict__ Q, // Q[64+0],
  const tarch::la::Vector<Dimensions,double>&  X,
  double t
) {
  constexpr int nVars = 64;
  constexpr double pi = M_PI;
  constexpr double peak_number = 2.0;
  constexpr double ICA = 1e-4; ///< Amplitude of the wave, should be very small to keep linearized.
  double HH     =  ICA*sin( peak_number*pi*( X[0] - t));
  double dxHH   =  peak_number*pi*ICA*cos( peak_number * pi*(X[0] - t));
  double dtHH   = -peak_number*pi*ICA*cos( peak_number * pi*(X[0] - t));
  memset(Q, .0, nVars*sizeof(double));
  Q[0]  = 1.0  ;		//\tilde(\gamma)_xx
  Q[3]  = 1+HH ;		//\tilde(\gamma)_yy
  Q[5]  = 1-HH ;		//\tilde(\gamma)_zz
  Q[6]  = 0.0	    ;		//\tilde(A)_xx
  Q[9]  = -0.5*dtHH ;		//\tilde(A)_yy
  Q[11] = 0.5*dtHH  ;		//\tilde(A)_zz
  Q[16] = log(1.0) ;		//ln(\alpha)
  Q[35] = 0.0       ;		//D_xxx
  Q[38] = 0.5*dxHH  ;		//D_xyy
  Q[40] = -0.5*dxHH ;		//D_xzz
  Q[54] = log(1.0) ;		//ln(\phi)
}

void examples::exahype2::mgccz4::forcedflat(
  double * __restrict__ Q, // Q[64+0],
  const tarch::la::Vector<Dimensions,double>&  x,
  double t
) {
  constexpr int nVars = 64;
  constexpr double pi = M_PI;
  constexpr double peak_number = 2.0;
  constexpr double ICA = 0.1; ///< Amplitude of the wave 
  double HH     = 1.0 - ICA*sin( peak_number*pi*( x[0] - t));
  double dxH    = -peak_number*pi*ICA*cos( peak_number * pi*(x[0] - t));
  double Kxx    = - 0.5*peak_number*pi*ICA*cos( peak_number * pi*(x[0] - t))/sqrt( 1.0 - ICA*sin( peak_number*pi*( x[0] - t))  );
  memset(Q, .0, nVars*sizeof(double));
  Q[0]  = 1.0 ;		//\tilde(\gamma)_xx
  Q[3]  = 1.0 ;		//\tilde(\gamma)_yy
  Q[5]  = 1.0 ;		//\tilde(\gamma)_zz
  Q[59] = HH;
  Q[60] = 2.0*Kxx;
  Q[61] = dxH;
}


