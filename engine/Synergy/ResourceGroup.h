#pragma once
#include <vector>
#include <map>
#include <string>

class Resource;

enum ResourceType {

	Resource_Texture, Resource_Video, Resource_Entity, Resource_Audio, Resource_Text

};

class ResourceGroup
{
public:

	ResourceGroup(ResourceType type);

private:

	ResourceType _ResType;
	std::string _Name;
	std::map<std::string, Resource*> _Resources;

};

