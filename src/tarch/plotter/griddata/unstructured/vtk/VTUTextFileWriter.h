// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _TARCH_PLOTTER_GRIDDATA_UNSTRUCTURED_VTU_VTUTEXTFILEWRITER_H_
#define _TARCH_PLOTTER_GRIDDATA_UNSTRUCTURED_VTU_VTUTEXTFILEWRITER_H_


#include "tarch/logging/Log.h"
#include "tarch/plotter/griddata/unstructured/UnstructuredGridWriter.h"
#include <vector>
#include <string>
#include "../../../PVDTimeSeriesWriter.h"


namespace tarch {
  namespace plotter {
    namespace griddata {
      namespace unstructured {
        namespace vtk {
          class VTUTextFileWriter;
        }
      }
    }
  }
}


/**
 * VTU Writer
 *
 * Output for vtk files (paraview) as text files. We write unstructured vtk
 * (vtu) files here.
 *
 * !! Usage
 *
 * - Create an instance of the VTUTextFileWriter.
 * - For the vertices you want to write, you have to create your own
 *   VertexWriter.
 * - Pass all the vertices to this writer (both hanging and persistent nodes).
 *   For each vertex you receive an unique number. Remember this number.
 * - For the elements you want to write, you have to create your own
 *   CellWriter.
 * - For each record create a data writer. There's two writers: One for the
 *   vertices and one for the cells.
 *
 * !!! Thread-safety
 *
 * The plotter is not thread-safe and shall never be thread-safe: It is the
 * responsibility of the using system to implement thread-safe calls. For
 * Peano, this is the mappings where some events could occur simultaneously.
 *
 * @author Tobias Weinzierl
 */
class tarch::plotter::griddata::unstructured::vtk::VTUTextFileWriter:
  public tarch::plotter::griddata::unstructured::UnstructuredGridWriter {
  private:
    /**
     * Logging device.
     */
    static tarch::logging::Log _log;

    static const std::string HEADER;

    const std::string _dataType;

    bool _writtenToFile;

    /**
     * Total number of vertices
     */
    int _numberOfVertices;

    /**
     * Total number of cells
     */
    int _numberOfCells;

    std::string _vertexDescription;
    std::string _cellDescription;
    std::string _vertexDataDescription;
    std::string _cellDataDescription;
    std::string _parallelVertexDataDescription;
    std::string _parallelCellDataDescription;

    std::string _fileName;

    void validateDataWriterIdentifier( const std::string& identifier ) const;

  public:
    VTUTextFileWriter(const std::string&  fileName, const std::string&  indexFileName, tarch::plotter::PVDTimeSeriesWriter::IndexFileMode modeFile, const int precision=6);
    virtual ~VTUTextFileWriter();

    bool isOpen() override;

    /**
     * @param filename Name of output file. Should be unique for each thread/rank combination
     * @param parallelMetaFilename Meta file giving an overview over all files written simultaneously
     */
    bool writeToFile() override;

    void clear() override;

    VertexWriter*      createVertexWriter() override;
    CellWriter*        createCellWriter() override;
    CellDataWriter*    createCellDataWriter( const std::string& identifier, int recordsPerCell ) override;
    VertexDataWriter*  createVertexDataWriter( const std::string& identifier, int recordsPerVertex ) override;

    /**
     * This can be called on any writer (if there are multiple ones in a
     * parallel run), but it cannot be static, as I have to know the unknown
     * identifiers, e.g.
     */
    void writeMetaDataFileForParallelSnapshot(
      const std::string& metaDataFilename,
	  const std::vector< std::string >& files
    );

    /**
     * This is the vertex writer you have to create to plot the vertices.
     * Besides the pure syntax management, the writer also provides a number
     * generator which provides you with a unique id for each vertex.
     *
     * Please ensure that you call close() on the vertex writer before you
     * close the underlying VTUTextFileWriter.
     */
    class VertexWriter:
      public tarch::plotter::griddata::unstructured::UnstructuredGridWriter::VertexWriter {
      private:
        /**
         * The father class is a friend. There are no other friends.
         */
        friend class VTUTextFileWriter;


        /** either "float" or "double" depending on _precision */
        const std::string _dataType;

        /**
         * Counter for the vertices written. Holds the maximum index.
         */
        int _currentVertexNumber;

        /**
         * Underlying VTU writer.
         */
        VTUTextFileWriter& _myWriter;

        /**
         * Output stream
         */
        std::ostringstream _out;

        VertexWriter(VTUTextFileWriter& writer, std::string datatype);

        /**
         * Do not copy a vertex writer.
         */
        VertexWriter(const VertexWriter& writer):
          _dataType(writer._dataType),
          _currentVertexNumber(writer._currentVertexNumber),
          _myWriter(writer._myWriter),
          _out() {
          assertion(false);
        }
      public:
        virtual ~VertexWriter();

        int plotVertex(const tarch::la::Vector<2,double>& position) override;
        int plotVertex(const tarch::la::Vector<3,double>& position) override;

        void close() override;
    };

    /**
     * Writes the element data.
     */
    class CellWriter:
      public tarch::plotter::griddata::unstructured::UnstructuredGridWriter::CellWriter {
      private:
        /**
         * The father class is a friend. There are no other friends.
         */
        friend class VTUTextFileWriter;

        const std::string _dataType;

        /**
         * Counter for the elements written. Holds the maximum index.
         */
        int _currentCellNumber;
        int _currentCellOffset;

        /**
         * Underlying VTU writer.
         */
        VTUTextFileWriter& _myWriter;

        /**
         * Output stream
         */
        std::ostringstream _connectivityOut;

        /**
         * Output stream
         */
        std::ostringstream _offsetsOut;

        /**
         * Output stream
         */
        std::ostringstream _typesOut;

        CellWriter(VTUTextFileWriter& writer, std::string datatype);

        CellWriter(const CellWriter& writer):
          _dataType(writer._dataType),
          _currentCellNumber(writer._currentCellNumber),
          _currentCellOffset(writer._currentCellOffset),
          _myWriter(writer._myWriter),
          _connectivityOut(),
          _offsetsOut(),
          _typesOut() {
          assertion(false);
        }
      public:
        virtual ~CellWriter();

        int plotHexahedron(int vertexIndex[8]) override;

        int plotQuadrangle(int vertexIndex[4]) override;

        int plotLine(int vertexIndex[2]) override;

        int plotTriangle(int vertexIndex[3]) override;

        int plotPoint(int vertexIndex) override;

        void close() override;
    };

    class CellDataWriter:
      public tarch::plotter::griddata::unstructured::UnstructuredGridWriter::CellDataWriter {
        private:
          /**
           * The father class is a friend. There are no other friends.
           */
          friend class VTUTextFileWriter;

          const std::string _dataType;

          /**
           * Only required for assertions
           */
          const std::string _identifier;

          /**
           * Is set to -1 in the beginning and then incremented by each data
           * plot call. If we close the writer, the counter is reset to -2.
           */
          int _lastWriteCommandCellNumber;

          /**
           * Underlying VTU writer.
           */
          VTUTextFileWriter& _myWriter;

          /**
           * Output stream
           */
          std::ostringstream _out;

          int _recordsPerCell;

          double _minValue;
          double _maxValue;
          CellDataWriter(const std::string& dataIdentifier, VTUTextFileWriter& writer, int recordsPerCell, std::string dataType);

          CellDataWriter(const CellDataWriter& copy):
            _dataType(copy._dataType),
            _myWriter(copy._myWriter) {
            assertion(false);
          }
      public:
        virtual ~CellDataWriter();

        void close() override;

        void plotCell( int index, double value ) override;
        void plotCell( int index, const tarch::la::Vector<2,double>& value ) override;
        void plotCell( int index, const tarch::la::Vector<3,double>& value ) override;
        void plotCell( int index, double* values, int numberOfValues ) override;

        double getMinValue() const;
        double getMaxValue() const;

        void assignRemainingCellsDefaultValues() override;
    };

    class VertexDataWriter:
      public tarch::plotter::griddata::unstructured::UnstructuredGridWriter::VertexDataWriter {
        private:
        /**
         * The father class is a friend. There are no other friends.
         */
        friend class VTUTextFileWriter;

        const std::string _dataType;

        /**
         *
         */
        int _lastWriteCommandVertexNumber;

        /**
         * Underlying VTU writer.
         */
        VTUTextFileWriter& _myWriter;

        /**
         * Output stream
         */
        std::ostringstream _out;

        int _recordsPerVertex;

        double _minValue;
        double _maxValue;

        std::string  _identifier;

        VertexDataWriter(const std::string& dataIdentifier, VTUTextFileWriter& writer, int recordsPerVertex, std::string dataType);

        VertexDataWriter(const VertexDataWriter& copy):
          _dataType(copy._dataType),
          _myWriter(copy._myWriter) {
          assertion(false);
        }
      public:
        virtual ~VertexDataWriter();

        void close() override;

        void plotVertex( int index, double value ) override;
        void plotVertex( int index, const tarch::la::Vector<2,double>& value ) override;
        void plotVertex( int index, const tarch::la::Vector<3,double>& value ) override;
        void plotVertex( int index, double* values, int numberOfValues ) override;

        double getMinValue() const;
        double getMaxValue() const;

        void assignRemainingVerticesDefaultValues() override;
    };
};

#endif
