#include "Node.h"


#include "peano4/grid/Spacetree.h"


#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds



#include "tarch/Assertions.h"
// @todo Node should be called Rank
// @todo parallel should be called mpi as namespace
#include "tarch/parallel/Node.h"


#include "tarch/multicore/Lock.h"


tarch::logging::Log  peano4::parallel::Node::_log("peano4::parallel::Node");


peano4::parallel::Node::Node() {
  registerId( 0, -1);
}


peano4::parallel::Node::~Node() {
}


bool peano4::parallel::Node::isGlobalMaster(int treeId) const {
  return treeId==0;
}


peano4::parallel::Node& peano4::parallel::Node::getInstance() {
  static Node singleton;
  return singleton;
}


int peano4::parallel::Node::getId(int rank, int threadId) const {
  const int numberOfRanks = tarch::parallel::Node::getInstance().getNumberOfNodes();
  return numberOfRanks * threadId + rank;
}


int peano4::parallel::Node::getRank(int id) const {
  const int numberOfRanks = tarch::parallel::Node::getInstance().getNumberOfNodes();
  return id % numberOfRanks;
}


int peano4::parallel::Node::reserveId(int rank, int forTreeId)  {
  int localThread = 0;
  // @todo There's a limited number of threads per rank
  int result = -1;
  while (result==-1) {
	if ( _treeEntries.count( getId(rank,localThread) )==0 ) result = getId(rank,localThread);
	localThread++;
  }

  registerId( result, forTreeId );

  return result;
}


void peano4::parallel::Node::registerId(int id, int masterId) {
  tarch::multicore::Lock lock(_semaphore);
  assertion( _treeEntries.count(id)==0 );
  assertion( id!=masterId );
  assertion( isGlobalMaster(id) or _treeEntries.count(masterId)==1 );

  TreeEntry newEntry;

  newEntry.setId( id );
  newEntry.setMaster( masterId );

  _treeEntries.insert( std::pair<int,TreeEntry>(id, newEntry) );
}



void peano4::parallel::Node::deregisterId(int id) {
  assertion( _treeEntries.count(id)==1 );
  assertion( not hasChildrenTree(id) );

  tarch::multicore::Lock lock(_semaphore);
  _treeEntries.erase(id);
}


int peano4::parallel::Node::getOutputStackNumberOfBoundaryExchange(int id) const {
  return peano4::grid::Spacetree::MaxNumberOfStacksPerSpacetreeInstance + id * 2;
}


int peano4::parallel::Node::getInputStackNumberOfBoundaryExchange(int id) const {
  return peano4::grid::Spacetree::MaxNumberOfStacksPerSpacetreeInstance + id * 2 + 1;
}


bool peano4::parallel::Node::isBoundaryExchangeOutputStackNumber(int id) const {
  return id>=peano4::grid::Spacetree::MaxNumberOfStacksPerSpacetreeInstance
     and ( (id-peano4::grid::Spacetree::MaxNumberOfStacksPerSpacetreeInstance) % 2 == 0 );
}


bool peano4::parallel::Node::isBoundaryExchangeInputStackNumber(int id) const {
  return id>=peano4::grid::Spacetree::MaxNumberOfStacksPerSpacetreeInstance
     and ( (id-peano4::grid::Spacetree::MaxNumberOfStacksPerSpacetreeInstance) % 2 == 1 );
}


int peano4::parallel::Node::getIdOfBoundaryExchangeOutputStackNumber(int number) const {
  assertion( isBoundaryExchangeOutputStackNumber(number) );
  assertion2( (number-peano4::grid::Spacetree::MaxNumberOfStacksPerSpacetreeInstance)%2==0, number, peano4::grid::Spacetree::MaxNumberOfStacksPerSpacetreeInstance );
  return (number-peano4::grid::Spacetree::MaxNumberOfStacksPerSpacetreeInstance) / 2;
}


void peano4::parallel::Node::sendVertexSynchronously( const peano4::grid::GridVertex& vertex, int fromId, int toId ) {
  tarch::multicore::Lock lock( _semaphore );

  std::pair<int,int> key( fromId, toId );

  _sendReceiveBuffer[key].push( vertex );

  logDebug( "sendVertexSynchronously(...)", "tree " << fromId << " pushes vertex " << vertex.toString() << " to buffer for tree " << toId );
}


peano4::grid::GridVertex peano4::parallel::Node::getVertexSynchronously( int fromId, int toId ) {
  std::pair<int,int> key( fromId, toId );

  tarch::multicore::Lock lock( _semaphore );
  bool isEmpty = _sendReceiveBuffer[key].empty();
  lock.free();

  while ( isEmpty ) {
    std::this_thread::sleep_for (std::chrono::seconds(1));
    lock.lock();
    isEmpty = _sendReceiveBuffer[key].empty();
	lock.free();
  }

  lock.lock();
  peano4::grid::GridVertex result = _sendReceiveBuffer[key].front();
  _sendReceiveBuffer[key].pop();

  logDebug( "getVertexSynchronously(int,int)", "deploy " << result.toString() << " from " << fromId << " to tree " << toId );

  return result;
}


void peano4::parallel::Node::treesCantCoarsenBecauseOfVetos( int treeId ) {
  tarch::multicore::Lock lock(_semaphore);

}


int peano4::parallel::Node::getParentTree( int treeId ) {
  tarch::multicore::Lock lock(_semaphore);

  assertion( _treeEntries.count(treeId) );
  return _treeEntries[treeId].getMaster();
}


bool peano4::parallel::Node::hasChildrenTree( int treeId ) {
  tarch::multicore::Lock lock(_semaphore);

  bool result = false;
  for (const auto& p: _treeEntries) {
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
