#pragma once

#include "glm/glm.hpp"

struct Vertex
{

	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 texcoord;
	glm::vec3 normal;
	glm::vec3 binormal;
	glm::vec3 tangent;
	glm::vec4 boneids;
	glm::vec4 weights;


};

