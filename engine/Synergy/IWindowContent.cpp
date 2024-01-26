#include "IWindowContent.h"
#include "ITheme.h"
#include "SynUI.h"

IWindowContent::IWindowContent() {

	SetScissor(true);
	_Image = SynUI::Theme->_WindowFrame;
	_Outline = true;
	_OutlineImage = _Image;

}

void IWindowContent::Render() {

	auto pos = GetRenderPosition();



	if (true) {

		SynUI::Draw(_Image, pos, GetSize(), GetColor());
	}
	else {
		SynUI::Draw(_Image, pos, GetSize() - glm::vec2(0, 32), GetColor()*4.0f);

		SynUI::Draw(_Image, pos+glm::vec2(1,1), GetSize() - glm::vec2(0, 32)+glm::vec2(-3,-1), GetColor());


		SynUI::Draw(SynUI::Theme->_WinLeft, pos + glm::vec2(0, _Size.y - 32), glm::vec2(32, 32), GetColor());
		SynUI::Draw(SynUI::Theme->_WinRight, pos + glm::vec2(_Size.x - 32, _Size.y - 32), glm::vec2(32, 32), GetColor());
		SynUI::Draw(SynUI::Theme->_WinMid, pos + glm::vec2(32, _Size.y - 32), glm::vec2(_Size.x - 64, 32), GetColor());
	}
}