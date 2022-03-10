#include "stdlibs.h"
#include "kernels/k1/kernel_1.h"
#include "kernels/k2/kernel_2.h"
#include "kernels/k3/kernel_3.h"
#include "kernels/swe1/swe_1.h"
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

bool isClose(double a, double b){
    return std::abs(a-b)<0.00000001;
}

void testKernel(const Kernel* k){
    double* outVec = (double*) malloc(k->outputVectorLength*sizeof(double));

    const int lfw = 20;
    const int rfw = 10;
    int passed = 0;
    
    //std::cout << "Runing test cases...\n";
    for(const auto& tc: k->testCases) {
        //std::cout << std::setw(lfw) << std::left << tc.name;

        for(int x=0; x<3; x++){
            for(int y=0; y<3; y++){
                const int voxelInPreImage  = x+1 + (y+1) * (3+2);
                const int voxelInImage     = x+ y * 3;
                for(int u=0; u<4; u++){
                    const int locationInPreimage = voxelInPreImage*4 + u;
                    const int locationInImage = voxelInImage*4 + u;
                    outVec[locationInImage]=tc.input[locationInPreimage];
                }
            }
        } 

        k->runKernel(&tc, outVec);

        bool allClose = true;
        for(int i=0; i<k->outputVectorLength; i++){
            if(!isClose(outVec[i], tc.expected[i])){
                //std::cout << "[" << i <<"] Expected: " << tc.expected[i] << " Recived: "<< outVec[i]<<std::endl;
            }
            allClose &= isClose(outVec[i], tc.expected[i]);
        }

        /*std::cout  << std::setw(rfw) << std::right;
        if (allClose){
        std::cout << "✔️\n"; }
         else{
             std::cout << "❌\n";
         }*/
         if (allClose){passed++;}
    }
    
    std::ostringstream out_str;
    out_str<<passed<<"/"<<k->testCases.size()<<" Tests passed";
    std::cout << std::setw(lfw) << std::left<<out_str.str();
    std::cout  << std::setw(rfw) << std::right;
    if (passed == k->testCases.size()){
        std::cout << "✔️\n"; }
    else{
        std::cout << "❌\n";
    }

    free(outVec);
}

void benchMarkKernel(const Kernel* k){
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
}

int main(){
    std::cout << "------------ Kernel Compare -----------" << std::endl;
    //benchmark::benchmark(doKernelStuff, benchmark::NONE, 5);

    std::vector<Kernel> allKernels = {
        kernels::swe1::swe1,
        kernels::k1::k1,
        kernels::k2::k2,
        kernels::k3::k3
    };

    for(const auto &k: allKernels){
        std::cout << std::endl<< k.name << std::endl;
        testKernel(&k);
        benchMarkKernel(&k);
    }
}

