#include "NewConversationWindow.h"
#include "ITextBox.h"
#include "ILabel.h"
#include "IWindowContent.h"
#include "IButton.h"

NewConversationWindow::NewConversationWindow() {

	SetText("New Conversation");
	SetPosition(glm::vec2(200, 200));
	SetSize(glm::vec2(420, 250));

	_TitleBox = new ITextBox;
	_TitleBox->SetSize(glm::vec2(280, 30));
	_TitleBox->SetPosition(glm::vec2(60, 20));

	auto lab = new ILabel("Title");
	lab->SetPosition(glm::vec2(10, 25));
	
	_Content->AddControl(_TitleBox);
	_Content->AddControl(lab);

	auto ok_but = new IButton;
	ok_but->SetPosition(glm::vec2(10, 190));
	ok_but->SetSize(glm::vec2(120, 30));
	_Content->AddControl(ok_but);
	ok_but->SetText("Create");

	RemoveSizers();

}