// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _TARCH_MULTICORE_DEFINITIONS_H_
#define _TARCH_MULTICORE_DEFINITIONS_H_

#include "config.h"

#if defined(SharedOMP) || defined(SharedTBB) || defined(SharedCPP)
  #define SharedMemoryParallelisation
#endif

#endif
