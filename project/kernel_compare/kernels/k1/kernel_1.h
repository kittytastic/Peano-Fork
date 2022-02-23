#include "../../stdlibs.h"
#include "tarch/la/Vector.h"

#include "../../data/data_generator.h"
#include "../../data/euler_data.h"

#include "../kernel_base.h"
#include "kernel_1_base.h"

void k1_getdata(int x, double* data){
    for(int i=0; i<x; i++){
        data[i] = in_euler2d_1[i];
    }

    //int b=0;
    //for(int i=0; i<10000000; i++){b++;}
}

void k1_runKernel(double * inVec, double* outVec){
    tarch::la::Vector<2,double> patchCenter;
    patchCenter(0)=1;
    patchCenter(1)=1;
    tarch::la::Vector<2,double> patchSize;
    patchSize(0)=1;
    patchSize(1)=1;
    kernels::k1::kernelLambda(
        patchCenter,
        patchSize,
        1.0,
        0.001,
        inVec,
        outVec
    );
    
}

std::vector<testCase> k1_tests = {
    testCase("Basic", in_euler2d_1, out_euler2d_1)
    ,testCase("Exciting 1", in_euler2d_2, out_euler2d_2)
    ,testCase("Exciting 2", in_euler2d_3, out_euler2d_3)
    };

Kernel k1(
    "Kernel 1: Base Euler",
    k1_getdata,
    k1_runKernel,
    5*5*4,
    3*3*4,
    k1_tests
    );

