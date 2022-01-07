
#include "InitGrid.h"
#include "repositories/DataRepository.h"

#include "peano4/grid/PeanoCurve.h"

#include "peano4/datamanagement/VertexEnumerator.h"
#include "peano4/datamanagement/VertexMarker.h"
#include "peano4/datamanagement/FaceEnumerator.h"
#include "peano4/datamanagement/FaceMarker.h"
#include "peano4/datamanagement/CellMarker.h"

#include "peano4/parallel/SpacetreeSet.h"


tarch::logging::Log project::base_2d_euler_inline::observers::InitGrid::_log( "project::base_2d_euler_inline::observers::InitGrid" );



project::base_2d_euler_inline::observers::InitGrid::InitGrid(int spacetreeId):
  _spacetreeId( spacetreeId ) , _actionSet0(spacetreeId), _actionSet1(spacetreeId), _actionSet2(spacetreeId), _actionSet3(spacetreeId), _actionSet4(spacetreeId), _actionSet5(spacetreeId), _actionSet6(spacetreeId)
{
}


  

peano4::grid::TraversalObserver* project::base_2d_euler_inline::observers::InitGrid::clone(int spacetreeId) {
  return new InitGrid(spacetreeId);
}

  

std::vector< peano4::grid::GridControlEvent > project::base_2d_euler_inline::observers::InitGrid::getGridControlEvents() const {
  std::vector< peano4::grid::GridControlEvent > result;

  {
    const std::vector< peano4::grid::GridControlEvent > actionResult = _actionSet0.getGridControlEvents();
    result.insert(result.begin(),actionResult.begin(),actionResult.end());
  }

  {
    const std::vector< peano4::grid::GridControlEvent > actionResult = _actionSet1.getGridControlEvents();
    result.insert(result.begin(),actionResult.begin(),actionResult.end());
  }

  {
    const std::vector< peano4::grid::GridControlEvent > actionResult = _actionSet2.getGridControlEvents();
    result.insert(result.begin(),actionResult.begin(),actionResult.end());
  }

  {
    const std::vector< peano4::grid::GridControlEvent > actionResult = _actionSet3.getGridControlEvents();
    result.insert(result.begin(),actionResult.begin(),actionResult.end());
  }

  {
    const std::vector< peano4::grid::GridControlEvent > actionResult = _actionSet4.getGridControlEvents();
    result.insert(result.begin(),actionResult.begin(),actionResult.end());
  }

  {
    const std::vector< peano4::grid::GridControlEvent > actionResult = _actionSet5.getGridControlEvents();
    result.insert(result.begin(),actionResult.begin(),actionResult.end());
  }

  {
    const std::vector< peano4::grid::GridControlEvent > actionResult = _actionSet6.getGridControlEvents();
    result.insert(result.begin(),actionResult.begin(),actionResult.end());
  }

  return result;
}



void project::base_2d_euler_inline::observers::InitGrid::beginTraversal( const tarch::la::Vector<Dimensions,double>&  x, const tarch::la::Vector<Dimensions,double>&  h ) {
  logTraceInWith2Arguments( "beginTraversal(...)", x, h );
  //
  // Invoke beginTraversal() on the actions
  //
  _actionSet0.beginTraversal();
  _actionSet1.beginTraversal();
  _actionSet2.beginTraversal();
  _actionSet3.beginTraversal();
  _actionSet4.beginTraversal();
  _actionSet5.beginTraversal();
  _actionSet6.beginTraversal();


  //
  // Fill call stacks with dummies which represent level -1 such that we can
  // call standard action routines on level 0 with parents. Without these
  // statements, a top(1) call would raise an assertion.
  //
  repositories::DataRepository::_CellDataeuler2DQStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->push( project::base_2d_euler_inline::celldata::euler2DQ() );
  repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->push( project::base_2d_euler_inline::celldata::euler2DCellLabel() );
  for (int i=0; i<TwoTimesD; i++) {
    repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->push( project::base_2d_euler_inline::facedata::euler2DQOld() );
  }
  for (int i=0; i<TwoTimesD; i++) {
    repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->push( project::base_2d_euler_inline::facedata::euler2DQNew() );
  }
  for (int i=0; i<TwoTimesD; i++) {
    repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->push( project::base_2d_euler_inline::facedata::euler2DQUpdate() );
  }
  for (int i=0; i<TwoTimesD; i++) {
    repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->push( project::base_2d_euler_inline::facedata::euler2DFaceLabel() );
  }

  logTraceOutWith2Arguments( "beginTraversal(...)", x, h );
}

  

void project::base_2d_euler_inline::observers::InitGrid::endTraversal( const tarch::la::Vector<Dimensions,double>&  x, const tarch::la::Vector<Dimensions,double>&  h ) {
  logTraceInWith2Arguments( "endTraversal(...)", x, h );
  _actionSet0.endTraversal();
  _actionSet1.endTraversal();
  _actionSet2.endTraversal();
  _actionSet3.endTraversal();
  _actionSet4.endTraversal();
  _actionSet5.endTraversal();
  _actionSet6.endTraversal();

  repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pop();
  repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pop();
  for (int i=0; i<TwoTimesD; i++) {
    repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pop();
  }
  for (int i=0; i<TwoTimesD; i++) {
    repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pop();
  }
  for (int i=0; i<TwoTimesD; i++) {
    repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pop();
  }
  for (int i=0; i<TwoTimesD; i++) {
    repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pop();
  }

  logTraceOutWith2Arguments( "endTraversal(...)", x, h );
}

  
void project::base_2d_euler_inline::observers::InitGrid::loadCell( const peano4::grid::GridTraversalEvent&  event ) {
  logTraceInWith2Arguments( "loadCell(...)", _spacetreeId, event.toString() );

  // Load face euler2DQOld
  {
    auto view = repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pushBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack          = event.getFaceDataFrom(i);
      int outFaceStackPosition = event.getFaceDataTo(i);
      logDebug("loadCell(...)", "face stack " << inFaceStack << "->pos-" << outFaceStackPosition );

      peano4::datamanagement::FaceMarker  marker(event,outFaceStackPosition);

      project::base_2d_euler_inline::facedata::euler2DQOld data ;
      if (
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        (not peano4::grid::PeanoCurve::isInOutStack(inFaceStack) or project::base_2d_euler_inline::facedata::euler2DQOld::loadPersistently(marker))
      ) {
        assertion4( not repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inFaceStack))->empty(), event.toString(), peano4::datamanagement::FaceMarker(event).toString(), _spacetreeId,inFaceStack );
        data = repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inFaceStack))->pop();
      }

      #if PeanoDebug>0
      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::NoData
        or
        not project::base_2d_euler_inline::facedata::euler2DQOld::loadPersistently(marker)
      ) {
        logDebug( "loadCell(...)", "initialise meta data of face euler2DQOld with " << marker.x(outFaceStackPosition) << " x " << marker.h() << ": load persistent data=" << project::base_2d_euler_inline::facedata::euler2DQOld::loadPersistently(marker)  << " (" << marker.toString() << ")" );
        data.setDebugX( marker.x(outFaceStackPosition) );
        data.setDebugH( marker.h() );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
      ) {
        assertionVectorNumericalEquals5( data.getDebugX(), marker.x(outFaceStackPosition), data.getDebugX(), data.getDebugH(), marker.toString(), outFaceStackPosition, _spacetreeId );
        assertionVectorNumericalEquals5( data.getDebugH(), marker.h(),                     data.getDebugX(), data.getDebugH(), marker.toString(), outFaceStackPosition, _spacetreeId );
      }
      #endif

      view.set(outFaceStackPosition,data);
    }
  }

  // Load face euler2DQNew
  {
    auto view = repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pushBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack          = event.getFaceDataFrom(i);
      int outFaceStackPosition = event.getFaceDataTo(i);
      logDebug("loadCell(...)", "face stack " << inFaceStack << "->pos-" << outFaceStackPosition );

      peano4::datamanagement::FaceMarker  marker(event,outFaceStackPosition);

      project::base_2d_euler_inline::facedata::euler2DQNew data ;
      if (
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        (not peano4::grid::PeanoCurve::isInOutStack(inFaceStack) or project::base_2d_euler_inline::facedata::euler2DQNew::loadPersistently(marker))
      ) {
        assertion4( not repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inFaceStack))->empty(), event.toString(), peano4::datamanagement::FaceMarker(event).toString(), _spacetreeId,inFaceStack );
        data = repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inFaceStack))->pop();
      }

      #if PeanoDebug>0
      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::NoData
        or
        not project::base_2d_euler_inline::facedata::euler2DQNew::loadPersistently(marker)
      ) {
        logDebug( "loadCell(...)", "initialise meta data of face euler2DQNew with " << marker.x(outFaceStackPosition) << " x " << marker.h() << ": load persistent data=" << project::base_2d_euler_inline::facedata::euler2DQNew::loadPersistently(marker)  << " (" << marker.toString() << ")" );
        data.setDebugX( marker.x(outFaceStackPosition) );
        data.setDebugH( marker.h() );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
      ) {
        assertionVectorNumericalEquals5( data.getDebugX(), marker.x(outFaceStackPosition), data.getDebugX(), data.getDebugH(), marker.toString(), outFaceStackPosition, _spacetreeId );
        assertionVectorNumericalEquals5( data.getDebugH(), marker.h(),                     data.getDebugX(), data.getDebugH(), marker.toString(), outFaceStackPosition, _spacetreeId );
      }
      #endif

      view.set(outFaceStackPosition,data);
    }
  }

  // Load face euler2DQUpdate
  {
    auto view = repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pushBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack          = event.getFaceDataFrom(i);
      int outFaceStackPosition = event.getFaceDataTo(i);
      logDebug("loadCell(...)", "face stack " << inFaceStack << "->pos-" << outFaceStackPosition );

      peano4::datamanagement::FaceMarker  marker(event,outFaceStackPosition);

      project::base_2d_euler_inline::facedata::euler2DQUpdate data ;
      if (
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        (not peano4::grid::PeanoCurve::isInOutStack(inFaceStack) or project::base_2d_euler_inline::facedata::euler2DQUpdate::loadPersistently(marker))
      ) {
        assertion4( not repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inFaceStack))->empty(), event.toString(), peano4::datamanagement::FaceMarker(event).toString(), _spacetreeId,inFaceStack );
        data = repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inFaceStack))->pop();
      }

      #if PeanoDebug>0
      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::NoData
        or
        not project::base_2d_euler_inline::facedata::euler2DQUpdate::loadPersistently(marker)
      ) {
        logDebug( "loadCell(...)", "initialise meta data of face euler2DQUpdate with " << marker.x(outFaceStackPosition) << " x " << marker.h() << ": load persistent data=" << project::base_2d_euler_inline::facedata::euler2DQUpdate::loadPersistently(marker)  << " (" << marker.toString() << ")" );
        data.setDebugX( marker.x(outFaceStackPosition) );
        data.setDebugH( marker.h() );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
      ) {
        assertionVectorNumericalEquals5( data.getDebugX(), marker.x(outFaceStackPosition), data.getDebugX(), data.getDebugH(), marker.toString(), outFaceStackPosition, _spacetreeId );
        assertionVectorNumericalEquals5( data.getDebugH(), marker.h(),                     data.getDebugX(), data.getDebugH(), marker.toString(), outFaceStackPosition, _spacetreeId );
      }
      #endif

      view.set(outFaceStackPosition,data);
    }
  }

  // Load face euler2DFaceLabel
  {
    auto view = repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pushBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack          = event.getFaceDataFrom(i);
      int outFaceStackPosition = event.getFaceDataTo(i);
      logDebug("loadCell(...)", "face stack " << inFaceStack << "->pos-" << outFaceStackPosition );

      peano4::datamanagement::FaceMarker  marker(event,outFaceStackPosition);

      project::base_2d_euler_inline::facedata::euler2DFaceLabel data ;
      if (
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        (not peano4::grid::PeanoCurve::isInOutStack(inFaceStack) or project::base_2d_euler_inline::facedata::euler2DFaceLabel::loadPersistently(marker))
      ) {
        assertion4( not repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inFaceStack))->empty(), event.toString(), peano4::datamanagement::FaceMarker(event).toString(), _spacetreeId,inFaceStack );
        data = repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inFaceStack))->pop();
      }

      #if PeanoDebug>0
      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::NoData
        or
        not project::base_2d_euler_inline::facedata::euler2DFaceLabel::loadPersistently(marker)
      ) {
        logDebug( "loadCell(...)", "initialise meta data of face euler2DFaceLabel with " << marker.x(outFaceStackPosition) << " x " << marker.h() << ": load persistent data=" << project::base_2d_euler_inline::facedata::euler2DFaceLabel::loadPersistently(marker)  << " (" << marker.toString() << ")" );
        data.setDebugX( marker.x(outFaceStackPosition) );
        data.setDebugH( marker.h() );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
      ) {
        assertionVectorNumericalEquals5( data.getDebugX(), marker.x(outFaceStackPosition), data.getDebugX(), data.getDebugH(), marker.toString(), outFaceStackPosition, _spacetreeId );
        assertionVectorNumericalEquals5( data.getDebugH(), marker.h(),                     data.getDebugX(), data.getDebugH(), marker.toString(), outFaceStackPosition, _spacetreeId );
      }
      #endif

      view.set(outFaceStackPosition,data);
    }
  }

  // Load cell euler2DQ
  {
    auto view = repositories::DataRepository::_CellDataeuler2DQStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pushBlock( 1 );

    peano4::datamanagement::CellMarker  marker(event);

    const int inCellStack  = event.getCellData();
    const int outCellStack = peano4::grid::PeanoCurve::CallStack;
    logDebug("loadCell(...)", "cell stack " << inCellStack << "->pos-" << outCellStack << "(" << project::base_2d_euler_inline::celldata::euler2DQ::loadPersistently(marker) << ")" );

    project::base_2d_euler_inline::celldata::euler2DQ& data = view.get(0);
    if (
      inCellStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      inCellStack!=peano4::grid::TraversalObserver::NoData
      and
      (not peano4::grid::PeanoCurve::isInOutStack(inCellStack) or project::base_2d_euler_inline::celldata::euler2DQ::loadPersistently(marker))
    ) {
      assertion3( not repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inCellStack))->empty(), event.toString(), _spacetreeId, inCellStack);
      data = repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inCellStack))->pop();
    }

    #if PeanoDebug>0
    if (
      inCellStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      or
      inCellStack==peano4::grid::TraversalObserver::NoData
      or
      not project::base_2d_euler_inline::celldata::euler2DQ::loadPersistently(marker)
    ) {
      logDebug( "loadCell(...)", "initialise meta data of cell euler2DQ with " << marker.x() << " x " << marker.h()  << " (" << marker.toString() << ")");
      data.setDebugX( marker.x() );
      data.setDebugH( marker.h() );
    }
    else {
      assertionVectorNumericalEquals4( data.getDebugX(), marker.x(), data.getDebugX(), data.getDebugH(), marker.toString(), _spacetreeId );
      assertionVectorNumericalEquals4( data.getDebugH(), marker.h(), data.getDebugX(), data.getDebugH(), marker.toString(), _spacetreeId );
    }
    #endif
  }

  // Load cell euler2DCellLabel
  {
    auto view = repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pushBlock( 1 );

    peano4::datamanagement::CellMarker  marker(event);

    const int inCellStack  = event.getCellData();
    const int outCellStack = peano4::grid::PeanoCurve::CallStack;
    logDebug("loadCell(...)", "cell stack " << inCellStack << "->pos-" << outCellStack << "(" << project::base_2d_euler_inline::celldata::euler2DCellLabel::loadPersistently(marker) << ")" );

    project::base_2d_euler_inline::celldata::euler2DCellLabel& data = view.get(0);
    if (
      inCellStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      inCellStack!=peano4::grid::TraversalObserver::NoData
      and
      (not peano4::grid::PeanoCurve::isInOutStack(inCellStack) or project::base_2d_euler_inline::celldata::euler2DCellLabel::loadPersistently(marker))
    ) {
      assertion3( not repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inCellStack))->empty(), event.toString(), _spacetreeId, inCellStack);
      data = repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,inCellStack))->pop();
    }

    #if PeanoDebug>0
    if (
      inCellStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      or
      inCellStack==peano4::grid::TraversalObserver::NoData
      or
      not project::base_2d_euler_inline::celldata::euler2DCellLabel::loadPersistently(marker)
    ) {
      logDebug( "loadCell(...)", "initialise meta data of cell euler2DCellLabel with " << marker.x() << " x " << marker.h()  << " (" << marker.toString() << ")");
      data.setDebugX( marker.x() );
      data.setDebugH( marker.h() );
    }
    else {
      assertionVectorNumericalEquals4( data.getDebugX(), marker.x(), data.getDebugX(), data.getDebugH(), marker.toString(), _spacetreeId );
      assertionVectorNumericalEquals4( data.getDebugH(), marker.h(), data.getDebugX(), data.getDebugH(), marker.toString(), _spacetreeId );
    }
    #endif
  }

  logTraceOutWith1Argument( "loadCell(...)", _spacetreeId );
}

void project::base_2d_euler_inline::observers::InitGrid::enterCell( const peano4::grid::GridTraversalEvent&  event ) {
  logTraceInWith2Arguments( "enterCell(...)", _spacetreeId, event.toString() );

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker marker( event );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack = event.getFaceDataFrom(i);
      int pick        = event.getFaceDataTo(i);

      marker.select(pick);

      assertion3( marker.isLocal() or not event.getIsCellLocal(), marker.toString(), event.toString(), i );

      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet0.createPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet0.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet0.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet0.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker marker( event );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack = event.getFaceDataFrom(i);
      int pick        = event.getFaceDataTo(i);

      marker.select(pick);

      assertion3( marker.isLocal() or not event.getIsCellLocal(), marker.toString(), event.toString(), i );

      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet1.createPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet1.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet1.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet1.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker marker( event );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack = event.getFaceDataFrom(i);
      int pick        = event.getFaceDataTo(i);

      marker.select(pick);

      assertion3( marker.isLocal() or not event.getIsCellLocal(), marker.toString(), event.toString(), i );

      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet2.createPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet2.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet2.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet2.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker marker( event );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack = event.getFaceDataFrom(i);
      int pick        = event.getFaceDataTo(i);

      marker.select(pick);

      assertion3( marker.isLocal() or not event.getIsCellLocal(), marker.toString(), event.toString(), i );

      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet3.createPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet3.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet3.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet3.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker marker( event );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack = event.getFaceDataFrom(i);
      int pick        = event.getFaceDataTo(i);

      marker.select(pick);

      assertion3( marker.isLocal() or not event.getIsCellLocal(), marker.toString(), event.toString(), i );

      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet4.createPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet4.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet4.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet4.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker marker( event );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack = event.getFaceDataFrom(i);
      int pick        = event.getFaceDataTo(i);

      marker.select(pick);

      assertion3( marker.isLocal() or not event.getIsCellLocal(), marker.toString(), event.toString(), i );

      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet5.createPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet5.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet5.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet5.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker marker( event );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack = event.getFaceDataFrom(i);
      int pick        = event.getFaceDataTo(i);

      marker.select(pick);

      assertion3( marker.isLocal() or not event.getIsCellLocal(), marker.toString(), event.toString(), i );

      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet6.createPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet6.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet6.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet6.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Invoke creational events on cell euler2DCellLabel
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
      _actionSet0.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  // Invoke creational events on cell euler2DCellLabel
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
      _actionSet1.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  // Invoke creational events on cell euler2DCellLabel
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
      _actionSet2.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  // Invoke creational events on cell euler2DCellLabel
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
      _actionSet3.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  // Invoke creational events on cell euler2DCellLabel
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
      _actionSet4.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  // Invoke creational events on cell euler2DCellLabel
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
      _actionSet5.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  // Invoke creational events on cell euler2DCellLabel
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
      _actionSet6.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet0.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet1.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet2.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet3.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet4.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet5.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet6.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  logTraceOut( "enterCell(...)" );
}

void project::base_2d_euler_inline::observers::InitGrid::leaveCell( const peano4::grid::GridTraversalEvent&  event ) {
  logTraceInWith2Arguments( "leaveCell(...)", _spacetreeId, event.toString() );

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet6.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet5.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet4.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet3.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet2.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet1.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet0.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
    _actionSet6.destroyCell(
      marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
    _actionSet5.destroyCell(
      marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
    _actionSet4.destroyCell(
      marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
    _actionSet3.destroyCell(
      marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
    _actionSet2.destroyCell(
      marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
    _actionSet1.destroyCell(
      marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      marker.isLocal()
    ) {
    _actionSet0.destroyCell(
      marker
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker  marker(event);

    for (int i=0; i<TwoTimesD; i++) {
      int outFaceStack      = event.getFaceDataTo(i);
      int pick              = event.getFaceDataFrom(i);

      marker.select(pick);

      if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet6.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet6.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet6.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet6.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker  marker(event);

    for (int i=0; i<TwoTimesD; i++) {
      int outFaceStack      = event.getFaceDataTo(i);
      int pick              = event.getFaceDataFrom(i);

      marker.select(pick);

      if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet5.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet5.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet5.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet5.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker  marker(event);

    for (int i=0; i<TwoTimesD; i++) {
      int outFaceStack      = event.getFaceDataTo(i);
      int pick              = event.getFaceDataFrom(i);

      marker.select(pick);

      if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet4.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet4.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet4.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet4.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker  marker(event);

    for (int i=0; i<TwoTimesD; i++) {
      int outFaceStack      = event.getFaceDataTo(i);
      int pick              = event.getFaceDataFrom(i);

      marker.select(pick);

      if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet3.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet3.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet3.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet3.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker  marker(event);

    for (int i=0; i<TwoTimesD; i++) {
      int outFaceStack      = event.getFaceDataTo(i);
      int pick              = event.getFaceDataFrom(i);

      marker.select(pick);

      if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet2.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet2.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet2.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet2.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker  marker(event);

    for (int i=0; i<TwoTimesD; i++) {
      int outFaceStack      = event.getFaceDataTo(i);
      int pick              = event.getFaceDataFrom(i);

      marker.select(pick);

      if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet1.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet1.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet1.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet1.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  // Handle face euler2DCellLabel
  {
    peano4::datamanagement::FaceMarker  marker(event);

    for (int i=0; i<TwoTimesD; i++) {
      int outFaceStack      = event.getFaceDataTo(i);
      int pick              = event.getFaceDataFrom(i);

      marker.select(pick);

      if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet0.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
        _actionSet0.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet0.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet0.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQOld>( &repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQNew>( &repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DQUpdate>( &repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<project::base_2d_euler_inline::facedata::euler2DFaceLabel>( &repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1),repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
        );
      }
    }
  }

  logTraceOutWith1Argument( "leaveCell(...)", _spacetreeId );
}

void project::base_2d_euler_inline::observers::InitGrid::storeCell( const peano4::grid::GridTraversalEvent&  event ) {
  logTraceInWith2Arguments( "storeCell(...)", _spacetreeId, event.toString() );

  // Handle cell euler2DQ
  {
    const int inCellStack   = peano4::grid::PeanoCurve::CallStack;
    const int outCellStack  = event.getCellData();
    logDebug("storeCell(...)", "cell stack " << inCellStack << "->pos-" << outCellStack );

    peano4::datamanagement::CellMarker  marker(event);

    auto view = repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->popBlock( 1 );

    if (
      outCellStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      outCellStack!=peano4::grid::TraversalObserver::NoData
      and
      (not peano4::grid::PeanoCurve::isInOutStack(outCellStack) or project::base_2d_euler_inline::celldata::euler2DQ::storePersistently(marker))
    ) {
      repositories::DataRepository::_CellDataeuler2DQStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,outCellStack))->push( view.get(0) );
    }
    else {
      logDebug( 
        "storeCell(...)", 
        "do not store cell euler2DQ with " << marker.x() << " x " << marker.h() << ":" << 
        "  destroy=" << (outCellStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity) <<
        ", no-data=" << (outCellStack==peano4::grid::TraversalObserver::NoData) <<
        ", is-in/out=" << peano4::grid::PeanoCurve::isInOutStack(outCellStack) <<
        ", store-persistently=" << project::base_2d_euler_inline::celldata::euler2DQ::storePersistently(marker)
      );
    }
  }

  // Handle cell euler2DCellLabel
  {
    const int inCellStack   = peano4::grid::PeanoCurve::CallStack;
    const int outCellStack  = event.getCellData();
    logDebug("storeCell(...)", "cell stack " << inCellStack << "->pos-" << outCellStack );

    peano4::datamanagement::CellMarker  marker(event);

    auto view = repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->popBlock( 1 );

    if (
      outCellStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      outCellStack!=peano4::grid::TraversalObserver::NoData
      and
      (not peano4::grid::PeanoCurve::isInOutStack(outCellStack) or project::base_2d_euler_inline::celldata::euler2DCellLabel::storePersistently(marker))
    ) {
      repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,outCellStack))->push( view.get(0) );
    }
    else {
      logDebug( 
        "storeCell(...)", 
        "do not store cell euler2DCellLabel with " << marker.x() << " x " << marker.h() << ":" << 
        "  destroy=" << (outCellStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity) <<
        ", no-data=" << (outCellStack==peano4::grid::TraversalObserver::NoData) <<
        ", is-in/out=" << peano4::grid::PeanoCurve::isInOutStack(outCellStack) <<
        ", store-persistently=" << project::base_2d_euler_inline::celldata::euler2DCellLabel::storePersistently(marker)
      );
    }
  }

  // Store face euler2DQOld
  {
    auto view = repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->popBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStackPosition  = event.getFaceDataFrom(i);
      int outFaceStack         = event.getFaceDataTo(i);
      logDebug("storeCell(...)", "pos-" << inFaceStackPosition << "->face stack " << outFaceStack );

      peano4::datamanagement::FaceMarker  marker(event,inFaceStackPosition);

      project::base_2d_euler_inline::facedata::euler2DQOld data = view.get(inFaceStackPosition);

      if (
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        (not peano4::grid::PeanoCurve::isInOutStack(outFaceStack) or project::base_2d_euler_inline::facedata::euler2DQOld::storePersistently(marker))
      ) {
        logDebug( "storeCell(...)", "store face euler2DQOld with " << marker.x(inFaceStackPosition) << " x " << marker.h() );
        repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,outFaceStack))->push(data);
      }
      else {
        logDebug( "storeCell(...)", "do not store face euler2DQOld with " << marker.x(inFaceStackPosition) << " x " << marker.h() << ": store persistently=" << project::base_2d_euler_inline::facedata::euler2DQOld::storePersistently(marker) );
      }
    }
  }

  // Store face euler2DQNew
  {
    auto view = repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->popBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStackPosition  = event.getFaceDataFrom(i);
      int outFaceStack         = event.getFaceDataTo(i);
      logDebug("storeCell(...)", "pos-" << inFaceStackPosition << "->face stack " << outFaceStack );

      peano4::datamanagement::FaceMarker  marker(event,inFaceStackPosition);

      project::base_2d_euler_inline::facedata::euler2DQNew data = view.get(inFaceStackPosition);

      if (
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        (not peano4::grid::PeanoCurve::isInOutStack(outFaceStack) or project::base_2d_euler_inline::facedata::euler2DQNew::storePersistently(marker))
      ) {
        logDebug( "storeCell(...)", "store face euler2DQNew with " << marker.x(inFaceStackPosition) << " x " << marker.h() );
        repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,outFaceStack))->push(data);
      }
      else {
        logDebug( "storeCell(...)", "do not store face euler2DQNew with " << marker.x(inFaceStackPosition) << " x " << marker.h() << ": store persistently=" << project::base_2d_euler_inline::facedata::euler2DQNew::storePersistently(marker) );
      }
    }
  }

  // Store face euler2DQUpdate
  {
    auto view = repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->popBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStackPosition  = event.getFaceDataFrom(i);
      int outFaceStack         = event.getFaceDataTo(i);
      logDebug("storeCell(...)", "pos-" << inFaceStackPosition << "->face stack " << outFaceStack );

      peano4::datamanagement::FaceMarker  marker(event,inFaceStackPosition);

      project::base_2d_euler_inline::facedata::euler2DQUpdate data = view.get(inFaceStackPosition);

      if (
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        (not peano4::grid::PeanoCurve::isInOutStack(outFaceStack) or project::base_2d_euler_inline::facedata::euler2DQUpdate::storePersistently(marker))
      ) {
        logDebug( "storeCell(...)", "store face euler2DQUpdate with " << marker.x(inFaceStackPosition) << " x " << marker.h() );
        repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,outFaceStack))->push(data);
      }
      else {
        logDebug( "storeCell(...)", "do not store face euler2DQUpdate with " << marker.x(inFaceStackPosition) << " x " << marker.h() << ": store persistently=" << project::base_2d_euler_inline::facedata::euler2DQUpdate::storePersistently(marker) );
      }
    }
  }

  // Store face euler2DFaceLabel
  {
    auto view = repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->popBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStackPosition  = event.getFaceDataFrom(i);
      int outFaceStack         = event.getFaceDataTo(i);
      logDebug("storeCell(...)", "pos-" << inFaceStackPosition << "->face stack " << outFaceStack );

      peano4::datamanagement::FaceMarker  marker(event,inFaceStackPosition);

      project::base_2d_euler_inline::facedata::euler2DFaceLabel data = view.get(inFaceStackPosition);

      if (
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        (not peano4::grid::PeanoCurve::isInOutStack(outFaceStack) or project::base_2d_euler_inline::facedata::euler2DFaceLabel::storePersistently(marker))
      ) {
        logDebug( "storeCell(...)", "store face euler2DFaceLabel with " << marker.x(inFaceStackPosition) << " x " << marker.h() );
        repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPush( repositories::DataRepository::DataKey(_spacetreeId,outFaceStack))->push(data);
      }
      else {
        logDebug( "storeCell(...)", "do not store face euler2DFaceLabel with " << marker.x(inFaceStackPosition) << " x " << marker.h() << ": store persistently=" << project::base_2d_euler_inline::facedata::euler2DFaceLabel::storePersistently(marker) );
      }
    }
  }

  logTraceOutWith1Argument( "storeCell(...)", _spacetreeId );
}

void project::base_2d_euler_inline::observers::InitGrid::exchangeAllVerticalDataExchangeStacks( int masterId ) {
  logTraceInWith2Arguments( "exchangeAllVerticalDataExchangeStacks(...)", masterId, _spacetreeId  );

  peano4::parallel::SpacetreeSet::exchangeAllVerticalDataExchangeStacks(
    repositories::DataRepository::_CellDataeuler2DQStack,
    _spacetreeId,
    masterId
  );

  peano4::parallel::SpacetreeSet::exchangeAllVerticalDataExchangeStacks(
    repositories::DataRepository::_CellDataeuler2DCellLabelStack,
    _spacetreeId,
    masterId
  );

  peano4::parallel::SpacetreeSet::exchangeAllVerticalDataExchangeStacks(
    repositories::DataRepository::_FaceDataeuler2DQOldStack,
    _spacetreeId,
    masterId
  );

  peano4::parallel::SpacetreeSet::exchangeAllVerticalDataExchangeStacks(
    repositories::DataRepository::_FaceDataeuler2DQNewStack,
    _spacetreeId,
    masterId
  );

  peano4::parallel::SpacetreeSet::exchangeAllVerticalDataExchangeStacks(
    repositories::DataRepository::_FaceDataeuler2DQUpdateStack,
    _spacetreeId,
    masterId
  );

  peano4::parallel::SpacetreeSet::exchangeAllVerticalDataExchangeStacks(
    repositories::DataRepository::_FaceDataeuler2DFaceLabelStack,
    _spacetreeId,
    masterId
  );

  logTraceOut( "exchangeAllVerticalDataExchangeStacks(...)" );
}

void project::base_2d_euler_inline::observers::InitGrid::exchangeAllHorizontalDataExchangeStacks( bool symmetricDataCardinality ) {
  logTraceInWith2Arguments( "exchangeAllHorizontalDataExchangeStacks(...)", symmetricDataCardinality, _spacetreeId  );

  peano4::parallel::SpacetreeSet::exchangeAllHorizontalDataExchangeStacks(
    repositories::DataRepository::_CellDataeuler2DQStack,
    _spacetreeId,
    symmetricDataCardinality
  );

  peano4::parallel::SpacetreeSet::exchangeAllHorizontalDataExchangeStacks(
    repositories::DataRepository::_CellDataeuler2DCellLabelStack,
    _spacetreeId,
    symmetricDataCardinality
  );

  peano4::parallel::SpacetreeSet::exchangeAllHorizontalDataExchangeStacks(
    repositories::DataRepository::_FaceDataeuler2DQOldStack,
    _spacetreeId,
    symmetricDataCardinality
  );

  peano4::parallel::SpacetreeSet::exchangeAllHorizontalDataExchangeStacks(
    repositories::DataRepository::_FaceDataeuler2DQNewStack,
    _spacetreeId,
    symmetricDataCardinality
  );

  peano4::parallel::SpacetreeSet::exchangeAllHorizontalDataExchangeStacks(
    repositories::DataRepository::_FaceDataeuler2DQUpdateStack,
    _spacetreeId,
    symmetricDataCardinality
  );

  peano4::parallel::SpacetreeSet::exchangeAllHorizontalDataExchangeStacks(
    repositories::DataRepository::_FaceDataeuler2DFaceLabelStack,
    _spacetreeId,
    symmetricDataCardinality
  );

  logTraceOut( "exchangeAllHorizontalDataExchangeStacks(...)" );
}

void project::base_2d_euler_inline::observers::InitGrid::exchangeAllPeriodicBoundaryDataStacks() {
  logTraceInWith1Argument( "exchangeAllPeriodicBoundaryDataStacks()", _spacetreeId  );

  peano4::parallel::SpacetreeSet::exchangeAllPeriodicBoundaryDataStacks(
    repositories::DataRepository::_CellDataeuler2DQStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::exchangeAllPeriodicBoundaryDataStacks(
    repositories::DataRepository::_CellDataeuler2DCellLabelStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::exchangeAllPeriodicBoundaryDataStacks(
    repositories::DataRepository::_FaceDataeuler2DQOldStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::exchangeAllPeriodicBoundaryDataStacks(
    repositories::DataRepository::_FaceDataeuler2DQNewStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::exchangeAllPeriodicBoundaryDataStacks(
    repositories::DataRepository::_FaceDataeuler2DQUpdateStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::exchangeAllPeriodicBoundaryDataStacks(
    repositories::DataRepository::_FaceDataeuler2DFaceLabelStack,
    _spacetreeId
  );

  logTraceOut( "exchangeAllPeriodicBoundaryDataStacks()" );
}

void project::base_2d_euler_inline::observers::InitGrid::streamDataFromSplittingTreeToNewTree(int newWorker) {
  logTraceInWith2Arguments( "streamDataFromSplittingTreeToNewTree(int)", _spacetreeId, newWorker );

  peano4::parallel::SpacetreeSet::streamDataFromSplittingTreeToNewTree(
    repositories::DataRepository::_CellDataeuler2DQStack,
    _spacetreeId,
    newWorker
  );

  peano4::parallel::SpacetreeSet::streamDataFromSplittingTreeToNewTree(
    repositories::DataRepository::_CellDataeuler2DCellLabelStack,
    _spacetreeId,
    newWorker
  );

  peano4::parallel::SpacetreeSet::streamDataFromSplittingTreeToNewTree(
    repositories::DataRepository::_FaceDataeuler2DQOldStack,
    _spacetreeId,
    newWorker
  );

  peano4::parallel::SpacetreeSet::streamDataFromSplittingTreeToNewTree(
    repositories::DataRepository::_FaceDataeuler2DQNewStack,
    _spacetreeId,
    newWorker
  );

  peano4::parallel::SpacetreeSet::streamDataFromSplittingTreeToNewTree(
    repositories::DataRepository::_FaceDataeuler2DQUpdateStack,
    _spacetreeId,
    newWorker
  );

  peano4::parallel::SpacetreeSet::streamDataFromSplittingTreeToNewTree(
    repositories::DataRepository::_FaceDataeuler2DFaceLabelStack,
    _spacetreeId,
    newWorker
  );

  logTraceOut( "streamDataFromSplittingTreeToNewTree(int)");
}

void project::base_2d_euler_inline::observers::InitGrid::streamDataFromJoiningTreeToMasterTree(int master) {
  logTraceInWith2Arguments( "streamDataFromJoiningTreeToMasterTree(int)", _spacetreeId, master );

  peano4::parallel::SpacetreeSet::streamDataFromJoiningTreeToMasterTree(
    repositories::DataRepository::_CellDataeuler2DQStack,
    _spacetreeId,
    master
  );

  peano4::parallel::SpacetreeSet::streamDataFromJoiningTreeToMasterTree(
    repositories::DataRepository::_CellDataeuler2DCellLabelStack,
    _spacetreeId,
    master
  );

  peano4::parallel::SpacetreeSet::streamDataFromJoiningTreeToMasterTree(
    repositories::DataRepository::_FaceDataeuler2DQOldStack,
    _spacetreeId,
    master
  );

  peano4::parallel::SpacetreeSet::streamDataFromJoiningTreeToMasterTree(
    repositories::DataRepository::_FaceDataeuler2DQNewStack,
    _spacetreeId,
    master
  );

  peano4::parallel::SpacetreeSet::streamDataFromJoiningTreeToMasterTree(
    repositories::DataRepository::_FaceDataeuler2DQUpdateStack,
    _spacetreeId,
    master
  );

  peano4::parallel::SpacetreeSet::streamDataFromJoiningTreeToMasterTree(
    repositories::DataRepository::_FaceDataeuler2DFaceLabelStack,
    _spacetreeId,
    master
  );

  logTraceOut( "streamDataFromJoiningTreeToMasterTree(int)");
}

void project::base_2d_euler_inline::observers::InitGrid::finishAllOutstandingSendsAndReceives() {
  logTraceInWith1Argument( "finishAllOutstandingSendsAndReceives()", _spacetreeId );

  peano4::parallel::SpacetreeSet::finishAllOutstandingSendsAndReceives(
    repositories::DataRepository::_CellDataeuler2DQStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::finishAllOutstandingSendsAndReceives(
    repositories::DataRepository::_CellDataeuler2DCellLabelStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::finishAllOutstandingSendsAndReceives(
    repositories::DataRepository::_FaceDataeuler2DQOldStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::finishAllOutstandingSendsAndReceives(
    repositories::DataRepository::_FaceDataeuler2DQNewStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::finishAllOutstandingSendsAndReceives(
    repositories::DataRepository::_FaceDataeuler2DQUpdateStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::finishAllOutstandingSendsAndReceives(
    repositories::DataRepository::_FaceDataeuler2DFaceLabelStack,
    _spacetreeId
  );

  logTraceOut( "finishAllOutstandingSendsAndReceives()");
}

void project::base_2d_euler_inline::observers::InitGrid::sendVertex(int position, int toStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::grid::GridTraversalEvent&  event) {
  logTraceInWith4Arguments( "sendVertex(int,int,int)", position, toStack, event.toString(), _spacetreeId );
  

  logTraceOut( "sendVertex(int,int,int)");
}

void project::base_2d_euler_inline::observers::InitGrid::sendFace(int position, int toStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::grid::GridTraversalEvent&  event) {
  logTraceInWith4Arguments( "sendFace(int,int,int)", position, toStack, event.toString(), _spacetreeId );


  {
    peano4::datamanagement::FaceMarker  marker(event,position);
    if (
      project::base_2d_euler_inline::facedata::euler2DQOld::storePersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::facedata::euler2DQOld::send(marker))
     ) {
      project::base_2d_euler_inline::facedata::euler2DQOld data = repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop( 
        repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack)
      )->top(TwoTimesD-1-position);
    
      logDebug( "sendFace(...)", "send out " << data.toString() << " to stack " << toStack << " on tree " << _spacetreeId << " for marker " << marker.toString() );

      repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPush(
        _spacetreeId, toStack
      ) -> push(data);
    }
  }

  {
    peano4::datamanagement::FaceMarker  marker(event,position);
    if (
      project::base_2d_euler_inline::facedata::euler2DQNew::storePersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::facedata::euler2DQNew::send(marker))
     ) {
      project::base_2d_euler_inline::facedata::euler2DQNew data = repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop( 
        repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack)
      )->top(TwoTimesD-1-position);
    
      logDebug( "sendFace(...)", "send out " << data.toString() << " to stack " << toStack << " on tree " << _spacetreeId << " for marker " << marker.toString() );

      repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPush(
        _spacetreeId, toStack
      ) -> push(data);
    }
  }

  {
    peano4::datamanagement::FaceMarker  marker(event,position);
    if (
      project::base_2d_euler_inline::facedata::euler2DQUpdate::storePersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::facedata::euler2DQUpdate::send(marker))
     ) {
      project::base_2d_euler_inline::facedata::euler2DQUpdate data = repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop( 
        repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack)
      )->top(TwoTimesD-1-position);
    
      logDebug( "sendFace(...)", "send out " << data.toString() << " to stack " << toStack << " on tree " << _spacetreeId << " for marker " << marker.toString() );

      repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPush(
        _spacetreeId, toStack
      ) -> push(data);
    }
  }

  {
    peano4::datamanagement::FaceMarker  marker(event,position);
    if (
      project::base_2d_euler_inline::facedata::euler2DFaceLabel::storePersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::facedata::euler2DFaceLabel::send(marker))
     ) {
      project::base_2d_euler_inline::facedata::euler2DFaceLabel data = repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop( 
        repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack)
      )->top(TwoTimesD-1-position);
    
      logDebug( "sendFace(...)", "send out " << data.toString() << " to stack " << toStack << " on tree " << _spacetreeId << " for marker " << marker.toString() );

      repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPush(
        _spacetreeId, toStack
      ) -> push(data);
    }
  }

  logTraceOut( "sendFace(int,int,int)");
}

void project::base_2d_euler_inline::observers::InitGrid::sendCell(int toStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::grid::GridTraversalEvent&  event) {
  logTraceInWith3Arguments( "sendCell(int,int,int)", toStack, event.toString(), _spacetreeId );
  

  {
    peano4::datamanagement::CellMarker  marker(event);
    if (
      project::base_2d_euler_inline::celldata::euler2DQ::storePersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::celldata::euler2DQ::send(marker))
     ) {
      project::base_2d_euler_inline::celldata::euler2DQ data = repositories::DataRepository::_CellDataeuler2DQStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top();
    
      logDebug( "sendCell(...)", "send out " << data.toString() << " to stack " << toStack << " on tree " << _spacetreeId );

      repositories::DataRepository::_CellDataeuler2DQStack.getForPush(
        _spacetreeId, toStack
      ) -> push(data);
    }
  }

  {
    peano4::datamanagement::CellMarker  marker(event);
    if (
      project::base_2d_euler_inline::celldata::euler2DCellLabel::storePersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::celldata::euler2DCellLabel::send(marker))
     ) {
      project::base_2d_euler_inline::celldata::euler2DCellLabel data = repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop( repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top();
    
      logDebug( "sendCell(...)", "send out " << data.toString() << " to stack " << toStack << " on tree " << _spacetreeId );

      repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPush(
        _spacetreeId, toStack
      ) -> push(data);
    }
  }

  logTraceOut( "sendCell(int,int,int)");
}

void project::base_2d_euler_inline::observers::InitGrid::receiveAndMergeCell(int fromStack, SendReceiveContext context, const peano4::grid::GridTraversalEvent& event ) {
  logTraceInWith3Arguments( "receiveAndMergeCell(...)", fromStack, event.toString(), _spacetreeId );

  {
    peano4::datamanagement::CellMarker  marker(event);

    if ( 
      project::base_2d_euler_inline::celldata::euler2DQ::loadPersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::celldata::euler2DQ::receiveAndMerge(marker))
     ) {
      auto   incomingData = repositories::DataRepository::_CellDataeuler2DQStack.getForPop(
        _spacetreeId, fromStack
      )->pop();

      project::base_2d_euler_inline::celldata::euler2DQ& data = repositories::DataRepository::_CellDataeuler2DQStack.getForPush( 
        repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack)
      )->top();

      logDebug( "receiveAndMergeCell(...)", "merge " << incomingData.toString() << " into " << data.toString() );

      if (context==::peano4::grid::TraversalObserver::SendReceiveContext::PeriodicBoundaryDataSwap) {
        assertion8(
          tarch::la::countEqualEntries(data.getDebugX(), incomingData.getDebugX())==Dimensions-1,
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), 
          fromStack, event.toString(), marker.toString(), _spacetreeId );
        assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }
      else {
        assertionVectorNumericalEquals6(
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), fromStack, event.toString(), marker.toString(), _spacetreeId );
          assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }

      data.merge(incomingData, marker);
    }
  }

  {
    peano4::datamanagement::CellMarker  marker(event);

    if ( 
      project::base_2d_euler_inline::celldata::euler2DCellLabel::loadPersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::celldata::euler2DCellLabel::receiveAndMerge(marker))
     ) {
      auto   incomingData = repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPop(
        _spacetreeId, fromStack
      )->pop();

      project::base_2d_euler_inline::celldata::euler2DCellLabel& data = repositories::DataRepository::_CellDataeuler2DCellLabelStack.getForPush( 
        repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack)
      )->top();

      logDebug( "receiveAndMergeCell(...)", "merge " << incomingData.toString() << " into " << data.toString() );

      if (context==::peano4::grid::TraversalObserver::SendReceiveContext::PeriodicBoundaryDataSwap) {
        assertion8(
          tarch::la::countEqualEntries(data.getDebugX(), incomingData.getDebugX())==Dimensions-1,
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), 
          fromStack, event.toString(), marker.toString(), _spacetreeId );
        assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }
      else {
        assertionVectorNumericalEquals6(
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), fromStack, event.toString(), marker.toString(), _spacetreeId );
          assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }

      data.merge(incomingData, marker);
    }
  }

  logTraceOut( "receiveAndMergeCell(...)");
}

void project::base_2d_euler_inline::observers::InitGrid::receiveAndMergeFace(int position, int fromStack, SendReceiveContext context, const peano4::grid::GridTraversalEvent& event) {
  logTraceInWith4Arguments( "receiveAndMergeFace(...)", position, fromStack, event.toString(), _spacetreeId );

  {
    peano4::datamanagement::FaceMarker  marker(event,position);

    if ( 
      project::base_2d_euler_inline::facedata::euler2DQOld::loadPersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::facedata::euler2DQOld::receiveAndMerge(marker))
     ) {
      auto   incomingData = repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPop(
        _spacetreeId, fromStack
      )->pop();

      project::base_2d_euler_inline::facedata::euler2DQOld& data = repositories::DataRepository::_FaceDataeuler2DQOldStack.getForPush( 
        repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack)
      )->top(TwoTimesD-1-position);

      logDebug( "receiveAndMergeFace(...)", "merge " << incomingData.toString() << " into " << data.toString() << " within marker " << marker.toString() );

      if (context==::peano4::grid::TraversalObserver::SendReceiveContext::PeriodicBoundaryDataSwap) {
        assertion8(
          tarch::la::countEqualEntries(data.getDebugX(), incomingData.getDebugX())==Dimensions-1,
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), 
          fromStack, event.toString(), marker.toString(), _spacetreeId );
        assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }
      else {
        assertionVectorNumericalEquals6(
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), fromStack, event.toString(), marker.toString(), _spacetreeId );
          assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }

      data.merge(incomingData, marker);
    }
  }

  {
    peano4::datamanagement::FaceMarker  marker(event,position);

    if ( 
      project::base_2d_euler_inline::facedata::euler2DQNew::loadPersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::facedata::euler2DQNew::receiveAndMerge(marker))
     ) {
      auto   incomingData = repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPop(
        _spacetreeId, fromStack
      )->pop();

      project::base_2d_euler_inline::facedata::euler2DQNew& data = repositories::DataRepository::_FaceDataeuler2DQNewStack.getForPush( 
        repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack)
      )->top(TwoTimesD-1-position);

      logDebug( "receiveAndMergeFace(...)", "merge " << incomingData.toString() << " into " << data.toString() << " within marker " << marker.toString() );

      if (context==::peano4::grid::TraversalObserver::SendReceiveContext::PeriodicBoundaryDataSwap) {
        assertion8(
          tarch::la::countEqualEntries(data.getDebugX(), incomingData.getDebugX())==Dimensions-1,
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), 
          fromStack, event.toString(), marker.toString(), _spacetreeId );
        assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }
      else {
        assertionVectorNumericalEquals6(
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), fromStack, event.toString(), marker.toString(), _spacetreeId );
          assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }

      data.merge(incomingData, marker);
    }
  }

  {
    peano4::datamanagement::FaceMarker  marker(event,position);

    if ( 
      project::base_2d_euler_inline::facedata::euler2DQUpdate::loadPersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::facedata::euler2DQUpdate::receiveAndMerge(marker))
     ) {
      auto   incomingData = repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPop(
        _spacetreeId, fromStack
      )->pop();

      project::base_2d_euler_inline::facedata::euler2DQUpdate& data = repositories::DataRepository::_FaceDataeuler2DQUpdateStack.getForPush( 
        repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack)
      )->top(TwoTimesD-1-position);

      logDebug( "receiveAndMergeFace(...)", "merge " << incomingData.toString() << " into " << data.toString() << " within marker " << marker.toString() );

      if (context==::peano4::grid::TraversalObserver::SendReceiveContext::PeriodicBoundaryDataSwap) {
        assertion8(
          tarch::la::countEqualEntries(data.getDebugX(), incomingData.getDebugX())==Dimensions-1,
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), 
          fromStack, event.toString(), marker.toString(), _spacetreeId );
        assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }
      else {
        assertionVectorNumericalEquals6(
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), fromStack, event.toString(), marker.toString(), _spacetreeId );
          assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }

      data.merge(incomingData, marker);
    }
  }

  {
    peano4::datamanagement::FaceMarker  marker(event,position);

    if ( 
      project::base_2d_euler_inline::facedata::euler2DFaceLabel::loadPersistently(marker) 
      and
      (context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or project::base_2d_euler_inline::facedata::euler2DFaceLabel::receiveAndMerge(marker))
     ) {
      auto   incomingData = repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPop(
        _spacetreeId, fromStack
      )->pop();

      project::base_2d_euler_inline::facedata::euler2DFaceLabel& data = repositories::DataRepository::_FaceDataeuler2DFaceLabelStack.getForPush( 
        repositories::DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack)
      )->top(TwoTimesD-1-position);

      logDebug( "receiveAndMergeFace(...)", "merge " << incomingData.toString() << " into " << data.toString() << " within marker " << marker.toString() );

      if (context==::peano4::grid::TraversalObserver::SendReceiveContext::PeriodicBoundaryDataSwap) {
        assertion8(
          tarch::la::countEqualEntries(data.getDebugX(), incomingData.getDebugX())==Dimensions-1,
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), 
          fromStack, event.toString(), marker.toString(), _spacetreeId );
        assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }
      else {
        assertionVectorNumericalEquals6(
          data.getDebugX(), incomingData.getDebugX(),
          data.getDebugH(), incomingData.getDebugH(), fromStack, event.toString(), marker.toString(), _spacetreeId );
          assertionVectorNumericalEquals6(
          data.getDebugH(), incomingData.getDebugH(),
          data.getDebugX(), incomingData.getDebugX(), fromStack, event.toString(), marker.toString(), _spacetreeId );
      }

      data.merge(incomingData, marker);
    }
  }

  logTraceOut( "receiveAndMergeFace(...)");
}

void project::base_2d_euler_inline::observers::InitGrid::receiveAndMergeVertex(int position, int fromStack, SendReceiveContext context, const peano4::grid::GridTraversalEvent& event) {
  logTraceInWith4Arguments( "receiveAndMergeVertex(...)", position, fromStack, event.toString(), _spacetreeId );

  logTraceOut( "receiveAndMergeVertex(...)");
}

void project::base_2d_euler_inline::observers::InitGrid::deleteAllStacks() {
  logTraceInWith1Argument( "deleteAllStacks()", _spacetreeId );

  peano4::parallel::SpacetreeSet::deleteAllStacks(
    repositories::DataRepository::_CellDataeuler2DQStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::deleteAllStacks(
    repositories::DataRepository::_CellDataeuler2DCellLabelStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::deleteAllStacks(
    repositories::DataRepository::_FaceDataeuler2DQOldStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::deleteAllStacks(
    repositories::DataRepository::_FaceDataeuler2DQNewStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::deleteAllStacks(
    repositories::DataRepository::_FaceDataeuler2DQUpdateStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::deleteAllStacks(
    repositories::DataRepository::_FaceDataeuler2DFaceLabelStack,
    _spacetreeId
  );

  logTraceOut( "deleteAllStacks()");
}
