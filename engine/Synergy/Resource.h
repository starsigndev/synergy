#pragma once
#include <string>

class SynResources;

class Resource
{
public:

	Resource(std::string name,SynResources* resources);
	void SetData(std::string path);
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
	
	char* GetData() {
		return _Data;
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

	//texture

	//entity

	//video

	//audio

	//text
};

