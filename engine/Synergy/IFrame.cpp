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

}