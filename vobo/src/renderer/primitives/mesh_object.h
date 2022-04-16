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
        virtual const StaticIndexBuffer& getIndexBuffer() const = 0;

        const glm::mat4& getModelMatrix() const { return objectPose_; }
        /**
         * @brief Rotate the object around the local axis by the specified angle
         */
        void rotate(float angle           = 0.0,
                    const glm::vec3& axis = {0.0f, 1.0f, 0.0f}) {
            objectPose_ = glm::rotate(objectPose_, angle, axis);
        }

        /**
         * @brief Translate the object by the provided vector
         */
        void translate(float x = 0.0, float y = 0.0, float z = 0.0) {
            objectPose_ = glm::translate(objectPose_, glm::vec3(x, y, z));
        }

        /**
         * @brief Scale the object along a certain axis
         */
        void scale(float x = 1.0, float y = 1.0, float z = 1.0) {
            objectPose_ = glm::scale(objectPose_, glm::vec3(x, y, z));
        }
};

}  // namespace vobo
#endif  //_mesh_object_h_ header