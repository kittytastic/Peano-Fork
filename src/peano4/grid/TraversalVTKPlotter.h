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
  private:
    static tarch::logging::Log  _log;

    const std::string                                                                _filename;
    const int                                                                        _spacetreeId;
    int                                                                              _counter;
    tarch::plotter::griddata::unstructured::vtk::VTUTextFileWriter*                  _writer;
    tarch::plotter::griddata::unstructured::UnstructuredGridWriter::VertexWriter*    _vertexWriter;
    tarch::plotter::griddata::unstructured::UnstructuredGridWriter::CellWriter*      _cellWriter;
//    tarch::plotter::griddata::unstructured::UnstructuredGridWriter::CellDataWriter*  _cellWriter;
    tarch::plotter::griddata::VTUTimeSeriesWriter                                    _timeSeriesWriter;

    std::vector<std::string>                                                         _clonedSpacetreeIds;
  public:
    TraversalVTKPlotter( const std::string& filename, int treeId=-1, int counter=0 );
    virtual ~TraversalVTKPlotter();

	void beginTraversal() override;
	void endTraversal() override;

	void enterCell(
      const tarch::la::Vector<Dimensions,double>& x,
      const tarch::la::Vector<Dimensions,double>& h,
	  bool                                        isRefined
    ) override;

	/**
	 * This is the main plotter. In the parallel case, I will have to check
	 * whether I'm on the global rank as well.
	 *
	 * <h2> Thread safety </h2>
	 *
	 * As clone() might be called by multiple threads in parallel, I need some
	 * semaphore mechanism.
	 */
	TraversalObserver* clone(int spacetreeId) override;

	void startNewSnapshot();
};

#endif
