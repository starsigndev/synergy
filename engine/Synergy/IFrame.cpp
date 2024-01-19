#include "IFrame.h"
#include "SynUI.h"
#include "ITheme.h"

IFrame::IFrame() {

	_Image = SynUI::Theme->_Frame;


}

void IFrame::Render() {

	auto pos = GetRenderPosition();
	SynUI::Draw(_Image, pos, GetSize(), GetColor());

}