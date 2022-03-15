#ifndef _pyramid_h_
#define _pyramid_h_

#include "mesh_object.h"
#include "glm/glm.hpp"
#include "vertices.h"

namespace vobo
{
	
#define NUM_PYRAMID_VERTICES 5

struct PyramidVertex
{
	glm::vec3 position;
	glm::vec3 color;
	
};

class Pyramid : public MeshObject
{
private:
	PyramidVertex vertices[NUM_PYRAMID_VERTICES] = {
		{{-0.5, 0.0f, 0.5f}, {0.1f, 0.0f, 0.02f}},
		{{-0.5f, 0.0f, -0.5f}, {0.8f, 0.3f, 0.02f}},
		{{0.5f, 0.0f, -0.5f}, {0.2f, 0.8f, 0.12f}},
		{{0.5f, 0.0f, 0.5f},{0.8f, 0.3f, 0.02f}},
		{{0.0f, 0.8f, 0.0f},{0.1f, 0.1f, 0.92f}}
	};

	uint pyramidData[3*6] = {0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};

public:
	Pyramid(/* args */);
	~Pyramid();
};

} // namespace vobo
#endif //_pyramid_h_ header