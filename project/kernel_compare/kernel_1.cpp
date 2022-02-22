#include <iostream>
#include "kernel_base.h"


void make_data(double* x){
    std::cout<<"making data\n";
}

void run_kernel(double* x){
    std::cout<<"run kernel\n";
}

void test_kernel(){
    std::cout << "Testing kernel\n";

    //Kernel x(make_data, run_kernel);
    // /x.prepareData = make_data;

//    double y =0.0;
  //  x.prepareData(&y);
    //x.runKernel(&y);
}