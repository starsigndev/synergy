#pragma once
#include "Node3D.h"

class Camera : public Node3D
{
public:

	glm::mat4 GetWorldMatrix();
	glm::mat4 GetProjectionMatrix();
	float GetNearZ();
	float GetFarZ();
	void SetNearZ(float z) { _NearZ = z; };
	void SetFarZ(float z) { _FarZ = z; };
	void SetFOV(float fov) { _FOV = fov; };

private:

	float _FOV = 45.0f;
	float _NearZ = 0.01f;
	float _FarZ = 100.0f;

};

