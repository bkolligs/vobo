#ifndef _perspective_camera_h_
#define _perspective_camera_h_
#include "camera.h"

namespace vobo {

class PerspectiveCamera : public Camera{
   public:
    PerspectiveCamera(float fov, float width, float height);
    ~PerspectiveCamera();

    void recalculateViewMatrix();
};

}  // namespace vobo

#endif  //_perspective_camera_h_ header