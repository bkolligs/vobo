#ifndef _ico_sphere_h_
#define _ico_sphere_h_

#include "mesh_object.h"
#include "vobo_math.h"

namespace vobo {

class IcoSphere : public MeshObject {
    private:
        struct IcoSphereVertex {
                glm::vec3 position;
                glm::vec3 color;
                glm::vec2 texCoords;
        };

        static constexpr float phi            = (1 + sqrt(5)) / 2;
        std::vector<IcoSphereVertex> vertices = {
            {
                position : {0, 1, phi},
                color : {0.1, 0, 0.3},
                texCoords : {},
            },
            {
                position : {0, 1, -phi},
                color : {0.1, 0, 0.4},
                texCoords : {},
            },
            {
                position : {0, -1, phi},
                color : {0.1, 0, 0.3},
                texCoords : {},
            },
            {
                position : {0, -1, -phi},
                color : {0.1, 0, 0.3},
                texCoords : {},
            },
            {
                position : {1, phi, 0},
                color : {0.2, 0, 0.8},
                texCoords : {},
            },
            {
                position : {1, -phi, 0},
                color : {0.1, 0, 0.9},
                texCoords : {},
            },
            {
                position : {-1, phi, 0},
                color : {0.1, 0.1, 0.5},
                texCoords : {},
            },
            {
                position : {-1, -phi, 0},
                color : {0.1, 0.3, 0.3},
                texCoords : {},
            },
            {
                position : {phi, 0, 1},
                color : {0.1, 0, 0.3},
                texCoords : {},
            },
            {
                position : {phi, 0, -1},
                color : {0.1, 0, 0.2},
                texCoords : {},
            },
            {
                position : {-phi, 0, 1},
                color : {0.1, 0, 0.3},
                texCoords : {},
            },
            {
                position : {-phi, 0, -1},
                color : {0.1, 0, 0.9},
                texCoords : {},
            },
        };

        // clang-format off
        std::vector<uint> sphereData = {
            // top level
            0, 2, 8, 
            0, 4, 8,
            0, 4, 6,
            0, 6, 10,
            0, 2, 10,
            // middle level
            2, 5, 8,
            5, 8, 9,
            8, 9, 4, 
            9, 4, 1,
            4, 1, 6,
            1, 6, 11,
            6, 11, 10,
            11, 10, 7,
            10, 7, 2,
            7, 2, 5,
            // bottom
            3, 5, 9,
            3, 9, 1,
            3, 1, 11,
            3, 11, 7,
            3, 5, 7,
        };
        // clang-format on

        VertexArray sphereArray;
        StaticVertexBuffer sphereBuffer;
        StaticIndexBuffer sphereIndices;
        VertexBufferLayout sphereLayout;

    public:
        IcoSphere(float x = 0, float y = 0, float z = 0, float radius = 1.0,
                  int subdivisions = 1);
        ~IcoSphere() {}
        void bind() const override;
        void unbind() const override;
        bool modifyShader(Shader& shader) const override;
        const VertexArray& getVertexArray() const override {
            return sphereArray;
        }
        const StaticIndexBuffer& getIndexBuffer() const override {
            if (sphereIndices.good())
                return sphereIndices;
            else {
                std::stringstream errorMessage;
                errorMessage << VOBO_ERROR_STRING(
                    "[IcoSphere] Sphere index buffer is not in a valid state!");
                throw std::runtime_error(errorMessage.str());
            }
        }
};

}  // namespace vobo

#endif  //_ico_sphere_h_ header