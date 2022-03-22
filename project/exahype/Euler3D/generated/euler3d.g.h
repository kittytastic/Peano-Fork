
namespace kernels::euler3d2{
    void PatchUpdate(double t, double dt, double patch_center_0, double patch_center_1, double patch_center_2, double patch_size_0, double patch_size_1, double patch_size_2, double *__restrict__ in_patch, double *__restrict__ out_patch);
}