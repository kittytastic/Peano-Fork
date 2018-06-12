#include "myproject/Cell.h"


myproject::Cell::Cell():
  Base() { 
}


void myproject::Cell::init(const tarch::la::Vector<DIMENSIONS,double>&  x) {
  _cellData.setEpsilon( x(1) * x(2) + static_cast<double>(rand() % 100)/100.0 );
}


double myproject::Cell::getEpsilon() const {
  return _cellData.getEpsilon();
}

myproject::Cell::Cell(const Base::DoNotCallStandardConstructor& value):
  Base(value) { 
  // Please do not insert anything here
}

myproject::Cell::Cell(const Base::PersistentCell& argument):
  Base(argument) {
  // @todo Insert your code here
}
