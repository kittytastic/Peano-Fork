#include "TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5.h"
/******************* Run Peak ********************/
#include  <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#define DO_TEST_PRINT 

const int TARGET_TEST_CASES = 10;
const int p_patchSize = 3;
const int p_QVars = 4;
const int p_inVars = (2+p_patchSize)*(2+p_patchSize)*p_QVars;
const int p_outVars = (p_patchSize)*(p_patchSize)*p_QVars;
int current_test_case = 0;
std::string problem_name = "swe";

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

double target_num = 1.0;
void should_print(const double* Qin, const double *Qout, tarch::la::Vector<2, double> pos, tarch::la::Vector<2, double> size, double t, double ts, bool* shouldPrint, bool* shouldKill){
  if(Qin[4]>target_num){
    target_num+=0.005;
    *shouldPrint=true;
    *shouldKill=current_test_case>=TARGET_TEST_CASES;
  }
}


void preprint(const double* Qin, const double *Qout, tarch::la::Vector<2, double> pos, tarch::la::Vector<2, double> size, double t, double ts){
      std::cout << "\n\nCell Pos: ("<< pos(0) << ", "<<  pos(1)<< ")\n";
      std::cout << "Cell size: ("<< size(0) << ", "<<  size(1)<< ")\n";
      std::cout << "Time: " << t << "\n";
      std::cout << "dt: " << ts << "\n"; 
}

void postprint(const double* Qin, const double *Qout, tarch::la::Vector<2, double> pos, tarch::la::Vector<2, double> size, double t, double ts){
  
  std::string in_vec = format_vector(Qin, p_inVars, 17);
  std::string out_vec = format_vector(Qout, 3*3*4, 17);
  
  testCaseFile << std::setprecision(17) << std::scientific;
  testCaseFile << "\ndouble "<<problem_name<<"_in_vec"<<current_test_case<<"["<<p_inVars<<"]={"<<in_vec<<"};\n";
  testCaseFile << "\ndouble "<<problem_name<<"_out_vec"<<current_test_case<<"["<<p_outVars<<"]={"<<out_vec<<"};\n";

  testCaseFile << std::setprecision(17) << std::scientific << 
  "\n\ntestCase "<<problem_name<<"TC_"<<current_test_case<<" = testCase(\"TC "<<current_test_case<<"\", "<< pos(0) <<", "<< pos(1) << ", " << size(0) << ", " << size(1) << ", " << t<< ", "<<ts << ", "<< problem_name <<"_in_vec"<<current_test_case<<", "<<problem_name<<"_out_vec"<<current_test_case<<");\n\n";
  
  
  std::cout << std::setprecision(17)<< "TEST CASE "<<current_test_case<< "/"<<TARGET_TEST_CASES<<"\n\n";

  current_test_case++;
}

void finalise(){
  testCaseFile<< "\n\n\nstd::vector<testCase> "<<problem_name<<"_2d_test_cases = {";
  for(int i=0; i<=TARGET_TEST_CASES; i++){
    testCaseFile << problem_name <<"TC_"<<i;
    if(i<TARGET_TEST_CASES){
      testCaseFile << ", ";
    }
  }
  testCaseFile <<"};";
  testCaseFile.close();
  assert(false);
}

/**********************************************************/

tarch::logging::Log project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::_log( "project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5");





project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5(int treeNumber) {
  _treeNumber = treeNumber;
}


project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::~TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5() {
// @todo Should be overwritten
}


std::vector< peano4::grid::GridControlEvent > project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::getGridControlEvents() const {
return std::vector< peano4::grid::GridControlEvent >();
}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::beginTraversal(
      ) {


}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::endTraversal(
      ) {


}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::swe::facedata::sweQOld& fineGridFacesweQOld,
      project::swe::facedata::sweQNew& fineGridFacesweQNew,
      project::swe::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::swe::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::swe::celldata::sweQ& coarseGridCellsweQ,
      project::swe::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::swe::facedata::sweQOld& fineGridFacesweQOld,
      project::swe::facedata::sweQNew& fineGridFacesweQNew,
      project::swe::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::swe::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::swe::celldata::sweQ& coarseGridCellsweQ,
      project::swe::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::swe::facedata::sweQOld& fineGridFacesweQOld,
      project::swe::facedata::sweQNew& fineGridFacesweQNew,
      project::swe::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::swe::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::swe::celldata::sweQ& coarseGridCellsweQ,
      project::swe::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::swe::facedata::sweQOld& fineGridFacesweQOld,
      project::swe::facedata::sweQNew& fineGridFacesweQNew,
      project::swe::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::swe::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::swe::celldata::sweQ& coarseGridCellsweQ,
      project::swe::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchFaceFirstTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::swe::facedata::sweQOld& fineGridFacesweQOld,
      project::swe::facedata::sweQNew& fineGridFacesweQNew,
      project::swe::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::swe::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::swe::celldata::sweQ& coarseGridCellsweQ,
      project::swe::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchFaceLastTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::swe::facedata::sweQOld& fineGridFacesweQOld,
      project::swe::facedata::sweQNew& fineGridFacesweQNew,
      project::swe::facedata::sweQUpdate& fineGridFacesweQUpdate,
      project::swe::facedata::sweFaceLabel& fineGridFacesweFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::swe::celldata::sweQ& coarseGridCellsweQ,
      project::swe::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::createCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> fineGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> fineGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> fineGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> fineGridFacessweFaceLabel,
      project::swe::celldata::sweQ& fineGridCellsweQ,
      project::swe::celldata::sweCellLabel& fineGridCellsweCellLabel,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::swe::celldata::sweQ& coarseGridCellsweQ,
      project::swe::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::destroyCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> fineGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> fineGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> fineGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> fineGridFacessweFaceLabel,
      project::swe::celldata::sweQ& fineGridCellsweQ,
      project::swe::celldata::sweCellLabel& fineGridCellsweCellLabel,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::swe::celldata::sweQ& coarseGridCellsweQ,
      project::swe::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchCellFirstTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> fineGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> fineGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> fineGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> fineGridFacessweFaceLabel,
      project::swe::celldata::sweQ& fineGridCellsweQ,
      project::swe::celldata::sweCellLabel& fineGridCellsweCellLabel,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::swe::celldata::sweQ& coarseGridCellsweQ,
      project::swe::celldata::sweCellLabel& coarseGridCellsweCellLabel) {

  fineGridCellsweCellLabel.setHasUpdated(false);

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
        reconstructedPatch[destinationCellSerialised*4+j] = fineGridCellsweQ.value[ sourceCellSerialised*4+j ];
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
            reconstructedPatch[ destinationCellSerialised*4+j ] = fineGridFacessweQNew(d).value[ sourceCellSerialised*4+j ];
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
            reconstructedPatch[ destinationCellSerialised*4+j ] = fineGridFacessweQNew(d+Dimensions).value[ sourceCellSerialised*4+j ];
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

    double* targetPatch = fineGridCellsweQ.value;
    
    double cellTimeStepSize = -1.0;
    double cellTimeStamp    = -1.0;
     
    
    
  cellTimeStepSize = repositories::InstanceOfswe.getAdmissibleTimeStepSize();
  cellTimeStamp    = fineGridCellsweCellLabel.getTimeStamp();
    
    assertion2( tarch::la::greaterEquals( cellTimeStepSize, 0.0 ), cellTimeStepSize, cellTimeStamp );
    assertion2( tarch::la::greaterEquals( cellTimeStamp, 0.0 ), cellTimeStepSize, cellTimeStamp );

    const double usedTimeStepSize = cellTimeStepSize;

    ::exahype2::fv::validatePatch(
        reconstructedPatch,
        3,
        1,
        3,
        1, // halo
        std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): " + marker.toString()
    ); // previous time step has to be valid
  
    ::exahype2::fv::copyPatch(
        reconstructedPatch,
        targetPatch,
        3,
        1,
        3,
        1 // halo size
    );

    #ifdef DO_TEST_PRINT
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
    #endif
    
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
            
            repositories::InstanceOfswe.flux( Q, faceCentre, volumeH, t, normal, F );
            
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
            
            repositories::InstanceOfswe.nonconservativeProduct( Q, deltaQ, faceCentre, volumeH, t, normal, BgradQ );
            
          },
          [] (
            const double * __restrict__                  Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal
          ) -> double {
            return repositories::InstanceOfswe.maxEigenvalue( Q, faceCentre, volumeH, t, normal);
          },
          QL, QR, x, dx, t, dt, normal,
          3,
          1,
          FL,FR,
          
          false,
          
          
          false
          
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
          
  std::fill_n(S,3,0.0);
        },
        marker.x(),
        marker.h(),
        cellTimeStamp,
        cellTimeStepSize,
        3,
        3,
        1,
        reconstructedPatch,
        targetPatch
    );
  
    
    const double maxEigenvalue = ::exahype2::fv::maxEigenvalue_AoS(
      [] (
        const double * __restrict__                  Q,
        const tarch::la::Vector<Dimensions,double>&  faceCentre,
        const tarch::la::Vector<Dimensions,double>&  volumeH,
        double                                       t,
        double                                       dt,
        int                                          normal
      ) -> double {
        return repositories::InstanceOfswe.maxEigenvalue( Q, faceCentre, volumeH, t, normal);
      },
      marker.x(),
      marker.h(),
      cellTimeStamp,
      cellTimeStepSize,
      3,
      3,
      1,
      targetPatch
    );
    
    #ifdef DO_TEST_PRINT
    if(print_round){
      postprint(reconstructedPatch, targetPatch, marker.x(), marker.h(), cellTimeStamp, cellTimeStepSize); 
      if(kill_run){finalise();}
    }
    #endif

    repositories::InstanceOfswe.setMaxEigenvalue( maxEigenvalue );  
    
    fineGridCellsweCellLabel.setTimeStamp(cellTimeStamp + usedTimeStepSize);
    fineGridCellsweCellLabel.setTimeStepSize(cellTimeStepSize);
    fineGridCellsweCellLabel.setHasUpdated(true);
    
    repositories::InstanceOfswe.update(cellTimeStepSize, cellTimeStamp + usedTimeStepSize, marker.h()(0) );

    ::exahype2::fv::validatePatch(
        targetPatch,
        3,
        1,
        3,
        0, // halo
        std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): " + marker.toString()
    ); // outcome has to be valid
  
    
    

    logTraceOut( "touchCellFirstTime(...)" );
  }

  else if (not marker.willBeRefined() and not marker.hasBeenRefined()) {
    double cellTimeStepSize = -1.0;
    double cellTimeStamp    = -1.0;
     
    
  cellTimeStepSize = repositories::InstanceOfswe.getAdmissibleTimeStepSize();
  cellTimeStamp    = fineGridCellsweCellLabel.getTimeStamp();
    
    assertion2( tarch::la::greaterEquals( cellTimeStepSize, 0.0 ), cellTimeStepSize, cellTimeStamp );
    assertion2( tarch::la::greaterEquals( cellTimeStamp, 0.0 ), cellTimeStepSize, cellTimeStamp );

    repositories::InstanceOfswe.update(0.0, cellTimeStamp, marker.h()(0) );
  }

}


void project::swe::observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5::touchCellLastTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> fineGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> fineGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> fineGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> fineGridFacessweFaceLabel,
      project::swe::celldata::sweQ& fineGridCellsweQ,
      project::swe::celldata::sweCellLabel& fineGridCellsweCellLabel,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQOld> coarseGridFacessweQOld,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQNew> coarseGridFacessweQNew,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweQUpdate> coarseGridFacessweQUpdate,
      peano4::datamanagement::FaceEnumerator<project::swe::facedata::sweFaceLabel> coarseGridFacessweFaceLabel,
      project::swe::celldata::sweQ& coarseGridCellsweQ,
      project::swe::celldata::sweCellLabel& coarseGridCellsweCellLabel) {


}


