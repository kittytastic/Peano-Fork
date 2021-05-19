#include "Tracer.h"
#include "particles.h"


#include "peano4/utils/Loop.h"


tarch::la::Vector<Dimensions,int> toolbox::particles::mapParticleOntoVoxel(
  const peano4::datamanagement::CellMarker& marker,
  int voxelsPerAxis,
  const tarch::la::Vector<Dimensions,double>& particleX
) {
  toolbox::particles::addBibTeXEntry();

  tarch::la::Vector<Dimensions,int> result;

  assertion(voxelsPerAxis>0);
  double cartesianMeshH = marker.h()(0) / voxelsPerAxis;

  for (int d=0; d<Dimensions; d++) {
    double positionWithinPatch = particleX(d) - marker.getOffset()(d);
    result(d) = static_cast<int>( std::floor( positionWithinPatch / cartesianMeshH ));
    result(d) = std::max(0, result(d));
    result(d) = std::min(voxelsPerAxis-1, result(d));
  }

  return result;
}


tarch::la::Vector<Dimensions,double> toolbox::particles::explicitEulerWithoutInterpolation(
  const peano4::datamanagement::CellMarker&   marker,
  int                                         voxelsPerAxis,
  int                                         unknownsPerVoxel,
  const tarch::la::Vector<Dimensions,int>&    velocityIndices,
  double                                      timeStepSize,
  double*                                     voxelField,
  const tarch::la::Vector<Dimensions,double>& particleX
) {
  tarch::la::Vector<Dimensions,int> voxel = toolbox::particles::mapParticleOntoVoxel(marker,unknownsPerVoxel,particleX);

  int voxelIndex = peano4::utils::dLinearised(voxel,unknownsPerVoxel);
  double* Q      = voxelField + voxelIndex * unknownsPerVoxel;

  tarch::la::Vector<Dimensions,double> result = particleX;
  for (int d=0; d<Dimensions; d++) {
    result(d) += timeStepSize * Q[ velocityIndices(d) ];
  }

  return result;
}


