#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "SynApp.h"
glm::mat4 Camera::GetWorldMatrix() {

	return glm::inverse(Node3D::GetWorldMatrix());

}

glm::mat4 Camera::GetProjectionMatrix() {

	return glm::perspective(glm::radians(_FOV), (float)SynApp::This->GetWidth() / (float)SynApp::This->GetHeight(),_NearZ,_FarZ);

}

float Camera::GetNearZ() {

	return _NearZ;

}

float Camera::GetFarZ() {

	return _FarZ;

}