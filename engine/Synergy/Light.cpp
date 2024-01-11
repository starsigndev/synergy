#include "Light.h"

Light::Light() {

	_DiffuseColor = glm::vec3(1, 1, 1);
	_SpecularColor = glm::vec3(1, 1, 1);
	_Range = 100;

}

glm::vec3 Light::GetDiffuseColor() {

	return _DiffuseColor;

}

glm::vec3 Light::GetSpecularColor() {

	return _SpecularColor;

}