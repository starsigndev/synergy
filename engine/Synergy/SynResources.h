#pragma once
#include <vector>
#include <string>
#include <map>

class ResourceGroup;


class SynResources
{
public:

	void AddGroup(ResourceGroup* group);

private:

	std::vector<ResourceGroup*> Groups;

};

