#pragma once
#include "../../stdlibs.h"

#include "../../data/euler3d_data.h"

#include "../kernel_base.h"
#include "euler3d_2_base.h"

namespace kernels::euler3d2{

    void euler3d_runKernel(const testCase* tc, double* outVec){
        PatchUpdate(
            tc->t,
            tc->dt,
            tc->cellPos0,
            tc->cellPos1,
            tc->cellPos2,
            tc->cellSize0,
            tc->cellSize1,
            tc->cellSize2,
            tc->input,
            outVec
        );
    }


    Kernel euler3d2(
        "Euler3D 2: Compiled",
        euler3d_runKernel,
        3,3,
        5,0,
        euler_3d_test_cases
    );
};
