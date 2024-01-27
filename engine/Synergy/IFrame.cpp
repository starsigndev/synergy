#include "IFrame.h"
#include "SynUI.h"
#include "ITheme.h"

IFrame::IFrame() {

	_Image = SynUI::Theme->_Frame;

	_Outline = false;
}

void IFrame::Render() {

	auto pos = GetRenderPosition();
	SynUI::Draw(_Image, pos, GetSize(), GetColor());
	SynUI::DrawStr(_GroupName, pos + glm::vec2(10, -25), glm::vec4(1, 1, 1, 1));


}