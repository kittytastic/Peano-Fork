#include "euler2DQUpdate.h"



#include "../repositories/SolverRepository.h"



project::base_2d_euler::facedata::euler2DQUpdate::euler2DQUpdate() {
}


project::base_2d_euler::facedata::euler2DQUpdate::euler2DQUpdate(const euler2DQUpdate& other) {
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


project::base_2d_euler::facedata::euler2DQUpdate& project::base_2d_euler::facedata::euler2DQUpdate::operator=(const euler2DQUpdate& other) {
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


std::string project::base_2d_euler::facedata::euler2DQUpdate::toString() const {
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

void project::base_2d_euler::facedata::euler2DQUpdate::setDebugX( const tarch::la::Vector<Dimensions,double>& data ) {
  _debugX = data;
}


void project::base_2d_euler::facedata::euler2DQUpdate::setDebugH( const tarch::la::Vector<Dimensions,double>& data ) {
  _debugH = data;
}


tarch::la::Vector<Dimensions,double> project::base_2d_euler::facedata::euler2DQUpdate::getDebugX() const {
  return _debugX;
}


tarch::la::Vector<Dimensions,double> project::base_2d_euler::facedata::euler2DQUpdate::getDebugH() const {
  return _debugH;
}
#endif


void project::base_2d_euler::facedata::euler2DQUpdate::merge(const euler2DQUpdate& neighbour, const peano4::datamanagement::FaceMarker& marker) {
  
}


bool project::base_2d_euler::facedata::euler2DQUpdate::send(const peano4::datamanagement::FaceMarker& marker) {
  return false;
}


bool project::base_2d_euler::facedata::euler2DQUpdate::receiveAndMerge(const peano4::datamanagement::FaceMarker& marker) {
  return false;
}


bool project::base_2d_euler::facedata::euler2DQUpdate::storePersistently(const peano4::datamanagement::FaceMarker& marker) {
  return false;
}


bool project::base_2d_euler::facedata::euler2DQUpdate::loadPersistently(const peano4::datamanagement::FaceMarker& marker) {
  return false;
}
#ifdef Parallel
void project::base_2d_euler::facedata::euler2DQUpdate::initDatatype() {
  project::base_2d_euler::facedata::euler2DQUpdate  instances[2];
 
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


void project::base_2d_euler::facedata::euler2DQUpdate::shutdownDatatype() {
  MPI_Type_free( &Datatype );
}
  

MPI_Datatype   project::base_2d_euler::facedata::euler2DQUpdate::Datatype;
#endif