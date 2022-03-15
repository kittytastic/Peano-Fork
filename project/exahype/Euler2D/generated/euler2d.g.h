namespace kernels::k3{
    void PatchUpdate(double t, double dt, double patch_center_0, double patch_center_1, double patch_size_0, double patch_size_1, double *__restrict__ in_patch, double *__restrict__ out_patch);
}