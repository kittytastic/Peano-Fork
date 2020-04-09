//
// ExaHyPE2 solver file
// Generated by Peano's Python API
// www.peano-framework.org
//
// This is generated. If you change fundamental properties, you will have to 
// generate this file. Backup your manual changes before you do so.
//
#ifndef _{INCLUDE_GUARD}_
#define _{INCLUDE_GUARD}_


#include "exahype2/RefinementControl.h"

#include "tarch/la/Vector.h"

#include "peano4/utils/Globals.h"



{OPEN_NAMESPACE}
  class {CLASSNAME};
{CLOSE_NAMESPACE}


class {FULL_QUALIFIED_CLASSNAME} {{
  public:
    /**
     * @param Q Vector of unknowns
     * @param t Time
     */
    virtual ::exahype2::RefinementCommand refinementCriterion(
      double Q[{NUMBER_OF_UNKNOWNS}],
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      const tarch::la::Vector<Dimensions,double>&  t
    ) = 0;

    /**
     * Feel free to change the solution in the particular finite volume.
     * You can for example change the initial conditions by overwriting
     * the solution for t=0. You may change Q. All other parameters are
     * in.
     */
    virtual void adjustSolution(
      double Q[{NUMBER_OF_UNKNOWNS}],
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      const tarch::la::Vector<Dimensions,double>&  t
    ) = 0;

    /**
     * Determine eigenvalues over Jacobian in a given point with solution values
     * (states) Q. All parameters are in besides lambda which is the output
     * vector.
     */
    virtual void eigenvalues(
      double                                       Q[{NUMBER_OF_UNKNOWNS}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      const tarch::la::Vector<Dimensions,double>&  t,
      int                                          normal,
      double                                       lambda[{NUMBER_OF_UNKNOWNS}]
    ) = 0;

    /**
     * Compute the flux for a given volume with states Q. All parameters
     * are in except F. F is the output vector.
     */
    virtual void flux(
      double                                       Q[{NUMBER_OF_UNKNOWNS}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      const tarch::la::Vector<Dimensions,double>&  t,
      int                                          normal,
      double                                       F[{NUMBER_OF_UNKNOWNS}]
    ) = 0;

    /**
     * Apply boundary conditions. You can overwrite both the inside and
     * outside values though most BCs only modify the outside ones. Please
     * note that the boundary conditions you set here are after that subject
     * to the Riemann solver, i.e. flux and eigenvalues.
     */
    virtual void boundaryConditions(
      double                                       Qinside[{NUMBER_OF_UNKNOWNS}],
      double                                       Qoutside[{NUMBER_OF_UNKNOWNS}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      const tarch::la::Vector<Dimensions,double>&  t,
      int                                          normal
    ) = 0;
}};


#endif
