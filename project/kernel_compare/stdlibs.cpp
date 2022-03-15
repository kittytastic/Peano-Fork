#include "stdlibs.h"

int pow(int num, int pow){
    int out_n = 1;
    for(int i=0; i<pow; i++){
        out_n *= num;
    }
    return out_n;
}