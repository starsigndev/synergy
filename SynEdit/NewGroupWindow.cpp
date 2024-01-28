#include "NewGroupWindow.h"
#include "ILabel.h"
#include "IButton.h"
#include "ITextBox.h"
#include "IWindowContent.h"
#include "ISelector.h"

NewGroupWindow::NewGroupWindow() {

	SetPosition(glm::vec2(200, 200));
	SetSize(glm::vec2(475, 295));
	_Text = "New Resource Group";
	auto create = new IButton;

	create->Set(glm::vec2(260, _Size.y - 55), glm::vec2(80, 30), "Create");

	_Content->AddControl(create);

	auto cancel = new IButton;

	cancel->Set(glm::vec2(355, _Size.y - 55), glm::vec2(80, 30), "Cancel");

	_Content->AddControl(cancel);

	auto name_lab = new ILabel("Group Name");
	name_lab->SetPosition(glm::vec2(10, 95));

	auto name_box = new ITextBox;
	name_box->Set(glm::vec2(140, 90), glm::vec2(240, 30), "");

	_Content->AddControl(name_lab);
	_Content->AddControl(name_box);


	auto res_lab = new ILabel("Resource Type");
	res_lab->SetPosition(glm::vec2(10, 45));

	auto res_type = new ISelector;
	res_type->Set(glm::vec2(140, 40), glm::vec2(240, 30), "");

	res_type->AddItems({ "3D","Texture","Audio","Video","Text" });

	_Content->AddControl(res_type);
	_Content->AddControl(res_lab);

	
	




}