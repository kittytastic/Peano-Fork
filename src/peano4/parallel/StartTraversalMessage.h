
//
// Generated by DaStGen2 (C) 2020 Tobias Weinzierl
//
// For DaStGen's copyright, visit www.peano-framework.org. These generated files
// however are not subject of copyright, i.e. feel free to add your copyright in 
// here
//  
#ifndef _INCLUDE_PEANO4_PARALLEL_STARTTRAVERSALMESSAGE_
#define _INCLUDE_PEANO4_PARALLEL_STARTTRAVERSALMESSAGE_

#include <string>
  

#include "tarch/la/Vector.h"
#include "tarch/mpi/Rank.h"
#include "tarch/services/ServiceRepository.h"
#include "peano4/utils/Globals.h"


#ifdef Parallel
  #include <mpi.h>
  #include <functional>
#endif


  
namespace peano4{
namespace parallel{

  struct StartTraversalMessage;
}
}



struct peano4::parallel::StartTraversalMessage {
  public:


    StartTraversalMessage() {}
    StartTraversalMessage(int  __stepIdentifier);

    int   getStepIdentifier() const;
    void   setStepIdentifier(int value);



#ifdef Parallel
    static void sendAndPollDanglingMessages(const peano4::parallel::StartTraversalMessage& message, int destination, int tag, MPI_Comm communicator=tarch::mpi::Rank::getInstance().getCommunicator());
    static void receiveAndPollDanglingMessages(peano4::parallel::StartTraversalMessage& message, int source, int tag, MPI_Comm communicator=tarch::mpi::Rank::getInstance().getCommunicator() );
#endif
    

    #ifdef Parallel
    /**
     * @return The rank of the sender of an object. It only make ssense to call
     *         this routine after you've invoked receive with MPI_ANY_SOURCE.
     */
    int getSenderRank() const;
    
    /**
     * To be called prior to any MPI usage of this class.
     */
    static void initDatatype();
    static void shutdownDatatype();
            
    /**
     * In DaStGen (the first version), I had a non-static version of the send
     * as well as the receive. However, this did not work with newer C++11 
     * versions, as a member function using this as pointer usually doesn't 
     * see the vtable while the init sees the object from outside, i.e. 
     * including a vtable. So this routine now is basically an alias for a
     * blocking MPI_Send. 
     */
    static void send(const peano4::parallel::StartTraversalMessage& buffer, int destination, int tag, MPI_Comm communicator );
    static void receive(peano4::parallel::StartTraversalMessage& buffer, int source, int tag, MPI_Comm communicator );

    /**
     * Alternative to the other send() where I trigger a non-blocking send an 
     * then invoke the functor until the corresponding MPI_Test tells me that 
     * the message went through. In systems with heavy MPI usage, this can 
     * help to avoid deadlocks.
     */
    static void send(const peano4::parallel::StartTraversalMessage& buffer, int destination, int tag, std::function<void()> waitFunctor, MPI_Comm communicator );
    static void receive(peano4::parallel::StartTraversalMessage& buffer, int source, int tag, std::function<void()> waitFunctor, MPI_Comm communicator );
    #endif


    std::string toString() const;
  
  private:
    int   _stepIdentifier;




    #ifdef Parallel
    public:
      static MPI_Datatype  Datatype;
    private:
    int                  _senderDestinationRank;
    #endif


    
};

#endif
  