#include "peano/geometry/Hexahedron.h"
#include "peano/utils/Loop.h"


tarch::logging::Log peano::geometry::Hexahedron::_log( "peano::geometry::Hexahedron" );


bool peano::geometry::Hexahedron::greaterUpToRelativeTolerance(const double& lhs, const double& rhs) {
  // --(false)---eps---(false)---rtol---(true)-->
  if ( tarch::la::smallerEquals( lhs, rhs, tarch::la::NUMERICAL_ZERO_DIFFERENCE ) ) {
    return false; // is smaller equals w.r.t. machine precision
  } else { // adjust the tolerance to the scale
    const double tolerance =
      tarch::la::NUMERICAL_ZERO_DIFFERENCE *
      tarch::la::max( 1.0, tarch::la::abs(lhs), tarch::la::abs(rhs) );
    return tarch::la::greater( lhs, rhs, tolerance );
  }
}

bool peano::geometry::Hexahedron::smallerUpToRelativeTolerance(const double& lhs, const double& rhs) {
  // --(true)---eps---(true)---rtol---(false)-->
  if ( tarch::la::smaller( lhs, rhs, tarch::la::NUMERICAL_ZERO_DIFFERENCE ) ) {
      return true; // is smaller  w.r.t. machine precision
  } else { // adjust the absolute tolerance to the scale
    const double tolerance =
        tarch::la::NUMERICAL_ZERO_DIFFERENCE *
        tarch::la::max( 1.0, tarch::la::abs(lhs), tarch::la::abs(rhs) );
    return tarch::la::smaller( lhs, rhs, tolerance );
  }
}

bool peano::geometry::Hexahedron::greaterEqualsUpToRelativeTolerance(const double& lhs, const double& rhs) {
  // --(false)---eps---(false)---rtol---(true)-->
  if ( tarch::la::smaller( lhs, rhs, tarch::la::NUMERICAL_ZERO_DIFFERENCE) ) {
    return false; // is smaller  w.r.t. machine precision
  } else { // adjust the tolerance to the scale
    const double tolerance =
        tarch::la::NUMERICAL_ZERO_DIFFERENCE *
        tarch::la::max( 1.0, tarch::la::abs(lhs), tarch::la::abs(rhs) );
    return tarch::la::greaterEquals( lhs, rhs, tolerance );
  }
}

bool peano::geometry::Hexahedron::smallerEqualsUpToRelativeTolerance(const double& lhs, const double& rhs) {
  // --(true)---eps---(true)---rtol---(false)-->
  if ( tarch::la::smallerEquals( lhs, rhs, tarch::la::NUMERICAL_ZERO_DIFFERENCE ) ) {
    return true; // is smaller equals w.r.t. machine precision 
  } else { // adjust the absolute tolerance to the scale
    const double tolerance =
        tarch::la::NUMERICAL_ZERO_DIFFERENCE *
        tarch::la::max( 1.0, tarch::la::abs(lhs), tarch::la::abs(rhs) );
    return tarch::la::smallerEquals( lhs, rhs, tolerance );
  }
}

peano::geometry::Hexahedron::Hexahedron(
  const tarch::la::Vector<DIMENSIONS,double>&  width,
  const tarch::la::Vector<DIMENSIONS,double>&  offset
):
  _offset(offset),
  _width(width) {

  for (int d=0; d<DIMENSIONS; d++) {
    assertion2( _width(d)>0.0, _width, _offset);
  }
  logDebug(
    "Hexahedron(...)",
    "created hexahedron with width " << _width
      << " at " << _offset << " (left bottom (front) point)"
  );
}


peano::geometry::Hexahedron::~Hexahedron() {}


bool peano::geometry::Hexahedron::domainHasChanged( const tarch::la::Vector<DIMENSIONS,double>& x, const tarch::la::Vector<DIMENSIONS,double> &resolution ) {
  return false;
}


bool peano::geometry::Hexahedron::isInsideOpenHexahedron( const tarch::la::Vector<DIMENSIONS,double>& x ) const {
  logTraceInWith3Arguments("isInsideOpenHexahedron(...)", x, _offset, _width);
  bool result = true;
  for (int d=0; d<DIMENSIONS; d++) {
    assertion( _width(d) >= 0.0 );
    result = result && greaterUpToRelativeTolerance(x(d),_offset(d));
    result = result && smallerUpToRelativeTolerance(x(d),_offset(d)+_width(d));
  }
  logTraceOutWith1Argument("isInsideOpenHexahedron(...)", result);
  return result;
}


bool peano::geometry::Hexahedron::isInsideClosedHexahedron( const tarch::la::Vector<DIMENSIONS,double>& x ) const {
  logTraceInWith1Argument("isInsideClosedHexahedron(...)", x);
  bool result = true;
  for (int d=0; d<DIMENSIONS; d++) {
    assertion( _width(d) >= 0.0 );
    result = result && !smallerUpToRelativeTolerance(x(d),_offset(d));
    result = result && !greaterUpToRelativeTolerance(x(d),_offset(d)+_width(d));
  }
  logTraceOutWith1Argument("isInsideClosedHexahedron(...)", result);
  return result;
}


tarch::la::Vector<DIMENSIONS,double> peano::geometry::Hexahedron::getOffset() const {
  return _offset;
}


tarch::la::Vector<DIMENSIONS,double> peano::geometry::Hexahedron::getBoundingBox() const {
  return _width;
}


bool peano::geometry::Hexahedron::isOutsideClosedDomain( const tarch::la::Vector<DIMENSIONS,double>& x ) {
  return !isInsideClosedHexahedron(x);
}


bool peano::geometry::Hexahedron::isCompletelyOutside( const tarch::la::Vector<DIMENSIONS,double>& x, const tarch::la::Vector<DIMENSIONS,double> &resolution ) {
//  logTraceInWith2Arguments( "isCompletelyInside(...)", x, resolution);
/*
  bool result = false;
  for( int i = 0; i < DIMENSIONS; i++ ){
    bool dimResult = true;
    dimResult &= !(smallerUpToRelativeTolerance(x(i) - resolution(i), _offset(i) + _width(i)) &&
                greaterUpToRelativeTolerance(x(i) - resolution(i), _offset(i)));
    dimResult &= !(smallerUpToRelativeTolerance(x(i) + resolution(i), _offset(i) + _width(i)) &&
                greaterUpToRelativeTolerance(x(i) + resolution(i), _offset(i)));
    dimResult &= !(!greaterUpToRelativeTolerance(x(i) - resolution(i), _offset(i)) &&
                !smallerUpToRelativeTolerance(x(i) + resolution(i), _offset(i) + _width(i)));
    result |= dimResult;
  }
*/


  bool inside = true;
  for (int d=0; d<DIMENSIONS; d++) {
    inside = inside && !smallerEqualsUpToRelativeTolerance(x(d),_offset(d)-resolution(d));
    inside = inside && !greaterEqualsUpToRelativeTolerance(x(d),_offset(d)+_width(d)+resolution(d));
  }
  logDebug( "isCompletelyOutside(...)", x << "x" << resolution << ":" << !inside );
  return !inside;
}


bool peano::geometry::Hexahedron::isCompletelyInside( const tarch::la::Vector<DIMENSIONS,double>& x, const tarch::la::Vector<DIMENSIONS,double> &resolution ) {
  logTraceInWith2Arguments( "isCompletelyInside(...)", x, resolution);
  bool result = isInsideOpenHexahedron(x);

  dfor2(i)
    tarch::la::Vector<DIMENSIONS,double> currentPoint0;
    tarch::la::Vector<DIMENSIONS,double> currentPoint1;
    for (int d=0; d<DIMENSIONS; d++) {
      currentPoint0(d) = (i(d)==0) ? x(d)-0.5*resolution(d) : x(d)+0.5*resolution(d);
      currentPoint1(d) = (i(d)==0) ? x(d)-1.0*resolution(d) : x(d)+1.0*resolution(d);
    }
    result = result && isInsideClosedHexahedron(currentPoint0);
    result = result && isInsideClosedHexahedron(currentPoint1);
   enddforx

  logTraceOutWith1Argument("isCompletelyInside(...)", result);
  return result;
}

