#include "ico_sphere.h"

namespace vobo {

IcoSphere::IcoSphere(float x, float y, float z, float radius, int subdivisions)
    : sphereBuffer{&vertices[0], vertices.size() * sizeof(IcoSphereVertex)},
      sphereIndices{&sphereData[0], sphereData.size()},
      MeshObject() {
    sphereArray.bind();
    sphereBuffer.bind();

    sphereLayout.push<float>(3, "positions");
    sphereLayout.push<float>(3, "color");
    sphereLayout.push<float>(2, "texture");

    /* Create the IcoSphere at the appropriate subdivision level */

    if (sphereBuffer.good() and sphereIndices.good())
        sphereArray.linkVBO(sphereBuffer, sphereLayout);
    else {
        std::stringstream errorMessage;
        errorMessage << VOBO_ERROR_STRING(
            "[IcoSphere] Sphere vertex buffer is not in a valid state!");
        throw std::runtime_error(errorMessage.str());
    }

    translate(x, y, z);
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
