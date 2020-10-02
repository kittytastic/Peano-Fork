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



class {% for item in NAMESPACE -%}{{ item }}::{%- endfor %}{{CLASSNAME}}: public Abstract{{CLASSNAME}} {
  private:
    static tarch::logging::Log   _log;

  public:
    {% if REFINEMENT_CRITERION_IMPLEMENTATION=="<user-defined>" %}
    ::exahype2::RefinementCommand refinementCriterion(
      double                                       Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t
    ) override;
    {% endif %}


    {% if INITIAL_CONDITIONS_IMPLEMENTATION=="<user-defined>" %}
    void adjustSolution(
      double                                       Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t
    )  override;
    {% endif %}


    {% if BOUNDARY_CONDITIONS_IMPLEMENTATION=="<user-defined>" %}
    virtual void boundaryConditions(
      double                                       Qinside[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      double                                       Qoutside[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal
    )  override;
    {% endif %}
};


#endif
