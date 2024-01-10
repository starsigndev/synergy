#pragma once
#include "glm/glm.hpp"

class Material2D;

class SmartDraw
{
public:

	SmartDraw();
	void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color);

private:

	Material2D* _drawmat;

};

