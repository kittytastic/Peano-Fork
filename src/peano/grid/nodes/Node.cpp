#include "Node.h"

#include "peano/parallel/loadbalancing/Oracle.h"


bool peano::grid::nodes::refineArtificiallyOutsideDomain() {
  #ifdef Parallel
  bool result = peano::parallel::loadbalancing::Oracle::getInstance().isLoadBalancingActivated();

  if ( tarch::parallel::Node::getInstance().isGlobalMaster() ) {
	result &= tarch::parallel::NodePool::getInstance().getNumberOfIdleNodes()>0;
  }
  else if ( peano::parallel::loadbalancing::Oracle::getInstance().hasForkFailedBefore() ) {
	result = false;
  }

  return result;
  #else
  return false;
  #endif
}
