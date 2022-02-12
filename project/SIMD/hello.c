// https://docs.microsoft.com/en-us/cpp/intrinsics/x64-amd64-intrinsics-list?view=msvc-170
#include <assert.h>
#include <immintrin.h>
#include <iostream>

__m256 mul8(const float* p1, const float *p2){
    const __m256 a = _mm256_loadu_ps( p1);
    const __m256 b = _mm256_loadu_ps( p2 );
    return _mm256_mul_ps( a, b );
}

__m256d mul4(const double* p1, const double *p2){
    const __m256d a = _mm256_loadu_pd( p1);
    const __m256d b = _mm256_loadu_pd( p2 );
    return _mm256_mul_pd( a, b );
}

__m256 add8(const float* p1, const float *p2){
    const __m256 a = _mm256_loadu_ps( p1);
    const __m256 b = _mm256_loadu_ps( p2 );
    return _mm256_add_ps( a, b );
}

void save_register(float* out, __m256 reg){
    _mm256_storeu_ps(out, reg);
}

void save_register(double* out, __m256d reg){
    _mm256_storeu_pd(out, reg);
}

__m256 permute8(const float* p1){
    const __m256i a = _mm256_setr_epi32(4,3,2,1,1,1,1,1);
    const __m256 b = _mm256_loadu_ps( p1 );
    return _mm256_permutevar8x32_ps(b, a);
}

void print_vector(float* vec, int length){
    std::cout << "[";
    for(int i=0; i<length; i++){
        std::cout << vec[i];
        if (i<length-1){
            std::cout<< ", ";
        }
    }
    std::cout << "]" << std::endl;

}

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
    float x[8] = {0,1,2,3,4,5,6,7};
    float y[8] = {0,1,2,3,4,5,6,7};
    float out_list[8];
    save_register(out_list, mul8(x,y));
    print_vector(out_list, 8);
   
    save_register(out_list, add8(x,y));
    print_vector(out_list, 8);

    double xd[4] = {1,2,3,4}; 
    double yd[4] = {1,2,3,4} ;
    double out_d[4];
    save_register(out_d, mul4(xd, yd));
    print_vector(out_d, 4);


    //int permute[8] = {4,3,2,1,1,1,1};
    //const __m256i a = _mm256_loadu_si256(permute);
    
    print_vector(out_list, 8);
    //const __m256 c = _mm256_permutexvar_ps(a, b);
    
    save_register(out_list, permute8(x));
    print_vector(out_list, 8);

}