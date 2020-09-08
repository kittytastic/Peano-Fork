//
// ExaHyPE2 solver file
// Generated by Peano's Python API
// www.peano-framework.org
//
// This is generated. Don't change it! Every rerun of the Python API will
// overwrite your changes.
//
#ifndef {% for item in NAMESPACE -%}_{{ item }}{%- endfor %}_{{CLASSNAME}}_H_
#define {% for item in NAMESPACE -%}_{{ item }}{%- endfor %}_{{CLASSNAME}}_H_


#include "exahype2/RefinementControl.h"

#include "tarch/la/Vector.h"

#include "peano4/utils/Globals.h"




{% for item in NAMESPACE -%}
  namespace {{ item }} {

{%- endfor %}
  class {{CLASSNAME}};

{% for item in NAMESPACE -%}
  }
{%- endfor %}



class {% for item in NAMESPACE -%}{{ item }}::{%- endfor %}{{CLASSNAME}} {
  public:
    enum class SolverState {
      GridConstruction,
      GridInitialisation,
      TimeStep,
      Plotting
    };

    static std::string toString(SolverState);

    {{CLASSNAME}}();

    double getMinTimeStamp() const;
    double getMaxTimeStamp() const;
    double getMinTimeStepSize() const;
    double getMaxTimeStepSize() const;

    /**
     * @param Q Vector of unknowns
     * @param t Time
     */
    virtual ::exahype2::RefinementCommand refinementCriterion(
      double                                       Q[{{NUMBER_OF_UNKNOWNS}}],
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t
    ) {% if REFINEMENT_CRITERION_IMPLEMENTATION=="<user-defined>" %}= 0{% endif %};

    /**
     * Feel free to change the solution in the particular finite volume.
     * You can for example change the initial conditions by overwriting
     * the solution for t=0. You may change Q. All other parameters are
     * in.
     */
    virtual void adjustSolution(
      double                                       Q[{{NUMBER_OF_UNKNOWNS}}],
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t
    ) {% if INITIAL_CONDITIONS_IMPLEMENTATION=="<user-defined>" %}= 0{% endif %};

    /**
     * Determine eigenvalues over Jacobian in a given point with solution values
     * (states) Q. All parameters are in besides lambda which is the output
     * vector.
     */
    virtual void eigenvalues(
      double                                       Q[{{NUMBER_OF_UNKNOWNS}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double                                       lambda[{{NUMBER_OF_UNKNOWNS}}]
    ) {% if EIGENVALUES_IMPLEMENTATION=="<user-defined>" %}= 0{% endif %};

    /**
     * Apply boundary conditions. You can overwrite both the inside and
     * outside values though most BCs only modify the outside ones. Please
     * note that the boundary conditions you set here are after that subject
     * to the Riemann solver, i.e. flux and eigenvalues.
     */
    virtual void boundaryConditions(
      double                                       Qinside[{{NUMBER_OF_UNKNOWNS}}],
      double                                       Qoutside[{{NUMBER_OF_UNKNOWNS}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal
    ) {% if BOUNDARY_CONDITIONS_IMPLEMENTATION=="<user-defined>" %}= 0{% endif %};


    virtual void startGridConstructionStep();
    virtual void finishGridConstructionStep();

    virtual void startGridInitialisationStep();
    virtual void finishGridInitialisationStep();

    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    virtual void startTimeStep(
      double globalMinTimeStamp,
      double globalMaxTimeStamp,
      double globalMinTimeStepSize,
      double globalMaxTimeStepSize
    );

    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    virtual void finishTimeStep();

    virtual void startPlottingStep(
      double globalMinTimeStamp,
      double globalMaxTimeStamp,
      double globalMinTimeStepSize,
      double globalMaxTimeStepSize
    );

    virtual void finishPlottingStep();

    {% if FLUX_IMPLEMENTATION!="<none>" %}
   virtual void flux(
     double                                       Q[{{NUMBER_OF_UNKNOWNS}}],
     const tarch::la::Vector<Dimensions,double>&  faceCentre,
     const tarch::la::Vector<Dimensions,double>&  volumeH,
     double                                       t,
     int                                          normal,
     double                                       F[{{NUMBER_OF_UNKNOWNS}}]
    ) {% if FLUX_IMPLEMENTATION=="<user-defined>" %}=0{% endif %};
     {% endif %}
     {% if NCP_IMPLEMENTATION!="<none>" %}
    virtual void nonconservativeProduct(
      double                                       Q[{{NUMBER_OF_UNKNOWNS}}],
      double                                       gradQ[{{NUMBER_OF_UNKNOWNS}}][Dimensions],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal,
      double                                       BgradQ[{{NUMBER_OF_UNKNOWNS}}]
    ) {% if NCP_IMPLEMENTATION=="<user-defined>" %}=0{% endif %};
     {% endif %}

    double getMaxMeshSize() const;
    double getMinMeshSize() const;
  protected:
    const int  _NumberOfFiniteVolumesPerAxisPerPatch;

    double     _timeStamp;

    SolverState  _solverState;

    double     _maxH;
    double     _minH;
};


#endif
