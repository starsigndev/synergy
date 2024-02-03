#include "IVec3.h"
#include "INumeric.h"
#include "ILabel.h"

IVec3::IVec3(std::string lab) {

	_Outline = false;

	_X = new INumeric;
	_Y = new INumeric;
	_Z = new INumeric;
	
	_X->SetPosition(glm::vec2(25, 5));
	_Y->SetPosition(glm::vec2(175, 5));
	_Z->SetPosition(glm::vec2(325, 5));

	auto xl = new ILabel("X");
	auto yl = new ILabel("Y");
	auto zl = new ILabel("Z");

	xl->SetPosition(glm::vec2(5, 10));
	yl->SetPosition(glm::vec2(155, 10));
	zl->SetPosition(glm::vec2(305, 10));

	AddControl(_X);
	AddControl(_Y);
	AddControl(_Z);
	AddControl(xl);
	AddControl(yl);
	AddControl(zl);

	auto label = new ILabel(lab);
	label->SetPosition(glm::vec2(-50, 10));
	AddControl(label);

}

void IVec3::SetValue(glm::vec3 value) {

	_X->SetNumber(value.x);
	_Y->SetNumber(value.y);
	_Z->SetNumber(value.z);

}

glm::vec3 IVec3::GetValue() {

	return glm::vec3(_X->GetNumber(), _Y->GetNumber(), _Z->GetNumber());

}

void IVec3::SetIncrement(float inc) {

	_X->SetIncrement(inc);
	_Y->SetIncrement(inc);
	_Z->SetIncrement(inc);

}