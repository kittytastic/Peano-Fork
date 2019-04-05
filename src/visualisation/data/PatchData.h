#ifndef _VISUALISATION_DATA_PATCH_DATA_H_
#define _VISUALISATION_DATA_PATCH_DATA_H_

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "Variable.h"


namespace visualisation {
  namespace data {
    class PatchData;
  }
}


#define MaxDimensions 3


/**
 * A patch is a square or cube in the domain. It can hold variables which have
 * been identified before via a Variable entry.
 */
class visualisation::data::PatchData {
  public:
	PatchData(int dimensions, double* offset_, double* size_, int dofsPerAxis);

	bool samePatch( const PatchData& otherPatch );
	bool overlaps( const PatchData& otherPatch );

	/**
	 * Free internal dynamic data types
	 */
	void free();

	const int dimensions;

	/*
	 * offset of the patch in each dimension
	 */
	double offset[MaxDimensions];

	/*
	 * size of the patch in each dimension
	 */
	double size[MaxDimensions];

	/**
	 * Mapping from variables onto the actual data. We store data as AoS. It
	 * is furthermore ordered lexicographically, i.e. the x index is the
	 * fastest running index.
	 */
	double* data;

	void copyData( const PatchData& otherData, int dofsPerAxis );
};

#endif
