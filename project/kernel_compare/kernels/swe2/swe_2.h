#pragma once
#include "../../stdlibs.h"

#include "../../data/swe_data.h"

#include "../kernel_base.h"
#include "swe_2_base.h"

namespace kernels::swe2{
    void swe2_getdata(int x, double* data){
        for(int i=0; i<x; i++){
            data[i] = swe_in_vec0[i];
        }
    }

    void swe2_runKernel(const testCase* tc, double* outVec){
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


    Kernel swe2(
        "SWE 2: Compiled",
        swe2_getdata,
        swe2_runKernel,
        5*5*4,
        3*3*4,
        swe_2d_test_cases
    );
};
