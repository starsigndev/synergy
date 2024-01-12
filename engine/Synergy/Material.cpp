#include "Material.h"
#include "Texture2D.h"

Material::Material() {

	_DiffuseMap = Texture2D::WhiteTexture();
	_SpecularMap = Texture2D::WhiteTexture();
	_NormalMap = Texture2D::BlankNormalTexture();
	_RoughnessMap = nullptr;

	_DiffuseColor = glm::vec3(1, 1, 1);
	_SpecularColor = glm::vec3(0.3f, 0.3f, 0.3f);
	_Roughness = glm::vec3(0, 0, 0);
	_NormalIntensity = 1.0f;

}

void Material::SetDiffuseMap(Texture2D* map) {

	_DiffuseMap = map;

}

void Material::SetSpecularMap(Texture2D* map) {

	_SpecularMap = map;

}

void Material::SetNormalMap(Texture2D* map) {

	_NormalMap = map;

}

Texture2D* Material::GetDiffuseMap() {

	return _DiffuseMap;

}

Texture2D* Material::GetSpecularMap() {

	return _SpecularMap;

}

Texture2D* Material::GetNormalMap() {

	return _NormalMap;

}


//Values

void Material::SetDiffuseColor(glm::vec3 color) {

	_DiffuseColor = color;

}

void Material::SetSpecularColor(glm::vec3 color) {

	_SpecularColor = color;

}

glm::vec3 Material::GetDiffuseColor() {

	return _DiffuseColor;

}

glm::vec3 Material::GetSpecularColor() {

	return _SpecularColor;

}

