#ifndef _orthographic_camera_h_
#define _orthographic_camera_h_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace vobo {

class OrthographicCamera {
   private:
    glm::mat4 projectionMatrix_     = glm::mat4(1.0);
    glm::mat4 viewMatrix_           = glm::mat4(1.0);
    glm::mat4 viewProjectionMatrix_ = glm::mat4(1.0);
    /* Position of the camera in world coordinates */
    glm::vec3 position_ = {0.0f, 0.0f, 0.0f};
    /* Rotation along the z-axis in degrees*/
    float rotation_ = 0;

   public:
    OrthographicCamera(float left, float right, float bottom, float top);
    ~OrthographicCamera();
    void setPosition(glm::vec3 position = {0.0f, 0.0f, 0.0f}) {
        position_ = position;
        recalculateViewMatrix();
    }
    const glm::mat4& getViewProjection() const { return viewProjectionMatrix_; }
    /* Set the rotation around the z-axis in degrees */
    void setRotation(float angle = 0) {
        rotation_ = angle;
        recalculateViewMatrix();
    }
    void recalculateViewMatrix();
};

}  // namespace vobo
#endif  //_orthographic_camera_h_ header