#pragma once
#include <string>

class SynResources;

class GameResources
{
public:

	GameResources(std::string path);

	static GameResources* Resources;

private:

	std::string _Path;
	SynResources* _Resources;

};

