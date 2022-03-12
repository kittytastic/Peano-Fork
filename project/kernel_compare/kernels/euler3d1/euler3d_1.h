#include "../../stdlibs.h"
#include "tarch/la/Vector.h"

#include "../../data/euler3d_data.h"

#include "../kernel_base.h"
#include "euler3d_1_base.h"

namespace kernels::euler3d1{
void k1_getdata(int x, double* data){
    for(int i=0; i<x; i++){
        data[i] = euler_3d_in_vec0[i];
    }

    //int b=0;
    //for(int i=0; i<10000000; i++){b++;}
}

void euler3d1_runKernel(const testCase* tc, double* output){
    tarch::la::Vector<3,double> patchCenter;
    patchCenter(0)=tc->cellPos0;
    patchCenter(1)=tc->cellPos1;
    patchCenter(2)=tc->cellPos2;
    tarch::la::Vector<3,double> patchSize;
    patchSize(0)=tc->cellSize0;
    patchSize(1)=tc->cellSize1;
    patchSize(2)=tc->cellSize2;
    kernels::euler3d1::kernelLambda(
        patchCenter,
        patchSize,
        tc->t,
        tc->dt,
        tc->input,
        output
    );
    
}



Kernel euler3d_1(
    "Euler 3D: default",
    euler3d1_runKernel,
    3,3,
    5,0,
    euler_3d_test_cases
    );
};

