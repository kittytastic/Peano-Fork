//
// Peano4 data file
// Generated by Peano's Python API
// www.peano-framework.org
// This is generated. Be careful with adding your own stuff
//
#ifndef _project_base_2d_euler_inline_facedata_euler2DQNew_H_
#define _project_base_2d_euler_inline_facedata_euler2DQNew_H_



#include <string>

#include "tarch/la/Vector.h"
#include "tarch/mpi/mpi.h"

#include "peano4/utils/Globals.h"

#include "peano4/datamanagement/CellMarker.h"
#include "peano4/datamanagement/FaceMarker.h"
#include "peano4/datamanagement/VertexMarker.h"


namespace project {namespace base_2d_euler_inline {namespace facedata {

  class euler2DQNew;

}}}



struct project::base_2d_euler_inline::facedata::euler2DQNew {
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
  double                                 value[24];
  #else
  double                                 value[72];
  #endif
  
  euler2DQNew();
  euler2DQNew(const euler2DQNew& other);
  euler2DQNew& operator=(const euler2DQNew& other);

  std::string toString() const;
  
  void merge(const euler2DQNew& neighbour, const peano4::datamanagement::FaceMarker& marker);
  static bool send(const peano4::datamanagement::FaceMarker& marker);
  static bool receiveAndMerge(const peano4::datamanagement::FaceMarker& marker);
  static bool storePersistently(const peano4::datamanagement::FaceMarker& marker);
  static bool loadPersistently(const peano4::datamanagement::FaceMarker& marker);
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