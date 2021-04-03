#include "TraversalVTKPlotter.h"
#include "Spacetree.h"
#include "GridControlEvent.h"
#include "GridTraversalEvent.h"

#include "peano4/utils/Loop.h"
#include "peano4/parallel/SpacetreeSet.h"

#include "tarch/mpi/Rank.h"
#include "tarch/mpi/StringMessage.h"
#include "tarch/mpi/IntegerMessage.h"

#include "tarch/multicore/Lock.h"
#include "tarch/multicore/Core.h"

#include <string>



tarch::logging::Log  peano4::grid::TraversalVTKPlotter::_log( "peano4::grid::TraversalVTKPlotter" );


int peano4::grid::TraversalVTKPlotter::_counter(0);


peano4::grid::TraversalVTKPlotter::TraversalVTKPlotter( const std::string& filename, int treeId ):
  _filename(filename),
  _spacetreeId(treeId),
  _writer(nullptr),
  _vertexWriter(nullptr),
  _cellWriter(nullptr),
  _spacetreeIdWriter(nullptr),
  _coreWriter(nullptr) {
}


peano4::grid::TraversalVTKPlotter::~TraversalVTKPlotter() {
}


void peano4::grid::TraversalVTKPlotter::beginTraversal(
  const tarch::la::Vector<Dimensions,double>&  x,
  const tarch::la::Vector<Dimensions,double>&  h
) {
  static int counter = 0;

  static tarch::multicore::BooleanSemaphore localSemaphore;
  tarch::multicore::Lock  localLock( localSemaphore );

  int isFirstBarrierHitOnThisRank = ::peano4::parallel::SpacetreeSet::getInstance().synchroniseFirstThreadPerRank(_filename + "-init");

  std::ostringstream snapshotFileName;
  snapshotFileName << _filename << "-" << counter;

  if ( counter==0 and isFirstBarrierHitOnThisRank and tarch::mpi::Rank::getInstance().isGlobalMaster() ) {
    _writer = new tarch::plotter::griddata::unstructured::vtk::VTUTextFileWriter(
        snapshotFileName.str(),
      _filename,
      tarch::plotter::PVDTimeSeriesWriter::IndexFileMode::CreateNew
    );
  }
  else if ( isFirstBarrierHitOnThisRank and tarch::mpi::Rank::getInstance().isGlobalMaster() ) {
    _writer = new tarch::plotter::griddata::unstructured::vtk::VTUTextFileWriter(
        snapshotFileName.str(),
      _filename,
      tarch::plotter::PVDTimeSeriesWriter::IndexFileMode::AppendNewDataSet
    );
  }

  counter++;

  ::peano4::parallel::SpacetreeSet::getInstance().synchroniseFirstThreadPerRank(_filename + "-write");

  if ( _writer==nullptr ) {
    _writer = new tarch::plotter::griddata::unstructured::vtk::VTUTextFileWriter(
        snapshotFileName.str(),
      _filename,
      tarch::plotter::PVDTimeSeriesWriter::IndexFileMode::AppendNewData
    );
  }

  _vertexWriter      = _writer->createVertexWriter();
  _cellWriter        = _writer->createCellWriter();
  _spacetreeIdWriter = _writer->createCellDataWriter( "tree-id", 1 );
  _coreWriter        = _writer->createCellDataWriter( "core-number", 1 );
}


void peano4::grid::TraversalVTKPlotter::endTraversal(
  const tarch::la::Vector<Dimensions,double>&  x,
  const tarch::la::Vector<Dimensions,double>&  h
) {
  assertion(_writer!=nullptr);

  _vertexWriter->close();
  _cellWriter->close();
  _spacetreeIdWriter->close();
  _coreWriter->close();

  if (_spacetreeId>=0) {
    _writer->writeToFile();
  }

  delete _writer;
  delete _vertexWriter;
  delete _cellWriter;
  delete _spacetreeIdWriter;
  delete _coreWriter;

  _writer            = nullptr;
  _vertexWriter      = nullptr;
  _cellWriter        = nullptr;
  _spacetreeIdWriter = nullptr;
  _coreWriter        = nullptr;

}


std::string peano4::grid::TraversalVTKPlotter::getFilename( int spacetreeId ) const {
  std::string currentFile = _filename;

  // we run serially
  if (spacetreeId==-1) {
    currentFile += "-" + std::to_string( _counter );
  }
  else {
    currentFile += "-" + std::to_string(spacetreeId) + "-" + std::to_string( _counter );
  }

  return currentFile;
}


void peano4::grid::TraversalVTKPlotter::enterCell(
  const GridTraversalEvent&  event
) {
  bool plot = event.getIsRefined()==0 and event.getIsCellLocal();
  if (plot) {
    plotCell(event);
  }
}


void peano4::grid::TraversalVTKPlotter::plotCell(
  const GridTraversalEvent&  event
) {
  int vertexIndices[TwoPowerD];

  dfor2(k)
    assertion( _vertexWriter!=nullptr );
    vertexIndices[kScalar] = _vertexWriter->plotVertex(
      event.getX() + tarch::la::multiplyComponents( tarch::la::convertScalar<double>(k), event.getH() ) - event.getH() * 0.5
    );
  enddforx

	assertion( _cellWriter!=nullptr );
	int cellIndex = -1;

	#if Dimensions==2
  cellIndex = _cellWriter->plotQuadrangle(vertexIndices);
  #elif Dimensions==3
  cellIndex = _cellWriter->plotHexahedron(vertexIndices);
  #else
  logError( "enterCell(...)", "supports only 2d and 3d" );
  #endif

  assertion( _spacetreeIdWriter!=nullptr );
  assertion( _coreWriter!=nullptr );
  _spacetreeIdWriter->plotCell(cellIndex,_spacetreeId);
   _coreWriter->plotCell(cellIndex,tarch::multicore::Core::getInstance().getCoreNumber());
}


void peano4::grid::TraversalVTKPlotter::leaveCell(
  const GridTraversalEvent&  event
) {
}


peano4::grid::TraversalObserver*  peano4::grid::TraversalVTKPlotter::clone(int spacetreeId) {
  return new peano4::grid::TraversalVTKPlotter(
    _filename,
    spacetreeId
  );
}


std::vector< peano4::grid::GridControlEvent > peano4::grid::TraversalVTKPlotter::getGridControlEvents() const {
  return std::vector< peano4::grid::GridControlEvent >();
}
