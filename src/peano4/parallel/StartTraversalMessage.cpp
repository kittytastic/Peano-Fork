#include "StartTraversalMessage.h"



#include <sstream>
#include <algorithm>



peano4::parallel::StartTraversalMessage::StartTraversalMessage(int  __stepIdentifier):
    _stepIdentifier(__stepIdentifier)
  {}



std::string peano4::parallel::StartTraversalMessage::toString() const {
  std::ostringstream out;
  out << "(";
  out << "stepIdentifier=" << _stepIdentifier;
  out << ")";
  return out.str();
}


int   peano4::parallel::StartTraversalMessage::getStepIdentifier() const {
  return _stepIdentifier;
}


void   peano4::parallel::StartTraversalMessage::setStepIdentifier(int value) {
  _stepIdentifier = value;
}






#ifdef Parallel
void peano4::parallel::StartTraversalMessage::sendAndPollDanglingMessages(const peano4::parallel::StartTraversalMessage& message, int destination, int tag ) {
  peano4::parallel::StartTraversalMessage::send(
    message, destination, tag,
    [&]() {
      int  timeOutWarning   = tarch::mpi::Rank::getInstance().getDeadlockWarningTimeStamp();
      int  timeOutShutdown  = tarch::mpi::Rank::getInstance().getDeadlockTimeOutTimeStamp();
      bool triggeredTimeoutWarning = false;
      if (
        tarch::mpi::Rank::getInstance().isTimeOutWarningEnabled() &&
        (clock()>timeOutWarning) &&
        (!triggeredTimeoutWarning)
      ) {
        tarch::mpi::Rank::getInstance().writeTimeOutWarning( "peano4::parallel::StartTraversalMessage", "sendAndPollDanglingMessages()",destination, tag );
        triggeredTimeoutWarning = true;
      }
      if (
        tarch::mpi::Rank::getInstance().isTimeOutDeadlockEnabled() &&
        (clock()>timeOutShutdown)
      ) {
        tarch::mpi::Rank::getInstance().triggerDeadlockTimeOut( "peano4::parallel::StartTraversalMessage", "sendAndPollDanglingMessages()", destination, tag );
      }
      tarch::services::ServiceRepository::getInstance().receiveDanglingMessages();
    },
    tarch::mpi::Rank::getInstance().getCommunicator()
  );
}


void peano4::parallel::StartTraversalMessage::receiveAndPollDanglingMessages(peano4::parallel::StartTraversalMessage& message, int source, int tag ) {
  peano4::parallel::StartTraversalMessage::receive(
    message, source, tag,
    [&]() {
      int  timeOutWarning   = tarch::mpi::Rank::getInstance().getDeadlockWarningTimeStamp();
      int  timeOutShutdown  = tarch::mpi::Rank::getInstance().getDeadlockTimeOutTimeStamp();
      bool triggeredTimeoutWarning = false;
      if (
        tarch::mpi::Rank::getInstance().isTimeOutWarningEnabled() &&
        (clock()>timeOutWarning) &&
        (!triggeredTimeoutWarning)
      ) {
        tarch::mpi::Rank::getInstance().writeTimeOutWarning( "peano4::parallel::StartTraversalMessage", "receiveAndPollDanglingMessages()", source, tag );
        triggeredTimeoutWarning = true;
      }
      if (
        tarch::mpi::Rank::getInstance().isTimeOutDeadlockEnabled() &&
        (clock()>timeOutShutdown)
      ) {
        tarch::mpi::Rank::getInstance().triggerDeadlockTimeOut( "peano4::parallel::StartTraversalMessage", "receiveAndPollDanglingMessages()", source, tag );
      }
      tarch::services::ServiceRepository::getInstance().receiveDanglingMessages();
    },
    tarch::mpi::Rank::getInstance().getCommunicator()
  );
}
#endif
    
#ifdef Parallel

MPI_Datatype peano4::parallel::StartTraversalMessage::Datatype;

int peano4::parallel::StartTraversalMessage::getSenderRank() const {
  return _senderDestinationRank;
}


void peano4::parallel::StartTraversalMessage::initDatatype() {
  peano4::parallel::StartTraversalMessage  instances[2];
    
  MPI_Datatype subtypes[] = { MPI_INT };
    
  int blocklen[] = { 1 };

  const int NumberOfAttributes = 1;
    
  MPI_Aint  baseFirstInstance;
  MPI_Aint  baseSecondInstance;
  MPI_Get_address( &instances[0], &baseFirstInstance );
  MPI_Get_address( &instances[1], &baseSecondInstance );
  MPI_Aint  disp[ NumberOfAttributes ];
  int       currentAddress = 0;
  MPI_Get_address( &(instances[0]._stepIdentifier), &disp[currentAddress] );
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


void peano4::parallel::StartTraversalMessage::shutdownDatatype() {
  MPI_Type_free( &Datatype );
}


void peano4::parallel::StartTraversalMessage::send(const peano4::parallel::StartTraversalMessage& buffer, int destination, int tag, MPI_Comm communicator ) {
  MPI_Send( &buffer, 1, Datatype, destination, tag, communicator);
}


void peano4::parallel::StartTraversalMessage::receive(peano4::parallel::StartTraversalMessage& buffer, int source, int tag, MPI_Comm communicator ) {
  MPI_Status status;
  MPI_Recv( &buffer, 1, Datatype, source, tag, communicator, &status);
  buffer._senderDestinationRank = status.MPI_SOURCE;
}


void peano4::parallel::StartTraversalMessage::send(const peano4::parallel::StartTraversalMessage& buffer, int destination, int tag, std::function<void()> waitFunctor, MPI_Comm communicator ) {
  MPI_Request sendRequestHandle; 
  int         flag = 0; 
  MPI_Isend( &buffer, 1, Datatype, destination, tag, communicator, &sendRequestHandle ); 
  MPI_Test( &sendRequestHandle, &flag, MPI_STATUS_IGNORE ); 
  while (!flag) { 
    waitFunctor();
    MPI_Test( &sendRequestHandle, &flag, MPI_STATUS_IGNORE ); 
  }
}


void peano4::parallel::StartTraversalMessage::receive(peano4::parallel::StartTraversalMessage& buffer, int source, int tag, std::function<void()> waitFunctor, MPI_Comm communicator ) {   
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
