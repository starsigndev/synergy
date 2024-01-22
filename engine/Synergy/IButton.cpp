#include "IButton.h"
#include "SynUI.h"
#include "ITheme.h"

IButton::IButton() {

	_Image = SynUI::Theme->_Button;
	SetColor(glm::vec4(0.7f, 0.7f, 0.7f, 0.8f));

}

void IButton::Render() {

	auto pos = GetRenderPosition();

	//SynUI::Draw(SynUI::Theme->_Frame, pos+glm::vec2(-1,-1), GetSize()+glm::vec2(2,2),glm::vec4(4,4,4,1));
	SynUI::Draw(_Image, pos, GetSize(), GetColor());

	if (_Text != "") {
		SynUI::DrawStr(_Text, pos + glm::vec2(_Size.x / 2, _Size.y / 2) - glm::vec2(SynUI::StrW(_Text) / 2, SynUI::StrH(_Text) / 2), SynUI::Theme->_FontFore);
	}
	if (_Icon != nullptr) {
		SynUI::Draw(_Icon, pos + glm::vec2(2, 2), GetSize() + glm::vec2(-4, -4), glm::vec4(1, 1, 1, 1));
	}


}

void IButton::OnMouseDown(int button) {

	SetColor(glm::vec4(1.5f, 1.5f, 1.5f, 0.8f));
	if (OnClick) {
		OnClick();
	}

}

void IButton::OnMouseUp(int button) {

	SetColor(glm::vec4(1.25f, 1.25f, 1.25f, 0.8f));

}

void IButton::OnMouseEnter() {

	SetColor(glm::vec4(1.15f, 1.15f, 1.15f, 0.8f));

}

void IButton::OnMouseLeave() {

	SetColor(glm::vec4(0.7f, 0.7f, 0.7f, 0.8f));

}

void IButton::OnMouseDrag(glm::vec2 pos,glm::vec2 delta) {

	if (OnDrag) {
		OnDrag(delta);
	}
}