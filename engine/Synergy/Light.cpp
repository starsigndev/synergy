#include "Light.h"

#include "RenderTargetCube.h"

Light::Light() {

	_DiffuseColor = glm::vec3(1, 1, 1);
	_SpecularColor = glm::vec3(0,0,0);
	_Range = 30;
	_ShadowRT = new RenderTargetCube(1024, 1024);

}

glm::vec3 Light::GetDiffuseColor() {

	return _DiffuseColor;

}

glm::vec3 Light::GetSpecularColor() {

	return _SpecularColor;

}

float Light::GetRange() {

	return _Range;

}