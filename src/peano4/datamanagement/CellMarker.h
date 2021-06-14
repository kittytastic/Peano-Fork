// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _PEANO4_DATAMANAGEMENT_CELL_MARKER_H_
#define _PEANO4_DATAMANAGEMENT_CELL_MARKER_H_


#include "tarch/la/Vector.h"
#include "peano4/utils/Globals.h"
#include "peano4/grid/GridTraversalEvent.h"


namespace peano4 {
  namespace datamanagement {
    struct CellMarker;
  }
}


std::ostream& operator<<( std::ostream& out, const peano4::datamanagement::CellMarker& marker );


/**
 *
 */
struct peano4::datamanagement::CellMarker {
  private:
    tarch::la::Vector<Dimensions,double>  _centre;

    tarch::la::Vector<Dimensions,double>  _h;

    bool _isRefined;
    bool _isLocal;
    bool _areAllVerticesRefined;
    bool _isOneVertexHanging;
    bool _areAllVerticesInsideDomain;
    bool _invokingSpacetreeIsNotInvolvedInAnyDynamicLoadBalancing;

    /**
     * Entries from (0,1,2). (0,0) or (0,0,0) is the left, bottom cell.
     */
    tarch::la::Vector<Dimensions,int>  _relativePositionOfCellWithinFatherCell;
  public:
    CellMarker(const peano4::grid::GridTraversalEvent& event);

    bool isRefined() const;

    /**
     * @return x coordinate of a cell is its centre.
     */
    tarch::la::Vector<Dimensions,double>  x() const;

    /**
     * Check whether the point x is contained within the marker.
     */
    bool isContained( const tarch::la::Vector<Dimensions,double>& x ) const;
    bool overlaps( const tarch::la::Vector<Dimensions,double>& offset, const tarch::la::Vector<Dimensions,double>& size ) const;

    /**
     * @return Size of cell
     */
    tarch::la::Vector<Dimensions,double>  h() const;

    /**
     * @return Offset of cell, i.e. the bottom left vertex's coordinate
     */
    tarch::la::Vector<Dimensions,double>  getOffset() const;

    std::string toString() const;

    bool isLocal() const;

    /*
    bool areAllVerticesRefined() const;
    bool isOneVertexHanging() const;
    bool isAdjacentToDomainBoundary() const;
     */


    /**
     * A enclave cell in the definition of Charrier, Hazelwood, Weinzierl is a
     * cell that is not a skeleton cell. A skeleton cell is cell which either
     *
     * - is adjacent to a resolution transitions; or
     * - is adjacent to a domain boundary.
     *
     * Enclave cells are cells that you can potentially (if your algorithm
     * allows) deploy to a task running in the background. The only thing you
     * have to do is to ensure that it is passed all data via firstprivate copy
     * and that you never refine an enclave cell.
     *
     * <h2> Dynamic load balancing </h2>
     *
     * In line with the above definition, we may label a cell as enclave cell
     * if some dynamic load balancing is triggered or actually running. In
     * this case, any enclave cell might be subject of a domain transfer. If
     * we deployed its computation to the background, we could move around a
     * cell whose computations is done by a thread currently.
     */
    bool isEnclaveCell() const;

    /**
     * A skeleton cell is a not-enclave cell
     */
    bool isSkeletonCell() const;

    tarch::la::Vector<Dimensions,int>  getRelativePositionWithinFatherCell() const;
};


#endif
