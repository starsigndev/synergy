#pragma once
#include "Node3D.h"

class Camera : public Node3D
{
public:

	glm::mat4 GetWorldMatrix();

};

