#pragma once
#include "stdlibs.h"

struct testCase{
    testCase(std::string name, double * input, double * expected):
    name(name),
    input(input),
    expected(expected) 
    {}
    std::string name;
    double * input;
    double * expected;
};

class Kernel {
    public:
        Kernel(std::string name, std::function<void(int, double*)> prepData, std::function<void(double *, double *)> runKernel, int inVecLen, int outVecLen
        , std::vector<testCase> testCases
        ):
            name(name),
            prepareData(prepData),
            runKernel(runKernel),
            inputVectorLength(inVecLen),
            outputVectorLength(outVecLen),
            testCases(testCases)
        {}
        std::string name;
        std::function<void(int, double *)> prepareData;
        std::function<void(double *, double *)> runKernel;
        int inputVectorLength; 
        int outputVectorLength;
        std::vector<testCase> testCases;
        void addTestCase(std::string name, double * input, double * expected);

};