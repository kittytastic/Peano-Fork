//
// ExaHyPE2 solver file
// Generated by Peano's Python API
// www.peano-framework.org
//
// This is generated. If you change fundamental properties, you will have to 
// generate this file. Backup your manual changes before you do so.
//
#ifndef _examples_exahype2_ccz4_FiniteVolumeCCZ4_H_
#define _examples_exahype2_ccz4_FiniteVolumeCCZ4_H_


#include "AbstractFiniteVolumeCCZ4.h"

#include "tarch/logging/Log.h"

#ifdef IncludeTwoPunctures
#include "libtwopunctures/TwoPunctures.h"
#endif

namespace examples {
  namespace exahype2 {
    namespace ccz4 {
      class FiniteVolumeCCZ4;
    }
  }
}



class examples::exahype2::ccz4::FiniteVolumeCCZ4: public AbstractFiniteVolumeCCZ4 {
  private:
    static tarch::logging::Log   _log;


  public:
    FiniteVolumeCCZ4();   

    void initialCondition(
      double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      bool                                         gridIsConstructred
    )  override;
    
    
    //#if defined(OpenMPGPUOffloading)
    //#pragma omp declare target
    //#endif
    void sourceTerm(
      const double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      double                                       dt,
      double * __restrict__ S
    ) override;
    //#if defined(OpenMPGPUOffloading)
    //#pragma omp end declare target
    //#endif
    
    
    virtual void boundaryConditions(
      const double * __restrict__ Qinside, // Qinside[59+0]
      double * __restrict__ Qoutside, // Qoutside[59+0]
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal
    )  override;


    
    double maxEigenvalue(
      const double * __restrict__ Q, // Q[59+0],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal
    ) override;
 
    void nonconservativeProduct(
      const double * __restrict__ Q, // Q[59+0],
      const double * __restrict__             deltaQ, // [59+0]
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__ BgradQ // BgradQ[59]
    ) override;
    
    ::exahype2::RefinementCommand refinementCriterion(
      const double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>& volumeCentre,
      const tarch::la::Vector<Dimensions,double>& volumeH,
      double t
    ) override;

    void prepare(TP::TwoPunctures* tp); 
};


#endif
