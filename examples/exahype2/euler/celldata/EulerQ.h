//
// Peano4 data file
// Generated by Peano's Python API
// www.peano-framework.org
// This is generated. Be careful with adding your own stuff
//
#ifndef _examples_exahype2_euler_celldata_EulerQ_H_
#define _examples_exahype2_euler_celldata_EulerQ_H_



#include <string>

#include "tarch/la/Vector.h"
#include "tarch/mpi/mpi.h"

#include "peano4/utils/Globals.h"

#include "peano4/datamanagement/CellMarker.h"
#include "peano4/datamanagement/FaceMarker.h"
#include "peano4/datamanagement/VertexMarker.h"


namespace examples {namespace exahype2 {namespace euler {namespace celldata {

  class EulerQ;

}}}}



struct examples::exahype2::euler::celldata::EulerQ {
  #if PeanoDebug>=1
  private:
    tarch::la::Vector<Dimensions,double> _debugX;
    tarch::la::Vector<Dimensions,double> _debugH;
  
  public:
    void setDebugX( const tarch::la::Vector<Dimensions,double>& data );
    void setDebugH( const tarch::la::Vector<Dimensions,double>& data );
    tarch::la::Vector<Dimensions,double> getDebugX() const;
    tarch::la::Vector<Dimensions,double> getDebugH() const;
  #endif

  #if Dimensions==2
  double                                 value[245];
  #else
  double                                 value[1715];
  #endif
  
  EulerQ();
  EulerQ(const EulerQ& other);
  EulerQ& operator=(const EulerQ& other);

  std::string toString() const;
  
  void merge(const EulerQ& neighbour, const peano4::datamanagement::CellMarker& marker);
  static bool send(const peano4::datamanagement::CellMarker& marker);
  static bool receiveAndMerge(const peano4::datamanagement::CellMarker& marker);
  static bool storePersistently(const peano4::datamanagement::CellMarker& marker);
  static bool loadPersistently(const peano4::datamanagement::CellMarker& marker);
  #ifdef Parallel
  /**
   * Sets the Datatype to MPI_Double.
   */
  static void initDatatype();

  /**
   * Degenerates to nop here, but we need such a function to fit to all other types.
   */
  static void shutdownDatatype();
  
  /**
   * Map each entry to an MPI_DOUBLE.
   */
  static MPI_Datatype   Datatype;
  #endif
};


#endif