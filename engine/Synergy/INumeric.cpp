#include "INumeric.h"
#include "ITextBox.h"
#include "IButton.h"

INumeric::INumeric() {

	_Number = new ITextBox;
	_Number->SetNumeric(true);
	_Up = new IButton;
	_Down = new IButton;
	SetSize(glm::vec2(120, 30));
	AddControl(_Number);
	AddControl(_Up);
	AddControl(_Down);
	_ScissorTest = false;
	_Number->SetNumber(0.0f);

	_Up->OnClick = [&](IControl* c,void* data) {

		_Number->SetNumber(_Number->GetNumber() + _Increment);


		};
	_Down->OnClick = [&](IControl* c, void* data) {

		_Number->SetNumber(_Number->GetNumber() - _Increment);

		};

	_Outline = false;
}

void INumeric::SizeChanged() {

	_Number->SetPosition(glm::vec2(0, 0));
	_Number->SetSize(glm::vec2(80, 30));
	_Up->SetPosition(glm::vec2(85, 0));
	_Up->SetSize(glm::vec2(30, 15));
	_Down->SetPosition(glm::vec2(85, 15));
	_Down->SetSize(glm::vec2(30, 15));
	_Up->SetText("/\\");
	_Down->SetText("\\/");

}

void INumeric::SetNumber(float value) {

	_Number->SetNumber(value);

}

float INumeric::GetNumber() {

	return _Number->GetNumber();

}