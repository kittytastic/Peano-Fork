// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _TARCH_PLOTTER_GRID_DATA_BLOCK_STRUCTURED_PATCH_WRITER_H_
#define _TARCH_PLOTTER_GRID_DATA_BLOCK_STRUCTURED_PATCH_WRITER_H_


#include "tarch/la/Vector.h"


namespace tarch {
  namespace plotter {
    namespace griddata {
      namespace blockstructured {
        class PatchWriter;
      }
    }
  }
}


/**
 * Abstract base class for a patch plotter
 *
 * Patch plotters are either wrappers around existing plotters or real
 * plotters. This is their abstract interface. They are different to
 * the
 *
 * @author Kristof Unterweger, Tobias Weinzierl
 */
class tarch::plotter::griddata::blockstructured::PatchWriter {
  public:
    /**
     * @return Write has been successful
     */
    virtual bool writeToFile( const std::string& filename ) = 0;

    /**
     * @return Whether writer is ready to accept data.
     */
    virtual bool isOpen() = 0;

    /**
     * Clear the writer, i.e. erase all the data. However, as the writer does
     * not track how many vertex and cell writers you've created, it's up to
     * you to ensure that none of these instances is left.
     */
    virtual void clear() = 0;

    /**
     * A writer for scalar data on elements.
     */
    class CellDataWriter {
   	  public:
        virtual ~CellDataWriter() {};

        /**
         * Write data for one cell.
         *
         * @param index Index of the cell. This index has to equal the index
         *              used for the cell within the VTKWriter class
         *              interface.
         * @param value Value for the cell.
         */
        virtual void plotCell( int index, double value ) = 0;
        virtual void plotCell( int index, double* values ) = 0;

        /**
         * If you close your writer, each cell/vertex has to be assigned a
         * value, i.e. you may not add less data than you have cells. See
         *
         */
        virtual void close() = 0;

        /**
         * @see close()
         */
        virtual void assignRemainingCellsDefaultValues() = 0;

        virtual int getFirstCellWithinPatch(int index) const = 0;
    };

    /**
     * A writer for scalar data on points (vertices).
     */
    class VertexDataWriter {
      public:
        virtual ~VertexDataWriter() {};

        /**
         * Write data for one cell.
         *
         * @param index Index of the vertex. This index has to equal the index
         *              used for the cell within the VTKWriter class
         *              interface.
         * @param value Value for the cell.
         */
        virtual void plotVertex( int index, double value ) = 0;
        virtual void plotVertex( int index, double* values ) = 0;

        virtual void close() = 0;

        /**
         * @see close()
         */
        virtual void assignRemainingVerticesDefaultValues() = 0;

        virtual int getFirstVertexWithinPatch(int index) const = 0;
    };

    virtual int plotPatch(
      const tarch::la::Vector<2,double>& offset,
      const tarch::la::Vector<2,double>& size
    ) = 0;

    virtual int plotPatch(
      const tarch::la::Vector<3,double>& offset,
      const tarch::la::Vector<3,double>& size
    ) = 0;


    /**
     * Caller has to destroy this instance manually.
     */
    virtual CellDataWriter*    createCellDataWriter( const std::string& identifier, int unknownsPerAxis, int recordsPerCell ) = 0;
    virtual CellDataWriter*    createCellDataWriter( const std::string& identifier, int unknownsPerAxis, int recordsPerCell, const std::string& metaData ) = 0;
    virtual CellDataWriter*    createCellDataWriter( const std::string& identifier, int unknownsPerAxis, int recordsPerCell, const std::string& metaData, double* mapping ) = 0;

    /**
     * Caller has to destroy this instance manually.
     */
    virtual VertexDataWriter*  createVertexDataWriter( const std::string& identifier, int unknownsPerAxis, int recordsPerVertex ) = 0;
    virtual VertexDataWriter*  createVertexDataWriter( const std::string& identifier, int unknownsPerAxis, int recordsPerVertex, const std::string& metaData  ) = 0;
    virtual VertexDataWriter*  createVertexDataWriter( const std::string& identifier, int unknownsPerAxis, int recordsPerVertex, const std::string& metaData, double* mapping ) = 0;

};

#endif
