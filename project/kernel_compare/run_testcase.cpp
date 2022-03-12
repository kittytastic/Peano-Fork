#include "run_testcase.h"

void load_out_vector(const Kernel* k, const testCase& tc, double* outVec){
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
        load_out_vector(k, tc, outVec);
        

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