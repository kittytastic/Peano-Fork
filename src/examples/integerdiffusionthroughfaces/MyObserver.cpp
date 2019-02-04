#include "MyObserver.h"
#include "CellDataPlotter.h"

#include "peano4/grid/GridControlEvent.h"
#include "peano4/grid/GridTraversalEvent.h"
#include "peano4/grid/PeanoCurve.h"
#include "peano4/parallel/Node.h"


tarch::logging::Log  examples::integerdiffusionthroughfaces::MyObserver::_log( "examples::integerdiffusionthroughfaces::MyObserver" );


std::map< examples::integerdiffusionthroughfaces::MyObserver::DataKey, examples::integerdiffusionthroughfaces::MyObserver::FaceDataContainer >   examples::integerdiffusionthroughfaces::MyObserver::_faceData;
std::map< examples::integerdiffusionthroughfaces::MyObserver::DataKey, examples::integerdiffusionthroughfaces::MyObserver::CellDataContainer >   examples::integerdiffusionthroughfaces::MyObserver::_cellData;


examples::integerdiffusionthroughfaces::MyObserver::MyObserver(int spacetreeId, int counter):
  _spacetreeId(spacetreeId),
  _iterationCounter(counter)
  {
  #if PeanoDebug>0
  _mapping.append( new MyMapping() );
  _mapping.append( new CellDataPlotter() );
  #endif
}


void examples::integerdiffusionthroughfaces::MyObserver::beginTraversal() {
  _iterationCounter++;
  _mapping.beginTraversal();
}


//
// @todo
//
// LOP: Wo ist Skeleton/Enclave Marker?
//      Wie identifizeren fuer parallelen Code lokale vs. andere Vertices, Faces und Zellen
//
//

void examples::integerdiffusionthroughfaces::MyObserver::endTraversal() {
  // @todo Level 8
  #if PeanoDebug>0
  for( auto& p: _cellData) {
	logDebug( "endTraversal()", "cell stack (" << p.first.first << "," << p.first.second << "): " << p.second.size() << " entries" );
  }
  #endif
  _mapping.endTraversal();
}


void examples::integerdiffusionthroughfaces::MyObserver::enterCell(
  const peano4::grid::GridTraversalEvent&  event
) {
  logTraceInWith1Argument("enterCell(...)",event.toString());

  // Vertex processing -> nop here
  // =============================


  // Face processing
  // ===============
  // @todo If there were vertices, then we would pass in vertices via an enumerator
  FaceDataContainer::PushBlockVertexStackView faceView = _faceData[ DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack) ].pushBlock(Dimensions*2);
  for (int i=0; i<Dimensions*2; i++) {
    int inFaceStack  = event.getFaceDataFrom(i);
	int outFaceStack = event.getFaceDataTo(i);
    FaceData data;

    tarch::la::Vector<Dimensions,double> x = event.getX();
    int normal = outFaceStack % Dimensions;
    x(normal) += outFaceStack >= Dimensions ? event.getH(normal)/2.0 : -event.getH(normal)/2.0;

	logDebug("enterCell(...)", "face " << inFaceStack << "->pos-" << outFaceStack );
    if (inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity) {
      _mapping.createPersistentFace(x,event.getH(),normal,data.value);
      _mapping.touchFaceFirstTime(x,event.getH(),normal,data.value);
      #if PeanoDebug>=1
      data.x = x;
      data.h = event.getH();
      #endif
    }
    else if (inFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity) {
      _mapping.createHangingFace(x,event.getH(),normal,data.value);
      _mapping.touchFaceFirstTime(x,event.getH(),normal,data.value);
      #if PeanoDebug>=1
      data.x = x;
      data.h = event.getH();
      #endif
    }
    else {
      data = _faceData[ DataKey(_spacetreeId,inFaceStack) ].pop();
      assertionVectorNumericalEquals4(data.x,x,event.toString(),normal,data.x,x );
      assertionVectorNumericalEquals4(data.h,event.getH(),event.toString(),normal,data.x,x );
      if (peano4::grid::PeanoCurve::isInOutStack(inFaceStack)) {
        _mapping.touchFaceFirstTime(x,event.getH(),normal,data.value);
      }
    }
    faceView.set(outFaceStack,data);
  }

  // @todo raus
  for (int i=0; i<Dimensions*2; i++) {
	logDebug( "enterCell()", "face " << i << ": " << faceView.get(i).x << "x" << faceView.get(i).h );
  }

  // Cell processing
  // ===============
  // @todo faces + enumerator
  // @todo coarser level + enumerator
  int inCellStack  = event.getCellData();
  int outCellStack = peano4::grid::PeanoCurve::CallStack;
  CellData data;
  logDebug("enterCell(...)", "cell " << inCellStack << "->pos-" << outCellStack << ": " << data.x << "x" << data.h );
  if (inCellStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity) {
    _mapping.createCell(event.getX(),event.getH(),data.value);
    #if PeanoDebug>=1
    data.x = event.getX();
    data.h = event.getH();
    #endif
  }
  else {
    data = _cellData[ DataKey(_spacetreeId,inCellStack) ].pop();
  }
  assertionVectorNumericalEquals4(data.x,event.getX(),data.value,event.toString(),data.x,data.h);
  assertionVectorNumericalEquals4(data.h,event.getH(),data.value,event.toString(),data.x,data.h);
  _cellData[ DataKey(_spacetreeId,outCellStack) ].push(data);

  // @todo Es gibt noch kein inside/outside hier, oder?
  // @todo Enclaves fehlen halt auch noch

  // @todo Ich will pointer durchreichen, aber nix auf dem Call-Stack
  _mapping.touchCellFirstTime( event.getX(), event.getH(), data.value );

  logTraceOutWith1Argument("enterCell(...)",event.toString());
}


void examples::integerdiffusionthroughfaces::MyObserver::leaveCell(
  const peano4::grid::GridTraversalEvent&  event
) {
  logTraceInWith1Argument("leaveCell(...)",event.toString());

  // @todo Es gibt noch kein inside/outside hier, oder?
  // @todo Enclaves fehlen halt auch noch

  int inCellStack   = peano4::grid::PeanoCurve::CallStack;
  int outCellStack  = event.getCellData();
  logDebug("leaveCell(...)", "cell " << inCellStack << "->" << outCellStack );
  CellData data = _cellData[ DataKey(_spacetreeId,inCellStack) ].pop();
  assertionVectorNumericalEquals4(data.x,event.getX(),data.value,data.x,data.h,event.toString());
  assertionVectorNumericalEquals4(data.h,event.getH(),data.value,data.x,data.h,event.toString());

  // @todo Ich will pointer durchreichen, aber nix auf dem Call-Stack -> moves directly
  _mapping.touchCellLastTime( event.getX(), event.getH(), data.value );

  if (outCellStack==TraversalObserver::CreateOrDestroyPersistentGridEntity) {
    _mapping.destroyCell(event.getX(),event.getH(),data.value);
  }
  else {
    _cellData[ DataKey(_spacetreeId,outCellStack) ].push(data);
  }

  // @todo Faces
  FaceDataContainer::PopBlockVertexStackView faceView = _faceData[ DataKey(_spacetreeId,peano4::grid::PeanoCurve::CallStack) ].popBlock(Dimensions*2);


  // @todo raus
  for (int i=0; i<Dimensions*2; i++) {
	logDebug( "leaveCell()", "face " << i << ": " << faceView.get(i).x << "x" << faceView.get(i).h );
  }

  for (int i=0; i<Dimensions*2; i++) {
    int inFaceStack  = event.getFaceDataFrom(i);
	int outFaceStack = event.getFaceDataTo(i);

	FaceData data = faceView.get(inFaceStack);
	logDebug("leaveCell(...)", "face pos-" << inFaceStack << "->" << outFaceStack << ": " << data.x << "x" << data.h << "x" << data.value );

    tarch::la::Vector<Dimensions,double> x = event.getX();
    int normal = inFaceStack % Dimensions;
    x(normal) += inFaceStack >= Dimensions ? event.getH(normal)/2.0 : -event.getH(normal)/2.0;

    assertionVectorNumericalEquals4(data.x,x,event.toString(),normal,data.x,x );
    assertionVectorNumericalEquals4(data.h,event.getH(),event.toString(),normal,data.x,x );

    if (outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyPersistentGridEntity) {
      _mapping.touchFaceLastTime(x,event.getH(),normal,data.value);
      _mapping.destroyPersistentFace(x,event.getH(),normal,data.value);
    }
    else if (outFaceStack==peano4::grid::TraversalObserver::CreateOrDestroyHangingGridEntity) {
      _mapping.touchFaceLastTime(x,event.getH(),normal,data.value);
      _mapping.destroyHangingFace(x,event.getH(),normal,data.value);
    }
    else {
      if (peano4::grid::PeanoCurve::isInOutStack(outFaceStack)) {
        _mapping.touchFaceLastTime(x,event.getH(),normal,data.value);
      }
      _faceData[ DataKey(_spacetreeId,outFaceStack) ].push(data);
    }
  }

  logTraceOutWith1Argument("leaveCell(...)",event.toString());
}


peano4::grid::TraversalObserver* examples::integerdiffusionthroughfaces::MyObserver::clone(int spacetreeId) {
  return new MyObserver( spacetreeId, _iterationCounter );
}


std::vector< peano4::grid::GridControlEvent > examples::integerdiffusionthroughfaces::MyObserver::getGridControlEvents() {
	// @todoo Das sollte natuerlich auch in mapping raus und muss dann dort u.U. gemerged werden
  std::vector< peano4::grid::GridControlEvent >  controlEvents;
  if (_iterationCounter<8) {
    peano4::grid::GridControlEvent newEvent;
    newEvent.setRefinementControl( peano4::grid::GridControlEvent::RefinementControl::Refine );
#if Dimensions==2
    newEvent.setOffset( {0.0,0.0} );
    newEvent.setWidth( {0.5,0.5} );
    newEvent.setH( {0.02,0.02} );
#elif Dimensions==3
    newEvent.setOffset( {0.0,0.0,0.0} );
    newEvent.setWidth( {0.5,0.5,0.5} );
    newEvent.setH( {0.02,0.02,0.02} );
#endif
    controlEvents.push_back(newEvent);
  }

  if (_iterationCounter>12) {
    peano4::grid::GridControlEvent newEvent;
	newEvent.setRefinementControl( peano4::grid::GridControlEvent::RefinementControl::Erase );
#if Dimensions==2
	newEvent.setOffset( {0.01,0.01} );
	newEvent.setWidth( {0.99,0.99} );
	newEvent.setH( {0.4,0.4} );
#elif Dimensions==3
	newEvent.setOffset( {0.01,0.01,0.01} );
	newEvent.setWidth( {0.99,0.99,0.99} );
	newEvent.setH( {0.4,0.4,0.4} );
#endif
    controlEvents.push_back(newEvent);
  }

  return controlEvents;
}

