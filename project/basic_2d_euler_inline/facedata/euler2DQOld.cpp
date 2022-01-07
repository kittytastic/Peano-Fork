#include "euler2DQOld.h"



#include "peano4/utils/Loop.h"
#include "repositories/SolverRepository.h" 

#include "../repositories/SolverRepository.h"



project::base_2d_euler_inline::facedata::euler2DQOld::euler2DQOld() {
}


project::base_2d_euler_inline::facedata::euler2DQOld::euler2DQOld(const euler2DQOld& other) {
  #if PeanoDebug>=1
  _debugX = other._debugX;
  _debugH = other._debugH;
  #endif

  #if Dimensions==2
  std::copy(other.value, other.value+24,value);
  #else
  std::copy(other.value, other.value+72,value);
  #endif
}


project::base_2d_euler_inline::facedata::euler2DQOld& project::base_2d_euler_inline::facedata::euler2DQOld::operator=(const euler2DQOld& other) {
  #if PeanoDebug>=1
  _debugX = other._debugX;
  _debugH = other._debugH;
  #endif
  
  #if Dimensions==2
  std::copy(other.value, other.value+24,value);
  #else
  std::copy(other.value, other.value+72,value);
  #endif
  return *this;
}


std::string project::base_2d_euler_inline::facedata::euler2DQOld::toString() const {
  std::ostringstream result;
  result << "(";
  #if PeanoDebug>=1
  result << "x=" << _debugX;
  result << ",";
  result << "h=" << _debugH;
  #endif
  result << ")";
  return result.str();
}


#if PeanoDebug>=1

void project::base_2d_euler_inline::facedata::euler2DQOld::setDebugX( const tarch::la::Vector<Dimensions,double>& data ) {
  _debugX = data;
}


void project::base_2d_euler_inline::facedata::euler2DQOld::setDebugH( const tarch::la::Vector<Dimensions,double>& data ) {
  _debugH = data;
}


tarch::la::Vector<Dimensions,double> project::base_2d_euler_inline::facedata::euler2DQOld::getDebugX() const {
  return _debugX;
}


tarch::la::Vector<Dimensions,double> project::base_2d_euler_inline::facedata::euler2DQOld::getDebugH() const {
  return _debugH;
}
#endif


void project::base_2d_euler_inline::facedata::euler2DQOld::merge(const euler2DQOld& neighbour, const peano4::datamanagement::FaceMarker& marker) {
  
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
  

  const int faceNormal = marker.getSelectedFaceNumber() % Dimensions;
  dfore(i,3,faceNormal,0) {
    for (int j=0; j<1.0; j++) {
      tarch::la::Vector<Dimensions,int> volume = i;
      volume(faceNormal) += marker.outerNormal()(faceNormal)>0 ? j + 1.0 : j;
      
      int volumeSerialised = serialisePatchIndex(volume, faceNormal);
      for (int k=0; k<4; k++) {
        assertion4( 
          neighbour.value[volumeSerialised*4+k]==neighbour.value[volumeSerialised*4+k],
          k, 4,
          volume,
          marker.toString()
        );
      
        value[volumeSerialised*4+k] = neighbour.value[volumeSerialised*4+k];
      
      }
      
      // This should be non-critical assertion, but this assertion is only
      // generically available in ExaHyPE 2, so I comment the assertion out
      // here.
      // assertion(value[volumeSerialised]==value[volumeSerialised]);
    }
  }

}


bool project::base_2d_euler_inline::facedata::euler2DQOld::send(const peano4::datamanagement::FaceMarker& marker) {
  return (repositories::InstanceOfeuler2D.getSolverState()==euler2D::SolverState::GridInitialisation);
}


bool project::base_2d_euler_inline::facedata::euler2DQOld::receiveAndMerge(const peano4::datamanagement::FaceMarker& marker) {
  return (repositories::InstanceOfeuler2D.getSolverState()==euler2D::SolverState::TimeStepAfterGridInitialisation or repositories::InstanceOfeuler2D.getSolverState()==euler2D::SolverState::PlottingAfterGridInitialisation);
}


bool project::base_2d_euler_inline::facedata::euler2DQOld::storePersistently(const peano4::datamanagement::FaceMarker& marker) {
  return not marker.willBeRefined() and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridConstruction;
}


bool project::base_2d_euler_inline::facedata::euler2DQOld::loadPersistently(const peano4::datamanagement::FaceMarker& marker) {
  return not marker.hasBeenRefined() and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridConstruction and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridInitialisation;
}
#ifdef Parallel
void project::base_2d_euler_inline::facedata::euler2DQOld::initDatatype() {
  project::base_2d_euler_inline::facedata::euler2DQOld  instances[2];
 
  #if PeanoDebug>=1
    MPI_Datatype subtypes[] = { MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE };

    #if Dimensions==2
    int blocklen[] = { Dimensions, Dimensions, 24 };
    #else
    int blocklen[] = { Dimensions, Dimensions, 72 };
    #endif

    const int NumberOfAttributes = 3;
  #else   
    MPI_Datatype subtypes[] = { MPI_DOUBLE };
    
    #if Dimensions==2
    int blocklen[] = { 24 };
    #else
    int blocklen[] = { 72 };
    #endif
  
    const int NumberOfAttributes = 1;  
  #endif

  MPI_Aint  baseFirstInstance;
  MPI_Aint  baseSecondInstance;
  MPI_Get_address( &instances[0], &baseFirstInstance );
  MPI_Get_address( &instances[1], &baseSecondInstance );
  MPI_Aint  disp[ NumberOfAttributes ];
  int       currentAddress = 0;
  #if PeanoDebug>=1
  MPI_Get_address( &(instances[0]._debugX.data()[0]), &disp[currentAddress] );
  currentAddress++;
  MPI_Get_address( &(instances[0]._debugH.data()[0]), &disp[currentAddress] );
  currentAddress++;
  #endif
  MPI_Get_address( &(instances[0].value), &disp[currentAddress] );
  currentAddress++;

  MPI_Aint offset = disp[0] - baseFirstInstance;
  MPI_Aint extent = baseSecondInstance - baseFirstInstance - offset;
  for (int i=NumberOfAttributes-1; i>=0; i--) {
    disp[i] = disp[i] - disp[0];
  }

  int errorCode = 0; 
  MPI_Datatype tmpType; 
  errorCode += MPI_Type_create_struct( NumberOfAttributes, blocklen, disp, subtypes, &tmpType );
  errorCode += MPI_Type_create_resized( tmpType, offset, extent, &Datatype );
  errorCode += MPI_Type_commit( &Datatype );
  errorCode += MPI_Type_free( &tmpType );
  if (errorCode) std::cerr << "error constructing MPI datatype in " << __FILE__ << ":" << __LINE__ << std::endl;
}


void project::base_2d_euler_inline::facedata::euler2DQOld::shutdownDatatype() {
  MPI_Type_free( &Datatype );
}
  

MPI_Datatype   project::base_2d_euler_inline::facedata::euler2DQOld::Datatype;
#endif