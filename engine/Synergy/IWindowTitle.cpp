#include "IWindowTitle.h"
#include "IWindow.h"
#include "SynUI.h"
#include "ITheme.h"
#include "SmartDraw.h"

IWindowTitle::IWindowTitle() {

	_Outline = false;
	
}

void IWindowTitle::SetWindow(IWindow* window) {

	_Window = window;

}

IWindow* IWindowTitle::GetWindow() {
 
	return _Window;

}

void IWindowTitle::Render() {

	int tw = 164;

	SynUI::Draw(SynUI::Theme->_Frame, GetRenderPosition()+glm::vec2(0,12), GetSize() + glm::vec2(1, -10), glm::vec4(0.5, 0.5, 0.5, 1));
	RenderTab(_Window->GetText(), -1,tw);

}

void IWindowTitle::RenderTab(std::string text, int dx,int w)
{
	auto pos = GetRenderPosition();

	SynUI::Draw(SynUI::Theme->_TitleBar, glm::vec2(pos.x + dx, pos.y+1), glm::vec2(w, GetSize().y), glm::vec4(1, 1, 1, 1));
	SynUI::DrawStr(text, glm::vec2(pos.x + dx + w/2-SynUI::StrW(text)/2, pos.y + 2), glm::vec4(1, 1, 1, 1));

}