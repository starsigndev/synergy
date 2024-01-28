#pragma once
#include <string>

class Resource
{
public:

	Resource(std::string name);
	void Load();
	void Unload();

private:
	bool _Loaded = false;
	bool _Compressed = false;
	long _ByteStart;
	long _ByteLength;
	std::string _Name;
	char* _Data = nullptr;
};

