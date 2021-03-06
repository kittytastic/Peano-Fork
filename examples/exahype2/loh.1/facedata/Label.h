
//
// Generated by DaStGen2 (C) 2020 Tobias Weinzierl
//
// For DaStGen's copyright, visit www.peano-framework.org. These generated files
// however are not subject of copyright, i.e. feel free to add your copyright in 
// here
//  
#ifndef _INCLUDE_EXAMPLES_EXAHYPE2_LOH1_FACEDATA_LABEL_
#define _INCLUDE_EXAMPLES_EXAHYPE2_LOH1_FACEDATA_LABEL_

#include <string>
  

#ifdef Parallel
  #include <mpi.h>
  #include <functional>
#endif


#include "tarch/la/Vector.h"
#include "tarch/mpi/Rank.h"
#include "tarch/services/ServiceRepository.h"
#include "peano4/utils/Globals.h"

#include "peano4/datamanagement/CellMarker.h"
#include "peano4/datamanagement/FaceMarker.h"
#include "peano4/datamanagement/VertexMarker.h"


  
namespace examples{
namespace exahype2{
namespace loh1{
namespace facedata{

  struct Label;
}
}
}
}



struct examples::exahype2::loh1::facedata::Label {
  public:


    Label() {}
    Label(tarch::la::Vector<Dimensions,double>  __debugX, tarch::la::Vector<Dimensions,double>  __debugH, bool  __Boundary);

    tarch::la::Vector<Dimensions,double>   getDebugX() const;
    void   setDebugX(const tarch::la::Vector<Dimensions,double>& value);
    double   getDebugX(int index) const;
    void   setDebugX(int index, double value);
    tarch::la::Vector<Dimensions,double>   getDebugH() const;
    void   setDebugH(const tarch::la::Vector<Dimensions,double>& value);
    double   getDebugH(int index) const;
    void   setDebugH(int index, double value);
    bool   getBoundary() const;
    void   setBoundary(bool value);



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
    static void send(const examples::exahype2::loh1::facedata::Label& buffer, int destination, int tag, MPI_Comm communicator );
    static void receive(examples::exahype2::loh1::facedata::Label& buffer, int source, int tag, MPI_Comm communicator );

    /**
     * Alternative to the other send() where I trigger a non-blocking send an 
     * then invoke the functor until the corresponding MPI_Test tells me that 
     * the message went through. In systems with heavy MPI usage, this can 
     * help to avoid deadlocks.
     */
    static void send(const examples::exahype2::loh1::facedata::Label& buffer, int destination, int tag, std::function<void()> waitFunctor, MPI_Comm communicator );
    static void receive(examples::exahype2::loh1::facedata::Label& buffer, int source, int tag, std::function<void()> waitFunctor, MPI_Comm communicator );
    #endif


#ifdef Parallel
    static void sendAndPollDanglingMessages(const examples::exahype2::loh1::facedata::Label& message, int destination, int tag );
    static void receiveAndPollDanglingMessages(examples::exahype2::loh1::facedata::Label& message, int source, int tag );
#endif
    
    void merge(const examples::exahype2::loh1::facedata::Label& neighbour, const peano4::datamanagement::FaceMarker& marker);

    static bool receiveAndMerge(const peano4::datamanagement::FaceMarker& marker);
    static bool send(const peano4::datamanagement::FaceMarker& marker);
    static bool storePersistently(const peano4::datamanagement::FaceMarker& marker);
    static bool loadPersistently(const peano4::datamanagement::FaceMarker& marker);


    std::string toString() const;
  
  private:
    tarch::la::Vector<Dimensions,double>   _debugX;
    tarch::la::Vector<Dimensions,double>   _debugH;
    bool   _Boundary;



    #ifdef Parallel
    public:
      static MPI_Datatype  Datatype;
    private:
    int                  _senderDestinationRank;
    #endif



    
};

#endif
  