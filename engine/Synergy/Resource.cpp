#include "Resource.h"

Resource::Resource(std::string name) {

	_ByteStart = 0;
	_ByteLength = 0;
	_Name = name;
	_Loaded = false;
	_Compressed = false;

}