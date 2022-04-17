#ifndef _ico_sphere_h_
#define _ico_sphere_h_

#include "mesh_object.h"

namespace vobo {

class IcoSphere : public MeshObject {
    private:
        struct IcoSphereVertex {
                glm::vec3 position;
                glm::vec3 color;
                glm::vec2 texCoords;
        };

        /* The poles are a the zenith, which in this case is aligned with the
         * y-axis */
        double northPoleAngle = glm::radians(0.0f);
        double southPoleAngle = glm::radians(180.0f);
        /* Inclination is the angle between zenith and line OP */
        double upperVertexInclinationAngle = glm::radians(90.0f) - glm::atan(0.5f);
        double lowerVertexInclinationAngle = glm::radians(90.0f) + glm::atan(0.5f);
        /* IcoSphere is a pentagon from above */
        std::vector<IcoSphereVertex> vertices;

        std::vector<uint> sphereData;

        VertexArray sphereArray;
        StaticVertexBuffer sphereBuffer;
        StaticIndexBuffer sphereIndices;
        VertexBufferLayout sphereLayout;

    public:
        IcoSphere(float x = 0, float y = 0, float z = 0, int subdivisions=1);
        ~IcoSphere(){}
        void bind() const override;
        void unbind() const override;
        bool modifyShader(Shader& shader) const override;
        const VertexArray& getVertexArray() const override {
            return sphereArray;
        }
        const StaticIndexBuffer& getIndexBuffer() const override {
            return sphereIndices;
        }
};

}  // namespace vobo

#endif  //_ico_sphere_h_ header