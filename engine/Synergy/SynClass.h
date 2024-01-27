#pragma once
#include <string>
#include <vector>

class SynData;

class SynClass
{
public:

	SynClass(std::string name);
	void AddInt(std::string name, int def = 0);
	void AddFloat(std::string name, float def = 0);
	void AddString(std::string name, std::string def = "");
	std::vector<SynData*>& GetFields();

private:

	std::string _Name;
	std::vector<SynData*> _Fields;

};

