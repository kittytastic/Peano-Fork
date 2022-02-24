#include "../stdlibs.h"
#include <random>

void generateNoise(int values, double *out){
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(5.0,0.5);

    for (int i=0; i<values; ++i) {
        out[i] = distribution(generator);
    }
}