#include "../../stdlibs.h"
#include "tarch/la/Vector.h"

#include "../../data/swe_data.h"

#include "../kernel_base.h"
#include "swe_1_base.h"

namespace kernels::swe1{
void swe1_getdata(int x, double* data){
    for(int i=0; i<x; i++){
        data[i] = swe_in_vec0[i];
    }

    //int b=0;
    //for(int i=0; i<10000000; i++){b++;}
}

void swe1_runKernel(const testCase* tc, double* output){
    tarch::la::Vector<2,double> patchCenter;
    patchCenter(0)=tc->cellPos0;
    patchCenter(1)=tc->cellPos1;
    tarch::la::Vector<2,double> patchSize;
    patchSize(0)=tc->cellSize0;
    patchSize(1)=tc->cellSize1;
    kernels::swe1::kernelLambda(
        patchCenter,
        patchSize,
        tc->t,
        tc->dt,
        tc->input,
        output
    );
    
}



Kernel swe1(
    "SWE 1: Default SWE",
    swe1_getdata,
    swe1_runKernel,
    5*5*4,
    3*3*4,
    swe_2d_test_cases
    );
};

