#include "multigrid/mappings/PlotCells.h"



/**
 * @todo Please tailor the parameters to your mapping's properties.
 */
peano::CommunicationSpecification   multigrid::mappings::PlotCells::communicationSpecification() {
  return peano::CommunicationSpecification(peano::CommunicationSpecification::SendDataAndStateBeforeFirstTouchVertexFirstTime,peano::CommunicationSpecification::SendDataAndStateAfterLastTouchVertexLastTime,false);
}


/**
 * @todo Please tailor the parameters to your mapping's properties.
 */
peano::MappingSpecification   multigrid::mappings::PlotCells::touchVertexLastTimeSpecification() {
  return peano::MappingSpecification(peano::MappingSpecification::WholeTree,peano::MappingSpecification::RunConcurrentlyOnFineGrid);
}


/**
 * @todo Please tailor the parameters to your mapping's properties.
 */
peano::MappingSpecification   multigrid::mappings::PlotCells::touchVertexFirstTimeSpecification() { 
  return peano::MappingSpecification(peano::MappingSpecification::WholeTree,peano::MappingSpecification::RunConcurrentlyOnFineGrid);
}


/**
 * @todo Please tailor the parameters to your mapping's properties.
 */
peano::MappingSpecification   multigrid::mappings::PlotCells::enterCellSpecification() {
  return peano::MappingSpecification(peano::MappingSpecification::WholeTree,peano::MappingSpecification::AvoidFineGridRaces);
}


/**
 * @todo Please tailor the parameters to your mapping's properties.
 */
peano::MappingSpecification   multigrid::mappings::PlotCells::leaveCellSpecification() {
  return peano::MappingSpecification(peano::MappingSpecification::WholeTree,peano::MappingSpecification::AvoidFineGridRaces);
}


/**
 * @todo Please tailor the parameters to your mapping's properties.
 */
peano::MappingSpecification   multigrid::mappings::PlotCells::ascendSpecification() {
  return peano::MappingSpecification(peano::MappingSpecification::WholeTree,peano::MappingSpecification::AvoidCoarseGridRaces);
}


/**
 * @todo Please tailor the parameters to your mapping's properties.
 */
peano::MappingSpecification   multigrid::mappings::PlotCells::descendSpecification() {
  return peano::MappingSpecification(peano::MappingSpecification::WholeTree,peano::MappingSpecification::AvoidCoarseGridRaces);
}


tarch::logging::Log                multigrid::mappings::PlotCells::_log( "multigrid::mappings::PlotCells" ); 


multigrid::mappings::PlotCells::PlotCells() {
  logTraceIn( "PlotCells()" );
  // @todo Insert your code here
  logTraceOut( "PlotCells()" );
}


multigrid::mappings::PlotCells::~PlotCells() {
  logTraceIn( "~PlotCells()" );
  // @todo Insert your code here
  logTraceOut( "~PlotCells()" );
}


#if defined(SharedMemoryParallelisation)
multigrid::mappings::PlotCells::PlotCells(const PlotCells&  masterThread) {
  logTraceIn( "PlotCells(PlotCells)" );
  // @todo Insert your code here
  logTraceOut( "PlotCells(PlotCells)" );
}


void multigrid::mappings::PlotCells::mergeWithWorkerThread(const PlotCells& workerThread) {
  logTraceIn( "mergeWithWorkerThread(PlotCells)" );
  // @todo Insert your code here
  logTraceOut( "mergeWithWorkerThread(PlotCells)" );
}
#endif


void multigrid::mappings::PlotCells::createHangingVertex(
      multigrid::Vertex&     fineGridVertex,
      const tarch::la::Vector<DIMENSIONS,double>&                fineGridX,
      const tarch::la::Vector<DIMENSIONS,double>&                fineGridH,
      multigrid::Vertex * const   coarseGridVertices,
      const peano::grid::VertexEnumerator&      coarseGridVerticesEnumerator,
      multigrid::Cell&       coarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&                   fineGridPositionOfVertex
) {
  logTraceInWith6Arguments( "createHangingVertex(...)", fineGridVertex, fineGridX, fineGridH, coarseGridVerticesEnumerator.toString(), coarseGridCell, fineGridPositionOfVertex );
  // @todo Insert your code here
  logTraceOutWith1Argument( "createHangingVertex(...)", fineGridVertex );
}


void multigrid::mappings::PlotCells::destroyHangingVertex(
      const multigrid::Vertex&   fineGridVertex,
      const tarch::la::Vector<DIMENSIONS,double>&                    fineGridX,
      const tarch::la::Vector<DIMENSIONS,double>&                    fineGridH,
      multigrid::Vertex * const  coarseGridVertices,
      const peano::grid::VertexEnumerator&          coarseGridVerticesEnumerator,
      multigrid::Cell&           coarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&                       fineGridPositionOfVertex
) {
  logTraceInWith6Arguments( "destroyHangingVertex(...)", fineGridVertex, fineGridX, fineGridH, coarseGridVerticesEnumerator.toString(), coarseGridCell, fineGridPositionOfVertex );
  // @todo Insert your code here
  logTraceOutWith1Argument( "destroyHangingVertex(...)", fineGridVertex );
}


void multigrid::mappings::PlotCells::createInnerVertex(
      multigrid::Vertex&               fineGridVertex,
      const tarch::la::Vector<DIMENSIONS,double>&                          fineGridX,
      const tarch::la::Vector<DIMENSIONS,double>&                          fineGridH,
      multigrid::Vertex * const        coarseGridVertices,
      const peano::grid::VertexEnumerator&                coarseGridVerticesEnumerator,
      multigrid::Cell&                 coarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&                             fineGridPositionOfVertex
) {
  logTraceInWith6Arguments( "createInnerVertex(...)", fineGridVertex, fineGridX, fineGridH, coarseGridVerticesEnumerator.toString(), coarseGridCell, fineGridPositionOfVertex );
  // @todo Insert your code here
  logTraceOutWith1Argument( "createInnerVertex(...)", fineGridVertex );
}


void multigrid::mappings::PlotCells::createBoundaryVertex(
      multigrid::Vertex&               fineGridVertex,
      const tarch::la::Vector<DIMENSIONS,double>&                          fineGridX,
      const tarch::la::Vector<DIMENSIONS,double>&                          fineGridH,
      multigrid::Vertex * const        coarseGridVertices,
      const peano::grid::VertexEnumerator&                coarseGridVerticesEnumerator,
      multigrid::Cell&                 coarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&                             fineGridPositionOfVertex
) {
  logTraceInWith6Arguments( "createBoundaryVertex(...)", fineGridVertex, fineGridX, fineGridH, coarseGridVerticesEnumerator.toString(), coarseGridCell, fineGridPositionOfVertex );
  // @todo Insert your code here
  logTraceOutWith1Argument( "createBoundaryVertex(...)", fineGridVertex );
}


void multigrid::mappings::PlotCells::destroyVertex(
      const multigrid::Vertex&   fineGridVertex,
      const tarch::la::Vector<DIMENSIONS,double>&                    fineGridX,
      const tarch::la::Vector<DIMENSIONS,double>&                    fineGridH,
      multigrid::Vertex * const  coarseGridVertices,
      const peano::grid::VertexEnumerator&          coarseGridVerticesEnumerator,
      multigrid::Cell&           coarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&                       fineGridPositionOfVertex
) {
  logTraceInWith6Arguments( "destroyVertex(...)", fineGridVertex, fineGridX, fineGridH, coarseGridVerticesEnumerator.toString(), coarseGridCell, fineGridPositionOfVertex );
  // @todo Insert your code here
  logTraceOutWith1Argument( "destroyVertex(...)", fineGridVertex );
}


void multigrid::mappings::PlotCells::createCell(
      multigrid::Cell&                 fineGridCell,
      multigrid::Vertex * const        fineGridVertices,
      const peano::grid::VertexEnumerator&                fineGridVerticesEnumerator,
      multigrid::Vertex * const        coarseGridVertices,
      const peano::grid::VertexEnumerator&                coarseGridVerticesEnumerator,
      multigrid::Cell&                 coarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&                             fineGridPositionOfCell
) {
  logTraceInWith4Arguments( "createCell(...)", fineGridCell, fineGridVerticesEnumerator.toString(), coarseGridCell, fineGridPositionOfCell );
  // @todo Insert your code here
  logTraceOutWith1Argument( "createCell(...)", fineGridCell );
}


void multigrid::mappings::PlotCells::destroyCell(
      const multigrid::Cell&           fineGridCell,
      multigrid::Vertex * const        fineGridVertices,
      const peano::grid::VertexEnumerator&                fineGridVerticesEnumerator,
      multigrid::Vertex * const        coarseGridVertices,
      const peano::grid::VertexEnumerator&                coarseGridVerticesEnumerator,
      multigrid::Cell&                 coarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&                             fineGridPositionOfCell
) {
  logTraceInWith4Arguments( "destroyCell(...)", fineGridCell, fineGridVerticesEnumerator.toString(), coarseGridCell, fineGridPositionOfCell );
  // @todo Insert your code here
  logTraceOutWith1Argument( "destroyCell(...)", fineGridCell );
}

#ifdef Parallel
void multigrid::mappings::PlotCells::mergeWithNeighbour(
  multigrid::Vertex&  vertex,
  const multigrid::Vertex&  neighbour,
  int                                           fromRank,
  const tarch::la::Vector<DIMENSIONS,double>&   fineGridX,
  const tarch::la::Vector<DIMENSIONS,double>&   fineGridH,
  int                                           level
) {
  logTraceInWith6Arguments( "mergeWithNeighbour(...)", vertex, neighbour, fromRank, fineGridX, fineGridH, level );
  // @todo Insert your code here
  logTraceOut( "mergeWithNeighbour(...)" );
}

void multigrid::mappings::PlotCells::prepareSendToNeighbour(
  multigrid::Vertex&  vertex,
      int                                           toRank,
      const tarch::la::Vector<DIMENSIONS,double>&   x,
      const tarch::la::Vector<DIMENSIONS,double>&   h,
      int                                           level
) {
  logTraceInWith3Arguments( "prepareSendToNeighbour(...)", vertex, toRank, level );
  // @todo Insert your code here
  logTraceOut( "prepareSendToNeighbour(...)" );
}

void multigrid::mappings::PlotCells::prepareCopyToRemoteNode(
  multigrid::Vertex&  localVertex,
      int                                           toRank,
      const tarch::la::Vector<DIMENSIONS,double>&   x,
      const tarch::la::Vector<DIMENSIONS,double>&   h,
      int                                           level
) {
  logTraceInWith5Arguments( "prepareCopyToRemoteNode(...)", localVertex, toRank, x, h, level );
  // @todo Insert your code here
  logTraceOut( "prepareCopyToRemoteNode(...)" );
}

void multigrid::mappings::PlotCells::prepareCopyToRemoteNode(
  multigrid::Cell&  localCell,
      int                                           toRank,
      const tarch::la::Vector<DIMENSIONS,double>&   cellCentre,
      const tarch::la::Vector<DIMENSIONS,double>&   cellSize,
      int                                           level
) {
  logTraceInWith5Arguments( "prepareCopyToRemoteNode(...)", localCell, toRank, cellCentre, cellSize, level );
  // @todo Insert your code here
  logTraceOut( "prepareCopyToRemoteNode(...)" );
}

void multigrid::mappings::PlotCells::mergeWithRemoteDataDueToForkOrJoin(
  multigrid::Vertex&  localVertex,
  const multigrid::Vertex&  masterOrWorkerVertex,
  int                                       fromRank,
  const tarch::la::Vector<DIMENSIONS,double>&  x,
  const tarch::la::Vector<DIMENSIONS,double>&  h,
  int                                       level
) {
  logTraceInWith6Arguments( "mergeWithRemoteDataDueToForkOrJoin(...)", localVertex, masterOrWorkerVertex, fromRank, x, h, level );
  // @todo Insert your code here
  logTraceOut( "mergeWithRemoteDataDueToForkOrJoin(...)" );
}

void multigrid::mappings::PlotCells::mergeWithRemoteDataDueToForkOrJoin(
  multigrid::Cell&  localCell,
  const multigrid::Cell&  masterOrWorkerCell,
  int                                       fromRank,
  const tarch::la::Vector<DIMENSIONS,double>&  cellCentre,
  const tarch::la::Vector<DIMENSIONS,double>&  cellSize,
  int                                       level
) {
  logTraceInWith3Arguments( "mergeWithRemoteDataDueToForkOrJoin(...)", localCell, masterOrWorkerCell, fromRank );
  // @todo Insert your code here
  logTraceOut( "mergeWithRemoteDataDueToForkOrJoin(...)" );
}

bool multigrid::mappings::PlotCells::prepareSendToWorker(
  multigrid::Cell&                 fineGridCell,
  multigrid::Vertex * const        fineGridVertices,
  const peano::grid::VertexEnumerator&                fineGridVerticesEnumerator,
  multigrid::Vertex * const        coarseGridVertices,
  const peano::grid::VertexEnumerator&                coarseGridVerticesEnumerator,
  multigrid::Cell&                 coarseGridCell,
  const tarch::la::Vector<DIMENSIONS,int>&                             fineGridPositionOfCell,
  int                                                                  worker
) {
  logTraceIn( "prepareSendToWorker(...)" );
  // @todo Insert your code here
  logTraceOutWith1Argument( "prepareSendToWorker(...)", true );
  return true;
}

void multigrid::mappings::PlotCells::prepareSendToMaster(
  multigrid::Cell&                       localCell,
  multigrid::Vertex *                    vertices,
  const peano::grid::VertexEnumerator&       verticesEnumerator, 
  const multigrid::Vertex * const        coarseGridVertices,
  const peano::grid::VertexEnumerator&       coarseGridVerticesEnumerator,
  const multigrid::Cell&                 coarseGridCell,
  const tarch::la::Vector<DIMENSIONS,int>&   fineGridPositionOfCell
) {
  logTraceInWith2Arguments( "prepareSendToMaster(...)", localCell, verticesEnumerator.toString() );
  // @todo Insert your code here
  logTraceOut( "prepareSendToMaster(...)" );
}


void multigrid::mappings::PlotCells::mergeWithMaster(
  const multigrid::Cell&           workerGridCell,
  multigrid::Vertex * const        workerGridVertices,
 const peano::grid::VertexEnumerator& workerEnumerator,
  multigrid::Cell&                 fineGridCell,
  multigrid::Vertex * const        fineGridVertices,
  const peano::grid::VertexEnumerator&                fineGridVerticesEnumerator,
  multigrid::Vertex * const        coarseGridVertices,
  const peano::grid::VertexEnumerator&                coarseGridVerticesEnumerator,
  multigrid::Cell&                 coarseGridCell,
  const tarch::la::Vector<DIMENSIONS,int>&                             fineGridPositionOfCell,
  int                                                                  worker,
  const multigrid::State&          workerState,
  multigrid::State&                masterState
) {
  logTraceIn( "mergeWithMaster(...)" );
  // @todo Insert your code here
  logTraceOut( "mergeWithMaster(...)" );
}


void multigrid::mappings::PlotCells::receiveDataFromMaster(
      multigrid::Cell&                        receivedCell, 
      multigrid::Vertex *                     receivedVertices,
      const peano::grid::VertexEnumerator&        receivedVerticesEnumerator,
      multigrid::Vertex * const               receivedCoarseGridVertices,
      const peano::grid::VertexEnumerator&        receivedCoarseGridVerticesEnumerator,
      multigrid::Cell&                        receivedCoarseGridCell,
      multigrid::Vertex * const               workersCoarseGridVertices,
      const peano::grid::VertexEnumerator&        workersCoarseGridVerticesEnumerator,
      multigrid::Cell&                        workersCoarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&    fineGridPositionOfCell
) {
  logTraceIn( "receiveDataFromMaster(...)" );
  // @todo Insert your code here
  logTraceOut( "receiveDataFromMaster(...)" );
}


void multigrid::mappings::PlotCells::mergeWithWorker(
  multigrid::Cell&           localCell, 
  const multigrid::Cell&     receivedMasterCell,
  const tarch::la::Vector<DIMENSIONS,double>&  cellCentre,
  const tarch::la::Vector<DIMENSIONS,double>&  cellSize,
  int                                          level
) {
  logTraceInWith2Arguments( "mergeWithWorker(...)", localCell.toString(), receivedMasterCell.toString() );
  // @todo Insert your code here
  logTraceOutWith1Argument( "mergeWithWorker(...)", localCell.toString() );
}


void multigrid::mappings::PlotCells::mergeWithWorker(
  multigrid::Vertex&        localVertex,
  const multigrid::Vertex&  receivedMasterVertex,
  const tarch::la::Vector<DIMENSIONS,double>&   x,
  const tarch::la::Vector<DIMENSIONS,double>&   h,
  int                                           level
) {
  logTraceInWith2Arguments( "mergeWithWorker(...)", localVertex.toString(), receivedMasterVertex.toString() );
  // @todo Insert your code here
  logTraceOutWith1Argument( "mergeWithWorker(...)", localVertex.toString() );
}
#endif

void multigrid::mappings::PlotCells::touchVertexFirstTime(
      multigrid::Vertex&               fineGridVertex,
      const tarch::la::Vector<DIMENSIONS,double>&                          fineGridX,
      const tarch::la::Vector<DIMENSIONS,double>&                          fineGridH,
      multigrid::Vertex * const        coarseGridVertices,
      const peano::grid::VertexEnumerator&                coarseGridVerticesEnumerator,
      multigrid::Cell&                 coarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&                             fineGridPositionOfVertex
) {
  logTraceInWith6Arguments( "touchVertexFirstTime(...)", fineGridVertex, fineGridX, fineGridH, coarseGridVerticesEnumerator.toString(), coarseGridCell, fineGridPositionOfVertex );
  // @todo Insert your code here
  logTraceOutWith1Argument( "touchVertexFirstTime(...)", fineGridVertex );
}


void multigrid::mappings::PlotCells::touchVertexLastTime(
      multigrid::Vertex&         fineGridVertex,
      const tarch::la::Vector<DIMENSIONS,double>&                    fineGridX,
      const tarch::la::Vector<DIMENSIONS,double>&                    fineGridH,
      multigrid::Vertex * const  coarseGridVertices,
      const peano::grid::VertexEnumerator&          coarseGridVerticesEnumerator,
      multigrid::Cell&           coarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&                       fineGridPositionOfVertex
) {
  logTraceInWith6Arguments( "touchVertexLastTime(...)", fineGridVertex, fineGridX, fineGridH, coarseGridVerticesEnumerator.toString(), coarseGridCell, fineGridPositionOfVertex );
  // @todo Insert your code here
  logTraceOutWith1Argument( "touchVertexLastTime(...)", fineGridVertex );
}


void multigrid::mappings::PlotCells::enterCell(
      multigrid::Cell&                 fineGridCell,
      multigrid::Vertex * const        fineGridVertices,
      const peano::grid::VertexEnumerator&                fineGridVerticesEnumerator,
      multigrid::Vertex * const        coarseGridVertices,
      const peano::grid::VertexEnumerator&                coarseGridVerticesEnumerator,
      multigrid::Cell&                 coarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&                             fineGridPositionOfCell
) {
  logTraceInWith4Arguments( "enterCell(...)", fineGridCell, fineGridVerticesEnumerator.toString(), coarseGridCell, fineGridPositionOfCell );
  // @todo Insert your code here
  logTraceOutWith1Argument( "enterCell(...)", fineGridCell );
}


void multigrid::mappings::PlotCells::leaveCell(
      multigrid::Cell&           fineGridCell,
      multigrid::Vertex * const  fineGridVertices,
      const peano::grid::VertexEnumerator&          fineGridVerticesEnumerator,
      multigrid::Vertex * const  coarseGridVertices,
      const peano::grid::VertexEnumerator&          coarseGridVerticesEnumerator,
      multigrid::Cell&           coarseGridCell,
      const tarch::la::Vector<DIMENSIONS,int>&                       fineGridPositionOfCell
) {
  logTraceInWith4Arguments( "leaveCell(...)", fineGridCell, fineGridVerticesEnumerator.toString(), coarseGridCell, fineGridPositionOfCell );
  // @todo Insert your code here
  logTraceOutWith1Argument( "leaveCell(...)", fineGridCell );
}


void multigrid::mappings::PlotCells::beginIteration(
  multigrid::State&  solverState
) {
  logTraceInWith1Argument( "beginIteration(State)", solverState );
  // @todo Insert your code here
  logTraceOutWith1Argument( "beginIteration(State)", solverState);
}


void multigrid::mappings::PlotCells::endIteration(
  multigrid::State&  solverState
) {
  logTraceInWith1Argument( "endIteration(State)", solverState );
  // @todo Insert your code here
  logTraceOutWith1Argument( "endIteration(State)", solverState);
}



void multigrid::mappings::PlotCells::descend(
  multigrid::Cell * const          fineGridCells,
  multigrid::Vertex * const        fineGridVertices,
  const peano::grid::VertexEnumerator&                fineGridVerticesEnumerator,
  multigrid::Vertex * const        coarseGridVertices,
  const peano::grid::VertexEnumerator&                coarseGridVerticesEnumerator,
  multigrid::Cell&                 coarseGridCell
) {
  logTraceInWith2Arguments( "descend(...)", coarseGridCell.toString(), coarseGridVerticesEnumerator.toString() );
  // @todo Insert your code here
  logTraceOut( "descend(...)" );
}


void multigrid::mappings::PlotCells::ascend(
  multigrid::Cell * const    fineGridCells,
  multigrid::Vertex * const  fineGridVertices,
  const peano::grid::VertexEnumerator&          fineGridVerticesEnumerator,
  multigrid::Vertex * const  coarseGridVertices,
  const peano::grid::VertexEnumerator&          coarseGridVerticesEnumerator,
  multigrid::Cell&           coarseGridCell
) {
  logTraceInWith2Arguments( "ascend(...)", coarseGridCell.toString(), coarseGridVerticesEnumerator.toString() );
  // @todo Insert your code here
  logTraceOut( "ascend(...)" );
}
