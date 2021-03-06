// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _PEANO4_DATAMANAGEMENT_VERTEX_ENUMERATOR_H_
#define _PEANO4_DATAMANAGEMENT_VERTEX_ENUMERATOR_H_


#include "peano4/utils/Globals.h"
#include "tarch/Assertions.h"


namespace peano4 {
  namespace datamanagement {
    template <class Vertex>
    struct VertexEnumerator;
  }
}


template <class Vertex>
struct peano4::datamanagement::VertexEnumerator {
  private:
    Vertex* _vertices[ TwoPowerD ];
  public:
    VertexEnumerator() {
      #if PeanoDebug>0
      for (int i=0; i<TwoPowerD; i++) {
        _vertices[i] = nullptr;
      }
      #endif
    }

    /**
     * Constructs vertex enumerator with default layout for consecutively
     * stored vertices.
     */
    VertexEnumerator(Vertex* firstVertex) {
      assertion( firstVertex!=nullptr );
      for (int i=0; i<TwoPowerD; i++) {
        _vertices[i] = firstVertex+i;
      }
    }


    /**
     * Usually is only used by the observers, i.e. users should not interact
     * with this routine.
     */
    void setPointer(int i, Vertex* value) {
      assertion(i>=0);
      assertion(i<TwoPowerD);
      assertion(value!=nullptr);
      _vertices[i] = value;
    }

    Vertex& operator()(int i) const {
      assertion1(i>=0,i);
      assertion1(i<TwoPowerD,i);
      assertion1( _vertices[i]!=nullptr,i );
      return *(_vertices[i]);
    }
};


#endif
