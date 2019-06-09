// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _EXAMPLES_DELTA_CELL_DATA_H_
#define _EXAMPLES_DELTA_CELL_DATA_H_


#include <string>


namespace examples {
  namespace delta {
    struct CellData;
  }
}



/**
 * In this simple example, we store exactly the same thing both in cells
 * and on faces. For most applications, that's not the case obviously.
 */
struct examples::delta::CellData {
  #if PeanoDebug>0
  tarch::la::Vector<Dimensions,double>   x;
  tarch::la::Vector<Dimensions,double>   h;
  #endif

  static constexpr int DoFsPerAxis = 10;

  #if Dimensions==2
  static constexpr int DoFsPerCell = DoFsPerAxis * DoFsPerAxis;
  #else
  static constexpr int DoFsPerCell = DoFsPerAxis * DoFsPerAxis * DoFsPerAxis;
  #endif

  double  value[DoFsPerAxis];

  std::string toString() const {
    return std::string("(")
         #if PeanoDebug>0
         + x.toString() + std::string(",")
         + h.toString() + std::string(",")
         #endif
         + std::string(")");
  }
};



#endif
