#include "petsc/runners/Runner.h"


#include "petsc/repositories/Repository.h"
#include "petsc/repositories/RepositoryFactory.h"

#include "peano/utils/UserInterface.h"

#include "tarch/Assertions.h"

#include "tarch/parallel/Node.h"
#include "tarch/parallel/NodePool.h"



#include "tarch/parallel/FCFSNodePoolStrategy.h"
#include "peano/parallel/loadbalancing/OracleForOnePhaseWithGreedyPartitioning.h"


#include "peano/geometry/Hexahedron.h" 



/**
 * We want to use the vectors from PETSc:
 */
#include "petscvec.h"



petsc::runners::Runner::Runner() {
  // @todo Insert your code here
}


petsc::runners::Runner::~Runner() {
  // @todo Insert your code here
}


int petsc::runners::Runner::run() {



  // @todo Insert your geometry generation here and adopt the repository 
  //       generation to your needs. There is a dummy implementation to allow 
  //       for a quick start, but this is really very dummy (it generates 
  //       solely a sphere computational domain and basically does nothing with 
  //       it).
  
  // Start of dummy implementation
  peano::geometry::Hexahedron geometry(
    tarch::la::Vector<DIMENSIONS,double>(1.0),
    tarch::la::Vector<DIMENSIONS,double>(0.0)
   );
  petsc::repositories::Repository* repository = 
    petsc::repositories::RepositoryFactory::getInstance().createWithSTDStackImplementation(
      geometry,
      tarch::la::Vector<DIMENSIONS,double>(1.0),   // domainSize,
      tarch::la::Vector<DIMENSIONS,double>(0.0)    // computationalDomainOffset
    );
  

  // This is new because of PETSc:
  if (tarch::parallel::Node::getInstance().isGlobalMaster()) {
    tarch::parallel::NodePool::getInstance().setStrategy(
      new tarch::parallel::FCFSNodePoolStrategy()
    );
  }
  tarch::parallel::NodePool::getInstance().restart();
  tarch::parallel::NodePool::getInstance().waitForAllNodesToBecomeIdle();
  peano::parallel::loadbalancing::Oracle::getInstance().setOracle(
    new peano::parallel::loadbalancing::OracleForOnePhaseWithGreedyPartitioning(false)
  );




  int result = 0;
  if (tarch::parallel::Node::getInstance().isGlobalMaster()) {
    result = runAsMaster( *repository );
  }
  #ifdef Parallel
  else {
    result = runAsWorker( *repository );
  }
  #endif
  
  delete repository;
  
  return result;
}


int petsc::runners::Runner::runAsMaster(petsc::repositories::Repository& repository) {
  peano::utils::UserInterface::writeHeader();


  /**
   * Build up the grid. Afterwards, we know how many vertices exist.
   */
  repository.switchToCreateGrid(); repository.iterate();


  /**
   * These are the global vectors that we use to make the adapter communicate
   * with PETSc:
   */
  Vec  _x;
  Vec  _rhs;

  /**
   * Create the global vector required for our work with PETSc.
   */
  PetscErrorCode errorX   = VecCreate(tarch::parallel::Node::getInstance().getCommunicator(), &_x);
  PetscErrorCode errorRhs = VecCreate(tarch::parallel::Node::getInstance().getCommunicator(), &_rhs);

  if (errorX!=0) {
    PetscError(
      tarch::parallel::Node::getInstance().getCommunicator(),
      __LINE__,  __FUNCT__,  __FILE__,
      errorX,  PETSC_ERROR_INITIAL, // first time we detect this error
      "creating global solution vector failed"
    );
  }
  if (errorRhs!=0) {
    PetscError(
      tarch::parallel::Node::getInstance().getCommunicator(),
      __LINE__,  __FUNCT__,  __FILE__,
      errorRhs,  PETSC_ERROR_INITIAL, // first time we detect this error
      "creating global rhs vector failed"
    );
  }


  /**
   * Local size (first parameter) and global size are the same for the time
   * being. Peano uses doubles to count vertices, as the number of vertices
   * sometimes exceed int. So we have to use an ugly cast here.
   */
  const PetscInt numberOfUnknowns = static_cast<int>(repository.getState().getNumberOfInnerLeafVertices());

  assertion1( numberOfUnknowns>0, numberOfUnknowns );

  VecSetSizes(_x,  PETSC_DECIDE,numberOfUnknowns);
  VecSetSizes(_rhs,PETSC_DECIDE,numberOfUnknowns);
  
  repository.switchToAssemble(); repository.iterate();
  repository.switchToPlot(); repository.iterate();


  /**
   * Clean up PETSc data structures
   */
  VecDestroy(&_x);
  VecDestroy(&_rhs);
 
 
  repository.logIterationStatistics( true );
  repository.terminate();

  return 0;
}
