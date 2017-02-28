#include "tarch/plotter/griddata/unstructured/vtk/VTUBinaryFileWriter.h"

#include <stdio.h>
#include <fstream>
#include <iomanip>

tarch::logging::Log tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::_log( "tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter" );


const std::string tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::HEADER =
"<?xml version=\"1.0\"?>\n\
<!-- Generated by Peano3 output component $Revision: 1.2 $ Author: Tobias Weinzierl -->\n";


tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::VTUBinaryFileWriter(const int precision):
  _dataType(precision < 7 ? "Float32" : "Float64"),
  _writtenToFile(false),
  _numberOfVertices(0),
  _numberOfCells(0) {}


tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::~VTUBinaryFileWriter() {
  if (!_writtenToFile) {
    assertionEqualsMsg( _numberOfVertices,    0, "Still vertices in vtk writer pipeline. Maybe you forgot to call writeToFile() on a data vtk writer?" );
    assertionEqualsMsg( _numberOfCells,       0, "Still cells in vtk writer pipeline. Maybe you forgot to call writeToFile() on a data vtk writer?" );
    assertionEqualsMsg( _numberOfCellEntries, 0, "Still cell entries in vtk writer pipeline. Maybe you forgot to call writeToFile() on a data vtk writer?" );
  }
}


void tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::clear() {
  _writtenToFile       = false;
  _numberOfVertices    = 0;
  _numberOfCells       = 0;
  _vertexDescription.clear();
  _cellDescription.clear();
  _vertexDataDescription.clear();
  _cellDataDescription.clear();
}


bool tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::writeToFile( const std::string& filename ) {
  assertion( !_writtenToFile );

  logError( "writeToFile(std::string)", "The VTU binary write is under construction. We do not recommend to use it. ");

  if (filename.rfind(".vtu")==std::string::npos) {
    logWarning( "writeToFile()", "filename should end with .vtu but is " << filename );
  }

  std::ofstream out;
  out.open( filename.c_str() );
  if ( (!out.fail()) && out.is_open() ) {
    _log.debug( "close()", "opened data file " + filename );

    out << HEADER << std::endl << std::endl
        << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">" << std::endl
        << "<UnstructuredGrid>" << std::endl
        << "<Piece NumberOfPoints=\"" << _numberOfVertices << "\" NumberOfCells=\"" << _numberOfCells << "\">" << std::endl
        << _vertexDescription.rdbuf() << std::endl
        << _cellDescription.rdbuf() << std::endl
        <<  "<PointData>" << std::endl
        << _vertexDataDescription.rdbuf() << std::endl
        << "</PointData>" << std::endl
        << "<CellData>" << std::endl
        << _cellDataDescription.rdbuf() << std::endl
        << "</CellData>\n\
        </Piece>\n\
      </UnstructuredGrid>\n\
    </VTKFile>\n";

    _log.debug( "close()", "data written to " + filename );
    _writtenToFile = true;
    return true;
  }
  else {
  	_log.error( "close()", "unable to write output file " + filename );
  	return false;
  }
}


bool tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::isOpen() {
  return !_writtenToFile;
}


tarch::plotter::griddata::unstructured::UnstructuredGridWriter::VertexWriter*
tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::createVertexWriter() {
  return new tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::VertexWriter(*this,_dataType);
}


tarch::plotter::griddata::unstructured::UnstructuredGridWriter::CellWriter*
tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::createCellWriter() {
  return new tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::CellWriter(*this,_dataType);
}


void tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::validateDataWriterIdentifier( const std::string& identifier ) const {
  if (identifier.empty()) {
    logWarning(
      "validateDataWriterIdentifier(string)",
      "identifier for vtk file is empty. Spaces are not allowed for vtk data field identifiers and some vtk visualisers might crash."
    );
  }
  if (identifier.find(' ')!=std::string::npos) {
    logWarning(
      "validateDataWriterIdentifier(string)",
      "identifier \"" << identifier << "\" contains spaces. Spaces are not allowed for vtk data field identifiers and some vtk visualisers might crash."
    );
  }
}


tarch::plotter::griddata::Writer::CellDataWriter*    tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::createCellDataWriter( const std::string& identifier, int recordsPerCell ) {
  validateDataWriterIdentifier(identifier);
  return new tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::CellDataWriter(identifier,*this, recordsPerCell, _dataType);
}


tarch::plotter::griddata::Writer::VertexDataWriter*  tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::createVertexDataWriter( const std::string& identifier, int recordsPerVertex ) {
  validateDataWriterIdentifier(identifier);
  return new tarch::plotter::griddata::unstructured::vtk::VTUBinaryFileWriter::VertexDataWriter(identifier,*this, recordsPerVertex, _dataType);
}
