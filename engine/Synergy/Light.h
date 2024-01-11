#pragma once
#include "Node3D.h"
#include "glm/glm.hpp"

class Light : public Node3D
{
public:

	Light();

	glm::vec3 GetDiffuseColor();
	glm::vec3 GetSpecularColor();

private:

	glm::vec3 _DiffuseColor;
	glm::vec3 _SpecularColor;
	float _Range;

};

