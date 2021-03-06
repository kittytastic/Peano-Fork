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
  if (tarch::mpi::Rank::getInstance().getNumberOfRanks()<5) {
    Node::GridDataExchangeMetaInformation metaInfoA = peano4::parallel::Node::getInstance().getGridDataExchangeMetaInformation(0,5,peano4::parallel::Node::ExchangeMode::HorizontalData);
    Node::GridDataExchangeMetaInformation metaInfoB = peano4::parallel::Node::getInstance().getGridDataExchangeMetaInformation(5,0,peano4::parallel::Node::ExchangeMode::HorizontalData);
    validateWithParams6(metaInfoA.first!=metaInfoB.first,
      metaInfoA.first, metaInfoB.first,
      Node::StacksPerCommunicationPartner, peano4::parallel::Node::getInstance().getLocalTreeId(0),
      peano4::parallel::Node::getInstance().getLocalTreeId(5), Node::MaxSpacetreesPerRank
    );
  }
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
