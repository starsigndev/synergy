#include "IProgressBar.h"
#include "SynUI.h"
#include "ITheme.h"

IProgressBar::IProgressBar() {

	_Value = 0;
	_Outline = true;

}

void IProgressBar::SetValue(float value) {

	_Value = value;

}

float IProgressBar::GetValue() {

	return _Value;

}

void IProgressBar::Render() {

	_Value += 0.002f;
	if (_Value > 1.0) _Value = 0.0f;

	auto pos = GetRenderPosition();

	SynUI::Draw(SynUI::Theme->_DarkFrame, pos, GetSize(), glm::vec4(1, 1, 1, 1));

	float ay = _Value * GetSize().x - 2;

	float yv = _Value;


	SynUI::Draw(SynUI::Theme->_Frame, pos + glm::vec2(1, 1), glm::vec2(ay, GetSize().y - 2),glm::vec4(0,1,1,0),glm::vec4(0,yv,yv,0), glm::vec4(1, 1, 1, 1));


}