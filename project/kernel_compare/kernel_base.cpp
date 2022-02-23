#include "kernel_base.h"
#include <iostream>

void Kernel::addTestCase(std::string name, double * input, double * expected){
    this->testCases.push_back(testCase(name, input, expected));
}