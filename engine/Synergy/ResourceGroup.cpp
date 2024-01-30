#include "ResourceGroup.h"

ResourceGroup::ResourceGroup(std::string name) {

	_Name = name;

}

void ResourceGroup::AddResource(Resource* resource) {

	_Resources.push_back(resource);

}

std::vector<Resource*> ResourceGroup::GetResources() {

	return _Resources;

}