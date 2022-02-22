#pragma once
#include <functional>

class Kernel {
    public:
        Kernel(std::function<void(int, double*)> prepData, std::function<void(double *, double *)> runKernel, int inVecLen, int outVecLen):
            prepareData(prepData),
            runKernel(runKernel),
            inputVectorLength(inVecLen),
            outputVectorLength(outVecLen)
        {}
        std::function<void(int, double *)> prepareData;
        std::function<void(double *, double *)> runKernel;
        int inputVectorLength; 
        int outputVectorLength; 
};