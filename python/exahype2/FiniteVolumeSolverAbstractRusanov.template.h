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

{OPEN_NAMESPACE}
  class {CLASSNAME};
{CLOSE_NAMESPACE}


class {FULL_QUALIFIED_CLASSNAME} {{
  public:
    /**
     * @param Q Vector of unknowns
     * @param x Position of unknowns (finite volume centre)
     * @param h Mesh size of finite volume
     * @param t Time
     */
    virtual exahype2::RefinementControl refinementCriterion(
      double Q[{NUMBER_OF_UNKNOWNS}],
      const tarch::la::Vector<Dimensions,double>&  x,
      const tarch::la::Vector<Dimensions,double>&  h,
      const tarch::la::Vector<Dimensions,double>&  t
    ) = 0;
}};


#endif
