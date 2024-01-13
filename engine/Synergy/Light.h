#pragma once
#include "Node3D.h"
#include "glm/glm.hpp"

class RenderTargetCube;

class Light : public Node3D
{
public:

	Light();

	glm::vec3 GetDiffuseColor();
	glm::vec3 GetSpecularColor();
	void SetDiffuseColor(glm::vec3 color);
	void SetSpecularColor(glm::vec3 color);
	float GetRange();
	RenderTargetCube* GetShadowRT() {
		return _ShadowRT;
	}
	

private:

	glm::vec3 _DiffuseColor;
	glm::vec3 _SpecularColor;
	float _Range;
	RenderTargetCube* _ShadowRT;

};

