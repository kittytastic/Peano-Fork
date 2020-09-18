//
// ExaHyPE2 solver file
// Generated by Peano's Python API
// www.peano-framework.org
//
// This is generated. If you change fundamental properties, you will have to 
// generate this file. Backup your manual changes before you do so.
//
#ifndef _examples_exahype2_euler_Euler_H_
#define _examples_exahype2_euler_Euler_H_


#include "AbstractEuler.h"

#include "tarch/logging/Log.h"
#include "tarch/multicore/multicore.h"


namespace examples {namespace exahype2 {namespace euler {
  class Euler;

}}}



class examples::exahype2::euler::Euler: public AbstractEuler {
  private:
    static tarch::logging::Log   _log;

  public:
    ::exahype2::RefinementCommand refinementCriterion(
      double                                       Q[5],
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t
    )  override;

    void adjustSolution(
      double                                       Q[5],
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t
    )  override;

    virtual double maxEigenvalue(
      double                                       Q[5],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal
    )  override;

    virtual void boundaryConditions(
      double                                       Qinside[5],
      double                                       Qoutside[5],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal
    )  override;


    
    void flux(
      double                                       Q[5],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double                                       F[5]
    ) override;
    


    #if defined(GPUOffloading)
    #pragma omp declare target
    #endif
    /**
     * OK, this seems to be quite some overengineering. For a raw CPU code, it
     * is. The reason why we need this becomes obvious only when you switch to
     * GPGPU codes. For the time being, take it as follows: the flux member
     * function (and the eigenvalue function as well) are totally stateless.
     * That is, they don't need the object Euler. So I implement them as static
     * functions (with this additional parameter device which distinguishes the
     * functions from the object member functions). The normal class member
     * functions then just delegate to this static counterpart.
     */
    static void flux(
      double                                       Q[5],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double                                       F[5],
      tarch::multicore::TargetDevice
    );


    static double maxEigenvalue(
      double                                       Q[5],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      tarch::multicore::TargetDevice               device
    );
     #if defined(GPUOffloading)
     #pragma omp end declare target
     #endif
};


#endif
