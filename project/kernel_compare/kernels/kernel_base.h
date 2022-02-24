#pragma once
#include "../stdlibs.h"

struct testCase{
    testCase(std::string name, double cellPos0,
    double cellPos1,
    double cellSize0,
    double cellSize1,
    double t,
    double dt, double * input, double * expected):
    name(name),
    cellPos0(cellPos0),
    cellPos1(cellPos1),
    cellSize0(cellSize0),
    cellSize1(cellSize1),
    t(t),
    dt(dt),
    input(input),
    expected(expected) 
    {}
    std::string name;
    double cellPos0;
    double cellPos1;
    double cellSize0;
    double cellSize1;
    double t;
    double dt;
    double * input;
    double * expected;
};

class Kernel {
    public:
        Kernel(std::string name, std::function<void(int, double*)> prepData, std::function<void(const testCase*, double *)> runKernel, int inVecLen, int outVecLen
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
        std::function<void(const testCase*, double *)> runKernel;
        int inputVectorLength; 
        int outputVectorLength;
        std::vector<testCase> testCases;
        void addTestCase(std::string name, double * input, double * expected);

};