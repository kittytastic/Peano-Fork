#include "stdlibs.h"
#include "run_testcase.h"
#include "kernels/k1/kernel_1.h"
#include "kernels/k2/kernel_2.h"
#include "kernels/k3/kernel_3.h"
#include "kernels/swe1/swe_1.h"
#include "kernels/swe2/swe_2.h"
#include "kernels/euler3d1/euler3d_1.h"
#include "kernels/euler3d2/euler3d_2.h"
#include "../benchmark/benchmark.h"

struct RunResults{
    std::string name;
    bool tests_passed;
    benchmark::BenchmarkResults *benchmark_results;
};

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

void benchMarkKernel(const Kernel* k, benchmark::BenchmarkResults* results, float target_time){
    int inputVectorLength = pow(k->cellsPerAxis+2, k->dim) * (k->unknowns + k->auxiliary);
    int outputVectorLength = pow(k->cellsPerAxis, k->dim) * (k->unknowns + k->auxiliary);
    double* inVec = (double*) malloc(inputVectorLength*sizeof(double));
    double* outVec = (double*) malloc(outputVectorLength*sizeof(double));

    benchmark::benchmark([&](){k->runKernel(&k->testCases[0], outVec);}, results, benchmark::NONE, target_time);    
    
    free(inVec);
    free(outVec);
}

void saveResults(std::vector<RunResults*> *results, std::string filename){

    std::ofstream resultFile;
    resultFile.open(filename);
    resultFile << "name, tests_passed, num_trials, total_time";
    for(const auto &r: *results){
        resultFile << r->name << ", " <<  (r->tests_passed?"true":"false") <<", " << r->benchmark_results->trials << ", " << r->benchmark_results->total_run_time<<std::endl;
    }
  
    resultFile.close();

}



char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char * argv[]){
    std::cout << "------------ Kernel Compare -----------" << std::endl;

    if(cmdOptionExists(argv, argv+argc, "-h"))
    {
        std::cout<<"-t target_time_float [default 5.0]\n-f file_name_str [default 'results.csv'}";
    }

    std::string resultsFileName="results.csv";

    char * filename = getCmdOption(argv, argv + argc, "-f");
    if (filename)
    {
        resultsFileName = std::string(filename);
    }
    
    float target_time = 5.0;
    char * target_time_str = getCmdOption(argv, argv + argc, "-t");
    if (target_time_str)
    {
        target_time = std::stof(target_time_str);
    }


    std::vector<Kernel> allKernels = {
        kernels::euler3d2::euler3d2,
        kernels::euler3d1::euler3d_1,
        kernels::swe2::swe2,
        kernels::swe1::swe1,
        kernels::k1::k1,
        kernels::k2::k2,
        kernels::k3::k3
    };

    std::vector<RunResults*> all_results;
    for(const auto &k: allKernels){
        RunResults* full_res=new RunResults();
        benchmark::BenchmarkResults* res=new benchmark::BenchmarkResults();
        full_res->benchmark_results = res;
        full_res->tests_passed = true;
        full_res->name=k.name;
        all_results.push_back(full_res);
        std::cout << std::endl<< k.name << std::endl;
        full_res->tests_passed=testKernel(&k);
        benchMarkKernel(&k, res, target_time);
    }

    std::cout << "\n\nSaving results to: "<<resultsFileName<<std::endl;
    saveResults(&all_results, resultsFileName);
}

