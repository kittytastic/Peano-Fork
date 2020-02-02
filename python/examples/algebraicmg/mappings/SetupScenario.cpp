#include "SetupScenario.h"


tarch::logging::Log examples::algebraicmg::mappings::SetupScenario::_log( "examples::algebraicmg::mappings::SetupScenario");


examples::algebraicmg::mappings::SetupScenario::SetupScenario(int treeNumber) {
// @todo Please implement
}


examples::algebraicmg::mappings::SetupScenario::~SetupScenario() {
// @todo Please implement
}


std::vector< peano4::grid::GridControlEvent > examples::algebraicmg::mappings::SetupScenario::getGridControlEvents() {
// @todo Please implement
return std::vector< peano4::grid::GridControlEvent >();
}


void examples::algebraicmg::mappings::SetupScenario::beginTraversal(
      ) {
// @todo Please implement
}


void examples::algebraicmg::mappings::SetupScenario::endTraversal(
      ) {
// @todo Please implement
}


void examples::algebraicmg::mappings::SetupScenario::createPersistentVertex(
  const tarch::la::Vector<Dimensions,double>& center,
  const tarch::la::Vector<Dimensions,double>& h,
  examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
  peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG
) {
}


void examples::algebraicmg::mappings::SetupScenario::destroyPersistentVertex(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {
// @todo Please implement
}


void examples::algebraicmg::mappings::SetupScenario::createHangingVertex(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {
// @todo Please implement
}


void examples::algebraicmg::mappings::SetupScenario::destroyHangingVertex(
      const tarch::la::Vector<Dimensions,double>& center,
      const tarch::la::Vector<Dimensions,double>& h,
      examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG) {
// @todo Please implement
}


examples::algebraicmg::vertexdata::MG::VertexType examples::algebraicmg::mappings::SetupScenario::getVertexType(const tarch::la::Vector<Dimensions,double>& x) {
  examples::algebraicmg::vertexdata::MG::VertexType result;
  switch (_scenario) {
    case Scenario::Mitchell:
      {
        const bool isBoundaryVertex =
          tarch::la::oneEquals(x,0.0)
          or
          tarch::la::oneEquals(x,1.0);

        result = isBoundaryVertex ? examples::algebraicmg::vertexdata::MG::VertexType::Boundary
                                  : examples::algebraicmg::vertexdata::MG::VertexType::Inside;
      }
      break;
    case Scenario::Ruede:
    {
      const bool isBoundaryVertex =
        tarch::la::oneEquals(x,-1.0)
        or
        tarch::la::oneEquals(x,1.0);

      result = isBoundaryVertex ? examples::algebraicmg::vertexdata::MG::VertexType::Boundary
                                : examples::algebraicmg::vertexdata::MG::VertexType::Inside;
      }
      break;
  }
  return result;
}


double examples::algebraicmg::mappings::SetupScenario::getSolution(const tarch::la::Vector<Dimensions,double>& x) {
  double result;
  switch (_scenario) {
    case Scenario::Mitchell:
      {
        tarch::la::Vector<Dimensions,double> c(0.0);
        const double alpha = 20.0;
        c(0)               = -0.05;
        c(1)               = -0.05;
        const double r0    =  0.7;

        double r = tarch::la::norm2(x-c);

        result = std::atan(alpha*(r-r0));
      }
      break;
    case Scenario::Ruede:
      {
        result = std::cos( 2.0*tarch::la::PI * (x(0)-x(1)) )
               * std::sinh( 2.0*tarch::la::PI * (x(0)+x(1)+2.0) )
               / std::sinh( 8.0*tarch::la::PI );
      }
      break;
  }
  return result;
}


void   examples::algebraicmg::mappings::SetupScenario::init(const tarch::la::Vector<Dimensions,double>& x, examples::algebraicmg::vertexdata::MG& fineGridVertexMG) {
  if ( getVertexType(x)==examples::algebraicmg::vertexdata::MG::VertexType::Boundary ) {
    fineGridVertexMG.setVertexType( examples::algebraicmg::vertexdata::MG::VertexType::Boundary );
    fineGridVertexMG.setU( getSolution(x) );
    fineGridVertexMG.setRhs( 0.0 );
    // @todo Document: Important to allow fusion
    fineGridVertexMG.setDiag( 1.0 );
  }
  else {
    const double Max = _scenario==Scenario::Mitchell ?  tarch::la::PI/2.0 :  1.0;
    const double Min = _scenario==Scenario::Mitchell ? -tarch::la::PI/2.0 : -1.0;

    const double scaledRandomValue = static_cast<double>( std::rand() ) /  static_cast<double>(RAND_MAX);
    fineGridVertexMG.setVertexType( examples::algebraicmg::vertexdata::MG::VertexType::Inside );
    fineGridVertexMG.setU( Min + scaledRandomValue*(Max-Min) );
    fineGridVertexMG.setRhs( 0.0 );
    fineGridVertexMG.setDiag( 1.0 );
  }
}


void examples::algebraicmg::mappings::SetupScenario::touchVertexFirstTime(
  const tarch::la::Vector<Dimensions,double>& center,
  const tarch::la::Vector<Dimensions,double>& h,
  examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
  peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG
) {
  init( center, fineGridVertexMG );
}


void examples::algebraicmg::mappings::SetupScenario::touchVertexLastTime(
  const tarch::la::Vector<Dimensions,double>& center,
  const tarch::la::Vector<Dimensions,double>& h,
  examples::algebraicmg::vertexdata::MG& fineGridVertexMG,
  peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG
) {
}


void examples::algebraicmg::mappings::SetupScenario::touchCellFirstTime(
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> fineGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> fineGridCell,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> coarseGridCell) {
// @todo Please implement
}


void examples::algebraicmg::mappings::SetupScenario::touchCellLastTime(
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> fineGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> fineGridCell,
      peano4::datamanagement::VertexEnumerator<examples::algebraicmg::vertexdata::MG> coarseGridVerticesMG,
      peano4::datamanagement::CellWrapper<void> coarseGridCell) {
// @todo Please implement
}


