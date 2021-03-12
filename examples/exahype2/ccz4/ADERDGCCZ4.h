//
// ExaHyPE2 solver file
// Generated by Peano's Python API
// www.peano-framework.org
//
// This is generated. If you change fundamental properties, you will have to 
// generate this file. Backup your manual changes before you do so.
//
#ifndef _examples_exahype2_ccz4_ADERDG_CCZ4_H_
#define _examples_exahype2_ccz4_ADERDG_CCZ4_H_


#include "AbstractADERDGCCZ4.h"

#include "tarch/logging/Log.h"

namespace examples {namespace exahype2 {namespace ccz4 {
  class ADERDGCCZ4;
}}}



class examples::exahype2::ccz4::ADERDGCCZ4: public AbstractADERDGCCZ4 {
  private:
    static tarch::logging::Log   _log;

  public:
    ADERDGCCZ4();


    
    void adjustSolution(
      double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t
    )  override;
    


    
    virtual void boundaryConditions(
      const double * __restrict__                  Qinside, // Qinside[59+0]
      double * __restrict__                        Qoutside, // Qoutside[59+0]
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t,
      int                                          normal
    )  override;
    


    
    double maxEigenvalue(
      const double * __restrict__ Q, // Q[59+0],
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t,
      int                                          normal
    ) override;
    


    


    
    void nonconservativeProduct(
      const double * __restrict__                  Q, // Q[59+0],
      const double * __restrict__                  deltaQ, // deltaQ[59+0]
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t,
      int                                          normal,
      double * __restrict__                        BgradQ // BgradQ[59]
    ) override;
    


    
    virtual void algebraicSource(
      const double * __restrict__ Q, // Q[59+0],
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t,
      double * __restrict__ S // S[59]
    );
    
};


#endif
