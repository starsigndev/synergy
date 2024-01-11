#pragma once
#include "glm/glm.hpp"

class Texture2D;

class Material
{
public:

	//Constructors
	Material();

	//Maps

	void SetDiffuseMap(Texture2D* map);
	void SetSpecularMap(Texture2D* map);
	void SetNormalMap(Texture2D* map);

	Texture2D* GetDiffuseMap();
	Texture2D* GetSpecularMap();
	Texture2D* GetNormalMap();

	//Values
	void SetDiffuseColor(glm::vec3 color);
	void SetSpecularColor(glm::vec3 color);

	glm::vec3 GetDiffuseColor();
	glm::vec3 GetSpecularColor();
	

private:

	//Maps
	Texture2D* _DiffuseMap;
	Texture2D* _SpecularMap;
	Texture2D* _NormalMap;
	Texture2D* _RoughnessMap;

	//Values
	glm::vec3 _DiffuseColor;
	glm::vec3 _SpecularColor;
	glm::vec3 _Roughness;
	float _NormalIntensity;

};

