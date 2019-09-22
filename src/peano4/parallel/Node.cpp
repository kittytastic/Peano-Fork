#include "Node.h"
#include "StartTraversalMessage.h"
#include "TreeManagementMessage.h"


#include "peano4/grid/Spacetree.h"
#include "peano4/grid/PeanoCurve.h"
#include "peano4/grid/AutomatonState.h"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds


#include "tarch/Assertions.h"
#include "tarch/mpi/Rank.h"
#include "tarch/multicore/Tasks.h"
#include "tarch/multicore/Lock.h"


tarch::logging::Log  peano4::parallel::Node::_log("peano4::parallel::Node");


void peano4::parallel::Node::initMPIDatatypes() {
  #ifdef Parallel
  StartTraversalMessage::initDatatype();
  TreeManagementMessage::initDatatype();

  peano4::grid::AutomatonState::initDatatype();
  peano4::grid::GridVertex::initDatatype();
  #endif
}


void peano4::parallel::Node::shutdownMPIDatatypes() {
  #ifdef Parallel
  StartTraversalMessage::shutdownDatatype();
  TreeManagementMessage::shutdownDatatype();

  peano4::grid::AutomatonState::shutdownDatatype();
  peano4::grid::GridVertex::shutdownDatatype();
  #endif
}


peano4::parallel::Node::Node():
  _currentProgramStep(UndefProgramStep),
  _rankOrchestrationTag( tarch::mpi::Rank::reserveFreeTag("peano4::parallel::Node") ),
  _treeManagementTag( tarch::mpi::Rank::reserveFreeTag("peano4::parallel::Node") ),
  _dataExchangeBaseTag( tarch::mpi::Rank::reserveFreeTag("peano4::parallel::Node", ReservedMPITagsForDataExchange) ) {
  if (tarch::mpi::Rank::getInstance().isGlobalMaster()) {
    registerId( 0, -1);
  }
}


peano4::parallel::Node::~Node() {
  assertionMsg( tarch::mpi::Rank::getInstance().getNumberOfRanks()==1 or _currentProgramStep==Terminate, "forgot to terminate node properly through peano4::parallel::Node::getInstance().shutdown()" );
}


int peano4::parallel::Node::getGridDataExchangeTag( int sendingTreeId, int receivingTreeId, ExchangeMode exchange ) {
  int result  = _dataExchangeBaseTag;
  result     += getLocalTreeId(sendingTreeId) * 2;
  switch (exchange) {
    case ExchangeMode::ReceiveHorizontalData:
    case ExchangeMode::SendHorizontalData:
      break;
    case ExchangeMode::ReceiveVerticalData:
    case ExchangeMode::SendVerticalData:
      result += 1;
      break;
  }
  return result;
}


bool peano4::parallel::Node::isGlobalMaster(int treeId) {
  return treeId==0;
}


peano4::parallel::Node& peano4::parallel::Node::getInstance() {
  static Node singleton;
  return singleton;
}


int peano4::parallel::Node::getId(int rank, int localTreeId) const {
  const int numberOfRanks = tarch::mpi::Rank::getInstance().getNumberOfRanks();
  return numberOfRanks * localTreeId + rank;
}


int peano4::parallel::Node::getRank(int id) const {
  const int numberOfRanks = tarch::mpi::Rank::getInstance().getNumberOfRanks();
  return id % numberOfRanks;
}


int peano4::parallel::Node::getLocalTreeId(int treeId) const {
  const int numberOfRanks = tarch::mpi::Rank::getInstance().getNumberOfRanks();
  return treeId / numberOfRanks;
}


int peano4::parallel::Node::reserveId(int rank, int forTreeId)  {
  int localThread = 0;
  int result = -1;
  while (result==-1) {
    if ( _treeEntries.count( getId(rank,localThread) )==0 ) {
      assertion(localThread<ReservedMPITagsForDataExchange/2);
      result = getId(rank,localThread);
    }
    else {
      logDebug( "reserveId(int,int)", "local tree " << localThread << " (global id=" << getId(rank,localThread) << ") on rank " << rank << " is already in use" );
    }
    localThread++;
  }

  registerId( result, forTreeId );

  return result;
}


void peano4::parallel::Node::registerId(int id, int masterId) {
  tarch::multicore::Lock lock(_semaphore);
  assertion( _treeEntries.count(id)==0 );
  assertion( id!=masterId );
  #ifndef Parallel
  assertion( isGlobalMaster(id) or _treeEntries.count(masterId)==1 );
  #endif

  TreeEntry newEntry;

  newEntry.setId( id );
  newEntry.setMaster( masterId );

  _treeEntries.insert( std::pair<int,TreeEntry>(id, newEntry) );
}


int peano4::parallel::Node::getNumberOfRegisteredTrees() const {
  return _treeEntries.size();
}


void peano4::parallel::Node::deregisterId(int id) {
  assertion1( _treeEntries.count(id)==1, id );

  tarch::multicore::Lock lock(_semaphore);
  _treeEntries.erase(id);

  logDebug( "deregisterId(int)", "removed tree " << id << " from list of trees" );
}


bool peano4::parallel::Node::isStorageStackNumber(int number) {
  return number<peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance;
}


int peano4::parallel::Node::getOutputStackNumberOfHorizontalDataExchange(int id) {
  return peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance + id * StacksPerCommunicationPartner;
}


int peano4::parallel::Node::getInputStackNumberOfHorizontalDataExchange(int id) {
  return peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance + id * StacksPerCommunicationPartner + 1;
}


std::bitset<2*Dimensions> peano4::parallel::Node::getPeriodicBoundaryNumber(const tarch::la::Vector<TwoPowerD,int>& flags) {
  std::bitset<2*Dimensions> result;

  for (int d=0; d<2*Dimensions; d++) {
    bool allFlagsSet = true;
    dfor2(k)
      tarch::la::Vector<Dimensions,int> entry;
      entry = k;
      entry( d%Dimensions ) = d/Dimensions;
      allFlagsSet &= flags( peano4::utils::dLinearised(entry,2) ) == peano4::grid::Spacetree::RankOfPeriodicBoundaryCondition;
    enddforx
    if (allFlagsSet) {
      result.set(d);
    }
  }
  return result;
}


std::set<peano4::parallel::Node::PeriodicBoundaryStackIdentifier> peano4::parallel::Node::getOutputStacksForPeriodicBoundaryExchange(const tarch::la::Vector<TwoPowerD,int>& flags) {
  std::bitset<2*Dimensions> boundaryNumbers = getPeriodicBoundaryNumber(flags);
  logTraceInWith2Arguments( "getOutputStacksForPeriodicBoundaryExchange(...)", flags, boundaryNumbers );

  std::set< int > powerSet;
  for (int i=0; i<2*Dimensions; i++) {
    if ( boundaryNumbers[i] ) {
      std::bitset<2*Dimensions> newEntry(0);
      newEntry.set(i);
      powerSet.insert( newEntry.to_ulong() );

      for (auto p: powerSet) {
        newEntry = p;
        newEntry.set(i);
        powerSet.insert( newEntry.to_ulong() );
      }
    }
  }

  const int baseIndex = peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance - peano4::grid::PeanoCurve::NumberOfPeriodicBoundaryConditionOutputStacks;
  std::set<peano4::parallel::Node::PeriodicBoundaryStackIdentifier> result;
  for (auto p: powerSet) {
    std::bitset<Dimensions> stackAnnotation(0);
    for (int i=0; i<Dimensions; i++) {
      stackAnnotation.set( i, std::bitset<2*Dimensions>(p)[i] or std::bitset<2*Dimensions>(p)[i+Dimensions] );
    }
    peano4::parallel::Node::PeriodicBoundaryStackIdentifier newEntry(baseIndex + p,stackAnnotation.to_ulong());
    result.insert( newEntry );
    logDebug( "getOutputStacksForPeriodicBoundaryExchange(...)", "inserted " << (baseIndex + p) << " as base is " << baseIndex );
  }

  logTraceOutWith1Argument( "getOutputStacksForPeriodicBoundaryExchange(...)", result.size() );
  return result;
}


std::set<peano4::parallel::Node::PeriodicBoundaryStackIdentifier> peano4::parallel::Node::getInputStacksForPeriodicBoundaryExchange(const tarch::la::Vector<TwoPowerD,int>&  flags) {
  std::set<peano4::parallel::Node::PeriodicBoundaryStackIdentifier> output = getOutputStacksForPeriodicBoundaryExchange(flags);
  std::set<peano4::parallel::Node::PeriodicBoundaryStackIdentifier> result;
  for (auto p: output) {
    peano4::parallel::Node::PeriodicBoundaryStackIdentifier newEntry(p.first - peano4::grid::PeanoCurve::NumberOfPeriodicBoundaryConditionOutputStacks,p.second);
    result.insert(newEntry);
  }
  return result;
}


int peano4::parallel::Node::getInputStackNumberForVerticalDataExchange(int id) {
  return peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance + id * StacksPerCommunicationPartner + 2;
}


int peano4::parallel::Node::getOutputStackNumberForVerticalDataExchange(int id) {
  return peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance + id * StacksPerCommunicationPartner + 3;
}


int  peano4::parallel::Node::getPeriodicBoundaryExchangeInputStackNumberForOutputStack(int outputStackNumber) {
  logTraceInWith4Arguments( "getPeriodicBoundaryExchangeInputStackNumberForOutputStack(int)", outputStackNumber, peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance, peano4::grid::PeanoCurve::NumberOfPeriodicBoundaryConditionStacks, peano4::grid::PeanoCurve::NumberOfPeriodicBoundaryConditionOutputStacks );
  assertion( isPeriodicBoundaryExchangeOutputStackNumber(outputStackNumber) );

  const int baseIndex = peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance - peano4::grid::PeanoCurve::NumberOfPeriodicBoundaryConditionOutputStacks;
  std::bitset<2*Dimensions> decodedOutputStackNumber( outputStackNumber-baseIndex );
  logDebug( "getPeriodicBoundaryExchangeInputStackNumberForOutputStack(int)", "data flow identifier = " << decodedOutputStackNumber );

  std::bitset<2*Dimensions> counterpartStackNumber( 0  );
  for (int i=0; i<2*Dimensions; i++) {
    if ( decodedOutputStackNumber[i] ) {
      counterpartStackNumber.set( i<Dimensions ? i + Dimensions : i - Dimensions );
    }
  }
  logDebug( "getPeriodicBoundaryExchangeInputStackNumberForOutputStack(int)", "counterpart identifier = " << counterpartStackNumber );

  int result = peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance - peano4::grid::PeanoCurve::NumberOfPeriodicBoundaryConditionOutputStacks*2 + counterpartStackNumber.to_ulong();
  logTraceOutWith1Argument( "getPeriodicBoundaryExchangeInputStackNumberForOutputStack(int)", result );
  return result;
}


bool peano4::parallel::Node::isPeriodicBoundaryExchangeOutputStackNumber(int id) {
  const bool periodicBoundary = id>=peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance - peano4::grid::PeanoCurve::NumberOfPeriodicBoundaryConditionOutputStacks
                            and id<peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance;

  return periodicBoundary;
}


bool peano4::parallel::Node::isHorizontalDataExchangeOutputStackNumber(int id) {
  const bool domainBoundary = id>=peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance
     and ( (id-peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance) % StacksPerCommunicationPartner == 0 );

  return domainBoundary;
}


bool peano4::parallel::Node::isHorizontalDataExchangeInputStackNumber(int id) {
  const bool domainBoundary = id>=peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance
     and ( (id-peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance) % StacksPerCommunicationPartner == 1 );

  return domainBoundary;
}


bool peano4::parallel::Node::isVerticalDataExchangeOutputStackNumber(int id) {
  return id>=peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance
     and ( (id-peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance) % StacksPerCommunicationPartner == 3 );
}


bool peano4::parallel::Node::isVerticalDataExchangeInputStackNumber(int id) {
  return id>=peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance
     and ( (id-peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance) % StacksPerCommunicationPartner == 2 );
}


int peano4::parallel::Node::getIdOfExchangeStackNumber(int number) {
  return (number-peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance) / StacksPerCommunicationPartner;
}


bool peano4::parallel::Node::continueToRun() {
  #ifdef Parallel
  if (tarch::mpi::Rank::getInstance().isGlobalMaster()) {
    for (int i=1; i<tarch::mpi::Rank::getInstance().getNumberOfRanks(); i++ ) {
      StartTraversalMessage message;
      message.setStepIdentifier(_currentProgramStep);
      logDebug( "continueToRun()", "send out " << message.toString() << " to rank " << i);
      message.send(i,_rankOrchestrationTag,false,StartTraversalMessage::ExchangeMode::NonblockingWithPollingLoopOverTests);
    }
  }
  else {
    StartTraversalMessage message;
    message.receive(tarch::mpi::Rank::getGlobalMasterRank(),_rankOrchestrationTag,false,StartTraversalMessage::ExchangeMode::NonblockingWithPollingLoopOverTests);
    logInfo( "continueToRun()", "received message " << message.toString() );
    _currentProgramStep = message.getStepIdentifier();
  }
  #endif
  return _currentProgramStep!=Terminate;
}


void peano4::parallel::Node::setNextProgramStep( int number ) {
  assertion1( number==Terminate or number>=0,  number);
  _currentProgramStep = number;
}


int peano4::parallel::Node::getCurrentProgramStep() const {
  return _currentProgramStep;
}


int peano4::parallel::Node::getTreeManagementTag() const {
  return _treeManagementTag;
}


void peano4::parallel::Node::shutdown() {
  if (tarch::mpi::Rank::getInstance().isGlobalMaster()) {
    setNextProgramStep(peano4::parallel::Node::Terminate);
    continueToRun();
  }
}
