#include "Material.h"
#include "Texture2D.h"

Texture2D* _WhiteTex = nullptr;
Texture2D* _BlankNormal;

Material::Material() {

	if (_WhiteTex == nullptr) {
		_WhiteTex = Texture2D::WhiteTexture();
		_BlankNormal = Texture2D::BlankNormalTexture();
	}
	_DiffuseMap = _WhiteTex;
	_SpecularMap = _WhiteTex;
	_NormalMap = _BlankNormal;
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

