#include "VertexMarker.h"


std::ostream& operator<<( std::ostream& out, const peano4::datamanagement::VertexMarker& marker ) {
  out << marker.toString();
  return out;
}


peano4::datamanagement::VertexMarker::VertexMarker(
  const peano4::grid::GridTraversalEvent&   event,
  int                                       select
):
  _cellCentre(event.getX()),
  _h(event.getH()),
  _select(select) {
  _hasBeenRefined                         = event.getHasBeenRefined();
  _willBeRefined                          = event.getWillBeRefined();
  _isLocal                                = event.getIsVertexLocal();
  //_isAdjacentToParallelDomainBoundary     = event.getIsRefined();
  _relativePositionOfCellWithinFatherCell = event.getRelativePositionToFather();
}


tarch::la::Vector<Dimensions,int>  peano4::datamanagement::VertexMarker::getRelativePositionWithinFatherCell() const {
  return getRelativePositionWithinFatherCell(_select);
}


tarch::la::Vector<Dimensions,int>  peano4::datamanagement::VertexMarker::getRelativePositionWithinFatherCell(int i) const {
  tarch::la::Vector<Dimensions,int> result = _relativePositionOfCellWithinFatherCell;
  std::bitset<Dimensions> index = i;
  for (int d=0; d<Dimensions; d++) {
    result(d) += index[d] ? 1 : 0;
  }
  return result;
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
  std::ostringstream msg;
  msg << "(" << _cellCentre << "," << _h << ",select=" << _select << ")";
  return msg.str();
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


int peano4::datamanagement::VertexMarker::getSelectedVertexNumber() const {
  return _select;
}


bool peano4::datamanagement::VertexMarker::hasBeenRefined() const {
  return hasBeenRefined(_select);
}


bool peano4::datamanagement::VertexMarker::hasBeenRefined(int i) const {
  return _hasBeenRefined[i];
}


bool peano4::datamanagement::VertexMarker::willBeRefined() const {
  return willBeRefined(_select);
}


bool peano4::datamanagement::VertexMarker::willBeRefined(int i) const {
  return _willBeRefined[i];
}


bool peano4::datamanagement::VertexMarker::isLocal() const {
  return isLocal(_select);
}


bool peano4::datamanagement::VertexMarker::isLocal(int i) const {
  return _isLocal[i];
}


/*
bool peano4::datamanagement::VertexMarker::isAdjacentToParallelDomainBoundary() const {
  return isAdjacentToParallelDomainBoundary(_select);
}


bool peano4::datamanagement::VertexMarker::isAdjacentToParallelDomainBoundary(int i) const {
  return _isAdjacentToParallelDomainBoundary[i];
}
*/

