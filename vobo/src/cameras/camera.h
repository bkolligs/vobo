#ifndef _vobo_camera_h_
#define _vobo_camera_h_


#include "vobo_pch.h"
/**
 * Abstract Camera class for interfacing with various types of cameras
 * The camera is built around the fact we need to produce a view and projection
 * matrix to multiply our vertices by. This abstract camera class allows for
 * implementation of the view calculation and projection matrix
 */
class Camera {
    protected:
	   /* Construct the class with a projection matrix */
        Camera(glm::mat4 projectionMatrix) : projectionMatrix_{projectionMatrix} {}
        /* Camera projection and view matrices */
        glm::mat4 viewMatrix_           = glm::mat4(1.0f);
        glm::mat4 projectionMatrix_     = glm::mat4(1.0f);
        glm::mat4 viewProjectionMatrix_ = glm::mat4(1.0f);

        /* Pivot pose in world */
        glm::vec3 pivotPosInWorld_ = {0.0f, 0.0f, 0.0f};
        glm::mat4 pivotOriInWorld_ = glm::mat4(1.0f);

        /* Camera pose in pivot frame */
        glm::vec3 camPosInPivot_ = {0.0f, 0.0f, 0.0f};
        glm::mat4 camOriInPivot_  = glm::mat4(1.0f);

        /* Camera pose in world frame */
        glm::vec3 camPosInWorld_ = {0.0f, 0.0f, 0.0f};
        glm::mat4 camOriInWorld_ = glm::mat4(1.0f);

    public:
        ~Camera(){}
        virtual void recalculateViewMatrix() = 0;
        /* Get camera view and projection information */
        const glm::mat4& getViewProjection() const {
            return viewProjectionMatrix_;
        }
        const glm::mat4& getProjectionMatrix() const {
            return projectionMatrix_;
        }
        const glm::mat4& getViewMatrix() const { return viewMatrix_; }

        /* Get camera pivot position in the world frame  */
        const glm::vec3& getPivotPos() const { return pivotPosInWorld_; }
        /* Get camera pivot rotation in the world frame  */
        const glm::mat4& getPivotOri() const { return pivotOriInWorld_; }
        /* Set the pivot position in the world frame */
        void setPivotPos(glm::vec3&& target) {
            pivotPosInWorld_ = target;
            recalculateViewMatrix();
        }
        /* Rotate the pivot in the world frame */
        void rotatePivot(float angle, glm::vec3&& axis) {
            pivotOriInWorld_ = glm::rotate(pivotOriInWorld_, angle, axis);
            recalculateViewMatrix();
        }

        /* Get the camera location in the world frame */
        const glm::vec3& getCamPosInWorld() const { return camPosInWorld_; }
		/* Get the camera rotation in the world frame */
		const glm::mat4& getCamOriInWorld() const {return camOriInWorld_;}
		/* Get the camera location in the pivot frame */
		const glm::vec3& getCamPosInPivot() const {return camPosInPivot_;}
		/* Get the camera rotation in the pivot frame */
		const glm::mat4& getCamOriInPivot() const {return camOriInPivot_;}
		/* Set the camera position in the pivot frame */
		void setCamPosInPivot(glm::vec3&& position) {camPosInPivot_ = position; recalculateViewMatrix();}
		/* Rotate the camera in the pivot frame */
		void rotateCamInPivot(float angle, glm::vec3 && axis){
			glm::rotate(camOriInPivot_, angle, axis);
			recalculateViewMatrix();
		}
};

#endif //_vobo_camera_h_ header