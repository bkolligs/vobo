#ifndef _mesh_object_h_
#define _mesh_object_h_

#include "shader.h"
#include "vertices.h"

namespace vobo {

class MeshObject {
    protected:
        /* Pose in 3D */
        glm::mat4 objectPose_;
        MeshObject() : objectPose_{1.0f} {}

    public:
        virtual void bind() const                         = 0;
        virtual void unbind() const                       = 0;
        virtual bool modifyShader(Shader& shader) const   = 0;
        virtual const VertexArray& getVertexArray() const = 0;
        virtual const IndexBuffer& getIndexBuffer() const = 0;

        const glm::mat4& getModelMatrix() const { return objectPose_; }
        /**
         * @brief Rotate the object around the local axis by the specified angle
         */
        void rotate(float angle, const glm::vec3& axis) {
            objectPose_ = glm::rotate(objectPose_, angle, axis);
        }

        /**
         * @brief Translate the object by the provided vector
         */
        void translate(float x, float y, float z) {
            objectPose_ = glm::translate(objectPose_, glm::vec3(x, y, z));
        }
};

}  // namespace vobo
#endif  //_mesh_object_h_ header