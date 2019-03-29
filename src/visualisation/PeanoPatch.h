#ifndef PEANOPATCH_H_
#define PEANOPATCH_H_

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "PeanoVariable.h"
#include "PeanoPatchData.h"

//#include "../config.h"
//#ifdef UseVTK
/*
#include "boost/algorithm/string/predicate.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/trim.hpp"
#include "boost/lexical_cast.hpp"
*/


class PeanoPatch {
  public:
	PeanoPatch();
	virtual ~PeanoPatch();
	int dimensions;//number of dimensions, probably 3

	/*
	 * number of points in each dimension
	 */
	int* resolution;

	/*
	 * offset of the patch in each dimension
	 */
	double* offsets;

	/*
	 * size of the patch in each dimension
	 */
	double* sizes;

	/**
	 * Mapping from
	 */
	std::unordered_map<std::string, PeanoPatchData*> patchData;
	bool hasMappings();
	PeanoVariable* getStructure();
	double* getPositionMap(int x, int y, int z);
	double* getPositionVertex(int x, int y, int z);
	double* getPositionCellCenter(int x, int y, int z);
	int getIndexCellData(int x, int y, int z);
	int getIndexVertexData(int x, int y, int z);
};

#endif /* PEANOPATCH_H_ */
