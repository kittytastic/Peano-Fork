// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _PEANO4_GRID_TRAVERSAL_VTK_PLOTTER_H_
#define _PEANO4_GRID_TRAVERSAL_VTK_PLOTTER_H_


#include "TraversalObserver.h"


#include "tarch/logging/Log.h"


#include "tarch/plotter/griddata/unstructured/vtk/VTUTextFileWriter.h"
#include "tarch/plotter/griddata/VTUTimeSeriesWriter.h"


namespace peano4 {
  namespace grid {
    class TraversalVTKPlotter;
  }
}


/**
 * Observer which pipes the automaton transitions into a VTK file
 *
 * While we use the up-to-date vtk format, the observer plots the whole thing
 * as a discontinuous unstructured mesh. It is not particular sophisticated.
 *
 * The plotter can write whole time series. For this, you have to invoke
 * startNewSnapshot() prior to each plot.
 */
class peano4::grid::TraversalVTKPlotter: public peano4::grid::TraversalObserver {
  protected:
    static tarch::logging::Log  _log;

    const std::string                                                                _filename;
    const int                                                                        _spacetreeId;

    static int                                                                       _counter;

    /**
     * In a parallel environment, please invoke this operation only on the main
     * writer. This guy himself will be empty, but it has to build up the vector
     * of existing data files.
     */
    void updateMetaFile(int spacetreeId);
    void closeFile();
    void openFile();

  private:
    tarch::plotter::griddata::unstructured::vtk::VTUTextFileWriter*                  _writer;
    tarch::plotter::griddata::unstructured::UnstructuredGridWriter::VertexWriter*    _vertexWriter;
    tarch::plotter::griddata::unstructured::UnstructuredGridWriter::CellWriter*      _cellWriter;
    tarch::plotter::griddata::unstructured::UnstructuredGridWriter::CellDataWriter*  _spacetreeIdWriter;
    tarch::plotter::griddata::unstructured::UnstructuredGridWriter::CellDataWriter*  _coreWriter;
    tarch::plotter::griddata::VTUTimeSeriesWriter                                    _timeSeriesWriter;

    std::vector<std::string>                                                         _clonedSpacetreeIds;
  public:
    /**
     * You have to invoke startNewSnapshot() if you wanna have a pvd file
     * immediately after you've created this observer in the main code.
     *
     * If this guy is ran on the global master,
     */
    TraversalVTKPlotter( const std::string& filename, int treeId=-1 );
    virtual ~TraversalVTKPlotter();

	void beginTraversal() override;
	void endTraversal() override;

	void enterCell(
      const GridTraversalEvent&  event
    ) override;

	void leaveCell(
      const GridTraversalEvent&  event
    ) override;

	/**
	 * This is the main plotter. In the parallel case, I will have to check
	 * whether I'm on the global rank as well.
	 *
	 * <h2> Thread safety </h2>
	 *
	 * As clone() might be called by multiple threads in parallel, I need some
	 * semaphore mechanism.
	 *
	 * <h2> Inheriting </h2>
	 *
	 * If you inherit from the plotter, please call updateMetaFile() whenever
	 * you clone. However, do this only on spacetreeId==-1, i.e. on the
	 * original observer.
	 */
	TraversalObserver* clone(int spacetreeId) override;

	/**
	 * @return Name of the meta file that has to link to all of the actual data files
	 */
	void startNewSnapshot(bool isParallelRun);
	std::vector< GridControlEvent > getGridControlEvents() override;
};

#endif
