#pragma once
#include "kernel_base.h"
#include "kernel_2_base.h"
#include "../data/data_generator.h"
#include "tarch/la/Vector.h"
#include  <iostream>
#include "../data/euler_data.h"

void k2_getdata(int x, double* data){
    for(int i=0; i<x; i++){
        data[i] = in_euler2d_1[i];
    }

    //int b=0;
    //for(int i=0; i<10000000; i++){b++;}
}

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

std::vector<testCase> k2_tests = {
    testCase("Basic", in_euler2d_1, out_euler2d_1)
    ,testCase("Exciting 1", in_euler2d_2, out_euler2d_2)
    ,testCase("Exciting 2", in_euler2d_3, out_euler2d_3)
    };

Kernel k2(
    "Kernel 2: Basic Inline",
    k2_getdata,
    k2_runKernel,
    5*5*4,
    3*3*4,
    k2_tests
    );

