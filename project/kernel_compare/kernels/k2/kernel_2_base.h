#pragma once
#include "../../stdlibs.h"
#include "tarch/la/Vector.h"
#include "peano4/utils/Globals.h"



namespace kernels::k2{
  const int Dimensions=2;

    void compliedKernel (
    const tarch::la::Vector<2, double>&  patchCentre,
    const tarch::la::Vector<2, double>&  patchSize,
    double t, double dt,
    const double *__restrict__ Qin, // length = (vol in preimage) * (num vars)
    double *__restrict__ Qout       // length = (vol in patch)    * (num vars)
    );

    

    void sourceTerm(
        const double * __restrict__                  Q,
        const tarch::la::Vector<2,double>&           volueCentre,
        double                                       volumeH,
        double                                       t,
        double                                       dt,
        double * __restrict__                        S
        );
    
    void splitRusanov1d(
        const double * __restrict__ QL,
        const double * __restrict__ QR,
        const tarch::la::Vector<Dimensions,double>&  x,
        double                                       dx,
        double                                       t,
        int                                          normal,
        double * __restrict__ FL,
        double * __restrict__ FR
    );

    inline int voxelPosInPreimage(int x, int y, int numberOfVolumesPerAxisInPatch);
    inline int voxelPosInImage(int x, int y, int numberOfVolumesPerAxisInPatch);
    


  void flux(
    const double * __restrict__ Q, // Q[4+0],
    const tarch::la::Vector<Dimensions,double>&  faceCentre,
    const tarch::la::Vector<Dimensions,double>&  volumeH,
    double                                       t,
    int                                          normal,
    double * __restrict__ F // F[4]
  );

  double maxEigenvalue(
    const double * __restrict__ Q, // Qma[4+0],
    const tarch::la::Vector<Dimensions,double>&  faceCentre,
    const tarch::la::Vector<Dimensions,double>&  volumeH,
    double                                       t,
    int                                          normal
  );


  tarch::la::Vector<2,double>  getVolumeSize(
      const tarch::la::Vector<2,double>&  h,
      int                                 numberOfVolumesPerAxisInPatch
    );
};
