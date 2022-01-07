#ifndef _PROJECT_BASE_2D_EULER_OBSERVERS_TIMESTEP2EXAHYPE2_GRID_CELLLABEL3_H_
#define _PROJECT_BASE_2D_EULER_OBSERVERS_TIMESTEP2EXAHYPE2_GRID_CELLLABEL3_H_



#include "peano4/utils/Globals.h"
#include "peano4/datamanagement/VertexEnumerator.h"
#include "peano4/datamanagement/VertexMarker.h"
#include "peano4/datamanagement/FaceEnumerator.h"
#include "peano4/datamanagement/FaceMarker.h"
#include "peano4/datamanagement/CellMarker.h"
#include "peano4/grid/GridControlEvent.h"
#include "tarch/la/Vector.h"

#include <vector>



#include "Constants.h"
#include "exahype2/EnclaveBookkeeping.h"
#include "repositories/SolverRepository.h"


#include "facedata/euler2DQOld.h"
#include "facedata/euler2DQNew.h"
#include "facedata/euler2DQUpdate.h"
#include "facedata/euler2DFaceLabel.h"
#include "celldata/euler2DQ.h"
#include "celldata/euler2DCellLabel.h"
namespace project {
namespace base_2d_euler {
namespace observers {
  class TimeStep2exahype2_grid_CellLabel3;
}
}
}
class project::base_2d_euler::observers::TimeStep2exahype2_grid_CellLabel3{
  private:
    static tarch::logging::Log  _log;
  public:

    /**
     * Create action instance for one tree for one grid sweep
     *
     * <h2> Thread safety </h2>
     *
     * The creation of individual trees usually happens through peano4::parallel::SpacetreeSet::createObserverCloneIfRequired().
     * This routine is called lazily when we start to traverse a subtree.
     * Therefore, the creation of actions is not thread-safe.
     *
     *
     * @param treeNumber Number of the spacetree for which we create the tree instance. Is
     *                   smaller 0 if this is the prototype action used on a rank from which
     *                   the real actions are constructed from.
     */
    TimeStep2exahype2_grid_CellLabel3(int treeNumber);

    ~TimeStep2exahype2_grid_CellLabel3();

    std::vector< peano4::grid::GridControlEvent > getGridControlEvents() const;

    void beginTraversal(
      );

    void endTraversal(
      );

    void createPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel);

    void destroyPersistentFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel);

    void createHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel);

    void destroyHangingFace(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel);

    void touchFaceFirstTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel);

    void touchFaceLastTime(
      const peano4::datamanagement::FaceMarker& marker,
      project::base_2d_euler::facedata::euler2DQOld& fineGridFaceeuler2DQOld,
      project::base_2d_euler::facedata::euler2DQNew& fineGridFaceeuler2DQNew,
      project::base_2d_euler::facedata::euler2DQUpdate& fineGridFaceeuler2DQUpdate,
      project::base_2d_euler::facedata::euler2DFaceLabel& fineGridFaceeuler2DFaceLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel);

    void createCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel);

    void destroyCell(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel);

    void touchCellFirstTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel);

    void touchCellLastTime(
      const peano4::datamanagement::CellMarker& marker,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> fineGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> fineGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> fineGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> fineGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& fineGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& fineGridCelleuler2DCellLabel,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQOld> coarseGridFaceseuler2DQOld,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQNew> coarseGridFaceseuler2DQNew,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DQUpdate> coarseGridFaceseuler2DQUpdate,
      peano4::datamanagement::FaceEnumerator<project::base_2d_euler::facedata::euler2DFaceLabel> coarseGridFaceseuler2DFaceLabel,
      project::base_2d_euler::celldata::euler2DQ& coarseGridCelleuler2DQ,
      project::base_2d_euler::celldata::euler2DCellLabel& coarseGridCelleuler2DCellLabel);

};


#endif

