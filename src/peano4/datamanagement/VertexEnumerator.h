// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _PEANO4_DATAMANAGEMENT_VERTEX_ENUMERATOR_H_
#define _PEANO4_DATAMANAGEMENT_VERTEX_ENUMERATOR_H_


#include "peano4/utils/Globals.h"
#include "tarch/la/Vector.h"

#include <bitset>


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

    /**
     * Bottom left vertex of associated cell.
     */
    tarch::la::Vector<Dimensions,double>  _cellCentre;

    tarch::la::Vector<Dimensions,double>  _h;
  public:
	/**
	 * Usually is only used by the observers, i.e. users should not interact
	 * with this routine.
	 */
	VertexEnumerator(const tarch::la::Vector<Dimensions,double>&  cellCentre, const tarch::la::Vector<Dimensions,double>&  h):
      _cellCentre(x),
	  _h(h) {
      #if PeanoDebug>0
	  for (int i=0; i<TwoTimesD; i++) {
		_vertices[i] = nullptr;
	  }
      #endif
	}


	/**
	 * Constructs vertex enumerator with default layout for consecutively
	 * stored vertices.
	 */
	VertexEnumerator(const tarch::la::Vector<Dimensions,double>&  cellCentre, const tarch::la::Vector<Dimensions,double>&  h, Vertex* firstVertex):
      _cellCentre(cellCentre),
	  _h(h) {
	  for (int i=0; i<TwoTimesD; i++) {
		  _vertices[i] = firstVertex+i;
	  }
    }


	/**
	 * Constructs a vertex enumerator within a cell specified by x and h.
	 * However, this
	 */
	VertexEnumerator(
	  const tarch::la::Vector<Dimensions,double>&  cellCentre,
	  const tarch::la::Vector<Dimensions,double>&  h,
	  const tarch::la::Vector<Dimensions,int>&     relativePositionToFather,
	  Vertex* firstVertex
	):
      _cellCentre(cellCentre),
	  _h(h) {
	  for (int i=0; i<TwoTimesD; i++) {
        _vertices[i] = firstVertex+i;
	  }

	  for (int d=0; d<Dimensions; d++) {
        _cellCentre(d) += (1.0-relativePositionToFather(d)) * _h(d);
	  }

	  _h = 3.0 * _h;
    }


	VertexEnumerator(const VertexEnumerator<Vertex>& copy ):
      _cellCentre(copy._cellCentre),
      _h(copy._h) {
      for (int i=0; i<TwoTimesD; i++) {
        _vertices[i] = copy._vertices[i];
      }
    }


    VertexEnumerator& operator=(const VertexEnumerator<Vertex>& copy ) {
      _cellCentre = copy._cellCentre;
      _h = copy._h;
      for (int i=0; i<TwoTimesD; i++) {
        _vertices[i] = copy._vertices[i];
      }
      return *this;
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
	  assertion(i>=0);
	  assertion(i<TwoPowerD);
	  return *(_vertices[i]);
	}

	tarch::la::Vector<Dimensions,double> x(int i) const {
      tarch::la::Vector<Dimensions,double> result( _cellCentre );
      std::bitset<Dimensions> myset(i);
      for (int d=0; d<Dimensions; d++) {
        result(d) -= 0.5 * _h(d);
        result(d) += static_cast<double>(myset[d]) * _h(d);
      }
      return result;
	}

	std::string toString() const {
	  return "(" + _cellCentre.toString() + "," + _h.toString() + ")";
	}
};


#endif
