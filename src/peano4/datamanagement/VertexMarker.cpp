#include "VertexMarker.h"


peano4::datamanagement::VertexMarker::VertexMarker(
  const peano4::grid::GridTraversalEvent&   event
):
  _cellCentre(event.getX()),
  _h(event.getH()),
  _select(0) {
/*
  ,
}
  _isRefined(event.getIsRefined()) {
*/
  for (int i=0; i<TwoPowerD; i++) {
    _isRefined[i]  = event.getIsRefined(i);
  }
}


tarch::la::Vector<Dimensions,double> peano4::datamanagement::VertexMarker::x(int i) const {
  tarch::la::Vector<Dimensions,double> result( _cellCentre );
  std::bitset<Dimensions> myset(i);
  for (int d=0; d<Dimensions; d++) {
    result(d) -= 0.5 * _h(d);
    result(d) += static_cast<double>(myset[d]) * _h(d);
  }
  return result;
}


tarch::la::Vector<Dimensions,double> peano4::datamanagement::VertexMarker::x() const {
  return x(_select);
}


std::string peano4::datamanagement::VertexMarker::toString() const {
  return "(" + _cellCentre.toString() + "," + _h.toString() + ")";
}


tarch::la::Vector<Dimensions,double>  peano4::datamanagement::VertexMarker::h() const {
  return _h;
}


peano4::datamanagement::VertexMarker& peano4::datamanagement::VertexMarker::select(int vertexNumber) {
  assertion2(vertexNumber>=0,vertexNumber,toString());
  assertion2(vertexNumber<TwoPowerD,vertexNumber,toString());
  _select = vertexNumber;
  return *this;
}


bool peano4::datamanagement::VertexMarker::isRefined() const {
  return isRefined(_select);
}


bool peano4::datamanagement::VertexMarker::isRefined(int i) const {
  return _isRefined[i];
}

