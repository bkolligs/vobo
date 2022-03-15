#ifndef _orthographic_camera_h_
#define _orthographic_camera_h_

#include "camera.h"

namespace vobo {

class OrthographicCamera : public Camera {
   public:
    OrthographicCamera(float left, float right, float bottom, float top);
    ~OrthographicCamera();
    void recalculateViewMatrix();
};

}  // namespace vobo
#endif  //_orthographic_camera_h_ header