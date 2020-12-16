//
// ExaHyPE2 solver file
// Generated by Peano's Python API
// www.peano-framework.org
//
// This is generated. If you change fundamental properties, you will have to 
// generate this file. Backup your manual changes before you do so.
//
#ifndef {% for item in NAMESPACE -%}_{{ item }}{%- endfor %}_{{CLASSNAME}}_H_
#define {% for item in NAMESPACE -%}_{{ item }}{%- endfor %}_{{CLASSNAME}}_H_


#include "Abstract{{CLASSNAME}}.h"

#include "tarch/logging/Log.h"

{% for item in NAMESPACE -%}
  namespace {{ item }} {

{%- endfor %}
  class {{CLASSNAME}};

{% for item in NAMESPACE -%}
  }
{%- endfor %}



class {{NAMESPACE | join("::")}}::{{CLASSNAME}}: public Abstract{{CLASSNAME}} {
  private:
    static tarch::logging::Log   _log;

  public:
    {% if REFINEMENT_CRITERION_IMPLEMENTATION=="<user-defined>" %}
    ::exahype2::RefinementCommand refinementCriterion(
      double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  x,
      const tarch::la::Vector<Dimensions,double>&  cellH,
      double                                       t
    ) override;
    {% endif %}


    {% if INITIAL_CONDITIONS_IMPLEMENTATION=="<user-defined>" %}
    void adjustSolution(
      double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t
    )  override;
    {% endif %}



    {% if BOUNDARY_CONDITIONS_IMPLEMENTATION=="<user-defined>" %}
    virtual void boundaryConditions(
      double * __restrict__ Qinside, // Qinside[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
      double * __restrict__ Qoutside, // Qoutside[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t,
      int                                          normal
    )  override;
    {% endif %}



    {% if RIEMANN_CONDITIONS_IMPLEMENTATION=="<user-defined>" %}
    virtual void boundaryConditions(
      double * __restrict__ Qinside, // Qinside[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
      double * __restrict__ Qoutside, // Qoutside[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t,
      int                                          normal
    )  override;
    {% endif %}


    {% if EIGENVALUES_IMPLEMENTATION=="<user-defined>" %}
    double maxEigenvalue(
      double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t
    ) override;
    {% endif %}


    {% if FLUX_IMPLEMENTATION=="<user-defined>" %}
    void flux(
      double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t,
      double * __restrict__ F // F[{{NUMBER_OF_UNKNOWNS}}]
    ) override;
    {% endif %}


    {% if NCP_IMPLEMENTATION=="<user-defined>" %}
    void nonconservativeProduct(
      double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      double                                       gradQ[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}][Dimensions],
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       t,
      double * __restrict__ BgradQ // BgradQ[{{NUMBER_OF_UNKNOWNS}}]
    ) override;
    {% endif %}
};


#endif
