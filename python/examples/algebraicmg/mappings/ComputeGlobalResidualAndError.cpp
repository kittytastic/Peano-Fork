#include "ComputeGlobalResidualAndError.h"
#include "SetupScenario.h"

#include "tarch/tarch.h"


tarch::logging::Log examples::algebraicmg::mappings::ComputeGlobalResidualAndError::_log( "examples::algebraicmg::mappings::ComputeGlobalResidualAndError");


examples::algebraicmg::mappings::ComputeGlobalResidualAndError::ComputeGlobalResidualAndError(int treeNumber) {
// @todo Please implement
}


examples::algebraicmg::mappings::ComputeGlobalResidualAndError::~ComputeGlobalResidualAndError() {
// @todo Please implement
}


std::vector< peano4::grid::GridControlEvent > examples::algebraicmg::mappings::ComputeGlobalResidualAndError::getGridControlEvents() {
// @todo Please implement
return std::vector< peano4::grid::GridControlEvent >();
}


void examples::algebraicmg::mappings::ComputeGlobalResidualAndError::beginTraversal() {
  _globalResidualL2        = 0.0;
  _globalResidualMax       = 0.0;
  _globalResidualEukledian = 0.0;
  _globalErrorL2           = 0.0;
  _globalErrorMax          = 0.0;
  _globalErrorEukledian    = 0.0;
}


void examples::algebraicmg::mappings::ComputeGlobalResidualAndError::endTraversal() {
  logInfo(
    "endTraversal",
    " \t |res|_h="   << std::sqrt(_globalResidualL2) <<
    " \t |res|_max=" << _globalResidualMax <<
    " \t |res|_2="   << std::sqrt(_globalResidualEukledian) <<
    " \t |e|_h="     << std::sqrt(_globalErrorL2) <<
    " \t |e|_max="   << _globalErrorMax <<
    " \t |e|_2="     << std::sqrt(_globalErrorEukledian) <<
	" \t mem="       << tarch::getMemoryUsage(tarch::MemoryUsageFormat::MByte) << "MB"
  );
}


void examples::algebraicmg::mappings::ComputeGlobalResidualAndError::createPersistentVertex(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {
// @todo Please implement
}


void examples::algebraicmg::mappings::ComputeGlobalResidualAndError::destroyPersistentVertex(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {
// @todo Please implement
}


void examples::algebraicmg::mappings::ComputeGlobalResidualAndError::createHangingVertex(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {
// @todo Please implement
}


void examples::algebraicmg::mappings::ComputeGlobalResidualAndError::destroyHangingVertex(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {
// @todo Please implement
}


void examples::algebraicmg::mappings::ComputeGlobalResidualAndError::touchVertexFirstTime(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {
// @todo Please implement
}


void examples::algebraicmg::mappings::ComputeGlobalResidualAndError::touchVertexLastTime(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {
  double solution = SetupScenario::getSolution(center);
  double error    = fineGridVertexMG.getU() - solution;

  _globalResidualMax         = std::max( _globalResidualMax, fineGridVertexMG.getRes() );
  _globalResidualL2         += fineGridVertexMG.getRes() * fineGridVertexMG.getRes() * tarch::la::volume(h);
  _globalResidualEukledian  += fineGridVertexMG.getRes() * fineGridVertexMG.getRes();

  _globalErrorMax         = std::max( _globalErrorMax, std::abs(error) );
  _globalErrorL2         += error * error * tarch::la::volume(h);
  _globalErrorEukledian  += error * error;
}


void examples::algebraicmg::mappings::ComputeGlobalResidualAndError::touchCellFirstTime(
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> fineGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> fineGridCell,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> coarseGridCell) {
// @todo Please implement
}


void examples::algebraicmg::mappings::ComputeGlobalResidualAndError::touchCellLastTime(
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> fineGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> fineGridCell,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> coarseGridCell) {
// @todo Please implement
}


