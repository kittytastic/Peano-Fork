#include "run_testcase.h"

void load_out_vector(const Kernel* k, const testCase& tc, double* outVec){
    if(k->dim == 2){
        for(int x=0; x<k->cellsPerAxis; x++){
                for(int y=0; y<k->cellsPerAxis; y++){
                    const int voxelInPreImage  = x+1 + (y+1) * (k->cellsPerAxis+2);
                    const int voxelInImage     = x+ y * k->cellsPerAxis;
                    for(int u=0; u<(k->unknowns + k->auxiliary); u++){
                        const int locationInPreimage = voxelInPreImage*(k->unknowns+k->auxiliary) + u;
                        const int locationInImage = voxelInImage*(k->unknowns+k->auxiliary) + u;
                        outVec[locationInImage]=tc.input[locationInPreimage];
                    }
                }
        } 
    }else if (k->dim==3){
        for(int x=0; x<k->cellsPerAxis; x++){
                for(int y=0; y<k->cellsPerAxis; y++){
                    for(int z=0; z<k->cellsPerAxis; z++){
                        const int voxelInPreImage  = x+1 + (y+1) * (k->cellsPerAxis+2) + (z+1) * (k->cellsPerAxis+2)*(k->cellsPerAxis+2);
                        const int voxelInImage     = x+ y * k->cellsPerAxis + z * k->cellsPerAxis* k->cellsPerAxis;
                        
                        for(int u=0; u<(k->unknowns + k->auxiliary); u++){
                            const int locationInPreimage = voxelInPreImage*(k->unknowns+k->auxiliary) + u;
                            const int locationInImage = voxelInImage*(k->unknowns+k->auxiliary) + u;
                            outVec[locationInImage]=tc.input[locationInPreimage];
                        }
                    }
                }
        } 
    }else{
        std::cout << "Illegal dim: "<< k->dim << "\n";
        assert(false);
    }
}


bool isClose(double a, double b){
    return std::abs(a-b)<0.00000001;
}


bool testKernel(const Kernel* k){
    int outputVectorLength = pow(k->cellsPerAxis, k->dim) * (k->unknowns + k->auxiliary);

    double* outVec = (double*) malloc(outputVectorLength*sizeof(double));

    const int lfw = 20;
    const int rfw = 10;
    int passed = 0;
    
    std::ostringstream detailed_report;
    detailed_report << "Runing test cases...\n";
    for(const auto& tc: k->testCases) {
        detailed_report << std::setw(lfw) << std::left << tc.name;
        load_out_vector(k, tc, outVec);
        

        k->runKernel(&tc, outVec);

        bool allClose = true;
        for(int i=0; i<outputVectorLength; i++){
            if(!isClose(outVec[i], tc.expected[i])){
                //std::cout << "[" << i <<"] Expected: " << tc.expected[i] << " Recived: "<< outVec[i]<<std::endl;
            }
            allClose &= isClose(outVec[i], tc.expected[i]);
        }

        detailed_report  << std::setw(rfw) << std::right;
        if (allClose){
        detailed_report << "✔️\n"; }
         else{
             detailed_report << "❌\n";
         }
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
        if(passed!=0){
            std::cout << detailed_report.str();
        }
    }

    free(outVec);
    return passed == k->testCases.size();
}