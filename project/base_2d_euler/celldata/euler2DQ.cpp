#include "euler2DQ.h"



#include "../repositories/SolverRepository.h"



project::base_2d_euler::celldata::euler2DQ::euler2DQ() {
}


project::base_2d_euler::celldata::euler2DQ::euler2DQ(const euler2DQ& other) {
  #if PeanoDebug>=1
  _debugX = other._debugX;
  _debugH = other._debugH;
  #endif

  #if Dimensions==2
  std::copy(other.value, other.value+36,value);
  #else
  std::copy(other.value, other.value+108,value);
  #endif
}


project::base_2d_euler::celldata::euler2DQ& project::base_2d_euler::celldata::euler2DQ::operator=(const euler2DQ& other) {
  #if PeanoDebug>=1
  _debugX = other._debugX;
  _debugH = other._debugH;
  #endif
  
  #if Dimensions==2
  std::copy(other.value, other.value+36,value);
  #else
  std::copy(other.value, other.value+108,value);
  #endif
  return *this;
}


std::string project::base_2d_euler::celldata::euler2DQ::toString() const {
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

void project::base_2d_euler::celldata::euler2DQ::setDebugX( const tarch::la::Vector<Dimensions,double>& data ) {
  _debugX = data;
}


void project::base_2d_euler::celldata::euler2DQ::setDebugH( const tarch::la::Vector<Dimensions,double>& data ) {
  _debugH = data;
}


tarch::la::Vector<Dimensions,double> project::base_2d_euler::celldata::euler2DQ::getDebugX() const {
  return _debugX;
}


tarch::la::Vector<Dimensions,double> project::base_2d_euler::celldata::euler2DQ::getDebugH() const {
  return _debugH;
}
#endif


void project::base_2d_euler::celldata::euler2DQ::merge(const euler2DQ& neighbour, const peano4::datamanagement::CellMarker& marker) {
  
}


bool project::base_2d_euler::celldata::euler2DQ::send(const peano4::datamanagement::CellMarker& marker) {
  return true;
}


bool project::base_2d_euler::celldata::euler2DQ::receiveAndMerge(const peano4::datamanagement::CellMarker& marker) {
  return true;
}


bool project::base_2d_euler::celldata::euler2DQ::storePersistently(const peano4::datamanagement::CellMarker& marker) {
  return not marker.willBeRefined() and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridConstruction;
}


bool project::base_2d_euler::celldata::euler2DQ::loadPersistently(const peano4::datamanagement::CellMarker& marker) {
  return not marker.hasBeenRefined() and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridConstruction and repositories::InstanceOfeuler2D.getSolverState()!=euler2D::SolverState::GridInitialisation;
}
#ifdef Parallel
void project::base_2d_euler::celldata::euler2DQ::initDatatype() {
  project::base_2d_euler::celldata::euler2DQ  instances[2];
 
  #if PeanoDebug>=1
    MPI_Datatype subtypes[] = { MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE };

    #if Dimensions==2
    int blocklen[] = { Dimensions, Dimensions, 36 };
    #else
    int blocklen[] = { Dimensions, Dimensions, 108 };
    #endif

    const int NumberOfAttributes = 3;
  #else   
    MPI_Datatype subtypes[] = { MPI_DOUBLE };
    
    #if Dimensions==2
    int blocklen[] = { 36 };
    #else
    int blocklen[] = { 108 };
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


void project::base_2d_euler::celldata::euler2DQ::shutdownDatatype() {
  MPI_Type_free( &Datatype );
}
  

MPI_Datatype   project::base_2d_euler::celldata::euler2DQ::Datatype;
#endif