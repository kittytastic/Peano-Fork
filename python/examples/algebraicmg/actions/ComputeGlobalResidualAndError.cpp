#include "ComputeGlobalResidualAndError.h"
#include "SetupScenario.h"


#include "tarch/tarch.h"


tarch::logging::Log examples::algebraicmg::actions::ComputeGlobalResidualAndError::_log( "examples::algebraicmg::actions::ComputeGlobalResidualAndError");

examples::algebraicmg::actions::ComputeGlobalResidualAndError::ComputeGlobalResidualAndError(int treeNumber) {}

examples::algebraicmg::actions::ComputeGlobalResidualAndError::~ComputeGlobalResidualAndError() {}


std::vector< peano4::grid::GridControlEvent > examples::algebraicmg::actions::ComputeGlobalResidualAndError::getGridControlEvents() {
  return std::vector< peano4::grid::GridControlEvent >();
}


void examples::algebraicmg::actions::ComputeGlobalResidualAndError::beginTraversal() {
  _globalResidualL2        = 0.0;
  _globalResidualMax       = 0.0;
  _globalResidualEukledian = 0.0;
  _globalErrorL2           = 0.0;
  _globalErrorMax          = 0.0;
  _globalErrorEukledian    = 0.0;
}


void examples::algebraicmg::actions::ComputeGlobalResidualAndError::endTraversal() {
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


void examples::algebraicmg::actions::ComputeGlobalResidualAndError::createPersistentVertex(
      const peano4::datamanagement::VertexMarker& marker,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {}

void examples::algebraicmg::actions::ComputeGlobalResidualAndError::destroyPersistentVertex(
      const peano4::datamanagement::VertexMarker& marker,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {}

void examples::algebraicmg::actions::ComputeGlobalResidualAndError::createHangingVertex(
      const peano4::datamanagement::VertexMarker& marker,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {}

void examples::algebraicmg::actions::ComputeGlobalResidualAndError::destroyHangingVertex(
      const peano4::datamanagement::VertexMarker& marker,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {}

void examples::algebraicmg::actions::ComputeGlobalResidualAndError::touchVertexFirstTime(
      const peano4::datamanagement::VertexMarker& marker,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {}

void examples::algebraicmg::actions::ComputeGlobalResidualAndError::touchCellFirstTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> fineGridVerticesMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {}

void examples::algebraicmg::actions::ComputeGlobalResidualAndError::touchCellLastTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> fineGridVerticesMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {}


void examples::algebraicmg::actions::ComputeGlobalResidualAndError::touchVertexLastTime(
      const peano4::datamanagement::VertexMarker& marker,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG
) {
  if (not marker.isRefined()) {
    double solution = SetupScenario::getSolution(marker.x());
    double error    = fineGridVertexMG.getU() - solution;

    _globalResidualMax         = std::max( _globalResidualMax, fineGridVertexMG.getRes() );
    _globalResidualL2         += fineGridVertexMG.getRes() * fineGridVertexMG.getRes() * tarch::la::volume(marker.h());
    _globalResidualEukledian  += fineGridVertexMG.getRes() * fineGridVertexMG.getRes();

    _globalErrorMax         = std::max( _globalErrorMax, std::abs(error) );
    _globalErrorL2         += error * error * tarch::la::volume(marker.h());
    _globalErrorEukledian  += error * error;
  }
}
