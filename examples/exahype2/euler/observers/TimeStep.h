// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _examples_exahype2_euler_observers_TimeStep_H_
#define _examples_exahype2_euler_observers_TimeStep_H_


#include "tarch/la/Vector.h"
#include "peano4/utils/Globals.h"
#include "peano4/grid/GridControlEvent.h"
#include "peano4/grid/GridTraversalEvent.h"
#include "peano4/grid/TraversalObserver.h"


#include "DataRepository.h"


#include "observers/TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0.h"
#include "observers/TimeStep2peano4_toolbox_blockstructured_ProjectPatchOntoFaces1.h"
#include "observers/TimeStep2peano4_toolbox_blockstructured_ApplyFunctorOnPatch2.h"
#include "observers/TimeStep2exahype2_grid_AMROnPatch3.h"
#include "observers/TimeStep2peano4_toolbox_blockstructured_BackupPatchOverlap4.h"
#include "observers/TimeStep2exahype2_grid_EnclaveLabels5.h"
#include "observers/TimeStep2peano4_toolbox_blockstructured_ApplyFunctorOnPatch6.h"
#include "observers/TimeStep2exahype2_grid_SetLabels7.h"



namespace examples {namespace exahype2 {namespace euler {namespace observers {
  class TimeStep;
}}}}


class examples::exahype2::euler::observers::TimeStep: public peano4::grid::TraversalObserver {
  public:
    /**
     * Logging device
     */
    static tarch::logging::Log  _log;
  
    const int _spacetreeId;
    
    observers::TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor0   _actionSet0; 
    observers::TimeStep2peano4_toolbox_blockstructured_ProjectPatchOntoFaces1   _actionSet1; 
    observers::TimeStep2peano4_toolbox_blockstructured_ApplyFunctorOnPatch2   _actionSet2; 
    observers::TimeStep2exahype2_grid_AMROnPatch3   _actionSet3; 
    observers::TimeStep2peano4_toolbox_blockstructured_BackupPatchOverlap4   _actionSet4; 
    observers::TimeStep2exahype2_grid_EnclaveLabels5   _actionSet5; 
    observers::TimeStep2peano4_toolbox_blockstructured_ApplyFunctorOnPatch6   _actionSet6; 
    observers::TimeStep2exahype2_grid_SetLabels7   _actionSet7; 

    
  public:
    /**
     * If you pass this marker into the constructor, it implies that this 
     * observer is used as prototype for the real observers which are created
     * per local spacetree.
     */
    static constexpr int SpacetreePrototype = -1; 
  
    /**
     * @param spacetreeId -1 is the dummy, i.e. this observer is not 
     *                    instantiated for a spacetree yet but serves as 
     *                    blueprint for the real trees later on.
     */
    TimeStep(int spacetreeId = SpacetreePrototype);
    
    void enterCell(
     const peano4::grid::GridTraversalEvent&  event
    ) override;

    void leaveCell(
      const peano4::grid::GridTraversalEvent&  event
    ) override;

    TraversalObserver* clone(int spacetreeId) override;

    std::vector< peano4::grid::GridControlEvent > getGridControlEvents() const override;

    void beginTraversal(
      const tarch::la::Vector<Dimensions,double>&  x,
      const tarch::la::Vector<Dimensions,double>&  h
    ) override;

    void endTraversal(
      const tarch::la::Vector<Dimensions,double>&  x,
      const tarch::la::Vector<Dimensions,double>&  h
    ) override;
    
    void exchangeAllVerticalDataExchangeStacks( int masterId ) override;
    void exchangeAllHorizontalDataExchangeStacks( bool symmetricDataCardinality ) override;
    void exchangeAllPeriodicBoundaryDataStacks() override;
    
    void streamDataFromSplittingTreeToNewTree( int newWorker ) override;
    void streamDataFromJoiningTreeToMasterTree( int masterId ) override;
    
    void finishAllOutstandingSendsAndReceives() override;
    
    void sendVertex(int inOutStack, int relativePositionOnInOutStack, int toStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::datamanagement::VertexMarker& marker) override;
    void sendFace(int inOutStack, int relativePositionOnInOutStack, int toStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::datamanagement::FaceMarker& marker) override;
    void sendCell(int inOutStack, int toStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::datamanagement::CellMarker& marker) override;

    void receiveAndMergeVertex(const peano4::grid::GridTraversalEvent&  event, int positionWithinCell, int inOutStack, int relativePositionOnInOutStack, int fromStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::datamanagement::VertexMarker& marker) override;
    void receiveAndMergeFace(const peano4::grid::GridTraversalEvent&  event, int positionWithinCell, int inOutStack, int relativePositionOnInOutStack, int fromStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::datamanagement::FaceMarker& marker) override;

    void deleteAllStacks() override;
};

#endif