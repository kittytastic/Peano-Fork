#include "TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5.h"
/******************* Run Peak ********************/
#include  <iomanip>
#include <iostream>
#include <fstream>
#include <string>

const int TARGET_TEST_CASES = 10;
int current_test_case = 0;

bool hasInitialised = false;

std::string format_vector(const double* vec, int length, int precision){
  std::ostringstream out_str;
    for(int i=0; i<length; i++){
            
        out_str <<std::scientific<< std::setprecision(precision)<< vec[i];
        if (i<length-1){
            out_str<< ", ";
        }
    }
    return out_str.str();
}

void print_vector(const double* vec, int length){
      std::cout << "[" << format_vector(vec, length, 2) << "]" << std::endl;
}

std::ofstream testCaseFile;

void initialise(){
  testCaseFile.open ("testCases.txt");
}

double target_num = 0.1;
void should_print(const double* Qin, const double *Qout, tarch::la::Vector<2, double> pos, tarch::la::Vector<2, double> size, double t, double ts, bool* shouldPrint, bool* shouldKill){
  if(Qin[4]>target_num){
    target_num+=0.02;
    *shouldPrint=true;
    *shouldKill=current_test_case>=TARGET_TEST_CASES;
  }
}


void preprint(const double* Qin, const double *Qout, tarch::la::Vector<2, double> pos, tarch::la::Vector<2, double> size, double t, double ts){
      std::cout << "Cell Pos: ("<< pos(0) << ", "<<  pos(1)<< ")\n";
      std::cout << "Cell size: ("<< size(0) << ", "<<  size(1)<< ")\n";
      std::cout << "Time: " << t << "\n";
      std::cout << "dt: " << ts << "\n"; 
        
      print_vector(Qin, 5*5*4);
}

void postprint(const double* Qin, const double *Qout, tarch::la::Vector<2, double> pos, tarch::la::Vector<2, double> size, double t, double ts){
  
  std::string in_vec = format_vector(Qin, 5*5*4, 17);
  std::string out_vec = format_vector(Qout, 3*3*4, 17);
  
  testCaseFile << std::setprecision(17) << std::scientific;
  testCaseFile << "\ndouble* euler_in_vec"<<current_test_case<<"[5*5*4]={"<<in_vec<<"};\n";
  testCaseFile << "\ndouble* euler_out_vec"<<current_test_case<<"[3*3*4]={"<<out_vec<<"};\n";

  testCaseFile << std::setprecision(17) << std::scientific << "\n\ntestCase eulerTC_"<<current_test_case<<" = testCase(\"TC "<<current_test_case<<"\", "<< pos(0) <<", "<< pos(1) << ", " << size(0) << ", " << size(1) << ", " << t<< ", "<<ts << ", euler_in_vec"<<current_test_case<<", euler_out_vec"<<current_test_case<<")\n\n";
  std::cout << std::setprecision(17)<< "\n\ntestCase eulerTC_"<<current_test_case<<"testCase(\"unnamed\", "<< pos(0) <<", "<< pos(1) << ", " << size(0) << ", " << size(1) << ", " << t<< ", "<<ts << ", euler_in_vec"<<current_test_case<<", euler_out_vec"<<current_test_case<<")\n\n";

  current_test_case++;
}

void finalise(){
  testCaseFile<< "\n\n\nstd::vector<testCase> k2_tests = {";
  for(int i=0; i<=TARGET_TEST_CASES; i++){
    testCaseFile << "eulerTC_"<<i;
    if(i<TARGET_TEST_CASES){
      testCaseFile << ", ";
    }
  }
  testCaseFile <<"};";
  testCaseFile.close();
  assert(false);
}

/**********************************************************/
tarch::logging::Log project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::_log( "project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5");





project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5(int treeNumber) {
  _treeNumber = treeNumber;
}


project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::~TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5() {
// @todo Should be overwritten
}


std::vector< peano4::grid::GridControlEvent > project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::getGridControlEvents() const {
return std::vector< peano4::grid::GridControlEvent >();
}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::beginTraversal(
      ) {


}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::endTraversal(
      ) {


}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::explore_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::explore_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::explore_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::explore_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::explore_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::explore_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::explore_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::explore_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::explore_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::explore_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::explore_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::explore_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::explore_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::explore_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::explore_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::explore_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchFaceFirstTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::explore_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::explore_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::explore_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::explore_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchFaceLastTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::explore_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::explore_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::explore_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::explore_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchCellFirstTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {

  fineGridCelleuler2DCellLabel.setHasUpdated(false);

  auto serialisePatchIndex = [](tarch::la::Vector<Dimensions,int> overlapCell, int normal) {
    int base   = 1;
    int result = 0;
    for (int d=0; d<Dimensions; d++) {
      result += overlapCell(d) * base;
      if (d==normal) {
        base *= 1.0*2;
      }
      else {
        base *= 3;
      }
    }
    return result;
  };
  
  if (not marker.willBeRefined() and not marker.hasBeenRefined()) {
    logTraceInWith1Argument( "touchCellFirstTime(...)", marker.toString() );

    
    #if Dimensions==2
    double reconstructedPatch[100];
    #elif Dimensions==3
    double reconstructedPatch[500];
    #endif


    //
    // Loop over original patch (k) and copy stuff over.
    //
    dfor(sourceCell,3) {
      tarch::la::Vector<Dimensions,int> destinationCell = sourceCell + tarch::la::Vector<Dimensions,int>(1.0);
      int sourceCellSerialised       = peano4::utils::dLinearised(sourceCell,3);
      int destinationCellSerialised  = peano4::utils::dLinearised(destinationCell,3 + 2*1.0);
      for (int j=0; j<4; j++) {
        reconstructedPatch[destinationCellSerialised*4+j] = fineGridCelleuler2DQ.value[ sourceCellSerialised*4+j ];
        nonCriticalAssertion4( reconstructedPatch[destinationCellSerialised*4+j]==reconstructedPatch[destinationCellSerialised*4+j], sourceCell, j, _treeNumber, marker.toString() );
      }
    }

    //
    // Bring in the auxiliary patches, i.e. befill halo
    //
    for(int d=0; d<Dimensions; d++) {
      logTraceInWith1Argument( "touchCellFirstTime(...)::loopOverFace", d );
      //
      // d-loop over all dimensions except d. The vector k's entry d is set
      // to 0. We start with the left/bottom face, i.e. the one closer to the 
      // coordinate system's origin.
      //
      dfore(k,3,d,0) {
        for (int i=0; i<1.0; i++) {
          tarch::la::Vector<Dimensions,int> destinationCell = k + tarch::la::Vector<Dimensions,int>(1.0);
          tarch::la::Vector<Dimensions,int> sourceCell      = k;
          destinationCell(d) = i;
          sourceCell(d)      = i;
          
          int destinationCellSerialised   = peano4::utils::dLinearised(destinationCell,3 + 2*1.0);
          int sourceCellSerialised        = serialisePatchIndex(sourceCell,d);

          for (int j=0; j<4; j++) {
            reconstructedPatch[ destinationCellSerialised*4+j ] = fineGridFaceseuler2DQNew(d).value[ sourceCellSerialised*4+j ];
            assertion7( 
              true or 
              reconstructedPatch[ destinationCellSerialised*4+j ]==reconstructedPatch[ destinationCellSerialised*4+j ], 
              sourceCell, destinationCell, j, d, marker.toString(), _treeNumber, marker.toString()
            );
          }

          destinationCell(d) = i+3+1.0;
          sourceCell(d)      = i+1.0;

          destinationCellSerialised   = peano4::utils::dLinearised(destinationCell,3 + 2*1.0);
          sourceCellSerialised        = serialisePatchIndex(sourceCell,d);
          for (int j=0; j<4; j++) {
            reconstructedPatch[ destinationCellSerialised*4+j ] = fineGridFaceseuler2DQNew(d+Dimensions).value[ sourceCellSerialised*4+j ];
            assertion7( 
              true or 
              reconstructedPatch[ destinationCellSerialised*4+j ]==reconstructedPatch[ destinationCellSerialised*4+j ], 
              sourceCell, destinationCell, j, d, marker.toString(), _treeNumber, marker.toString()
            );
          }
        }
      }
      logTraceOut( "touchCellFirstTime(...)::loopOverFace" );
    }

    double* targetPatch = fineGridCelleuler2DQ.value;
    
    double cellTimeStepSize = -1.0;
    double cellTimeStamp    = -1.0;
     
    
    
  cellTimeStepSize = repositories::InstanceOfeuler2D.getTimeStepSize();
  cellTimeStamp    = fineGridCelleuler2DCellLabel.getTimeStamp();
    
    assertion2( tarch::la::greaterEquals( cellTimeStepSize, 0.0 ), cellTimeStepSize, cellTimeStamp );
    assertion2( tarch::la::greaterEquals( cellTimeStamp, 0.0 ), cellTimeStepSize, cellTimeStamp );

    const double usedTimeStepSize = cellTimeStepSize;

    ::exahype2::fv::validatePatch(
        reconstructedPatch,
        4,
        0,
        3,
        1, // halo
        std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): " + marker.toString()
    ); // previous time step has to be valid
  
    ::exahype2::fv::copyPatch(
        reconstructedPatch,
        targetPatch,
        4,
        0,
        3,
        1 // halo size
    );


    if(!hasInitialised){
      initialise();
      hasInitialised=true;
    }
    bool print_round = false;
    bool kill_run = false;
    should_print(reconstructedPatch, targetPatch, marker.x(), marker.h(), cellTimeStamp, cellTimeStepSize, &print_round, &kill_run);

    if(print_round){
     preprint(reconstructedPatch, targetPatch, marker.x(), marker.h(), cellTimeStamp, cellTimeStepSize); 
    }
    
    #if Dimensions==2
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS2d(
    #else
    ::exahype2::fv::applySplit1DRiemannToPatch_Overlap1AoS3d(
    #endif
    
        [&](
          const double * __restrict__                  QL,
          const double * __restrict__                  QR,
          const tarch::la::Vector<Dimensions,double>&  x,
          double                                       dx,
          double                                       t,
          double                                       dt,
          int                                          normal,
          double                                       FL[],
          double                                       FR[]
        ) -> void {
          
        ::exahype2::fv::splitRusanov1d(
          [] (
            const double * __restrict__                  Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double                                       F[]
          ) -> void {
            
            repositories::InstanceOfeuler2D.flux( Q, faceCentre, volumeH, t, normal, F );
            
          },
          [] (
            const double * __restrict__                  Q,
            const double * __restrict__                  deltaQ,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double                                       BgradQ[]
          ) -> void {
            
            std::fill_n(BgradQ,4,0.0);
            
          },
          [] (
            const double * __restrict__                  Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal
          ) -> double {
            return repositories::InstanceOfeuler2D.maxEigenvalue( Q, faceCentre, volumeH, t, normal);
          },
          QL, QR, x, dx, t, dt, normal,
          4,
          0,
          FL,FR,
          
          false,
          
          
          true
          
        );
        },
        [&](
          const double * __restrict__                  Q,
          const tarch::la::Vector<Dimensions,double>&  x,
          double                                       dx,
          double                                       t,
          double                                       dt,
          double * __restrict__                        S
        ) -> void {
          
  std::fill_n(S,4,0.0);
        },
        marker.x(),
        marker.h(),
        cellTimeStamp,
        cellTimeStepSize,
        3,
        4,
        0,
        reconstructedPatch,
        targetPatch
    );
  
    if(print_round){
      postprint(reconstructedPatch, targetPatch, marker.x(), marker.h(), cellTimeStamp, cellTimeStepSize); 
      if(kill_run){finalise();}
    }
    
    fineGridCelleuler2DCellLabel.setTimeStamp(cellTimeStamp + usedTimeStepSize);
    fineGridCelleuler2DCellLabel.setTimeStepSize(cellTimeStepSize);
    fineGridCelleuler2DCellLabel.setHasUpdated(true);
    
    repositories::InstanceOfeuler2D.update(cellTimeStepSize, cellTimeStamp + usedTimeStepSize, marker.h()(0) );

    ::exahype2::fv::validatePatch(
        targetPatch,
        4,
        0,
        3,
        0, // halo
        std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): " + marker.toString()
    ); // outcome has to be valid
  
    
    

    logTraceOut( "touchCellFirstTime(...)" );
  }

  else if (not marker.willBeRefined() and not marker.hasBeenRefined()) {
    double cellTimeStepSize = -1.0;
    double cellTimeStamp    = -1.0;
     
    
  cellTimeStepSize = repositories::InstanceOfeuler2D.getTimeStepSize();
  cellTimeStamp    = fineGridCelleuler2DCellLabel.getTimeStamp();
    
    assertion2( tarch::la::greaterEquals( cellTimeStepSize, 0.0 ), cellTimeStepSize, cellTimeStamp );
    assertion2( tarch::la::greaterEquals( cellTimeStamp, 0.0 ), cellTimeStepSize, cellTimeStamp );

    repositories::InstanceOfeuler2D.update(0.0, cellTimeStamp, marker.h()(0) );
  }

}


void project::explore_2d_euler::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchCellLastTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::explore_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::explore_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::explore_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel) {


}


