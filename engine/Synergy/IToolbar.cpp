#include "IToolbar.h"
#include "SynUI.h"
#include "ITheme.h"
#include "IButton.h"

IButton* IToolbar::AddButton(std::string text)
{

	IButton* new_but = new IButton;
	new_but->Set(glm::vec2(_CurrentX, 5), glm::vec2(5 + SynUI::StrW(text) + 5, 35), text);
	AddControl(new_but);

	_CurrentX += SynUI::StrW(text) + 25;

	return new_but;
}

IButton* IToolbar::AddButton(Texture2D* icon) {

	IButton* new_but = new IButton;
	new_but->Set(glm::vec2(_CurrentX, 7), glm::vec2(35, 32),"");
	new_but->SetIcon(icon);
	new_but->SetOutline(false);
	AddControl(new_but);


	_CurrentX += 35 + 10;

	return new_but;

}

void IToolbar::Add(IControl* control) {

	AddControl(control);
	control->Set(glm::vec2(_CurrentX, 8), control->GetSize(),control->GetText());
	_CurrentX += control->GetSize().x + 25;
}

void IToolbar::AddSpace(float x) {

	_CurrentX += x;

}

void IToolbar::Render() {

	auto pos = GetRenderPosition();

	SynUI::Draw(SynUI::Theme->_DarkFrame, pos, GetSize(), glm::vec4(1, 1, 1, 1));

}