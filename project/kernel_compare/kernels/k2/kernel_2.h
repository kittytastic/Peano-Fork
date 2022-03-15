#pragma once
#include "../../stdlibs.h"

#include "tarch/la/Vector.h"

#include "../../data/data_generator.h"
#include "../../data/euler_data.h"

#include "../kernel_base.h"
#include "kernel_2_base.h"

namespace kernels::k2{
    void k2_getdata(int x, double* data){
        for(int i=0; i<x; i++){
            data[i] = euler_in_vec0[i];
        }

        //int b=0;
        //for(int i=0; i<10000000; i++){b++;}
    }

    void k2_runKernel(const testCase* tc, double* outVec){
        tarch::la::Vector<2,double> patchCenter;
        patchCenter(0)=tc->cellPos0;
        patchCenter(1)=tc->cellPos1;
        tarch::la::Vector<2,double> patchSize;
        patchSize(0)=tc->cellSize0;
        patchSize(1)=tc->cellSize1;
        compliedKernel(
            patchCenter,
            patchSize,
            tc->t,
            tc->dt,
            tc->input,
            outVec
        );
    }


    Kernel k2(
        "Kernel 2: Basic Inline",
        k2_runKernel,
        2,
        3,
        4,
        0,
        euler_2d_test_cases
    );
};
