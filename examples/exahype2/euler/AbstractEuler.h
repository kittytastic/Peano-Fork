//
// ExaHyPE2 solver file
// Generated by Peano's Python API
// www.peano-framework.org
//
// This is generated. Don't change it! Every rerun of the Python API will
// overwrite your changes.
//
#ifndef _examples_exahype2_euler_AbstractEuler_H_
#define _examples_exahype2_euler_AbstractEuler_H_


#include "exahype2/RefinementControl.h"
#include "exahype2/Solver.h"

#include "tarch/la/Vector.h"

#include "peano4/utils/Globals.h"




namespace examples {namespace exahype2 {namespace euler {
  class AbstractEuler;

}}}



class examples::exahype2::euler::AbstractEuler: public ::exahype2::Solver {
  public:
    enum class SolverState {
      GridConstruction,
      GridInitialisation,
      Primary,
      Secondary,
      PlottingInitialCondition,
      PrimaryAfterGridInitialisation,
      Plotting
    };

    static std::string toString(SolverState);

    AbstractEuler();

    /**
     * Determine max eigenvalue over Jacobian in a given point with solution values
     * (states) Q. All parameters are in.
     */
    virtual double maxEigenvalue(
      double * __restrict__ Q, // Q[5+0],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal
    ) = 0;


    
    virtual void flux(
      double * __restrict__ Q, // Q[5+0],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double * __restrict__ F // F[5]
    ) =0;
    


     


        double getMinTimeStamp() const final;
    double getMaxTimeStamp() const final;
    double getMinTimeStepSize() const final;
    double getMaxTimeStepSize() const final;


    /**
     * @param Q Vector of unknowns
     * @param t Time
     */
    virtual ::exahype2::RefinementCommand refinementCriterion(
      double * __restrict__ Q, // Q[5+0],
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t
    ) = 0;



    /**
     * Feel free to change the solution in the particular finite volume.
     * You can for example change the initial conditions by overwriting
     * the solution for t=0. You may change Q. All other parameters are
     * in.
     */
    virtual void adjustSolution(
      double * __restrict__ Q, // Q[5+0],
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t
    ) = 0;


    /**
     * Apply boundary conditions. You can overwrite both the inside and
     * outside values though most BCs only modify the outside ones. Please
     * note that the boundary conditions you set here are after that subject
     * to the Riemann solver, i.e. flux and eigenvalues.
     */
    virtual void boundaryConditions(
      double * __restrict__ Qinside, // Qinside[5+0]
      double * __restrict__ Qoutside, // Qoutside[5+0]
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal
    ) = 0;




    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void startGridConstructionStep() override;

    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void finishGridConstructionStep() override;



    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void startGridInitialisationStep() override;

    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void finishGridInitialisationStep() override;




    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void startTimeStep(
      double globalMinTimeStamp,
      double globalMaxTimeStamp,
      double globalMinTimeStepSize,
      double globalMaxTimeStepSize
    ) override;

    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void finishTimeStep() override;


    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void startPlottingStep(
      double globalMinTimeStamp,
      double globalMaxTimeStamp,
      double globalMinTimeStepSize,
      double globalMaxTimeStepSize
    ) override;

    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void finishPlottingStep() override;


    double getMaxMeshSize() const;
    double getMinMeshSize() const;

    SolverState  getSolverState() const;
  protected:
    static tarch::logging::Log  _log;

    const int  _NumberOfFiniteVolumesPerAxisPerPatch;

    double     _timeStamp;

    SolverState  _solverState;

    double     _maxH;
    double     _minH;
};


#endif