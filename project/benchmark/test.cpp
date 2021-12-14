#include "benchmark.h"

void do_smth(){
    int b =0;
    for(int i =0; i<10000000; i++){
        b++;
    }
    return;
}

int main(){
    benchmark::benchmark(do_smth, benchmark::NONE, 6);   
    return 0;    
}