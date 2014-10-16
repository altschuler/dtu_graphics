#ifndef __OBJ_LOADER_H
#define __OBJ_LOADER_H

#include <vector>
#include "Angel.h"

static std::vector<vec3> DEFAULT_VEC3_VECTOR;
static std::vector<vec2> DEFAULT_VEC2_VECTOR;

// Load an OBJ model into the out parameters.
// Note only simple OBJ files are supported.
bool loadObject(const char * filename,
	std::vector<vec3> &outPositions,
	std::vector<int> &outIndices,
	std::vector<vec3> &outNormal = DEFAULT_VEC3_VECTOR,
	std::vector<vec2> &outUv = DEFAULT_VEC2_VECTOR,
	float scale = 1.0f
	);

#endif
