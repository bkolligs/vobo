#include "cube.h"

namespace vobo {

Cube::Cube(float x, float y, float z)
    : cubeBuffer{&vertices[0], vertices.size() * sizeof(CubeVertex)},
      cubeIndices{cubeData, sizeof(cubeData) / sizeof(unsigned int)},
      MeshObject{} {
	cubeArray.bind();	  
	cubeBuffer.bind();


    cubeLayout.push<float>(3, "positions");
    cubeLayout.push<float>(3, "color");
    cubeLayout.push<float>(2, "texture");
    /* link the vertex array and buffer objects */
    cubeArray.linkVBO(cubeBuffer, cubeLayout);

    translate(x, y, z);
}

void Cube::bind() const {
	cubeArray.bind();
	cubeIndices.bind();
}

void Cube::unbind() const {
	cubeArray.unbind();
	cubeIndices.unbind();
	cubeBuffer.unbind();
}

bool Cube::modifyShader(Shader & shader) const {
	return true;
}

}  // namespace vobo
