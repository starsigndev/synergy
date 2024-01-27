#include "SynData.h"

SynData::SynData(DataType type,std::string name) {

	_Type = type;
	_Name = name;
	
	switch (type) {
	case I32:
	
		_Value = (char*)malloc(4);
		break;
	case F32:

		_Value = (char*)malloc(4);
		break;
	case String:
		break;
	}

}

void SynData::SetValue(int value) {

//	char* cast = (char*) & value;
	SetData((char*)&value, 4);

}

void SynData::SetValue(float value) {

	SetData((char*)&value, 4);

}

void SynData::SetValue(std::string value) {

	_StrValue = value;

}

void SynData::SetData(char* data, int len)
{

	for (int i = 0; i < len; i++) {
		_Value[i] = data[i];
	}

}