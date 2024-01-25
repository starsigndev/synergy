#include "ILabel.h"
#include "SynUI.h"

ILabel::ILabel(std::string text) {

	_Text = text;

}

void ILabel::Render() {

	SynUI::DrawStr(_Text, GetRenderPosition(), GetColor());

}