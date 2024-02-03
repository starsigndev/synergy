#pragma once
#include <string>
#include "glm/glm.hpp"

enum ResourceType {
	RT_Entity,RT_Actor,RT_Texture,RT_Material
};

class SynResources;

class Resource
{
public:

	Resource(std::string name,SynResources* resources);
	void SetData(std::string path);
	void SetType(ResourceType type)
	{
		_Type = type;
	}
	std::string GetName();
	std::string GetPath();
	void Load();
	void Unload();
	bool IsLoaded();
	bool IsCompressed();
	long GetStart();
	long GetSize();
	void SetStart(long start);
	void SetSize(long size);
	void SetCompressed(bool compressed);
	void SetEntity(std::string name, glm::vec3 scale);
	char* GetData() {
		return _Data;
	}
	ResourceType GetType() {
		return _Type;
	}
	glm::vec3 GetScale() {
		return _EntityScale;
	}
	std::string GetEntityName() {
		return _EntityName;
	}
	

private:
	bool _Loaded = false;
	bool _Compressed = false;
	long _ByteStart;
	long _ByteLength;
	std::string _Name = "";
	std::string _Path = "";
	char* _Data = nullptr;
	SynResources* _Owner = nullptr;
	ResourceType _Type = ResourceType::RT_Entity;

	//texture

	//entity
	glm::vec3 _EntityScale;
	std::string _EntityName;

	//video

	//audio

	//text
};

