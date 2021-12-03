#include "euler2DFaceLabel.h"



#include <sstream>
#include <algorithm>



project::base_2d_euler::facedata::euler2DFaceLabel::euler2DFaceLabel(tarch::la::Vector<Dimensions,double>  __debugX, tarch::la::Vector<Dimensions,double>  __debugH, bool  __Boundary, std::bitset<2>  __Updated, tarch::la::Vector<2,double>  __UpdatedTimeStamp, tarch::la::Vector<2,double>  __NewTimeStamp, tarch::la::Vector<2,double>  __OldTimeStamp):
    _debugX(__debugX)
  , _debugH(__debugH)
  , _Boundary(__Boundary)
  , _Updated(__Updated)
  , _UpdatedTimeStamp(__UpdatedTimeStamp)
  , _NewTimeStamp(__NewTimeStamp)
  , _OldTimeStamp(__OldTimeStamp)
  {}



std::string project::base_2d_euler::facedata::euler2DFaceLabel::toString() const {
  std::ostringstream out;
  out << "(";
  out << "debugX=" << _debugX;
  out << ","; 
  out << "debugH=" << _debugH;
  out << ","; 
  out << "Boundary=" << _Boundary;
  out << ","; 
  out << "Updated=" << _Updated;
  out << ","; 
  out << "UpdatedTimeStamp=" << _UpdatedTimeStamp;
  out << ","; 
  out << "NewTimeStamp=" << _NewTimeStamp;
  out << ","; 
  out << "OldTimeStamp=" << _OldTimeStamp;
  out << ")";
  return out.str();
}


tarch::la::Vector<Dimensions,double>   project::base_2d_euler::facedata::euler2DFaceLabel::getDebugX() const {
  return _debugX;
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setDebugX(const tarch::la::Vector<Dimensions,double>& value) {
  _debugX = value;
}


double   project::base_2d_euler::facedata::euler2DFaceLabel::getDebugX(int index) const {
  return _debugX(index);
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setDebugX(int index, double value) {
  _debugX(index) = value;
}


tarch::la::Vector<Dimensions,double>   project::base_2d_euler::facedata::euler2DFaceLabel::getDebugH() const {
  return _debugH;
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setDebugH(const tarch::la::Vector<Dimensions,double>& value) {
  _debugH = value;
}


double   project::base_2d_euler::facedata::euler2DFaceLabel::getDebugH(int index) const {
  return _debugH(index);
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setDebugH(int index, double value) {
  _debugH(index) = value;
}


bool   project::base_2d_euler::facedata::euler2DFaceLabel::getBoundary() const {
  return _Boundary;
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setBoundary(bool value) {
  _Boundary = value;
}


std::bitset<2>   project::base_2d_euler::facedata::euler2DFaceLabel::getUpdated() const {
  return _Updated;
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setUpdated(const std::bitset<2>&  value) {
  _Updated = value;
}


bool   project::base_2d_euler::facedata::euler2DFaceLabel::getUpdated(int index) const {
  return _Updated[index];
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setUpdated(int index, bool value) {
  _Updated[index] = value;
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::flipUpdated(int index) {
  _Updated.flip(index);
}


tarch::la::Vector<2,double>   project::base_2d_euler::facedata::euler2DFaceLabel::getUpdatedTimeStamp() const {
  return _UpdatedTimeStamp;
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setUpdatedTimeStamp(const tarch::la::Vector<2,double>& value) {
  _UpdatedTimeStamp = value;
}


double   project::base_2d_euler::facedata::euler2DFaceLabel::getUpdatedTimeStamp(int index) const {
  return _UpdatedTimeStamp(index);
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setUpdatedTimeStamp(int index, double value) {
  _UpdatedTimeStamp(index) = value;
}


tarch::la::Vector<2,double>   project::base_2d_euler::facedata::euler2DFaceLabel::getNewTimeStamp() const {
  return _NewTimeStamp;
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setNewTimeStamp(const tarch::la::Vector<2,double>& value) {
  _NewTimeStamp = value;
}


double   project::base_2d_euler::facedata::euler2DFaceLabel::getNewTimeStamp(int index) const {
  return _NewTimeStamp(index);
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setNewTimeStamp(int index, double value) {
  _NewTimeStamp(index) = value;
}


tarch::la::Vector<2,double>   project::base_2d_euler::facedata::euler2DFaceLabel::getOldTimeStamp() const {
  return _OldTimeStamp;
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setOldTimeStamp(const tarch::la::Vector<2,double>& value) {
  _OldTimeStamp = value;
}


double   project::base_2d_euler::facedata::euler2DFaceLabel::getOldTimeStamp(int index) const {
  return _OldTimeStamp(index);
}


void   project::base_2d_euler::facedata::euler2DFaceLabel::setOldTimeStamp(int index, double value) {
  _OldTimeStamp(index) = value;
}






#ifdef Parallel

MPI_Datatype project::base_2d_euler::facedata::euler2DFaceLabel::Datatype;

int project::base_2d_euler::facedata::euler2DFaceLabel::getSenderRank() const {
  return _senderDestinationRank;
}


void project::base_2d_euler::facedata::euler2DFaceLabel::initDatatype() {
  project::base_2d_euler::facedata::euler2DFaceLabel  instances[2];
    
  MPI_Datatype subtypes[] = { MPI_DOUBLE, MPI_DOUBLE, MPI_BYTE, MPI_UNSIGNED_LONG, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE };
    
  int blocklen[] = { Dimensions, Dimensions, 1, 1, 2, 2, 2 };

  const int NumberOfAttributes = 7;
    
  MPI_Aint  baseFirstInstance;
  MPI_Aint  baseSecondInstance;
  MPI_Get_address( &instances[0], &baseFirstInstance );
  MPI_Get_address( &instances[1], &baseSecondInstance );
  MPI_Aint  disp[ NumberOfAttributes ];
  int       currentAddress = 0;
  MPI_Get_address( &(instances[0]._debugX.data()[0]), &disp[currentAddress] );
  currentAddress++;
  MPI_Get_address( &(instances[0]._debugH.data()[0]), &disp[currentAddress] );
  currentAddress++;
  MPI_Get_address( &(instances[0]._Boundary), &disp[currentAddress] );
  currentAddress++;
  MPI_Get_address( &(instances[0]._Updated), &disp[currentAddress] );
  currentAddress++;
  MPI_Get_address( &(instances[0]._UpdatedTimeStamp.data()[0]), &disp[currentAddress] );
  currentAddress++;
  MPI_Get_address( &(instances[0]._NewTimeStamp.data()[0]), &disp[currentAddress] );
  currentAddress++;
  MPI_Get_address( &(instances[0]._OldTimeStamp.data()[0]), &disp[currentAddress] );
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


void project::base_2d_euler::facedata::euler2DFaceLabel::shutdownDatatype() {
  MPI_Type_free( &Datatype );
}


void project::base_2d_euler::facedata::euler2DFaceLabel::send(const project::base_2d_euler::facedata::euler2DFaceLabel& buffer, int destination, int tag, MPI_Comm communicator ) {
  MPI_Send( &buffer, 1, Datatype, destination, tag, communicator);
}


void project::base_2d_euler::facedata::euler2DFaceLabel::receive(project::base_2d_euler::facedata::euler2DFaceLabel& buffer, int source, int tag, MPI_Comm communicator ) {
  MPI_Status status;
  MPI_Recv( &buffer, 1, Datatype, source, tag, communicator, &status);
  buffer._senderDestinationRank = status.MPI_SOURCE;
}


void project::base_2d_euler::facedata::euler2DFaceLabel::send(const project::base_2d_euler::facedata::euler2DFaceLabel& buffer, int destination, int tag, std::function<void()> waitFunctor, MPI_Comm communicator ) {
  MPI_Request sendRequestHandle; 
  int         flag = 0; 
  MPI_Isend( &buffer, 1, Datatype, destination, tag, communicator, &sendRequestHandle ); 
  MPI_Test( &sendRequestHandle, &flag, MPI_STATUS_IGNORE ); 
  while (!flag) { 
    waitFunctor();
    MPI_Test( &sendRequestHandle, &flag, MPI_STATUS_IGNORE ); 
  }
}


void project::base_2d_euler::facedata::euler2DFaceLabel::receive(project::base_2d_euler::facedata::euler2DFaceLabel& buffer, int source, int tag, std::function<void()> waitFunctor, MPI_Comm communicator ) {   
  MPI_Status  status;
  MPI_Request receiveRequestHandle; 
  int         flag = 0; 
  MPI_Irecv( &buffer, 1, Datatype, source, tag, communicator, &receiveRequestHandle ); 
  MPI_Test( &receiveRequestHandle, &flag, &status ); 
  while (!flag) { 
    waitFunctor();
    MPI_Test( &receiveRequestHandle, &flag, &status ); 
  }
  buffer._senderDestinationRank = status.MPI_SOURCE;
}

#endif

#ifdef Parallel
void project::base_2d_euler::facedata::euler2DFaceLabel::sendAndPollDanglingMessages(const project::base_2d_euler::facedata::euler2DFaceLabel& message, int destination, int tag, MPI_Comm communicator ) {
  project::base_2d_euler::facedata::euler2DFaceLabel::send(
    message, destination, tag,
    [&]() {
      auto  timeOutWarning   = tarch::mpi::Rank::getInstance().getDeadlockWarningTimeStamp();
      auto timeOutShutdown  = tarch::mpi::Rank::getInstance().getDeadlockTimeOutTimeStamp();
      bool triggeredTimeoutWarning = false;
      if (
        tarch::mpi::Rank::getInstance().isTimeOutWarningEnabled() &&
        (std::chrono::system_clock::now()>timeOutWarning) &&
        (!triggeredTimeoutWarning)
      ) {
        tarch::mpi::Rank::getInstance().writeTimeOutWarning( "project::base_2d_euler::facedata::euler2DFaceLabel", "sendAndPollDanglingMessages()",destination, tag );
        triggeredTimeoutWarning = true;
      }
      if (
        tarch::mpi::Rank::getInstance().isTimeOutDeadlockEnabled() &&
        (std::chrono::system_clock::now()>timeOutShutdown)
      ) {
        tarch::mpi::Rank::getInstance().triggerDeadlockTimeOut( "project::base_2d_euler::facedata::euler2DFaceLabel", "sendAndPollDanglingMessages()", destination, tag );
      }
      tarch::services::ServiceRepository::getInstance().receiveDanglingMessages();
    },
    communicator
  );
}


void project::base_2d_euler::facedata::euler2DFaceLabel::receiveAndPollDanglingMessages(project::base_2d_euler::facedata::euler2DFaceLabel& message, int source, int tag, MPI_Comm communicator ) {
  project::base_2d_euler::facedata::euler2DFaceLabel::receive(
    message, source, tag,
    [&]() {
      auto timeOutWarning   = tarch::mpi::Rank::getInstance().getDeadlockWarningTimeStamp();
      auto timeOutShutdown  = tarch::mpi::Rank::getInstance().getDeadlockTimeOutTimeStamp();
      bool triggeredTimeoutWarning = false;
      if (
        tarch::mpi::Rank::getInstance().isTimeOutWarningEnabled() &&
        (std::chrono::system_clock::now()>timeOutWarning) &&
        (!triggeredTimeoutWarning)
      ) {
        tarch::mpi::Rank::getInstance().writeTimeOutWarning( "project::base_2d_euler::facedata::euler2DFaceLabel", "receiveAndPollDanglingMessages()", source, tag );
        triggeredTimeoutWarning = true;
      }
      if (
        tarch::mpi::Rank::getInstance().isTimeOutDeadlockEnabled() &&
        (std::chrono::system_clock::now()>timeOutShutdown)
      ) {
        tarch::mpi::Rank::getInstance().triggerDeadlockTimeOut( "project::base_2d_euler::facedata::euler2DFaceLabel", "receiveAndPollDanglingMessages()", source, tag );
      }
      tarch::services::ServiceRepository::getInstance().receiveDanglingMessages();
    },
    communicator
  );
}
#endif
    
void project::base_2d_euler::facedata::euler2DFaceLabel::merge(const project::base_2d_euler::facedata::euler2DFaceLabel& neighbour, const peano4::datamanagement::FaceMarker& marker) {

  _Boundary = _Boundary or neighbour._Boundary;
  
  const int normal         = marker.getSelectedFaceNumber() % Dimensions;
  const int neighbourEntry = marker.outerNormal()(normal)<0.0 ? 0 : 1;
  
  _Updated[ neighbourEntry ]          = neighbour._Updated[ neighbourEntry ];
  _UpdatedTimeStamp( neighbourEntry ) = neighbour._UpdatedTimeStamp( neighbourEntry );
  _NewTimeStamp( neighbourEntry )     = neighbour._NewTimeStamp( neighbourEntry );
  _OldTimeStamp( neighbourEntry )     = neighbour._OldTimeStamp( neighbourEntry );
  

}


bool project::base_2d_euler::facedata::euler2DFaceLabel::receiveAndMerge(const peano4::datamanagement::FaceMarker& marker) {
  return true;
}


bool project::base_2d_euler::facedata::euler2DFaceLabel::send(const peano4::datamanagement::FaceMarker& marker) {
  return true;
}


bool project::base_2d_euler::facedata::euler2DFaceLabel::storePersistently(const peano4::datamanagement::FaceMarker& marker) {
  return true;
}


bool project::base_2d_euler::facedata::euler2DFaceLabel::loadPersistently(const peano4::datamanagement::FaceMarker& marker) {
  return true;
}
