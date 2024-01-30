#pragma once
#include <string>

class SynResources;

class GameResources
{
public:

	GameResources(std::string path);
	void SetResources(SynResources* resources);
	SynResources* GetResources();
	static GameResources* Resources;



private:

	std::string _Path;
	SynResources* _Resources;

};

