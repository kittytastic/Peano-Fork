//
// Peano4 data file
// Generated by Peano's Python API
// www.peano-framework.org
// This is generated. Be careful with adding your own stuff
//
#ifndef _PROJECT_BASE_2D_EULER_INLINE_REPOSITORIES_DATAREPOSITORY_
#define _PROJECT_BASE_2D_EULER_INLINE_REPOSITORIES_DATAREPOSITORY_


#include "peano4/stacks/STDVectorStack.h" 
             #include "celldata/euler2DCellLabel.h"

#include "peano4/stacks/STDVectorStack.h"    
#include "celldata/euler2DQ.h"


#include "peano4/stacks/STDVectorStack.h"    
#include "facedata/euler2DQOld.h"


#include "peano4/stacks/STDVectorStack.h"    
#include "facedata/euler2DQNew.h"


#include "peano4/stacks/STDVectorStack.h"    
#include "facedata/euler2DQUpdate.h"

#include "peano4/stacks/STDVectorStack.h" 
             #include "facedata/euler2DFaceLabel.h"



#include <utility>
#include "peano4/datamanagement/FaceEnumerator.h"
#include "peano4/datamanagement/VertexEnumerator.h"
#include "peano4/maps/HierarchicalStackMap.h"
#include "peano4/maps/STDStackMap.h"

namespace project{
namespace base_2d_euler_inline{
namespace repositories{

  class DataRepository;
}
}
}



class project::base_2d_euler_inline::repositories::DataRepository {
  public:
	/**
	 * To look up the right stack, we use a combination of tree number (id) and
	 * stack number.
	 */
	typedef std::pair<int,int>  DataKey;
	
	

    static peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::celldata::euler2DCellLabel >>  _CellDataeuler2DCellLabelStack;
static peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::celldata::euler2DQ >>  _CellDataeuler2DQStack;
static peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::facedata::euler2DQOld >>  _FaceDataeuler2DQOldStack;
static peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::facedata::euler2DQNew >>  _FaceDataeuler2DQNewStack;
static peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::facedata::euler2DQUpdate >>  _FaceDataeuler2DQUpdateStack;
static peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::facedata::euler2DFaceLabel >>  _FaceDataeuler2DFaceLabelStack;

    
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
