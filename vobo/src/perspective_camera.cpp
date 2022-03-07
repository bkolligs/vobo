#include "perspective_camera.h"

namespace vobo
{

PerspectiveCamera::PerspectiveCamera(float fov, float width, float height)
    : projectionMatrix_{
          glm::perspective(glm::radians(fov), (float) width / height, 0.1f, 100.0f)} {}

PerspectiveCamera::~PerspectiveCamera() {}

void PerspectiveCamera::recalculateViewMatrix() {
    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), position_) * rotationMatrix_;
	viewMatrix_ = glm::inverse(transform);
	viewProjectionMatrix_ = projectionMatrix_ * viewMatrix_;
}

} // namespace vobo