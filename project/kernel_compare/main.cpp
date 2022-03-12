#include "stdlibs.h"
#include "run_testcase.h"
#include "kernels/k1/kernel_1.h"
#include "kernels/k2/kernel_2.h"
#include "kernels/k3/kernel_3.h"
#include "kernels/swe1/swe_1.h"
#include "kernels/swe2/swe_2.h"
#include "kernels/euler3d1/euler3d_1.h"
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

/*void benchMarkKernel(const Kernel* k){
    double* inVec = (double*) malloc(k->inputVectorLength*sizeof(double));
    double* outVec = (double*) malloc(k->outputVectorLength*sizeof(double));

    //k->prepareData(k->inputVectorLength, inVec);
    //std::cout << "In before:  ";
    //print_vector(inVec, k.inputVectorLength);
    //std::cout << "Out before: ";
    //print_vector(outVec, k.outputVectorLength);
    benchmark::benchmark([&](){k->runKernel(&k->testCases[0], outVec);}, benchmark::NONE, 5);
    //std::cout << "Out after:  ";
    //print_vector(outVec, k.outputVectorLength);
    free(inVec);
    free(outVec);
}*/

int main(){
    std::cout << "------------ Kernel Compare -----------" << std::endl;
    //benchmark::benchmark(doKernelStuff, benchmark::NONE, 5);

    std::vector<Kernel> allKernels = {
        kernels::euler3d1::euler3d_1,
        kernels::swe2::swe2,
        kernels::swe1::swe1,
        kernels::k1::k1,
        kernels::k2::k2,
        kernels::k3::k3
    };

    for(const auto &k: allKernels){
        std::cout << std::endl<< k.name << std::endl;
        testKernel(&k);
        //benchMarkKernel(&k);
    }
}

