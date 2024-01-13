#pragma once
#include <vector>
#include <string>
#include "glm/glm.hpp"

class AssimpNodeData
{
public:

	glm::mat4 _Transform;
	std::string _Name;
	int _ChildrenCount = 0;
	std::vector<AssimpNodeData*> _Children;

//public:


};

