#include "perspective_camera.h"
#include "log.h"

namespace vobo {

PerspectiveCamera::PerspectiveCamera(float fov, float width, float height)
    : Camera{{glm::perspective(glm::radians(fov), (float)width / height, 0.1f,
                               100.0f)}} {}

PerspectiveCamera::~PerspectiveCamera() {}

void PerspectiveCamera::recalculateViewMatrix() {
    /* Transform the camera from the pivot frame to the world frame */
    glm::mat4 camInPivot =
        glm::translate(glm::mat4(1.0f), camPosInPivot_) * camOriInPivot_;
    glm::mat4 pivotInWorld =
        glm::translate(glm::mat4(1.0), pivotPosInWorld_) * pivotOriInWorld_;
    glm::vec4 homogCamWorld = pivotInWorld * glm::vec4(camPosInPivot_, 1.0);
    /* Update the camera position and orientation */
    camPosInWorld_        = {homogCamWorld.x, homogCamWorld.y, homogCamWorld.z};
    camOriInWorld_ = pivotOriInWorld_ * camOriInPivot_;
    /* Update the view and view projection matrix */
    viewMatrix_           = glm::inverse(pivotInWorld * camInPivot);
    viewProjectionMatrix_ = projectionMatrix_ * viewMatrix_;
}

}  // namespace vobo