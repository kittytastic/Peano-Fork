
#include "TimeStep.h"
#include "DataRepository.h"

#include "peano4/grid/PeanoCurve.h"

#include "peano4/datamanagement/VertexEnumerator.h"
#include "peano4/datamanagement/VertexMarker.h"
#include "peano4/datamanagement/FaceEnumerator.h"
#include "peano4/datamanagement/FaceMarker.h"
#include "peano4/datamanagement/CellMarker.h"

#include "peano4/parallel/SpacetreeSet.h"


tarch::logging::Log examples::exahype2::swe::observers::TimeStep::_log( "examples::exahype2::swe::observers::TimeStep" );


  
examples::exahype2::swe::observers::TimeStep::TimeStep(int spacetreeId):
  _spacetreeId( spacetreeId ) , _actionSet0(spacetreeId), _actionSet1(spacetreeId), _actionSet2(spacetreeId), _actionSet3(spacetreeId), _actionSet4(spacetreeId), _actionSet5(spacetreeId)
{
}
  

  
  
peano4::grid::TraversalObserver* examples::exahype2::swe::observers::TimeStep::clone(int spacetreeId) {
  return new TimeStep(spacetreeId);
}
  
  
  
std::vector< peano4::grid::GridControlEvent > examples::exahype2::swe::observers::TimeStep::getGridControlEvents() const {
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

  return result;
}
  

  
void examples::exahype2::swe::observers::TimeStep::beginTraversal( const tarch::la::Vector<Dimensions,double>&  x, const tarch::la::Vector<Dimensions,double>&  h ) {
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


  //
  // Fill call stacks with dummies which represent level -1 such that we can 
  // call standard action routines on level 0 with parents. Without these 
  // statements, a top(1) call would raise an assertion. 
  //
  DataRepository::_CellDataSWEQStack.getForPush( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->push( examples::exahype2::swe::celldata::SWEQ() );
  for (int i=0; i<TwoTimesD; i++) {
    DataRepository::_FaceDataSWEQStack.getForPush( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->push( examples::exahype2::swe::facedata::SWEQ() );
  }
  for (int i=0; i<TwoTimesD; i++) {
    DataRepository::_FaceDataSWEQNewStack.getForPush( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->push( examples::exahype2::swe::facedata::SWEQNew() );
  }
  for (int i=0; i<TwoTimesD; i++) {
    DataRepository::_FaceDataLabelStack.getForPush( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->push( examples::exahype2::swe::facedata::Label() );
  }

  logTraceOutWith2Arguments( "beginTraversal(...)", x, h );
}
  
  
  
void examples::exahype2::swe::observers::TimeStep::endTraversal( const tarch::la::Vector<Dimensions,double>&  x, const tarch::la::Vector<Dimensions,double>&  h ) {
  logTraceInWith2Arguments( "endTraversal(...)", x, h );
  _actionSet0.endTraversal();
  _actionSet1.endTraversal();
  _actionSet2.endTraversal();
  _actionSet3.endTraversal();
  _actionSet4.endTraversal();
  _actionSet5.endTraversal();

  DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pop();
  for (int i=0; i<TwoTimesD; i++) {
    DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pop();
  }
  for (int i=0; i<TwoTimesD; i++) {
    DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pop();
  }
  for (int i=0; i<TwoTimesD; i++) {
    DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pop();
  }

  logTraceOutWith2Arguments( "endTraversal(...)", x, h );
}
  
    
void examples::exahype2::swe::observers::TimeStep::enterCell( const peano4::grid::GridTraversalEvent&  event ) {
  logTraceInWith2Arguments( "enterCell(...)", _spacetreeId, event.toString() );
  
  // Load face SWEQ
  {
    auto view = DataRepository::_FaceDataSWEQStack.getForPush( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pushBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack          = event.getFaceDataFrom(i);
      int outFaceStackPosition = event.getFaceDataTo(i);
      logDebug("enterCell(...)", "face stack " << inFaceStack << "->pos-" << outFaceStackPosition );

      peano4::datamanagement::FaceMarker  marker(event,outFaceStackPosition);
      
      examples::exahype2::swe::facedata::SWEQ data ;
      if (
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        examples::exahype2::swe::facedata::SWEQ::loadPersistently(marker)
      ) {
        assertion4( not DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,inFaceStack))->empty(), event.toString(), peano4::datamanagement::FaceMarker(event).toString(), _spacetreeId,inFaceStack );
        data = DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,inFaceStack))->pop();
      }
      
      #if PeanoDebug>0  
      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::NoData
        or
        not examples::exahype2::swe::facedata::SWEQ::loadPersistently(marker)
      ) {
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
  
  // Load face SWEQNew
  {
    auto view = DataRepository::_FaceDataSWEQNewStack.getForPush( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pushBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack          = event.getFaceDataFrom(i);
      int outFaceStackPosition = event.getFaceDataTo(i);
      logDebug("enterCell(...)", "face stack " << inFaceStack << "->pos-" << outFaceStackPosition );

      peano4::datamanagement::FaceMarker  marker(event,outFaceStackPosition);
      
      examples::exahype2::swe::facedata::SWEQNew data ;
      if (
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        examples::exahype2::swe::facedata::SWEQNew::loadPersistently(marker)
      ) {
        assertion4( not DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,inFaceStack))->empty(), event.toString(), peano4::datamanagement::FaceMarker(event).toString(), _spacetreeId,inFaceStack );
        data = DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,inFaceStack))->pop();
      }
      
      #if PeanoDebug>0  
      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::NoData
        or
        not examples::exahype2::swe::facedata::SWEQNew::loadPersistently(marker)
      ) {
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
  
  // Load face Label
  {
    auto view = DataRepository::_FaceDataLabelStack.getForPush( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pushBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStack          = event.getFaceDataFrom(i);
      int outFaceStackPosition = event.getFaceDataTo(i);
      logDebug("enterCell(...)", "face stack " << inFaceStack << "->pos-" << outFaceStackPosition );

      peano4::datamanagement::FaceMarker  marker(event,outFaceStackPosition);
      
      examples::exahype2::swe::facedata::Label data ;
      if (
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        inFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        examples::exahype2::swe::facedata::Label::loadPersistently(marker)
      ) {
        assertion4( not DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,inFaceStack))->empty(), event.toString(), peano4::datamanagement::FaceMarker(event).toString(), _spacetreeId,inFaceStack );
        data = DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,inFaceStack))->pop();
      }
      
      #if PeanoDebug>0  
      if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        or
        inFaceStack==peano4::grid::TraversalObserver::NoData
        or
        not examples::exahype2::swe::facedata::Label::loadPersistently(marker)
      ) {
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
  
  // Handle face Label
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet0.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet0.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet0.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet0.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }
  
  // Handle face Label
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet1.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet1.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet1.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet1.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }
  
  // Handle face Label
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet2.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet2.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet2.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet2.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }
  
  // Handle face Label
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet3.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet3.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet3.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet3.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }
  
  // Handle face Label
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet4.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet4.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet4.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet4.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }
  
  // Handle face Label
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet5.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet5.createHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet5.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(inFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet5.touchFaceFirstTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }
  
  // Load cell SWEQ
  {
    auto view = DataRepository::_CellDataSWEQStack.getForPush( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->pushBlock( 1 );
    
    peano4::datamanagement::CellMarker  marker(event);

    const int inCellStack  = event.getCellData();
    const int outCellStack = peano4::grid::PeanoCurve::CallStack;
    logDebug("enterCell(...)", "cell stack " << inCellStack << "->pos-" << outCellStack << "(" << examples::exahype2::swe::celldata::SWEQ::loadPersistently(marker) << ")" );
        
    examples::exahype2::swe::celldata::SWEQ& data = view.get(0);
    if (
      inCellStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      inCellStack!=peano4::grid::TraversalObserver::NoData
      and
      examples::exahype2::swe::celldata::SWEQ::loadPersistently(marker)
    ) {
      assertion3( not DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,inCellStack))->empty(), event.toString(), _spacetreeId, inCellStack);
      data = DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,inCellStack))->pop();
    }
    
    #if PeanoDebug>0  
    if (
      inCellStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      or
      inCellStack==peano4::grid::TraversalObserver::NoData
      or
      not examples::exahype2::swe::celldata::SWEQ::loadPersistently(marker)
    ) {
      data.setDebugX( marker.x() );
      data.setDebugH( marker.h() );
    }
    else {
      assertionVectorNumericalEquals3( data.getDebugX(), marker.x(), data.getDebugX(), marker.toString(), _spacetreeId );
      assertionVectorNumericalEquals3( data.getDebugH(), marker.h(), data.getDebugX(), marker.toString(), _spacetreeId );
    }
    #endif
  }
  
  // Invoke creational events on cell SWEQ
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and 
      marker.isLocal()
    ) {
      _actionSet0.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }  
  }
  
  // Invoke creational events on cell SWEQ
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and 
      marker.isLocal()
    ) {
      _actionSet1.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }  
  }
  
  // Invoke creational events on cell SWEQ
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and 
      marker.isLocal()
    ) {
      _actionSet2.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }  
  }
  
  // Invoke creational events on cell SWEQ
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and 
      marker.isLocal()
    ) {
      _actionSet3.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }  
  }
  
  // Invoke creational events on cell SWEQ
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and 
      marker.isLocal()
    ) {
      _actionSet4.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }  
  }
  
  // Invoke creational events on cell SWEQ
  {
    peano4::datamanagement::CellMarker marker( event );
    if (
      event.getCellData()==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and 
      marker.isLocal()
    ) {
      _actionSet5.createCell(
        marker,
        
        peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),
        DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }  
  }
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet0.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet1.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet2.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet3.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet4.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet5.touchCellFirstTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }

  logTraceOut( "enterCell(...)" );
}
  
void examples::exahype2::swe::observers::TimeStep::leaveCell( const peano4::grid::GridTraversalEvent&  event ) {
  logTraceInWith2Arguments( "leaveCell(...)", _spacetreeId, event.toString() );
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet5.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet4.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet3.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet2.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet1.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      );
    }
  }
  
  {
    peano4::datamanagement::CellMarker marker( event );
    if (marker.isLocal()) {
      _actionSet0.touchCellLastTime(
         marker
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
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
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
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
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
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
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
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
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
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
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
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
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )
        ,DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(1)
      ); 
    }
  }
  
  // Handle cell SWEQ
  {
    const int inCellStack   = peano4::grid::PeanoCurve::CallStack;
    const int outCellStack  = event.getCellData();
    logDebug("leaveCell(...)", "cell stack " << inCellStack << "->pos-" << outCellStack );

    peano4::datamanagement::CellMarker  marker(event);

    auto view = DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->popBlock( 1 );

    if (
      outCellStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
      and
      outCellStack!=peano4::grid::TraversalObserver::NoData
      and
      examples::exahype2::swe::celldata::SWEQ::storePersistently(marker)
    ) {
      DataRepository::_CellDataSWEQStack.getForPush( DataRepository::DataKey(_spacetreeId,outCellStack))->push( view.get(0) );
    }
  }

  // Handle face SWEQ
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet5.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet5.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet5.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet5.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }

  // Handle face SWEQ
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet4.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet4.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet4.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet4.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }

  // Handle face SWEQ
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet3.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet3.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet3.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet3.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }

  // Handle face SWEQ
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet2.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet2.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet2.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet2.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }

  // Handle face SWEQ
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet1.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet1.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet1.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet1.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }

  // Handle face SWEQ
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
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet0.destroyPersistentFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        marker.isLocal()
      ) {
        _actionSet0.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
        _actionSet0.destroyHangingFace(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
      else if (
        peano4::grid::PeanoCurve::isInOutStack(outFaceStack)
        and
        marker.isLocal()
      ) {
        _actionSet0.touchFaceLastTime(
           marker
          
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD-1) )(pick)
          ,peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQ>( &DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::SWEQNew>( &DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),peano4::datamanagement::FaceEnumerator<examples::exahype2::swe::facedata::Label>( &DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(TwoTimesD*2-1) ),DataRepository::_CellDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->top(0)
        );
      }
    }
  }

  // Store face SWEQ
  {
    auto view = DataRepository::_FaceDataSWEQStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->popBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStackPosition  = event.getFaceDataFrom(i);
      int outFaceStack         = event.getFaceDataTo(i);
      logDebug("leaveCell(...)", "pos-" << inFaceStackPosition << "->face stack " << outFaceStack );
      
      peano4::datamanagement::FaceMarker  marker(event,inFaceStackPosition);

      examples::exahype2::swe::facedata::SWEQ data = view.get(inFaceStackPosition);
      
      if (
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        examples::exahype2::swe::facedata::SWEQ::storePersistently(marker)
      ) {
        DataRepository::_FaceDataSWEQStack.getForPush( DataRepository::DataKey(_spacetreeId,outFaceStack))->push(data);
      }
    }
  }

  // Store face SWEQNew
  {
    auto view = DataRepository::_FaceDataSWEQNewStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->popBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStackPosition  = event.getFaceDataFrom(i);
      int outFaceStack         = event.getFaceDataTo(i);
      logDebug("leaveCell(...)", "pos-" << inFaceStackPosition << "->face stack " << outFaceStack );
      
      peano4::datamanagement::FaceMarker  marker(event,inFaceStackPosition);

      examples::exahype2::swe::facedata::SWEQNew data = view.get(inFaceStackPosition);
      
      if (
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        examples::exahype2::swe::facedata::SWEQNew::storePersistently(marker)
      ) {
        DataRepository::_FaceDataSWEQNewStack.getForPush( DataRepository::DataKey(_spacetreeId,outFaceStack))->push(data);
      }
    }
  }

  // Store face Label
  {
    auto view = DataRepository::_FaceDataLabelStack.getForPop( DataRepository::DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack))->popBlock( TwoTimesD );
    for (int i=0; i<TwoTimesD; i++) {
      int inFaceStackPosition  = event.getFaceDataFrom(i);
      int outFaceStack         = event.getFaceDataTo(i);
      logDebug("leaveCell(...)", "pos-" << inFaceStackPosition << "->face stack " << outFaceStack );
      
      peano4::datamanagement::FaceMarker  marker(event,inFaceStackPosition);

      examples::exahype2::swe::facedata::Label data = view.get(inFaceStackPosition);
      
      if (
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity
        and
        outFaceStack!=peano4::grid::TraversalObserver::NoData
        and
        examples::exahype2::swe::facedata::Label::storePersistently(marker)
      ) {
        DataRepository::_FaceDataLabelStack.getForPush( DataRepository::DataKey(_spacetreeId,outFaceStack))->push(data);
      }
    }
  }
  
  logTraceOut( "leaveCell(...)" );
}

void examples::exahype2::swe::observers::TimeStep::exchangeAllVerticalDataExchangeStacks( int masterId ) {
  logTraceInWith2Arguments( "exchangeAllVerticalDataExchangeStacks(...)", masterId, _spacetreeId  );

  peano4::parallel::SpacetreeSet::exchangeAllVerticalDataExchangeStacks(
    DataRepository::_CellDataSWEQStack,
    _spacetreeId,
    masterId
  );

  peano4::parallel::SpacetreeSet::exchangeAllVerticalDataExchangeStacks(
    DataRepository::_FaceDataSWEQStack,
    _spacetreeId,
    masterId
  );

  peano4::parallel::SpacetreeSet::exchangeAllVerticalDataExchangeStacks(
    DataRepository::_FaceDataSWEQNewStack,
    _spacetreeId,
    masterId
  );

  peano4::parallel::SpacetreeSet::exchangeAllVerticalDataExchangeStacks(
    DataRepository::_FaceDataLabelStack,
    _spacetreeId,
    masterId
  );

  logTraceOut( "exchangeAllVerticalDataExchangeStacks(...)" );
}

void examples::exahype2::swe::observers::TimeStep::exchangeAllHorizontalDataExchangeStacks( bool symmetricDataCardinality ) {
  logTraceInWith2Arguments( "exchangeAllHorizontalDataExchangeStacks(...)", symmetricDataCardinality, _spacetreeId  );

  peano4::parallel::SpacetreeSet::exchangeAllHorizontalDataExchangeStacks(
    DataRepository::_CellDataSWEQStack,
    _spacetreeId,
    symmetricDataCardinality
  );

  peano4::parallel::SpacetreeSet::exchangeAllHorizontalDataExchangeStacks(
    DataRepository::_FaceDataSWEQStack,
    _spacetreeId,
    symmetricDataCardinality
  );

  peano4::parallel::SpacetreeSet::exchangeAllHorizontalDataExchangeStacks(
    DataRepository::_FaceDataSWEQNewStack,
    _spacetreeId,
    symmetricDataCardinality
  );

  peano4::parallel::SpacetreeSet::exchangeAllHorizontalDataExchangeStacks(
    DataRepository::_FaceDataLabelStack,
    _spacetreeId,
    symmetricDataCardinality
  );

  logTraceOut( "exchangeAllHorizontalDataExchangeStacks(...)" );
}

void examples::exahype2::swe::observers::TimeStep::exchangeAllPeriodicBoundaryDataStacks() {
  logTraceInWith1Argument( "exchangeAllPeriodicBoundaryDataStacks()", _spacetreeId  );

  peano4::parallel::SpacetreeSet::exchangeAllPeriodicBoundaryDataStacks(
    DataRepository::_CellDataSWEQStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::exchangeAllPeriodicBoundaryDataStacks(
    DataRepository::_FaceDataSWEQStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::exchangeAllPeriodicBoundaryDataStacks(
    DataRepository::_FaceDataSWEQNewStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::exchangeAllPeriodicBoundaryDataStacks(
    DataRepository::_FaceDataLabelStack,
    _spacetreeId
  );

  logTraceOut( "exchangeAllPeriodicBoundaryDataStacks()" );
}

void examples::exahype2::swe::observers::TimeStep::streamDataFromSplittingTreeToNewTree(int newWorker) {
  logTraceInWith2Arguments( "streamDataFromSplittingTreeToNewTree(int)", _spacetreeId, newWorker );

  peano4::parallel::SpacetreeSet::streamDataFromSplittingTreeToNewTree(
    DataRepository::_CellDataSWEQStack,
    _spacetreeId,
    newWorker
  );

  peano4::parallel::SpacetreeSet::streamDataFromSplittingTreeToNewTree(
    DataRepository::_FaceDataSWEQStack,
    _spacetreeId,
    newWorker
  );

  peano4::parallel::SpacetreeSet::streamDataFromSplittingTreeToNewTree(
    DataRepository::_FaceDataSWEQNewStack,
    _spacetreeId,
    newWorker
  );

  peano4::parallel::SpacetreeSet::streamDataFromSplittingTreeToNewTree(
    DataRepository::_FaceDataLabelStack,
    _spacetreeId,
    newWorker
  );

  logTraceOut( "streamDataFromSplittingTreeToNewTree(int)");
}

void examples::exahype2::swe::observers::TimeStep::streamDataFromJoiningTreeToMasterTree(int master) {
  logTraceInWith2Arguments( "streamDataFromJoiningTreeToMasterTree(int)", _spacetreeId, master );

  peano4::parallel::SpacetreeSet::streamDataFromJoiningTreeToMasterTree(
    DataRepository::_CellDataSWEQStack,
    _spacetreeId,
    master
  );

  peano4::parallel::SpacetreeSet::streamDataFromJoiningTreeToMasterTree(
    DataRepository::_FaceDataSWEQStack,
    _spacetreeId,
    master
  );

  peano4::parallel::SpacetreeSet::streamDataFromJoiningTreeToMasterTree(
    DataRepository::_FaceDataSWEQNewStack,
    _spacetreeId,
    master
  );

  peano4::parallel::SpacetreeSet::streamDataFromJoiningTreeToMasterTree(
    DataRepository::_FaceDataLabelStack,
    _spacetreeId,
    master
  );

  logTraceOut( "streamDataFromJoiningTreeToMasterTree(int)");
}

void examples::exahype2::swe::observers::TimeStep::finishAllOutstandingSendsAndReceives() {
  logTraceInWith1Argument( "finishAllOutstandingSendsAndReceives()", _spacetreeId );

  peano4::parallel::SpacetreeSet::finishAllOutstandingSendsAndReceives(
    DataRepository::_CellDataSWEQStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::finishAllOutstandingSendsAndReceives(
    DataRepository::_FaceDataSWEQStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::finishAllOutstandingSendsAndReceives(
    DataRepository::_FaceDataSWEQNewStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::finishAllOutstandingSendsAndReceives(
    DataRepository::_FaceDataLabelStack,
    _spacetreeId
  );

  logTraceOut( "finishAllOutstandingSendsAndReceives()");
}

void examples::exahype2::swe::observers::TimeStep::sendVertex(int inOutStack, int relativePositionOnInOutStack, int toStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::datamanagement::VertexMarker& marker) {
  logTraceInWith4Arguments( "sendVertex(int,int,int)", inOutStack, relativePositionOnInOutStack, toStack, _spacetreeId );

  logTraceOut( "sendVertex(int,int,int)");
}

void examples::exahype2::swe::observers::TimeStep::sendFace(int inOutStack, int relativePositionOnInOutStack, int toStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::datamanagement::FaceMarker& marker) {
  logTraceInWith4Arguments( "sendFace(int,int,int)", inOutStack, relativePositionOnInOutStack, toStack, _spacetreeId );

  if ( context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or examples::exahype2::swe::facedata::SWEQ::send(marker) ) {
    auto& data = DataRepository::_FaceDataSWEQStack.getForPop(
      _spacetreeId,inOutStack
    )->top(relativePositionOnInOutStack);
    logDebug( "sendXXX(...)", "send out " << data.toString() << " to stack " << toStack << " (relativePositionOnInOutStack=" << relativePositionOnInOutStack << ")" );
    
    DataRepository::_FaceDataSWEQStack.getForPush(
      _spacetreeId, toStack
    ) -> push(data);
  }

  if ( context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or examples::exahype2::swe::facedata::SWEQNew::send(marker) ) {
    auto& data = DataRepository::_FaceDataSWEQNewStack.getForPop(
      _spacetreeId,inOutStack
    )->top(relativePositionOnInOutStack);
    logDebug( "sendXXX(...)", "send out " << data.toString() << " to stack " << toStack << " (relativePositionOnInOutStack=" << relativePositionOnInOutStack << ")" );
    
    DataRepository::_FaceDataSWEQNewStack.getForPush(
      _spacetreeId, toStack
    ) -> push(data);
  }

  if ( context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or examples::exahype2::swe::facedata::Label::send(marker) ) {
    auto& data = DataRepository::_FaceDataLabelStack.getForPop(
      _spacetreeId,inOutStack
    )->top(relativePositionOnInOutStack);
    logDebug( "sendXXX(...)", "send out " << data.toString() << " to stack " << toStack << " (relativePositionOnInOutStack=" << relativePositionOnInOutStack << ")" );
    
    DataRepository::_FaceDataLabelStack.getForPush(
      _spacetreeId, toStack
    ) -> push(data);
  }

  logTraceOut( "sendFace(int,int,int)");
}

void examples::exahype2::swe::observers::TimeStep::sendCell(int inOutStack, int toStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::datamanagement::CellMarker& marker) {
  logTraceInWith3Arguments( "sendCell(int,int)", inOutStack, toStack, _spacetreeId );
  const int relativePositionOnInOutStack = 0;

  if ( context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or examples::exahype2::swe::celldata::SWEQ::send(marker) ) {
    auto& data = DataRepository::_CellDataSWEQStack.getForPop(
      _spacetreeId,inOutStack
    )->top(relativePositionOnInOutStack);
    logDebug( "sendXXX(...)", "send out " << data.toString() << " to stack " << toStack << " (relativePositionOnInOutStack=" << relativePositionOnInOutStack << ")" );
    
    DataRepository::_CellDataSWEQStack.getForPush(
      _spacetreeId, toStack
    ) -> push(data);
  }

  logTraceOut( "sendCell(int,int)");
}

void examples::exahype2::swe::observers::TimeStep::receiveAndMergeVertex(const peano4::grid::GridTraversalEvent&  event, int positionWithinCell, int inOutStack, int relativePositionOnInOutStack, int fromStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::datamanagement::VertexMarker& marker) {
  logTraceInWith7Arguments( "receiveAndMergeVertex(...)", event.toString(), positionWithinCell, inOutStack, relativePositionOnInOutStack, fromStack, marker.toString(), _spacetreeId );

  logTraceOut( "receiveAndMergeVertex(...)");
}

void examples::exahype2::swe::observers::TimeStep::receiveAndMergeFace(const peano4::grid::GridTraversalEvent&  event, int positionWithinCell, int inOutStack, int relativePositionOnInOutStack, int fromStack, ::peano4::grid::TraversalObserver::SendReceiveContext context, const peano4::datamanagement::FaceMarker& marker) {
  logTraceInWith7Arguments( "receiveAndMergeFace(...)", event.toString(), positionWithinCell, inOutStack, relativePositionOnInOutStack, fromStack, marker.toString(), _spacetreeId ); 

  if ( context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or examples::exahype2::swe::facedata::SWEQ::receiveAndMerge(marker) ) {
    auto   incomingData = DataRepository::_FaceDataSWEQStack.getForPop(
      _spacetreeId, fromStack
    )->pop();
  
    auto&  data = DataRepository::_FaceDataSWEQStack.getForPush( _spacetreeId, inOutStack )->top(
      relativePositionOnInOutStack
    );
    
    assertionVectorNumericalEquals7( 
      data.getDebugX(), incomingData.getDebugX(), 
      data.getDebugH(), incomingData.getDebugH(), fromStack, inOutStack, relativePositionOnInOutStack, marker.toString(), _spacetreeId );
    assertionVectorNumericalEquals7( 
      data.getDebugH(), incomingData.getDebugH(), 
      data.getDebugX(), incomingData.getDebugX(), fromStack, inOutStack, relativePositionOnInOutStack, marker.toString(), _spacetreeId );
    
    data.merge(incomingData, marker);
  }

  if ( context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or examples::exahype2::swe::facedata::SWEQNew::receiveAndMerge(marker) ) {
    auto   incomingData = DataRepository::_FaceDataSWEQNewStack.getForPop(
      _spacetreeId, fromStack
    )->pop();
  
    auto&  data = DataRepository::_FaceDataSWEQNewStack.getForPush( _spacetreeId, inOutStack )->top(
      relativePositionOnInOutStack
    );
    
    assertionVectorNumericalEquals7( 
      data.getDebugX(), incomingData.getDebugX(), 
      data.getDebugH(), incomingData.getDebugH(), fromStack, inOutStack, relativePositionOnInOutStack, marker.toString(), _spacetreeId );
    assertionVectorNumericalEquals7( 
      data.getDebugH(), incomingData.getDebugH(), 
      data.getDebugX(), incomingData.getDebugX(), fromStack, inOutStack, relativePositionOnInOutStack, marker.toString(), _spacetreeId );
    
    data.merge(incomingData, marker);
  }

  if ( context==::peano4::grid::TraversalObserver::SendReceiveContext::Rebalancing or examples::exahype2::swe::facedata::Label::receiveAndMerge(marker) ) {
    auto   incomingData = DataRepository::_FaceDataLabelStack.getForPop(
      _spacetreeId, fromStack
    )->pop();
  
    auto&  data = DataRepository::_FaceDataLabelStack.getForPush( _spacetreeId, inOutStack )->top(
      relativePositionOnInOutStack
    );
    
    assertionVectorNumericalEquals7( 
      data.getDebugX(), incomingData.getDebugX(), 
      data.getDebugH(), incomingData.getDebugH(), fromStack, inOutStack, relativePositionOnInOutStack, marker.toString(), _spacetreeId );
    assertionVectorNumericalEquals7( 
      data.getDebugH(), incomingData.getDebugH(), 
      data.getDebugX(), incomingData.getDebugX(), fromStack, inOutStack, relativePositionOnInOutStack, marker.toString(), _spacetreeId );
    
    data.merge(incomingData, marker);
  }

  logTraceOut( "receiveAndMergeFace(...)");
}

void examples::exahype2::swe::observers::TimeStep::deleteAllStacks() {
  logTraceInWith1Argument( "deleteAllStacks()", _spacetreeId );

  peano4::parallel::SpacetreeSet::deleteAllStacks(
    DataRepository::_CellDataSWEQStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::deleteAllStacks(
    DataRepository::_FaceDataSWEQStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::deleteAllStacks(
    DataRepository::_FaceDataSWEQNewStack,
    _spacetreeId
  );

  peano4::parallel::SpacetreeSet::deleteAllStacks(
    DataRepository::_FaceDataLabelStack,
    _spacetreeId
  );

  logTraceOut( "deleteAllStacks()");
}
