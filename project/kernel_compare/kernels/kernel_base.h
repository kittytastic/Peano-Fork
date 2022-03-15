#pragma once
#include "../stdlibs.h"

struct testCase{
    testCase(std::string name, double cellPos0,
    double cellPos1,
    double cellPos2,
    double cellSize0,
    double cellSize1,
    double cellSize2,
    double t,
    double dt, double * input, double * expected):
    name(name),
    cellPos0(cellPos0),
    cellPos1(cellPos1),
    cellPos2(cellPos2),
    cellSize0(cellSize0),
    cellSize1(cellSize1),
    cellSize2(cellSize2),
    t(t),
    dt(dt),
    input(input),
    expected(expected) 
    {}
    std::string name;
    double cellPos0;
    double cellPos1;
    double cellPos2;
    double cellSize0;
    double cellSize1;
    double cellSize2;
    double t;
    double dt;
    double * input;
    double * expected;
};

class Kernel {
    public:
        Kernel(std::string name, std::function<void(const testCase*, double *)> runKernel, int dim, int cellsPerAxis, int unknowns, int auxiliary
        , std::vector<testCase> testCases
        ):
            name(name),
            runKernel(runKernel),
            dim(dim),
            cellsPerAxis(cellsPerAxis),
            unknowns(unknowns),
            auxiliary(auxiliary),
            testCases(testCases)
        {}
        std::string name;
        std::function<void(const testCase*, double *)> runKernel;
        int dim;
        int cellsPerAxis;
        int unknowns;
        int auxiliary;
        std::vector<testCase> testCases;
        void addTestCase(std::string name, double * input, double * expected);

};