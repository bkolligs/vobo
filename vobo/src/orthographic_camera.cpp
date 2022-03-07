#include "orthographic_camera.h"

namespace vobo
{

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	: projectionMatrix_ {glm::ortho(left, right, bottom, top, -1.0f, 1.0f)}{}

OrthographicCamera::~OrthographicCamera() {}

void OrthographicCamera::recalculateViewMatrix() {
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position_) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), {1.0f, 0.0f, 0.0f});
	/* View is the inverse of the transform in world space */
	viewMatrix_ = glm::inverse(transform);
	/* Update the view projection matrix */
	viewProjectionMatrix_ = projectionMatrix_ * viewMatrix_;
}

} // namespace vobo