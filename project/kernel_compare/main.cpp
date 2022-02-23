#include <iostream>
#include "data/data_generator.h"
#include "kernel_base.h"
#include "kernels/kernel_1.h"
#include "kernels/kernel_2.h"
#include "../benchmark/benchmark.h"
#include <cmath>


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

bool isClose(double a, double b){
    return std::abs(a-b)<0.02;
}

void testKernel(const Kernel* k){
    double* outVec = (double*) malloc(k->outputVectorLength*sizeof(double));

    const int lfw = 20;
    const int rfw = 10;
    
    std::cout << "Runing test cases...\n";
    for(const auto& tc: k->testCases) {
        std::cout << std::setw(lfw) << std::left << tc.name;
        k->runKernel(tc.input, outVec);

        bool allClose = true;
        for(int i=0; i<k->outputVectorLength; i++){
            /*if(!isClose(outVec[i], tc.expected[i])){
                std::cout << "[" << i <<"] Expected: " << tc.expected[i] << " Recived: "<< outVec[i]<<std::endl;
            }*/
            allClose &= isClose(outVec[i], tc.expected[i]);
        }

        std::cout  << std::setw(rfw) << std::right;
        if (allClose){
        std::cout << "✔️\n"; }
         else{
             std::cout << "❌\n";
         }
    }

    free(outVec);
}

void benchMarkKernel(const Kernel* k){
    double* inVec = (double*) malloc(k->inputVectorLength*sizeof(double));
    double* outVec = (double*) malloc(k->outputVectorLength*sizeof(double));

    k->prepareData(k->inputVectorLength, inVec);
    //std::cout << "In before:  ";
    //print_vector(inVec, k.inputVectorLength);
    //std::cout << "Out before: ";
    //print_vector(outVec, k.outputVectorLength);
    k->runKernel(inVec, outVec);
    //std::cout << "Out after:  ";
    //print_vector(outVec, k.outputVectorLength);
    free(inVec);
    free(outVec);
}

int main(){
    std::cout << "------------ Kernel Compare -----------" << std::endl;
    //benchmark::benchmark(doKernelStuff, benchmark::NONE, 5);

    std::vector<Kernel> allKernels = {k1, k2};

    for(const auto &k: allKernels){
        std::cout << std::endl<< k.name << std::endl;
        testKernel(&k);
        benchMarkKernel(&k);
    }
}

