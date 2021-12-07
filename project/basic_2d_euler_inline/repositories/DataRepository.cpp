#include "DataRepository.h"


peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::celldata::euler2DCellLabel >>   project::base_2d_euler_inline::repositories::DataRepository::_CellDataeuler2DCellLabelStack;
peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::celldata::euler2DQ >>   project::base_2d_euler_inline::repositories::DataRepository::_CellDataeuler2DQStack;
peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::facedata::euler2DQOld >>   project::base_2d_euler_inline::repositories::DataRepository::_FaceDataeuler2DQOldStack;
peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::facedata::euler2DQNew >>   project::base_2d_euler_inline::repositories::DataRepository::_FaceDataeuler2DQNewStack;
peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::facedata::euler2DQUpdate >>   project::base_2d_euler_inline::repositories::DataRepository::_FaceDataeuler2DQUpdateStack;
peano4::maps::HierarchicalStackMap< peano4::stacks::STDVectorStack< project::base_2d_euler_inline::facedata::euler2DFaceLabel >>   project::base_2d_euler_inline::repositories::DataRepository::_FaceDataeuler2DFaceLabelStack;



void project::base_2d_euler_inline::repositories::DataRepository::initDatatypes() {
  #ifdef Parallel
  project::base_2d_euler_inline::celldata::euler2DCellLabel::initDatatype();
project::base_2d_euler_inline::celldata::euler2DQ::initDatatype();
project::base_2d_euler_inline::facedata::euler2DQOld::initDatatype();
project::base_2d_euler_inline::facedata::euler2DQNew::initDatatype();
project::base_2d_euler_inline::facedata::euler2DQUpdate::initDatatype();
project::base_2d_euler_inline::facedata::euler2DFaceLabel::initDatatype();

  #endif
}


void project::base_2d_euler_inline::repositories::DataRepository::shutdownDatatypes() {

  _CellDataeuler2DCellLabelStack.clear();
_CellDataeuler2DQStack.clear();
_FaceDataeuler2DQOldStack.clear();
_FaceDataeuler2DQNewStack.clear();
_FaceDataeuler2DQUpdateStack.clear();
_FaceDataeuler2DFaceLabelStack.clear();


  #ifdef Parallel
  project::base_2d_euler_inline::celldata::euler2DCellLabel::shutdownDatatype();
project::base_2d_euler_inline::celldata::euler2DQ::shutdownDatatype();
project::base_2d_euler_inline::facedata::euler2DQOld::shutdownDatatype();
project::base_2d_euler_inline::facedata::euler2DQNew::shutdownDatatype();
project::base_2d_euler_inline::facedata::euler2DQUpdate::shutdownDatatype();
project::base_2d_euler_inline::facedata::euler2DFaceLabel::shutdownDatatype();

  #endif
}
