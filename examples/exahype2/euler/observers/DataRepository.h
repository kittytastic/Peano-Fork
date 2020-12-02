//
// Peano4 data file
// Generated by Peano's Python API
// www.peano-framework.org
// This is generated. Be careful with adding your own stuff
//
#ifndef _EXAMPLES_EXAHYPE2_EULER_OBSERVERS_DATAREPOSITORY_
#define _EXAMPLES_EXAHYPE2_EULER_OBSERVERS_DATAREPOSITORY_



#include "peano4/stacks/STDVectorStack.h"    
#include "celldata/EulerQ.h"

#include "peano4/stacks/STDVectorStack.h" 
             #include "celldata/EulerCellSemaphoreLabel.h"

#include "peano4/stacks/STDVectorStack.h"    
#include "facedata/EulerQ.h"


#include "peano4/stacks/STDVectorStack.h"    
#include "facedata/EulerQNew.h"

#include "peano4/stacks/STDVectorStack.h" 
             #include "facedata/Label.h"



#include <utility>
#include "peano4/datamanagement/FaceEnumerator.h"
#include "peano4/datamanagement/VertexEnumerator.h"
#include "peano4/maps/HierarchicalStackMap.h"
#include "peano4/maps/STDStackMap.h"

namespace examples{
namespace exahype2{
namespace euler{
namespace observers{

  class DataRepository;
}
}
}
}



class examples::exahype2::euler::observers::DataRepository {
  public:
	/**
	 * To look up the right stack, we use a combination of tree number (id) and
	 * stack number.
	 */
	typedef std::pair<int,int>  DataKey;
	
	

    static peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< examples::exahype2::euler::celldata::EulerQ >>  _CellDataEulerQStack;
static peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< examples::exahype2::euler::celldata::EulerCellSemaphoreLabel >>  _CellDataEulerCellSemaphoreLabelStack;
static peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< examples::exahype2::euler::facedata::EulerQ >>  _FaceDataEulerQStack;
static peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< examples::exahype2::euler::facedata::EulerQNew >>  _FaceDataEulerQNewStack;
static peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< examples::exahype2::euler::facedata::Label >>  _FaceDataLabelStack;

    
    /**
     * Init all the MPI datatypes
     */
    static void initDatatypes();
    
    /**
     * Shutdown the MPI datatypes and free the local data containers.
     */
    static void shutdownDatatypes();
};


#endif
