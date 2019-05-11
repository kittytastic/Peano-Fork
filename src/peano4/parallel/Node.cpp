#include "Node.h"
#include "StartTraversalMessage.h"
#include "TreeManagementMessage.h"
#include "IntegerMessage.h"

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
  IntegerMessage::initDatatype();

  peano4::grid::AutomatonState::initDatatype();
  peano4::grid::GridVertex::initDatatype();
  #endif
}


void peano4::parallel::Node::shutdownMPIDatatypes() {
  #ifdef Parallel
  StartTraversalMessage::shutdownDatatype();
  TreeManagementMessage::shutdownDatatype();
  IntegerMessage::shutdownDatatype();

  peano4::grid::AutomatonState::shutdownDatatype();
  peano4::grid::GridVertex::shutdownDatatype();
  #endif
}


peano4::parallel::Node::Node():
  _currentProgramStep(UndefProgramStep),
  _rankOrchestrationTag( tarch::mpi::Rank::reserveFreeTag("peano4::parallel::Node") ),
  _treeManagementTag( tarch::mpi::Rank::reserveFreeTag("peano4::parallel::Node") ) {
  if (tarch::mpi::Rank::getInstance().isGlobalMaster()) {
    registerId( 0, -1);
  }

  _maxTreesPerRank               = std::thread::hardware_concurrency()+1;
  _gridVertexDataExchangeBaseTag = -1;
}


peano4::parallel::Node::~Node() {
  assertionMsg( tarch::mpi::Rank::getInstance().getNumberOfRanks()==1 or _currentProgramStep==Terminate, "forgot to terminate node properly through peano4::parallel::Node::getInstance().shutdown()" );
}


int peano4::parallel::Node::getGridDataExchangeTag( int sendingTreeId, int receivingTreeId, bool boundaryDataExchange ) {
  if (_gridVertexDataExchangeBaseTag < 0) {
    _gridVertexDataExchangeBaseTag = tarch::mpi::Rank::reserveFreeTag("grid-data-exchange", _maxTreesPerRank*_maxTreesPerRank*2 );
  }
  int result = _gridVertexDataExchangeBaseTag +
		       ( (getLocalTreeId(sendingTreeId)*_maxTreesPerRank) + getLocalTreeId(sendingTreeId) )*2;

  if (boundaryDataExchange) result++;
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
  // @todo There's a limited number of threads per rank
  int result = -1;
  while (result==-1) {
	if ( _treeEntries.count( getId(rank,localThread) )==0 ) {
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


int peano4::parallel::Node::getMaximumNumberOfTreesPerRank() const {
  return _maxTreesPerRank;
}


void peano4::parallel::Node::deregisterId(int id) {
  assertion1( _treeEntries.count(id)==1, id );
  assertion1( not hasTreeForkedBefore(id), id );

  tarch::multicore::Lock lock(_semaphore);
  _treeEntries.erase(id);

  logDebug( "deregisterId(int)", "removed tree " << id << " from list of trees" );
}


int peano4::parallel::Node::getOutputStackNumberOfBoundaryExchange(int id) {
  return peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance + id * StacksPerCommunicationPartner;
}


int peano4::parallel::Node::getInputStackNumberOfBoundaryExchange(int id) {
  return peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance + id * StacksPerCommunicationPartner + 1;
}


int peano4::parallel::Node::getInputStackNumberForSplitMergeDataExchange(int id) {
  return peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance + id * StacksPerCommunicationPartner + 2;
}


int peano4::parallel::Node::getOutputStackNumberForSplitMergeDataExchange(int id) {
  return peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance + id * StacksPerCommunicationPartner + 3;
}


bool peano4::parallel::Node::isBoundaryExchangeOutputStackNumber(int id) {
  return id>=peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance
     and ( (id-peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance) % StacksPerCommunicationPartner == 0 );
}


bool peano4::parallel::Node::isBoundaryExchangeInputStackNumber(int id) {
  return id>=peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance
     and ( (id-peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance) % StacksPerCommunicationPartner == 1 );
}


bool peano4::parallel::Node::isSplitMergeOutputStackNumber(int id) {
  return id>=peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance
     and ( (id-peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance) % StacksPerCommunicationPartner == 3 );
}


int peano4::parallel::Node::getIdOfExchangeStackNumber(int number) {
  return (number-peano4::grid::PeanoCurve::MaxNumberOfStacksPerSpacetreeInstance) / StacksPerCommunicationPartner;
}



// @todo Should be const
bool peano4::parallel::Node::hasTreeForkedBefore( int treeId ) {
  tarch::multicore::Lock lock(_semaphore);

  bool result = false;
  for (const auto& p: _treeEntries) {
	  // @todo Falsches Flag
	  // @todo Master raus. Wir muesseen nur wissen, ob jemand gefork that oder net;
	  // Wie wird das allerdings wiederum zurueckgesetzt?
	result |= p.second.getMaster()==treeId;
  }

  return result;
}


std::set< int > peano4::parallel::Node::getChildren( int treeId ) {
  std::set< int > result;

  for (const auto& p: _treeEntries) {
    if ( p.second.getMaster()==treeId ) {
      result.insert( p.first);
    }
  }

  return result;
}


bool peano4::parallel::Node::continueToRun() {
  #ifdef Parallel
  if (tarch::mpi::Rank::getInstance().isGlobalMaster()) {
	for (int i=1; i<tarch::mpi::Rank::getInstance().getNumberOfRanks(); i++ ) {
      StartTraversalMessage message;
      message.setStepIdentifier(_currentProgramStep);
      // @todo Switch to logDebug
      logInfo( "continueToRun()", "send out " << message.toString() << " to rank " << i);
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
