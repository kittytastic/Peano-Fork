#include <iostream>
#include "data_generator.h"


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

int main(){
    std::cout << "Hello world" << std::endl;

    double data[10];
    generateNoise(10, data);
}