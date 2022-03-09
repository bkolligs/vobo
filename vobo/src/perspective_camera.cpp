#include "perspective_camera.h"
#include "log.h"

namespace vobo {

PerspectiveCamera::PerspectiveCamera(float fov, float width, float height,
                                     CameraMode mode)
    : mode_{mode},
      projectionMatrix_{glm::perspective(
          glm::radians(fov), (float)width / height, 0.1f, 100.0f)} {}

PerspectiveCamera::~PerspectiveCamera() {}

void PerspectiveCamera::recalculateViewMatrix() {

    glm::mat4 camInPivot = glm::translate(glm::mat4(1.0f), camPosInPivot_) * rotationMatrix_;
    glm::mat4 pivotInWorld = glm::translate(glm::mat4(1.0), viewPivotPos_) * viewPivotRot_;
    glm::vec4 homogCamWorld = pivotInWorld * glm::vec4(camPosInPivot_, 1.0);
    camPosInWorld_ = {homogCamWorld.x, homogCamWorld.y, homogCamWorld.z};
	viewMatrix_ = glm::inverse(pivotInWorld*camInPivot);
    viewProjectionMatrix_ = projectionMatrix_ * viewMatrix_;
}

}  // namespace vobo