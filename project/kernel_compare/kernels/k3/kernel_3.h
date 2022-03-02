#pragma once
#include "../../stdlibs.h"

#include "../../data/data_generator.h"
#include "../../data/euler_data.h"

#include "../kernel_base.h"
#include "kernel_3_base.h"

namespace kernels::k3{
    void k3_getdata(int x, double* data){
        for(int i=0; i<x; i++){
            data[i] = euler_in_vec0[i];
        }

        //int b=0;
        //for(int i=0; i<10000000; i++){b++;}
    }

    void k3_runKernel(const testCase* tc, double* outVec){
        PatchUpdate(
            tc->t,
            tc->dt,
            tc->cellPos0,
            tc->cellPos1,
            tc->cellSize0,
            tc->cellSize1,
            tc->input,
            outVec
        );
    }


    Kernel k3(
        "Kernel 3: Compiled",
        k3_getdata,
        k3_runKernel,
        5*5*4,
        3*3*4,
        euler_2d_test_cases
    );
};
