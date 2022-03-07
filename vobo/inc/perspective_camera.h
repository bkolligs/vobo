#ifndef _perspective_camera_h_
#define _perspective_camera_h_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace vobo {

class PerspectiveCamera {
   private:
    glm::vec3 position_             = {0.0, 0.0, 0.0};
    glm::mat4 rotationMatrix_       = glm::mat4(1.0f);
    glm::mat4 viewMatrix_           = glm::mat4(1.0f);
    glm::mat4 projectionMatrix_     = glm::mat4(1.0f);
    glm::mat4 viewProjectionMatrix_ = glm::mat4(1.0f);
    glm::vec3 upVector_             = {0.0f, 1.0f, 0.0f};

   public:
    PerspectiveCamera(float fov, float width, float height);
    ~PerspectiveCamera();
    const glm::mat4& getViewProjection() const { return viewProjectionMatrix_; }
    void setPosition(glm::vec3 position) { position_ = position; }
    void rotateBy(float angle, glm::vec3 axis) {
        rotationMatrix_ = glm::rotate(rotationMatrix_, glm::radians(angle), axis);
        recalculateViewMatrix();
    }
    void setRotation(float angle, glm::vec3 axis) {
        rotationMatrix_ = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
        recalculateViewMatrix();
    }

    void recalculateViewMatrix();
};

}  // namespace vobo

#endif  //_perspective_camera_h_ header