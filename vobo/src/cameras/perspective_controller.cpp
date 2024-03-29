#include "perspective_controller.h"

namespace vobo {

PerspectiveController::PerspectiveController(
    WindowEvents& inputs, float fov, float width, float height,
    const glm::vec3 initialPosition)
    : inputs_{inputs},
      camera_{fov, width, height},
      windowWidth_{width},
      windowHeight_{height} {
    camera_.setCamPosInPivot(initialPosition);
}

PerspectiveController::~PerspectiveController() {}

void PerspectiveController::onUpdate() {
    double xVel = inputs_.getMouseXVel();
    double yVel = inputs_.getMouseYVel();
    /* Get the camera position in pivot */
    glm::vec3 camPosPivot = camera_.getCamPosInPivot();
    glm::vec3 pivotPos = camera_.getPivotPos();

    /* Orbit around pivot */
    if (inputs_.isMousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
        float dXAngle = (2 * M_PI / windowWidth_),
              dYAngle = (M_PI / windowHeight_);
        float xAngle  = -xVel * dXAngle;
        float yAngle  = -yVel * dYAngle;

        /* Rotate around the x-axis */
        camera_.rotatePivot(xAngle, {0.0f, 1.0f, 0.0f});
        /* Rotate around the y-axis */
        camera_.rotatePivot(yAngle, {1.0f, 0.0f, 0.0f});
    }

    /* Zoom in and out */
    camera_.setCamPosInPivot(
        {camPosPivot.x, camPosPivot.y,
         camPosPivot.z + inputs_.getScrollY() * zoomSpeed_});
    /* Pan around the pivot */
    if (inputs_.isMousePressed(GLFW_MOUSE_BUTTON_RIGHT)) {
        camera_.setCamPosInPivot({
            camPosPivot.x - xVel * xPanSpeed_,
            camPosPivot.y + yVel * yPanSpeed_,
            camPosPivot.z,
        });
    }

    /* Move the pivot in space */
    if (inputs_.isMousePressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
        camera_.setPivotPos({
            pivotPos.x + xVel * xPanSpeed_,
            pivotPos.y + yVel * yPanSpeed_,
            pivotPos.z
        });
    }
}
}  // namespace vobo