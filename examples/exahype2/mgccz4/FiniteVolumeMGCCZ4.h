//
// ExaHyPE2 solver file
// Generated by Peano's Python API
// www.peano-framework.org
//
// This is generated. If you change fundamental properties, you will have to 
// generate this file. Backup your manual changes before you do so.
//
#ifndef _examples_exahype2_mgccz4_FiniteVolumeMGCCZ4_H_
#define _examples_exahype2_mgccz4_FiniteVolumeMGCCZ4_H_


#include "AbstractFiniteVolumeMGCCZ4.h"

#include "tarch/logging/Log.h"

namespace examples {
  namespace exahype2 {
    namespace mgccz4 {
      class FiniteVolumeMGCCZ4;
    }
  }
}



class examples::exahype2::mgccz4::FiniteVolumeMGCCZ4: public AbstractFiniteVolumeMGCCZ4 {
  private:
    static tarch::logging::Log   _log;

  public:
    FiniteVolumeMGCCZ4();   

    
    //#if defined(OpenMPGPUOffloading)
    //#pragma omp declare target
    //#endif
    void adjustSolution(
      double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      double                                       dt
    )  override;
    //#if defined(OpenMPGPUOffloading)
    //#pragma omp end declare target
    //#endif
    
    
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
    );
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
    );
 
    void nonconservativeProduct(
      const double * __restrict__ Q, // Q[59+0],
      const double * __restrict__             deltaQ, // [59+0]
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__ BgradQ // BgradQ[59]
    );
};


#endif
