#include "Camera.h"

glm::mat4 Camera::GetProjectionMatrix() {
	return glm::perspective(fov, Window::GetAspect(), near, far);
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

ViewFrustum* Camera::GetViewFrustum() const {
	return viewFrustum;
}

void Camera::Update() {
	viewFrustum->Update(GetProjectionMatrix() * GetViewMatrix());
}

