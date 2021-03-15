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
#include "exahype2/Solver.h"

#include "tarch/la/Vector.h"

#include "peano4/utils/Globals.h"



/**
 * Import for ClawPack's FORTRAN routine
 *
 *
 * See the subchapter "Passing Data Arguments by Value" at
 *
 * https://northstar-www.dartmouth.edu/doc/solaris-forte/manuals/fortran/prog_guide/11_cfort.html
 *
 * By default, FORTRAN routines should have return value int. I don't check
 * error codes anyway, so it does not really make a difference.
 */
{% if DISCRIMINATE_NORMAL==True -%}
  extern "C" int {{CLAWPACK_RIEMANN_SOLVER}}_(int* ixy, int* num_eqn, int* num_aux, int* num_waves, const double * __restrict__ q_l, const double * __restrict__ q_r, const double * __restrict__ aux_l, const double * __restrict__ aux_r, double wave[3][3], double* s, double* amdq, double* apdq);
{% else -%}
   extern "C" int {{CLAWPACK_RIEMANN_SOLVER}}_(int* num_eqn, int* num_aux, int* num_waves, double* q_l, double* q_r, double* aux_l, double* aux_r, double* wave, double* s, double* amdq, double* apdq);
{% endif %}



{% for item in NAMESPACE -%}
  namespace {{ item }} {

{%- endfor %}
  class {{CLASSNAME}};

{% for item in NAMESPACE -%}
  }
{%- endfor %}



class {{NAMESPACE | join("::")}}::{{CLASSNAME}}: public ::exahype2::Solver {
  public:
    enum class SolverState {
      GridConstruction,
      GridInitialisation,
      TimeStep,
      Plotting
    };

    static std::string toString(SolverState);

    {{CLASSNAME}}();

    virtual void sourceTerm(
      const double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      double                                       dt,
      double * __restrict__ S
    ) {% if SOURCE_TERM_IMPLEMENTATION=="<user-defined>" %}= 0{% else %} final {% endif %};

    {% include "AbstractSolverFixedTimeStepSize.template.h" %}
};


#endif
