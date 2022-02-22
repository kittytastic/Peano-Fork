#include "kernel_base.h"
#include "kernel_2_base.h"
#include "data_generator.h"
#include "tarch/la/Vector.h"

void k2_runKernel(double * inVec, double* outVec){
    tarch::la::Vector<2,double> patchCenter;
    patchCenter(0)=1;
    patchCenter(1)=1;
    tarch::la::Vector<2,double> patchSize;
    patchSize(0)=1;
    patchSize(1)=1;
    compliedKernel(
        patchCenter,
        patchSize,
        1.0,
        0.001,
        inVec,
        outVec
    );
}

Kernel k2(generateNoise, k2_runKernel, 5*5*4, 3*3*4);

