#pragma once
#include <vector>
#include <string>
#include <map>

class ResourceGroup;
class Resource;

class SynResources
{
public:
	SynResources(std::string path);
	void LoadIndex();
	void SaveIndex();
	void SaveContent();
	std::string GetPath() {
		return _Path;
	}
	void AddGroup(ResourceGroup* group);
	std::vector<ResourceGroup*> GetGroups() {
		return _Groups;
	}
	static void SaveDefault(SynResources* resources);
	static void LoadDefault();
	Resource* FindResource(std::string name);
private:

	std::string _Path;
	std::string _IndexPath;
	std::string _ContentPath;
	std::vector<ResourceGroup*> _Groups;

};
