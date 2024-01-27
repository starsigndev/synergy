#pragma once
#include <string>


class SynData
{
public:
	enum DataType {
		I16, I32,I64, F32,F64,String,Node,Object,Data,FilePath, Resource,
		Vec2,Vec3,Vec4,Matrix4,Matrix3
	};

	SynData(DataType type,std::string name);
	void SetValue(float value);
	void SetValue(int value);
	void SetValue(std::string value);
	void SetData(char* val, int num);

private:

	std::string _Name;
	DataType _Type;
	char* _Value;
	std::string _StrValue;

};

