
//
// Generated by DaStGen2 (C) 2020 Tobias Weinzierl
//
// For DaStGen's copyright, visit www.peano-framework.org. These generated files
// however are not subject of copyright, i.e. feel free to add your copyright in 
// here
//  
#ifndef _INCLUDE_PEANO4_GRID_GRIDTRAVERSALEVENT_
#define _INCLUDE_PEANO4_GRID_GRIDTRAVERSALEVENT_

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

  struct GridTraversalEvent;
}
}



struct peano4::grid::GridTraversalEvent {
  public:


    GridTraversalEvent() {}
    GridTraversalEvent(tarch::la::Vector<Dimensions,double>  __x, tarch::la::Vector<Dimensions,double>  __h, std::bitset<TwoPowerD>  __isRefined, std::bitset<TwoPowerD>  __isLocal, std::bitset<TwoPowerD>  __isHanging, tarch::la::Vector<TwoPowerD,int>  __vertexDataFrom, tarch::la::Vector<TwoPowerD,int>  __vertexDataTo, tarch::la::Vector<TwoTimesD,int>  __faceDataFrom, tarch::la::Vector<TwoTimesD,int>  __faceDataTo, int  __cellData, tarch::la::Vector<Dimensions,int>  __relativePositionToFather, tarch::la::Vector<TwoPowerDTimesTwoPowerDMinusOne,int>  __exchangeVertexData, tarch::la::Vector<TwoPowerD,int>  __exchangeFaceData);

    tarch::la::Vector<Dimensions,double>   getX() const;
    void   setX(const tarch::la::Vector<Dimensions,double>& value);
    double   getX(int index) const;
    void   setX(int index, double value);
    tarch::la::Vector<Dimensions,double>   getH() const;
    void   setH(const tarch::la::Vector<Dimensions,double>& value);
    double   getH(int index) const;
    void   setH(int index, double value);
    std::bitset<TwoPowerD>   getIsRefined() const;
    void   setIsRefined(const std::bitset<TwoPowerD>&  value);
    bool   getIsRefined(int index) const;
    void   setIsRefined(int index, bool value);
    void   flipIsRefined(int index);
    std::bitset<TwoPowerD>   getIsLocal() const;
    void   setIsLocal(const std::bitset<TwoPowerD>&  value);
    bool   getIsLocal(int index) const;
    void   setIsLocal(int index, bool value);
    void   flipIsLocal(int index);
    std::bitset<TwoPowerD>   getIsHanging() const;
    void   setIsHanging(const std::bitset<TwoPowerD>&  value);
    bool   getIsHanging(int index) const;
    void   setIsHanging(int index, bool value);
    void   flipIsHanging(int index);
    tarch::la::Vector<TwoPowerD,int>   getVertexDataFrom() const;
    void   setVertexDataFrom(const tarch::la::Vector<TwoPowerD,int>& value);
    int   getVertexDataFrom(int index) const;
    void   setVertexDataFrom(int index, int value);
    tarch::la::Vector<TwoPowerD,int>   getVertexDataTo() const;
    void   setVertexDataTo(const tarch::la::Vector<TwoPowerD,int>& value);
    int   getVertexDataTo(int index) const;
    void   setVertexDataTo(int index, int value);
    tarch::la::Vector<TwoTimesD,int>   getFaceDataFrom() const;
    void   setFaceDataFrom(const tarch::la::Vector<TwoTimesD,int>& value);
    int   getFaceDataFrom(int index) const;
    void   setFaceDataFrom(int index, int value);
    tarch::la::Vector<TwoTimesD,int>   getFaceDataTo() const;
    void   setFaceDataTo(const tarch::la::Vector<TwoTimesD,int>& value);
    int   getFaceDataTo(int index) const;
    void   setFaceDataTo(int index, int value);
    int   getCellData() const;
    void   setCellData(int value);
    tarch::la::Vector<Dimensions,int>   getRelativePositionToFather() const;
    void   setRelativePositionToFather(const tarch::la::Vector<Dimensions,int>& value);
    int   getRelativePositionToFather(int index) const;
    void   setRelativePositionToFather(int index, int value);
    tarch::la::Vector<TwoPowerDTimesTwoPowerDMinusOne,int>   getExchangeVertexData() const;
    void   setExchangeVertexData(const tarch::la::Vector<TwoPowerDTimesTwoPowerDMinusOne,int>& value);
    int   getExchangeVertexData(int index) const;
    void   setExchangeVertexData(int index, int value);
    tarch::la::Vector<TwoPowerD,int>   getExchangeFaceData() const;
    void   setExchangeFaceData(const tarch::la::Vector<TwoPowerD,int>& value);
    int   getExchangeFaceData(int index) const;
    void   setExchangeFaceData(int index, int value);



#ifdef Parallel
    static void sendAndPollDanglingMessages(const peano4::grid::GridTraversalEvent& message, int destination, int tag );
    static void receiveAndPollDanglingMessages(peano4::grid::GridTraversalEvent& message, int source, int tag );
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
    static void send(const peano4::grid::GridTraversalEvent& buffer, int destination, int tag, MPI_Comm communicator );
    static void receive(peano4::grid::GridTraversalEvent& buffer, int source, int tag, MPI_Comm communicator );

    /**
     * Alternative to the other send() where I trigger a non-blocking send an 
     * then invoke the functor until the corresponding MPI_Test tells me that 
     * the message went through. In systems with heavy MPI usage, this can 
     * help to avoid deadlocks.
     */
    static void send(const peano4::grid::GridTraversalEvent& buffer, int destination, int tag, std::function<void()> waitFunctor, MPI_Comm communicator );
    static void receive(peano4::grid::GridTraversalEvent& buffer, int source, int tag, std::function<void()> waitFunctor, MPI_Comm communicator );

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
    tarch::la::Vector<Dimensions,double>   _x;
    tarch::la::Vector<Dimensions,double>   _h;
    std::bitset<TwoPowerD>   _isRefined;
    std::bitset<TwoPowerD>   _isLocal;
    std::bitset<TwoPowerD>   _isHanging;
    tarch::la::Vector<TwoPowerD,int>   _vertexDataFrom;
    tarch::la::Vector<TwoPowerD,int>   _vertexDataTo;
    tarch::la::Vector<TwoTimesD,int>   _faceDataFrom;
    tarch::la::Vector<TwoTimesD,int>   _faceDataTo;
    int   _cellData;
    tarch::la::Vector<Dimensions,int>   _relativePositionToFather;
    tarch::la::Vector<TwoPowerDTimesTwoPowerDMinusOne,int>   _exchangeVertexData;
    tarch::la::Vector<TwoPowerD,int>   _exchangeFaceData;




    #ifdef Parallel
    public:
      static MPI_Datatype  Datatype;
    private:
    int                  _senderDestinationRank;
    #endif


    
};

#endif
  