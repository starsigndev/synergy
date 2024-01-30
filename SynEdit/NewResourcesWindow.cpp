#include "NewResourcesWindow.h"
#include "ITextBox.h"
#include "IButton.h"
#include "ILabel.h"
#include "IToggle.h"
#include "IWindowContent.h"
#include "SynUI.h"
#include "GameResources.h"
#include "SynResources.h"

NewResourcesWindow::NewResourcesWindow() {

	_Text = "New Resources File";
	Set(glm::vec2(200, 200), glm::vec2(400, 350), "New Resources File");

	auto name_lab = new ILabel("Resources Name");
	auto name_box = new ITextBox;

	name_lab->SetPosition(glm::vec2(10, 40));

	name_box->Set(glm::vec2(130, 35), glm::vec2(240, 30),"");

	_NameBox = name_box;

	_Content->AddControl(name_lab);
	_Content->AddControl(name_box);

	auto comp = new IToggle;

	comp->SetLabel("Compressed");

	comp->Set(glm::vec2(10, 80), glm::vec2(16, 16), "");

	_Content->AddControl(comp);

	auto create = new IButton;

	create->Set(glm::vec2(10, 290), glm::vec2(120, 30), "Create");

	create->OnClick = [&](IControl* c, void* d) {
		SynUI::This->SetTop(nullptr);

		auto new_Res = new SynResources("project/resources/" + _NameBox->GetText());
		GameResources::Resources->SetResources(new_Res);
		SynResources::SaveDefault(new_Res);



		//delete this;


		};

	auto cancel = new IButton;

	cancel->Set(glm::vec2(150, 290), glm::vec2(120, 30), "Cancel");

	cancel->OnClick = [&](IControl* c, void* d) {

		SynUI::This->SetTop(nullptr);

		//delete this;

		};


	_Content->AddControl(create);
	_Content->AddControl(cancel);

	RemoveSizers();

}