#ifndef _EXAMPLES_ALGEBRAICMG_MAPPINGS_COMPUTEGLOBALRESIDUALANDERROR_H_
#define _EXAMPLES_ALGEBRAICMG_MAPPINGS_COMPUTEGLOBALRESIDUALANDERROR_H_


#include "peano4/utils/Globals.h" 
#include "peano4/datamanagement/VertexEnumerator.h" 
#include "peano4/datamanagement/FaceEnumerator.h" 
#include "peano4/datamanagement/CellWrapper.h" 
#include "peano4/grid/GridControlEvent.h" 
#include "tarch/la/Vector.h" 


#include <vector>


#include "vertexdata/MG.h"


namespace examples {
  namespace algebraicmg {
    namespace mappings {
      class ComputeGlobalResidualAndError;
    }
  }
}



class examples::algebraicmg::mappings::ComputeGlobalResidualAndError{
  private:
    static tarch::logging::Log  _log;

    double _globalResidualL2;
    double _globalResidualMax;
    double _globalResidualEukledian;
    double _globalErrorL2;
    double _globalErrorMax;
    double _globalErrorEukledian;
  public:

    /**
     * Create mapping instance for one tree for one grid sweep
     *
     * <h2> Thread safety </h2>
     *
     * The creation of individual trees usually happens through peano4::parallel::SpacetreeSet::createObserverCloneIfRequired().
     * This routine is called lazily when we start to traverse a subtree. 
     * Therefore, the creation of mappings is not thread-safe.
     *
     *
     * @param treeNumber Number of the spacetree for which we create the tree instance. Is 
     *                   smaller 0 if this is the prototype mapping used on a rank from which 
     *                   the real mappings are constructed from.
     */      
    ComputeGlobalResidualAndError(int treeNumber);

    ~ComputeGlobalResidualAndError();

    std::vector< peano4::grid::GridControlEvent > getGridControlEvents();

    void beginTraversal(
      );

    void endTraversal(
      );

    void createPersistentVertex(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG);

    void destroyPersistentVertex(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG);

    void createHangingVertex(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG);

    void destroyHangingVertex(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG);

    void touchVertexFirstTime(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG);

    void touchVertexLastTime(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG);

    void touchCellFirstTime(
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> fineGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> fineGridCell,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> coarseGridCell);

    void touchCellLastTime(
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> fineGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> fineGridCell,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> coarseGridCell);

};


#endif

