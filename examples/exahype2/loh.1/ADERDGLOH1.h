//
// ExaHyPE2 solver file
// Generated by Peano's Python API
// www.peano-framework.org
//
// This is generated. If you change fundamental properties, you will have to 
// generate this file. Backup your manual changes before you do so.
//
#ifndef _examples_exahype2_loh1_ADERDGLOH1_H_
#define _examples_exahype2_loh1_ADERDGLOH1_H_


#include "AbstractADERDGLOH1.h"

#include "tarch/logging/Log.h"

namespace examples {namespace exahype2 {namespace loh1 {
  class ADERDGLOH1;

}}}



class examples::exahype2::loh1::ADERDGLOH1: public AbstractADERDGLOH1 {
  private:
    static tarch::logging::Log   _log;
    
    static constexpr int Unknowns = 13;
    
    struct VariablesShortcuts {
      const int v = 0; 
      const int sigma = 3;
      const int rho = 9;
      const int cp = 10;
      const int cs = 11;
      const int alpha = 12;
    } s;

    void prescribeGaussianWave(
        const tarch::la::Vector<Dimensions,double>&  x,
    		double Q[]);

  public:
    
    void adjustSolution(
      double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t
    )  override;
    
    virtual void boundaryConditions(
      const double * __restrict__                  Qinside, // Qinside[9+4]
      double * __restrict__                        Qoutside, // Qoutside[9+4]
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t,
      int                                          normal
    )  override;
    
    double maxEigenvalue(
      const double * __restrict__ Q, // Q[9+4],
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t,
      int                                          normal
    ) override;
    
    void nonconservativeProduct(
      const double * __restrict__                  Q, // [9+4],
      const double * __restrict__                  deltaQ, // [9+4],
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t,
      int                                          normal,
      double * __restrict__ BgradQ // BgradQ[13]
     ) override;
};


#endif
