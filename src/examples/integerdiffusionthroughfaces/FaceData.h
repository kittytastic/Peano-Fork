// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _EXAMPLES_INTEGER_DIFFUSION_THROUGH_FACES_FACE_DATA_H_
#define _EXAMPLES_INTEGER_DIFFUSION_THROUGH_FACES_FACE_DATA_H_



namespace examples {
  namespace integerdiffusionthroughfaces {
    struct FaceData;
  }
}



/**
 * In this simple example, we store exactly the same thing both in cells
 * and on faces. For most applications, that's not the case obviously.
 */
struct examples::integerdiffusionthroughfaces::FaceData {
  #if PeanoDebug>0
  tarch::la::Vector<Dimensions,double>   x;
  tarch::la::Vector<Dimensions,double>   h;
  #endif
  int                                    value;
};



#endif
