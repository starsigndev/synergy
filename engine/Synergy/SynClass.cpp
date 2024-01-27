#include "SynClass.h"
#include "SynData.h"

SynClass::SynClass(std::string name) {

	_Name = name;

}

void SynClass::AddInt(std::string name, int def) {

	auto data = new SynData(SynData::DataType::I32, name);
	data->SetValue(def);
	_Fields.push_back(data);

}

void SynClass::AddFloat(std::string name, float def) {

	auto data = new SynData(SynData::DataType::F32, name);
	data->SetValue(def);
	_Fields.push_back(data);

}

void SynClass::AddString(std::string name, std::string def) {

	auto data = new SynData(SynData::DataType::String,name);
	data->SetValue(def);
	_Fields.push_back(data);

}

std::vector<SynData*>& SynClass::GetFields() {

	return _Fields;

}