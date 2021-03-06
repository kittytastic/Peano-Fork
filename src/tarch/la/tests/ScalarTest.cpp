#include "tarch/la/tests/ScalarTest.h"

#include "tarch/la/ScalarOperations.h"

#include "tarch/compiler/CompilerSpecificSettings.h"



tarch::la::tests::ScalarTest::ScalarTest():
  TestCase("tarch::la::ScalarTest") {
}


void tarch::la::tests::ScalarTest::run () {
  testMethod (testComparison);
  testMethod (testAbs);
}

void tarch::la::tests::ScalarTest::testComparison()
{
  double a = 1.0;
  double b = 2.0;
  double eps = 1e-14;

  validate (greater(b, a, eps));
  validate (! greater(a, a - eps, eps));
  validate (greater(a, a - 10.0 * eps, eps));

  validate (! greaterEquals(a, b, eps));
  validate (greaterEquals(b, a, eps));
  validate (greaterEquals(a, a, eps));
  validate (greaterEquals(a, a + 0.1*eps, eps));
  validate (! greaterEquals(a, a + 10*eps, eps));

  validate (smaller(a, b, eps));
  validate (! smaller(a, a + eps, eps));
  validate (smaller(a, a + 10.0 * eps, eps));

  validate (smallerEquals(a, b, eps));
  validate (smallerEquals(a, a + eps, eps));
  validate (smallerEquals(a + eps, a, eps));
  validate (smallerEquals(a, a + 10.0 * eps, eps));

  validate (! equals(a, b, eps));
  validate (equals(a, a, eps));
  validate (equals(a, a + eps, eps));
  validate (! equals(a, a + 10.0 * eps, eps));
  validate (equals(a, a + 10.0 * eps, 10.0 * eps));
}

void tarch::la::tests::ScalarTest::testAbs()
{
  double a = -1.0;
  int b = -1;

  validateEquals (abs(a), 1.0);
  validateEquals (abs(b), 1);
}

