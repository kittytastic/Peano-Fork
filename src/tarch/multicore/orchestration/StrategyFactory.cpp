#include "StrategyFactory.h"

#include "BSP.h"
#include "Fuse.h"
#include "NativeTasks.h"

#include "tarch/logging/Log.h"


tarch::multicore::orchestration::Strategy* tarch::multicore::orchestration::parseRealisation( const std::string& realisationString ) {
  if ( realisationString.compare( "bsp" )==0 ) {
    return new BSP();
  }
  if ( realisationString.compare( "fuse-" )==0 ) {
    std::string argument = realisationString.substr( std::string("fuse-").size() );
    std::cout << std::endl << "parameter: " << argument << std::endl;

    return new Fuse(15);
  }
  if ( realisationString.compare( "native" )==0 ) {
    return new NativeTasks();
  }
  if ( realisationString.compare( "default" )==0 ) {
    return createDefaultStrategy();
  }
  else {
    return nullptr;
  }
}


std::string tarch::multicore::orchestration::getListOfRealisations() {
  return "bsp,fuse-[1,2,3...],native,default";
}


tarch::multicore::orchestration::Strategy* tarch::multicore::orchestration::createDefaultStrategy() {
  return new NativeTasks();
}
