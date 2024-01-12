#include "Camera.h"

glm::mat4 Camera::GetWorldMatrix() {

	return glm::inverse(Node3D::GetWorldMatrix());

}