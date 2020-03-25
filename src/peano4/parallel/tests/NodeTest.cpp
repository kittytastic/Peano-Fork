#include "NodeTest.h"
#include "../Node.h"

#include "tarch/la/Vector.h"

#include "peano4/grid/Spacetree.h"



tarch::logging::Log peano4::parallel::tests::NodeTest::_log("peano4::parallel::tests::NodeTest");


#ifdef UseTestSpecificCompilerSettings
#pragma optimize("",off)
#endif


peano4::parallel::tests::NodeTest::NodeTest():
  TestCase( "peano4::parallel::tests::NodeTest" ) {
}


void peano4::parallel::tests::NodeTest::testTagCalculation() {
  logTraceIn( "testTagCalculation()" );
  int tagA = peano4::parallel::Node::getInstance().getGridDataExchangeTag(0,5,peano4::parallel::Node::ExchangeMode::HorizontalData);
  int tagB = peano4::parallel::Node::getInstance().getGridDataExchangeTag(5,0,peano4::parallel::Node::ExchangeMode::HorizontalData);
  validateWithParams2(tagA!=tagB, tagA, tagB);
/*

  tagA = peano4::parallel::Node::getInstance().getGridDataExchangeTag(0,1,peano4::parallel::Node::ExchangeMode::HorizontalData);
  tagB = peano4::parallel::Node::getInstance().getGridDataExchangeTag(1,0,peano4::parallel::Node::ExchangeMode::HorizontalData);
  validateWithParams5(
   tagA!=tagB,
   tagA, tagB,
   peano4::parallel::Node::getInstance().getLocalTreeId(0),
   peano4::parallel::Node::MaxSpacetreesPerRank,
   peano4::parallel::Node::getInstance().getLocalTreeId(1)
  );
*/
  logTraceOut( "testTagCalculation()" );
}


void peano4::parallel::tests::NodeTest::testGetPeriodicBoundaryNumber() {
  #if Dimensions==2
  tarch::la::Vector<TwoPowerD,int>  flags(1);
  flags(0) = peano4::grid::Spacetree::RankOfPeriodicBoundaryCondition;
  flags(1) = peano4::grid::Spacetree::RankOfPeriodicBoundaryCondition;

  std::bitset<2*Dimensions> result = peano4::parallel::Node::getPeriodicBoundaryNumber(flags);
  validateEqualsWithParams1( result.to_ulong(), 2, flags );
  #endif
}


void peano4::parallel::tests::NodeTest::run() {
  logTraceIn( "run()" );
  testMethod( testGetPeriodicBoundaryNumber );
  testMethod( testTagCalculation );
  logTraceOut( "run()" );
}


#ifdef UseTestSpecificCompilerSettings
#pragma optimize("",on)
#endif
