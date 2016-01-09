#include "multigrid/Vertex.h"
#include "peano/utils/Loop.h"
#include "peano/grid/Checkpoint.h"


multigrid::Vertex::Vertex():
  Base() { 
  // @todo Insert your code here
}


multigrid::Vertex::Vertex(const Base::DoNotCallStandardConstructor& value):
  Base(value) { 
  // Please do not insert anything here
}


multigrid::Vertex::Vertex(const Base::PersistentVertex& argument):
  Base(argument) {
  // @todo Insert your code here
}


void multigrid::Vertex::initInnerVertex(double f, const tarch::la::Vector<DIMENSIONS,double>&  fineGridH) {
  _vertexData.setVertexType( Records::Unknown );
  _vertexData.setU(0.0);
  _vertexData.setF(f * tarch::la::volume(fineGridH) );
}


void multigrid::Vertex::initDirichletVertex(double u) {
  _vertexData.setVertexType( Records::Dirichlet );
  _vertexData.setU(u);
}


double multigrid::Vertex::getF() const {
  return _vertexData.getF();
}


void multigrid::Vertex::clearF() {
  return _vertexData.setF(0.0);
}


double multigrid::Vertex::getResidual() const {
  return _vertexData.getF() + _vertexData.getR();
}


double multigrid::Vertex::getHierarchicalResidual() const {
  return _vertexData.getF() + _vertexData.getHierarchicalR();
}


double multigrid::Vertex::getU() const {
  return _vertexData.getU();
}


void multigrid::Vertex::clearAccumulatedAttributes() {
  _vertexData.setR(0.0);
  _vertexData.setD(0.0);
}


bool multigrid::Vertex::performJacobiSmoothingStep( double omega ) {
  if ( _vertexData.getVertexType()== Records::Unknown ) {
    assertion1( _vertexData.getD()>0.0, toString() );
    assertion2( omega>0.0, toString(), omega );
    const double update = omega / _vertexData.getD() * getResidual();
    _vertexData.setU( _vertexData.getU() + update );
    _vertexData.setUUpdate( update );
     return getRefinementControl()==Vertex::Records::Unrefined;
  }
  else {
    return false;
  }
}


void multigrid::Vertex::inject(const Vertex& fineGridVertex) {
  _vertexData.setU( fineGridVertex._vertexData.getU() );
}


void multigrid::Vertex::setU( double u ) {
  _vertexData.setU( u );
}


void multigrid::Vertex::incF(double value) {
  _vertexData.setF( _vertexData.getF()+value );
}


void multigrid::Vertex::clearHierarchicalValues() {
  _vertexData.setHierarchicalU(0.0);
  _vertexData.setHierarchicalR(0.0);
}


void multigrid::Vertex::determineUHierarchical(double Pu_3h) {
  _vertexData.setHierarchicalU( _vertexData.getU()-Pu_3h );
}
