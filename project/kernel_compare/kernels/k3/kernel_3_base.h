#pragma once
#include "../../stdlibs.h"
#include "tarch/la/Vector.h"
#include "peano4/utils/Globals.h"



namespace kernels::k3{
  void PatchUpdate(double t, double dt, double patch_center_0, double patch_center_1, double patch_size_0, double patch_size_1, double *in_patch, double *out_patch);
};
