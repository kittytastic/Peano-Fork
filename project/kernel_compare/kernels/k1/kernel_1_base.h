#include "../../stdlibs.h"
#include "tarch/la/Vector.h"

namespace kernels{
    namespace k1{
void kernelLambda(tarch::la::Vector<2,double> patchCenter, tarch::la::Vector<2,double> patchSize, double t, double dt, double * Qin, double * Qout);

const int Dimensions=2;
double maxEigenvalue(
      const double * __restrict__ Q, // Q[4+0],
      const tarch::la::Vector<2,double>&  faceCentre,
      const tarch::la::Vector<2,double>&  volumeH,
      double                                       t,
      int                                          normal
    );
    
void flux(
      const double * __restrict__ Q, // Q[4+0],
      const tarch::la::Vector<2,double>&  faceCentre,
      const tarch::la::Vector<2,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__ F // F[4]
    );

}}