#include "UnitTests.h"


#include "tarch/tests/TreeTestCaseCollection.h"


#include "tarch/la/tests/GramSchmidtTest.h"
#include "tarch/la/tests/LUDecompositionTest.h"
#include "tarch/la/tests/MatrixTest.h"
#include "tarch/la/tests/MatrixVectorTest.h"
#include "tarch/la/tests/ScalarTest.h"
#include "tarch/la/tests/VectorTest.h"



tarch::tests::TestCase* tarch::getUnitTests() {
  tarch::tests::TreeTestCaseCollection* result = new tarch::tests::TreeTestCaseCollection("");

  result->addTestCase( new tarch::la::tests::GramSchmidtTest() );
  result->addTestCase( new tarch::la::tests::LUDecompositionTest() );
  result->addTestCase( new tarch::la::tests::MatrixTest() );
  result->addTestCase( new tarch::la::tests::MatrixVectorTest() );
  result->addTestCase( new tarch::la::tests::ScalarTest() );
  result->addTestCase( new tarch::la::tests::VectorTest() );

  return result;
}
