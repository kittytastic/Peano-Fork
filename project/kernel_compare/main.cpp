#include <iostream>
#include "data_generator.h"
#include "kernel_base.h"
#include "kernel_1.h"
#include "kernel_2.h"


void print_vector(double* vec, int length){
    std::cout << "[";
    for(int i=0; i<length; i++){
        std::cout << vec[i];
        if (i<length-1){
            std::cout<< ", ";
        }
    }
    std::cout << "]" << std::endl;
}

void doKernelStuff(){
    Kernel& k = k2;
    double* inVec = (double*) malloc(k.inputVectorLength*sizeof(double));
    double* outVec = (double*) malloc(k.outputVectorLength*sizeof(double));

    k.prepareData(k.inputVectorLength, inVec);
    k.runKernel(inVec, outVec);
}

int main(){
    std::cout << "Hello world" << std::endl;

    double data[10];
    generateNoise(10, data);

    //test_kernel();
    doKernelStuff();
    std::cout << "Done" << std::endl;
}

