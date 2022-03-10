#ifndef _perspective_controller_h_
#define _perspective_controller_h_

#include "perspective_camera.h"
#include "vobo_memory.h"
#include "window_events.h"

namespace vobo {

class PerspectiveController {
    private:
        PerspectiveCamera camera_;
        WindowEvents& inputs_;
        float windowWidth_, windowHeight_;
        /* Panning speeds */
        float xPanSpeed_ = 0.001, yPanSpeed_ = 0.001;
        /* Zoom speed */
        float zoomSpeed_ = 0.01;

    public:
        PerspectiveController(WindowEvents& inputs, float fov, float width,
                              float height, const glm::vec3 initialPosition = {0.0f, 0.0f, 3.0f});
        ~PerspectiveController();
        /* Maybe add method to change camera properties after initialization? */
        void onUpdate();
        void setMouseSpeeds(float xPanSpeed, float yPanSpeed) {
            xPanSpeed_ = xPanSpeed;
            yPanSpeed_ = yPanSpeed;
        }
        const PerspectiveCamera& getCamera() const { return camera_; }
};

}  // namespace vobo
#endif  //_perspective_controller_h_ header