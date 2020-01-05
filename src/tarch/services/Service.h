// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _TARCH_SERVICES_SERVICE_H_
#define _TARCH_SERVICES_SERVICE_H_

#define registerService(name) \
  static tarch::services::ServiceFactory<name> thisServiceFactoryInstance( #name );


#include "tarch/multicore/RecursiveSemaphore.h"


namespace tarch {
  namespace services {
    class Service;
  }
}


/**
 * Service Interface
 *
 * A service is a singleton running the background which is available always.
 * If it is shut down, all calls to the service becomes nop, i.e. it is a
 * robust thing. On a parallel machine, services are also do exist only once,
 * i.e. they are global singletons. Therefore, you shall never access a service
 * directly, but always via a proxy/accessor. This proxy either invokes the
 * service directly (if the services are on the local node) or it creates an
 * MPI call to the real service. Consequently, services have to poll the MPI
 * queue regularly. To enable them to do so, all services register at the
 * service repository, and this service repository has a poll operation.
 * Services also have to be protected by semaphores in a multicore environment.
 *
 * If you wanna write a service yourself, you have to do two things:
 * - Implement this interface.
 * - Register your object through tarch::services::ServiceRepository::getInstance().addService().
 *
 * I usually make services singletons. I can then do the registration in the
 * constructor.
 *
 * @author Tobias Weinzierl
 */
class tarch::services::Service {
  public:
    virtual ~Service() {};

    virtual void receiveDanglingMessages() = 0;

    /**
     * Recursive semaphores
     *
     * We have ensure that receiveDanglingMessages is not ran in parallel with
     * other operations on one rank. This holds for example for MPI updates or
     * updates of lists of MPIRequests. Yet, there can be cases where
     * receiveDanglingMessages() in turn invokes receiveDanglingMessages()
     * recursively. With a standard semaphore, we would now run into a deadlock
     * as default semaphores are not recursion-safe. Therefore, I provide this
     * recursive semaphore. The ServiceRepository does already lock
     * it, so receiveDanglingMessages() invoked through the factory should be
     * fine. You might however want to lock it yourself, too.
     *
     * I had severe issues when I outsourced the tarch into a library. The
     * static initialisation of the recursive semaphores then led to seg faults
     * from time to time. Therefore, I decided to make this semaphore a pointer.
     * It is initialised lazily tarch::services::ServiceRepository::receiveDanglingMessages().
     */
	static tarch::multicore::RecursiveSemaphore*  receiveDanglingMessagesSemaphore;
};

#endif
