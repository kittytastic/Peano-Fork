
//
// Generated by DaStGen2 (C) 2020 Tobias Weinzierl
//
// For DaStGen's copyright, visit www.peano-framework.org. These generated files
// however are not subject of copyright, i.e. feel free to add your copyright in 
// here
//  
#ifndef _INCLUDE_PEANO4_GRID_AUTOMATONSTATE_
#define _INCLUDE_PEANO4_GRID_AUTOMATONSTATE_

#include <string>
  

#include "tarch/la/Vector.h"
#include "tarch/mpi/Rank.h"
#include "peano4/utils/Globals.h"


#ifdef Parallel
  #include <mpi.h>
  #include <functional>
#endif


  
namespace peano4{
namespace grid{

  struct AutomatonState;
}
}



struct peano4::grid::AutomatonState {
  public:


    int   getLevel() const;
    void   setLevel(int value);
    tarch::la::Vector<Dimensions,double>   getX() const;
    void   setX(const tarch::la::Vector<Dimensions,double>& value);
    double   getX(int index) const;
    void   setX(int index, double value);
    tarch::la::Vector<Dimensions,double>   getH() const;
    void   setH(const tarch::la::Vector<Dimensions,double>& value);
    double   getH(int index) const;
    void   setH(int index, double value);
    bool   getInverted() const;
    void   setInverted(bool value);
    std::bitset<Dimensions>   getEvenFlags() const;
    void   setEvenFlags(const std::bitset<Dimensions>&  value);
    bool   getEvenFlags(int index) const;
    void   setEvenFlags(int index, bool value);
    void   flipEvenFlags(int index);
    tarch::la::Vector<DimensionsTimesTwo,int>   getAccessNumber() const;
    void   setAccessNumber(const tarch::la::Vector<DimensionsTimesTwo,int>& value);
    int   getAccessNumber(int index) const;
    void   setAccessNumber(int index, int value);



#ifdef Parallel
    static void sendAndPollDanglingMessages(const peano4::grid::AutomatonState& message, int destination, int tag );
    static void receiveAndPollDanglingMessages(peano4::grid::AutomatonState& message, int source, int tag );
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
    static void send(const peano4::grid::AutomatonState& buffer, int destination, int tag, MPI_Comm communicator );
    static void receive(peano4::grid::AutomatonState& buffer, int source, int tag, MPI_Comm communicator );

    /**
     * Alternative to the other send() where I trigger a non-blocking send an 
     * then invoke the functor until the corresponding MPI_Test tells me that 
     * the message went through. In systems with heavy MPI usage, this can 
     * help to avoid deadlocks.
     */
    static void send(const peano4::grid::AutomatonState& buffer, int destination, int tag, std::function<void()> waitFunctor, MPI_Comm communicator );
    static void receive(peano4::grid::AutomatonState& buffer, int source, int tag, std::function<void()> waitFunctor, MPI_Comm communicator );

    /**
     * In older DaStGen version, I tried to find out whether a particular 
     * message type is in the MPI queue. That is, I looked whether a message
     * on this tag does exist, and then I looked whether the memory footprint
     * matches via count. I think this is invalid. MPI really looks only into
     * the number of bytes, so you have to know which type drops in once there
     * is a message on a tag.
     */            
    static bool isMessageInQueue(int tag, MPI_Comm communicator);
    #endif


    std::string toString() const;
  
  private:
    int   _level;
    tarch::la::Vector<Dimensions,double>   _x;
    tarch::la::Vector<Dimensions,double>   _h;
    bool   _inverted;
    std::bitset<Dimensions>   _evenFlags;
    tarch::la::Vector<DimensionsTimesTwo,int>   _accessNumber;




    #ifdef Parallel
    public:
      static MPI_Datatype  Datatype;
    private:
    int                  _senderDestinationRank;
    #endif


    
};

#endif
  