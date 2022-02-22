#include <iostream>
#include "data_generator.h"
#include "kernel_base.h"
#include "kernel_1.h"
#include "kernel_2.h"
#include "../benchmark/benchmark.h"


void print_vector(double* vec, int length){
    std::cout << "[";
    bool skipped = false;
    for(int i=0; i<length; i++){
            
        std::cout << std::setprecision(2)<< vec[i];
        if (i<length-1){
            std::cout<< ", ";
        }
        if(length>10 && i>=5 && !skipped){
            skipped = true;
            i = length - 5;
            std:: cout << "..., ";
        }
    }
    std::cout << "]" << std::endl;
}

void doKernelStuff(){
    Kernel& k = k2;
    double* inVec = (double*) malloc(k.inputVectorLength*sizeof(double));
    double* outVec = (double*) malloc(k.outputVectorLength*sizeof(double));

    k.prepareData(k.inputVectorLength, inVec);
    //std::cout << "In before:  ";
    //print_vector(inVec, k.inputVectorLength);
    //std::cout << "Out before: ";
    //print_vector(outVec, k.outputVectorLength);
    k.runKernel(inVec, outVec);
    //std::cout << "Out after:  ";
    //print_vector(outVec, k.outputVectorLength);
    free(inVec);
    free(outVec);
}

int main(){
    std::cout << "Hello world" << std::endl;

    double data[10];
    generateNoise(10, data);

    //test_kernel();
    benchmark::benchmark(doKernelStuff, benchmark::NONE, 5);
    //doKernelStuff();
    std::cout << "Done" << std::endl;
}

