
//
// Generated by DaStGen2 (C) 2020 Tobias Weinzierl
//
// For DaStGen's copyright, visit www.peano-framework.org. These generated files
// however are not subject of copyright, i.e. feel free to add your copyright in 
// here
//  
#ifndef _INCLUDE_PEANO4_GRID_GRIDVERTEX_
#define _INCLUDE_PEANO4_GRID_GRIDVERTEX_

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
namespace grid{

  struct GridVertex;
}
}



struct peano4::grid::GridVertex {
  public:
    enum class State: int {
      HangingVertex=0, New=1, Unrefined=2, Refined=3, RefinementTriggered=4, Refining=5, EraseTriggered=6, Erasing=7, Delete=8    
    };

    GridVertex() {}
    GridVertex(State  __state, tarch::la::Vector<TwoPowerD,int>  __adjacentRanks, tarch::la::Vector<TwoPowerD,int>  __backupOfAdjacentRanks, bool  __hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, bool  __isAntecessorOfRefinedVertexInCurrentTreeSweep, int  __numberOfAdjacentRefinedLocalCells, tarch::la::Vector<Dimensions,double>  __x, int  __level);

    peano4::grid::GridVertex::State   getState() const;
    void   setState(State value);
    tarch::la::Vector<TwoPowerD,int>   getAdjacentRanks() const;
    void   setAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& value);
    int   getAdjacentRanks(int index) const;
    void   setAdjacentRanks(int index, int value);
    tarch::la::Vector<TwoPowerD,int>   getBackupOfAdjacentRanks() const;
    void   setBackupOfAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& value);
    int   getBackupOfAdjacentRanks(int index) const;
    void   setBackupOfAdjacentRanks(int index, int value);
    bool   getHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep() const;
    void   setHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep(bool value);
    bool   getIsAntecessorOfRefinedVertexInCurrentTreeSweep() const;
    void   setIsAntecessorOfRefinedVertexInCurrentTreeSweep(bool value);
    int   getNumberOfAdjacentRefinedLocalCells() const;
    void   setNumberOfAdjacentRefinedLocalCells(int value);
    tarch::la::Vector<Dimensions,double>   getX() const;
    void   setX(const tarch::la::Vector<Dimensions,double>& value);
    double   getX(int index) const;
    void   setX(int index, double value);
    int   getLevel() const;
    void   setLevel(int value);



#ifdef Parallel
    static void sendAndPollDanglingMessages(const peano4::grid::GridVertex& message, int destination, int tag );
    static void receiveAndPollDanglingMessages(peano4::grid::GridVertex& message, int source, int tag );
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
    static void send(const peano4::grid::GridVertex& buffer, int destination, int tag, MPI_Comm communicator );
    static void receive(peano4::grid::GridVertex& buffer, int source, int tag, MPI_Comm communicator );

    /**
     * Alternative to the other send() where I trigger a non-blocking send an 
     * then invoke the functor until the corresponding MPI_Test tells me that 
     * the message went through. In systems with heavy MPI usage, this can 
     * help to avoid deadlocks.
     */
    static void send(const peano4::grid::GridVertex& buffer, int destination, int tag, std::function<void()> waitFunctor, MPI_Comm communicator );
    static void receive(peano4::grid::GridVertex& buffer, int source, int tag, std::function<void()> waitFunctor, MPI_Comm communicator );
    #endif


    std::string toString() const;
  
  private:
    State   _state;
    tarch::la::Vector<TwoPowerD,int>   _adjacentRanks;
    tarch::la::Vector<TwoPowerD,int>   _backupOfAdjacentRanks;
    bool   _hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep;
    bool   _isAntecessorOfRefinedVertexInCurrentTreeSweep;
    int   _numberOfAdjacentRefinedLocalCells;
    tarch::la::Vector<Dimensions,double>   _x;
    int   _level;




    #ifdef Parallel
    public:
      static MPI_Datatype  Datatype;
    private:
    int                  _senderDestinationRank;
    #endif


    
};

#endif
  