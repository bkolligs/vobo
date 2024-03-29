#include "pyramid.h"
namespace vobo {

Pyramid::Pyramid(float x, float y, float z)
    : pyramidBuffer{&vertices[0], vertices.size() * sizeof(PyramidVertex)},
      pyramidIndices{pyramidData, sizeof(pyramidData) / sizeof(unsigned int)},
      MeshObject{} {
    /* Bind the current array to the data */
    pyramidArray.bind();
    pyramidBuffer.bind();

    /* We "push" a new type of data onto the pyramidLayout, so it can calculate
     * stride and offset automatically */
    pyramidLayout.push<float>(3, "positions");
    pyramidLayout.push<float>(3, "color");
    pyramidLayout.push<float>(2, "texture");
    /* link the vertex array and buffer objects */
    pyramidArray.linkVBO(pyramidBuffer, pyramidLayout);

    translate(x, y, z);
}

void Pyramid::bind() const {
    pyramidArray.bind();
    pyramidIndices.bind();
}

void Pyramid::unbind() const {
    pyramidArray.unbind();
    pyramidIndices.unbind();
    pyramidBuffer.unbind();
}

bool Pyramid::modifyShader(Shader& shader) const {
    /* Do stuff with the shader and return true if successful*/
    return true;
}

}  // namespace vobo
