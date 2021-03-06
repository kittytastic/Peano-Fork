AUTOMAKE_OPTIONS = subdir-objects
#
# By default, automake does dfs. We need the libs to be built first however.
# So we add the . explicitly. Please note that it is not enough to add your
# directory here. You also have to add any new directory to the root's 
# configure.ac script and rerun the whole autotool pipeline (see comment 
# within configure.ac as well as its very last line).
#
SUBDIRS = . \
  toolbox/blockstructured \
  toolbox/finiteelements \
  toolbox/loadbalancing \
  toolbox/multiprecision \
  toolbox/particles \
  exahype2 \
  unittests convert

#
# I want Peano4 to be as fast as possible and thus build it as static library
# such that a linker/compiler can ipo. One of the other reasons for this is 
# that I have a couple of singletons and I did struggle with singletons and 
# shared libraries. 
#
lib_LIBRARIES = libTarch.a        libTarch_debug.a        libTarch_asserts.a        libTarch_trace.a        libTarch_stats.a \
                libPeano4Core2d.a libPeano4Core2d_debug.a libPeano4Core2d_asserts.a libPeano4Core2d_trace.a libPeano4Core2d_stats.a \
                libPeano4Core3d.a libPeano4Core3d_debug.a libPeano4Core3d_asserts.a libPeano4Core3d_trace.a libPeano4Core3d_stats.a


libTarch_a_CXXFLAGS         = $(CXXFLAGS_PEANO_2D_RELEASE) 
libTarch_trace_a_CXXFLAGS   = $(CXXFLAGS_PEANO_2D_TRACE)
libTarch_asserts_a_CXXFLAGS = $(CXXFLAGS_PEANO_2D_ASSERTS)
libTarch_debug_a_CXXFLAGS   = $(CXXFLAGS_PEANO_2D_DEBUG)
libTarch_stats_a_CXXFLAGS   = $(CXXFLAGS_PEANO_2D_STATS)


libPeano4Core2d_a_CXXFLAGS          = $(CXXFLAGS_PEANO_2D_RELEASE) 
libPeano4Core2d_stats_a_CXXFLAGS    = $(CXXFLAGS_PEANO_2D_STATS) 
libPeano4Core2d_trace_a_CXXFLAGS    = $(CXXFLAGS_PEANO_2D_TRACE)
libPeano4Core2d_asserts_a_CXXFLAGS  = $(CXXFLAGS_PEANO_2D_ASSERTS) 
libPeano4Core2d_debug_a_CXXFLAGS    = $(CXXFLAGS_PEANO_2D_DEBUG)

libPeano4Core3d_a_CXXFLAGS          = $(CXXFLAGS_PEANO_3D_RELEASE) 
libPeano4Core3d_stats_a_CXXFLAGS    = $(CXXFLAGS_PEANO_3D_STATS)
libPeano4Core3d_trace_a_CXXFLAGS    = $(CXXFLAGS_PEANO_3D_TRACE)
libPeano4Core3d_asserts_a_CXXFLAGS  = $(CXXFLAGS_PEANO_3D_ASSERTS)
libPeano4Core3d_debug_a_CXXFLAGS    = $(CXXFLAGS_PEANO_3D_DEBUG)

#
# All sources below
#
Peano4Core_SOURCES = \
  peano4/datamanagement/CellMarker.cpp \
  peano4/datamanagement/FaceMarker.cpp \
  peano4/datamanagement/VertexMarker.cpp \
  peano4/peano.cpp \
  peano4/UnitTests.cpp \
  peano4/grid/AutomatonState.cpp \
  peano4/grid/EmptyTraversalObserver.cpp \
  peano4/grid/grid.cpp \
  peano4/grid/GridControlEvent.cpp \
  peano4/grid/GridVertex.cpp \
  peano4/grid/GridStatistics.cpp \
  peano4/grid/GridTraversalEvent.cpp \
  peano4/grid/GridTraversalEventGenerator.cpp \
  peano4/grid/PeanoCurve.cpp \
  peano4/grid/Spacetree.cpp \
  peano4/grid/TraversalObserver.cpp \
  peano4/grid/TraversalVTKPlotter.cpp \
  peano4/grid/tests/GridControlEventTest.cpp \
  peano4/grid/tests/SpacetreeTest.cpp \
  peano4/grid/tests/GridTraversalEventGeneratorTest.cpp \
  peano4/parallel/Node.cpp \
  peano4/parallel/parallel.cpp \
  peano4/parallel/SpacetreeSet.cpp \
  peano4/parallel/StartTraversalMessage.cpp \
  peano4/parallel/Tasks.cpp \
  peano4/parallel/TreeEntry.cpp \
  peano4/parallel/TreeManagementMessage.cpp \
  peano4/parallel/tests/PingPongTest.cpp \
  peano4/parallel/tests/NodeTest.cpp \
  peano4/stacks/stacks.cpp \
  peano4/stacks/STDVectorStack.cpp \
  peano4/utils/Loop.cpp



Tarch_SOURCES= tarch/tarch.cpp \
 tarch/UnitTests.cpp \
 tarch/la/tests/DynamicMatrixTest.cpp \
 tarch/la/tests/MatrixVectorTest.cpp \
 tarch/la/tests/MatrixTest.cpp \
 tarch/la/tests/ScalarTest.cpp \
 tarch/la/tests/GramSchmidtTest.cpp \
 tarch/la/tests/LUDecompositionTest.cpp \
 tarch/la/tests/VectorTest.cpp \
 tarch/la/ScalarOperations.cpp \
 tarch/la/Scalar.cpp \
 tarch/la/Vector.cpp \
 tarch/la/DynamicMatrix.cpp \
 tarch/multicore/BooleanSemaphore.cpp \
 tarch/multicore/multicore.cpp \
 tarch/multicore/Core.cpp \
 tarch/multicore/Lock.cpp \
 tarch/multicore/RecursiveLock.cpp \
 tarch/multicore/RecursiveSemaphore.cpp \
 tarch/multicore/SmartScheduler.cpp \
 tarch/multicore/Tasks.cpp \
 tarch/multicore/cpp/multicore.cpp \
 tarch/multicore/cpp/BooleanSemaphore.cpp \
 tarch/multicore/cpp/Core.cpp \
 tarch/multicore/cpp/RecursiveSemaphore.cpp \
 tarch/multicore/cpp/Tasks.cpp \
 tarch/multicore/omp/multicore.cpp \
 tarch/multicore/omp/BooleanSemaphore.cpp \
 tarch/multicore/omp/Core.cpp \
 tarch/multicore/omp/RecursiveSemaphore.cpp \
 tarch/multicore/omp/Tasks.cpp \
 tarch/multicore/orchestration/Hardcoded.cpp \
 tarch/multicore/orchestration/StrategyFactory.cpp \
 tarch/tests/TestCaseCollection.cpp \
 tarch/tests/TreeTestCaseCollection.cpp \
 tarch/tests/TestCase.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTUTextFileWriter_CellWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTKTextFileWriter_VertexDataWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTKTextFileWriter_VertexWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/tests/VTKBinaryFileTestCase.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTKBinaryFileWriter_CellWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTUTextFileWriter_CellDataWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTKTextFileWriter_CellWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTUTextFileWriter_VertexDataWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTKBinaryFileWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTUTextFileWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTKBinaryFileWriter_VertexWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTKBinaryFileWriter_CellDataWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTKTextFileWriter_CellDataWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTKBinaryFileWriter_VertexDataWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTUTextFileWriter_VertexWriter.cpp \
 tarch/plotter/griddata/unstructured/vtk/VTKTextFileWriter.cpp \
 tarch/plotter/PVDTimeSeriesWriter.cpp \
 tarch/plotter/griddata/blockstructured/PeanoTextPatchFileWriter.cpp \
 tarch/plotter/griddata/blockstructured/PeanoTextPatchFileWriter_VertexDataWriter.cpp \
 tarch/plotter/griddata/blockstructured/PeanoHDF5PatchFileWriter.cpp \
 tarch/plotter/griddata/blockstructured/PeanoHDF5PatchFileWriter_CellDataWriter.cpp \
 tarch/plotter/griddata/blockstructured/PeanoHDF5PatchFileWriter_VertexDataWriter.cpp \
 tarch/plotter/griddata/blockstructured/PeanoTextPatchFileWriter_CellDataWriter.cpp \
 tarch/plotter/pointdata/vtk/VTKWriter.cpp \
 tarch/mpi/BooleanSemaphore.cpp \
 tarch/mpi/Lock.cpp \
 tarch/mpi/Rank.cpp \
 tarch/mpi/mpi.cpp \
 tarch/mpi/DoubleMessage.cpp \
 tarch/mpi/IntegerMessage.cpp \
 tarch/mpi/StringMessage.cpp \
 tarch/mpi/tests/StringTest.cpp \
 tarch/logging/CommandLineLogger.cpp \
 tarch/logging/ChromeTraceFileLogger.cpp \
 tarch/logging/ITACLogger.cpp \
 tarch/logging/Log.cpp \
 tarch/logging/LogFilterFileReader.cpp \
 tarch/logging/NVTXLogger.cpp \
 tarch/logging/ScorePLogger.cpp \
 tarch/logging/LogFilter.cpp \
 tarch/logging/Statistics.cpp \
 tarch/timing/Watch.cpp \
 tarch/timing/Measurement.cpp \
 tarch/timing/GlidingAverageMeasurement.cpp \
 tarch/services/Service.cpp \
 tarch/services/ServiceRepository.cpp 


#
# Map defined source sequences onto libraries
#
libTarch_a_SOURCES         = $(Tarch_SOURCES)
libTarch_stats_a_SOURCES   = $(Tarch_SOURCES)
libTarch_trace_a_SOURCES   = $(Tarch_SOURCES)
libTarch_asserts_a_SOURCES = $(Tarch_SOURCES)
libTarch_debug_a_SOURCES   = $(Tarch_SOURCES)

libPeano4Core2d_a_SOURCES         = $(Peano4Core_SOURCES)
libPeano4Core2d_trace_a_SOURCES   = $(Peano4Core_SOURCES)
libPeano4Core2d_asserts_a_SOURCES = $(Peano4Core_SOURCES)
libPeano4Core2d_debug_a_SOURCES   = $(Peano4Core_SOURCES)
libPeano4Core2d_stats_a_SOURCES   = $(Peano4Core_SOURCES)
libPeano4Core3d_a_SOURCES         = $(Peano4Core_SOURCES)
libPeano4Core3d_trace_a_SOURCES   = $(Peano4Core_SOURCES)
libPeano4Core3d_asserts_a_SOURCES = $(Peano4Core_SOURCES)
libPeano4Core3d_debug_a_SOURCES   = $(Peano4Core_SOURCES)
libPeano4Core3d_stats_a_SOURCES   = $(Peano4Core_SOURCES)

