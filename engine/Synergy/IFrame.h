#pragma once
#include "IControl.h"
class IFrame : public IControl
{
public:

	IFrame();
	void SetName(std::string name) {
		_GroupName = name;
	}
	void Render();
private:

	std::string _GroupName = "";

};

