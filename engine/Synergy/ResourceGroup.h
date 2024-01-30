#pragma once
#include <vector>
#include <map>
#include <string>

class Resource;



class ResourceGroup
{
public:

	ResourceGroup(std::string name);

	std::string GetName() {
		return _Name;
	}
	void AddResource(Resource* resource);
	std::vector<Resource*> GetResources();


private:


	std::string _Name;
	std::vector<Resource*> _Resources;
	//std::map<std::string, Resource*> _Resources;


};

