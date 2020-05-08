// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _PEANO4_GRID_TRAVERSAL_VTK_PLOTTER_H_
#define _PEANO4_GRID_TRAVERSAL_VTK_PLOTTER_H_


#include "TraversalObserver.h"


#include "tarch/logging/Log.h"


#include "tarch/plotter/griddata/unstructured/vtk/VTUTextFileWriter.h"
#include "tarch/plotter/griddata/VTUTimeSeriesWriter.h"


#include "../config.h"


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
 * startNewSnapshot() prior to each plot. It is the latter which also ensures
 * that parallel plots in an MPI environment do work.
 */
class peano4::grid::TraversalVTKPlotter: public peano4::grid::TraversalObserver {
  protected:
    static tarch::logging::Log  _log;

    #ifdef Parallel
    static int _plotterMessageTag;
    #endif

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

    /**
     * Does the actual plotting, i.e. all checks/decision making is already done before
     */
    void plotCell(
        const GridTraversalEvent&  event
    );
  private:
    tarch::plotter::griddata::unstructured::vtk::VTUTextFileWriter*                  _writer;
    tarch::plotter::griddata::unstructured::UnstructuredGridWriter::VertexWriter*    _vertexWriter;
    tarch::plotter::griddata::unstructured::UnstructuredGridWriter::CellWriter*      _cellWriter;
    tarch::plotter::griddata::unstructured::UnstructuredGridWriter::CellDataWriter*  _spacetreeIdWriter;
    tarch::plotter::griddata::unstructured::UnstructuredGridWriter::CellDataWriter*  _coreWriter;
    tarch::plotter::griddata::VTUTimeSeriesWriter                                    _timeSeriesWriter;

    /**
     * Whenever I clone this observer, it enters its filename into this vector.
     * This way, I know per rank which trees have written something. Whenever I
     * dump a time series file, this thing is cleared as we restart to "collect"
     * dumps.
     */
    std::vector<std::string>                                                         _clonedSpacetreeIds;

    std::string getFilename( int spacetreeId ) const;
  public:
    /**
     * You have to invoke startNewSnapshot() if you wanna have a pvd file
     * immediately after you've created this observer in the main code.
     *
     * If this guy is ran on the global master,
     */
    TraversalVTKPlotter( const std::string& filename, int treeId=-1 );
    virtual ~TraversalVTKPlotter();

    void beginTraversal(
      const tarch::la::Vector<Dimensions,double>&  x,
      const tarch::la::Vector<Dimensions,double>&  h
    ) override;

    void endTraversal(
      const tarch::la::Vector<Dimensions,double>&  x,
      const tarch::la::Vector<Dimensions,double>&  h
    ) override;

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
 * \section Thread safety
 *
 * As clone() might be called by multiple threads in parallel, I need some
 * semaphore mechanism.
 *
 * \section Inheriting
 *
 * If you inherit from the plotter, please call updateMetaFile() whenever
 * you clone. However, do this only on spacetreeId==-1, i.e. on the
 * original observer.
     */
    TraversalObserver* clone(int spacetreeId) override;

    /**
     * This routine has to be called prior to the traversal call on the
     * spacetree set. In an MPI environment, it has to be called on all
     * ranks. So it is different to beginTraversal(). beginTraversal()
     * is invoked per thread/per tree, while this one per rank.
     */
    void beginTraversalOnRank(bool isParallelRun);
    void endTraversalOnRank(bool isParallelRun);

    /**
     * Obviously empty for this particular observer.
     */
    std::vector< GridControlEvent > getGridControlEvents() override;

    void exchangeAllVerticalDataExchangeStacks(int masterId ) override;
    void exchangeAllHorizontalDataExchangeStacks(bool symmetricDataCardinality ) override;
    void exchangeAllPeriodicBoundaryDataStacks() override;
    void finishAllOutstandingSendsAndReceives() override;

};

#endif
