#include "Resource.h"
#include "SynResources.h"
#include "VFile.h"

Resource::Resource(std::string name,SynResources* resources) {

	_ByteStart = 0;
	_ByteLength = 0;
	_Name = name;
	_Loaded = false;
	_Compressed = false;
	_Owner = resources;

}

void Resource::SetData(std::string path) {

	_Path = path;

}

std::string Resource::GetName() {
	
	return _Name;

}

std::string Resource::GetPath() {

	return _Path;

}

bool Resource::IsLoaded() {

	return _Loaded;

}

bool Resource::IsCompressed() {

	return _Compressed;

}

long Resource::GetStart() {

	return _ByteStart;

}

long Resource::GetSize() {

	return _ByteLength;

}

void Resource::SetStart(long start) {

	_ByteStart = start;

}

void Resource::SetSize(long size) {

	_ByteLength = size;

}

void Resource::SetCompressed(bool compressed) {

	_Compressed = compressed;

}

void Resource::Load() {


	if (_Loaded) {
		return;
	}

	auto path = _Owner->GetPath() + ".content";

	VFile* file = new VFile(path.c_str(), FileMode::Read);
	
	file->Seek(_ByteStart);

	_Data = (char*)file->ReadBytes(_ByteLength);
		

	file->Close();
	
	_Loaded = true;
	int b = 5;


}