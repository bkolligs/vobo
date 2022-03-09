#ifndef _perspective_camera_h_
#define _perspective_camera_h_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace vobo {

enum class CameraMode {
    LOOKAT=0,
    RELATIVE
};

class PerspectiveCamera {
   private:
    glm::mat4 rotationMatrix_       = glm::mat4(1.0f);
    glm::mat4 viewMatrix_           = glm::mat4(1.0f);
    glm::mat4 projectionMatrix_     = glm::mat4(1.0f);
    glm::mat4 viewProjectionMatrix_ = glm::mat4(1.0f);
    glm::vec3 viewPivotPos_           = {0.0f, 0.0f, 0.0f};
    glm::mat4 viewPivotRot_           = glm::mat4(1.0f);
    glm::vec3 camPosInPivot_ = {0.0f, 0.0f, 0.0f};
    glm::vec3 camPosInWorld_ = {0.0f, 0.0f, 0.0f};
    CameraMode mode_;

   public:
    PerspectiveCamera(float fov, float width, float height, CameraMode mode = CameraMode::LOOKAT);
    ~PerspectiveCamera();
    const glm::mat4& getViewProjection() const { return viewProjectionMatrix_; }
	const glm::vec3& getCamWorld() const {return camPosInWorld_;}
    const glm::vec3& getCamPivot() const {return camPosInPivot_;}
    
    void setCamPivotPos(glm::vec3 &&position) { camPosInPivot_ = position; recalculateViewMatrix();}

    /* Dealing with camera in it's local coordinates */
    const glm::mat4 & getCamRot() const {return rotationMatrix_;}
    void rotateCamPivot(float angle, glm::vec3&& axis) {
        rotationMatrix_ = glm::rotate(rotationMatrix_, glm::radians(angle), axis);
        recalculateViewMatrix();
    }
    
	const glm::vec3 & getPivot() const {return viewPivotPos_;}
    void setPivotPos(glm::vec3 && target) { viewPivotPos_ = target; recalculateViewMatrix();
    }
    void rotatePivot(float angle, glm::vec3 &&axis) {
        viewPivotRot_ = glm::rotate(viewPivotRot_, angle, axis); recalculateViewMatrix();
    }

    void recalculateViewMatrix();
};

}  // namespace vobo

#endif  //_perspective_camera_h_ header