#include "ico_sphere.h"

namespace vobo {

IcoSphere::IcoSphere(float x, float y, float z, int subdivisions)
    : sphereBuffer( &vertices[0], vertices.size() * sizeof(IcoSphereVertex) ),
      sphereIndices( &sphereData[0], sizeof(sphereData) / sizeof(unsigned int) ),
      MeshObject( ) {
    sphereArray.bind();
    sphereBuffer.bind();

    sphereLayout.push<float>(3, "positions");
    sphereLayout.push<float>(3, "color");
    sphereLayout.push<float>(2, "texture");

    sphereArray.linkVBO(sphereBuffer, sphereLayout);
}

void IcoSphere::bind() const {
    sphereArray.bind();
    sphereIndices.bind();
}

void IcoSphere::unbind() const {
    sphereArray.unbind();
    sphereIndices.unbind();
    sphereBuffer.unbind();
}

bool IcoSphere::modifyShader(Shader& shader) const { return true; }

}  // namespace vobo
