#include "euler2DCellLabel.h"



#include <sstream>
#include <algorithm>



project::base_2d_euler::celldata::euler2DCellLabel::euler2DCellLabel(tarch::la::Vector<Dimensions,double>  __debugX, tarch::la::Vector<Dimensions,double>  __debugH, int  __SemaphoreNumber, double  __TimeStamp, double  __TimeStepSize, bool  __HasUpdated):
    _debugX(__debugX)
  , _debugH(__debugH)
  , _SemaphoreNumber(__SemaphoreNumber)
  , _TimeStamp(__TimeStamp)
  , _TimeStepSize(__TimeStepSize)
  , _HasUpdated(__HasUpdated)
  {}



std::string project::base_2d_euler::celldata::euler2DCellLabel::toString() const {
  std::ostringstream out;
  out << "(";
  out << "debugX=" << _debugX;
  out << ","; 
  out << "debugH=" << _debugH;
  out << ","; 
  out << "SemaphoreNumber=" << _SemaphoreNumber;
  out << ","; 
  out << "TimeStamp=" << _TimeStamp;
  out << ","; 
  out << "TimeStepSize=" << _TimeStepSize;
  out << ","; 
  out << "HasUpdated=" << _HasUpdated;
  out << ")";
  return out.str();
}


tarch::la::Vector<Dimensions,double>   project::base_2d_euler::celldata::euler2DCellLabel::getDebugX() const {
  return _debugX;
}


void   project::base_2d_euler::celldata::euler2DCellLabel::setDebugX(const tarch::la::Vector<Dimensions,double>& value) {
  _debugX = value;
}


double   project::base_2d_euler::celldata::euler2DCellLabel::getDebugX(int index) const {
  return _debugX(index);
}


void   project::base_2d_euler::celldata::euler2DCellLabel::setDebugX(int index, double value) {
  _debugX(index) = value;
}


tarch::la::Vector<Dimensions,double>   project::base_2d_euler::celldata::euler2DCellLabel::getDebugH() const {
  return _debugH;
}


void   project::base_2d_euler::celldata::euler2DCellLabel::setDebugH(const tarch::la::Vector<Dimensions,double>& value) {
  _debugH = value;
}


double   project::base_2d_euler::celldata::euler2DCellLabel::getDebugH(int index) const {
  return _debugH(index);
}


void   project::base_2d_euler::celldata::euler2DCellLabel::setDebugH(int index, double value) {
  _debugH(index) = value;
}


int   project::base_2d_euler::celldata::euler2DCellLabel::getSemaphoreNumber() const {
  return _SemaphoreNumber;
}


void   project::base_2d_euler::celldata::euler2DCellLabel::setSemaphoreNumber(int value) {
  _SemaphoreNumber = value;
}


double   project::base_2d_euler::celldata::euler2DCellLabel::getTimeStamp() const {
  return _TimeStamp;
}


void   project::base_2d_euler::celldata::euler2DCellLabel::setTimeStamp(double value) {
  _TimeStamp = value;
}


double   project::base_2d_euler::celldata::euler2DCellLabel::getTimeStepSize() const {
  return _TimeStepSize;
}


void   project::base_2d_euler::celldata::euler2DCellLabel::setTimeStepSize(double value) {
  _TimeStepSize = value;
}


bool   project::base_2d_euler::celldata::euler2DCellLabel::getHasUpdated() const {
  return _HasUpdated;
}


void   project::base_2d_euler::celldata::euler2DCellLabel::setHasUpdated(bool value) {
  _HasUpdated = value;
}






#ifdef Parallel

MPI_Datatype project::base_2d_euler::celldata::euler2DCellLabel::Datatype;

int project::base_2d_euler::celldata::euler2DCellLabel::getSenderRank() const {
  return _senderDestinationRank;
}


void project::base_2d_euler::celldata::euler2DCellLabel::initDatatype() {
  project::base_2d_euler::celldata::euler2DCellLabel  instances[2];
    
  MPI_Datatype subtypes[] = { MPI_DOUBLE, MPI_DOUBLE, MPI_INT, MPI_DOUBLE, MPI_DOUBLE, MPI_BYTE };
    
  int blocklen[] = { Dimensions, Dimensions, 1, 1, 1, 1 };

  const int NumberOfAttributes = 6;
    
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
  MPI_Get_address( &(instances[0]._SemaphoreNumber), &disp[currentAddress] );
  currentAddress++;
  MPI_Get_address( &(instances[0]._TimeStamp), &disp[currentAddress] );
  currentAddress++;
  MPI_Get_address( &(instances[0]._TimeStepSize), &disp[currentAddress] );
  currentAddress++;
  MPI_Get_address( &(instances[0]._HasUpdated), &disp[currentAddress] );
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


void project::base_2d_euler::celldata::euler2DCellLabel::shutdownDatatype() {
  MPI_Type_free( &Datatype );
}


void project::base_2d_euler::celldata::euler2DCellLabel::send(const project::base_2d_euler::celldata::euler2DCellLabel& buffer, int destination, int tag, MPI_Comm communicator ) {
  MPI_Send( &buffer, 1, Datatype, destination, tag, communicator);
}


void project::base_2d_euler::celldata::euler2DCellLabel::receive(project::base_2d_euler::celldata::euler2DCellLabel& buffer, int source, int tag, MPI_Comm communicator ) {
  MPI_Status status;
  MPI_Recv( &buffer, 1, Datatype, source, tag, communicator, &status);
  buffer._senderDestinationRank = status.MPI_SOURCE;
}


void project::base_2d_euler::celldata::euler2DCellLabel::send(const project::base_2d_euler::celldata::euler2DCellLabel& buffer, int destination, int tag, std::function<void()> waitFunctor, MPI_Comm communicator ) {
  MPI_Request sendRequestHandle; 
  int         flag = 0; 
  MPI_Isend( &buffer, 1, Datatype, destination, tag, communicator, &sendRequestHandle ); 
  MPI_Test( &sendRequestHandle, &flag, MPI_STATUS_IGNORE ); 
  while (!flag) { 
    waitFunctor();
    MPI_Test( &sendRequestHandle, &flag, MPI_STATUS_IGNORE ); 
  }
}


void project::base_2d_euler::celldata::euler2DCellLabel::receive(project::base_2d_euler::celldata::euler2DCellLabel& buffer, int source, int tag, std::function<void()> waitFunctor, MPI_Comm communicator ) {   
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
void project::base_2d_euler::celldata::euler2DCellLabel::sendAndPollDanglingMessages(const project::base_2d_euler::celldata::euler2DCellLabel& message, int destination, int tag, MPI_Comm communicator ) {
  project::base_2d_euler::celldata::euler2DCellLabel::send(
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
        tarch::mpi::Rank::getInstance().writeTimeOutWarning( "project::base_2d_euler::celldata::euler2DCellLabel", "sendAndPollDanglingMessages()",destination, tag );
        triggeredTimeoutWarning = true;
      }
      if (
        tarch::mpi::Rank::getInstance().isTimeOutDeadlockEnabled() &&
        (std::chrono::system_clock::now()>timeOutShutdown)
      ) {
        tarch::mpi::Rank::getInstance().triggerDeadlockTimeOut( "project::base_2d_euler::celldata::euler2DCellLabel", "sendAndPollDanglingMessages()", destination, tag );
      }
      tarch::services::ServiceRepository::getInstance().receiveDanglingMessages();
    },
    communicator
  );
}


void project::base_2d_euler::celldata::euler2DCellLabel::receiveAndPollDanglingMessages(project::base_2d_euler::celldata::euler2DCellLabel& message, int source, int tag, MPI_Comm communicator ) {
  project::base_2d_euler::celldata::euler2DCellLabel::receive(
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
        tarch::mpi::Rank::getInstance().writeTimeOutWarning( "project::base_2d_euler::celldata::euler2DCellLabel", "receiveAndPollDanglingMessages()", source, tag );
        triggeredTimeoutWarning = true;
      }
      if (
        tarch::mpi::Rank::getInstance().isTimeOutDeadlockEnabled() &&
        (std::chrono::system_clock::now()>timeOutShutdown)
      ) {
        tarch::mpi::Rank::getInstance().triggerDeadlockTimeOut( "project::base_2d_euler::celldata::euler2DCellLabel", "receiveAndPollDanglingMessages()", source, tag );
      }
      tarch::services::ServiceRepository::getInstance().receiveDanglingMessages();
    },
    communicator
  );
}
#endif
    
void project::base_2d_euler::celldata::euler2DCellLabel::merge(const project::base_2d_euler::celldata::euler2DCellLabel& neighbour, const peano4::datamanagement::CellMarker& marker) {

}


bool project::base_2d_euler::celldata::euler2DCellLabel::receiveAndMerge(const peano4::datamanagement::CellMarker& marker) {
  return true;
}


bool project::base_2d_euler::celldata::euler2DCellLabel::send(const peano4::datamanagement::CellMarker& marker) {
  return true;
}


bool project::base_2d_euler::celldata::euler2DCellLabel::storePersistently(const peano4::datamanagement::CellMarker& marker) {
  return true;
}


bool project::base_2d_euler::celldata::euler2DCellLabel::loadPersistently(const peano4::datamanagement::CellMarker& marker) {
  return true;
}
