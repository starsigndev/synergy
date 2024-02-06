#include "CE_MainMenuBar.h"
#include "SynApp.h"
#include "GeneralOSState.h"
#include "ConvEditor_Global.h"

CE_MainMenubar::CE_MainMenubar() {

	SetPosition(glm::vec2(1, 1));
	SetSize(glm::vec2(SynApp::This->GetWidth() - 2, 24));

	auto scene = AddItem("Conversation");
	auto edit = AddItem("Edit");
	auto import = AddItem("Import");

	auto new_conv = scene->AddItem("New Conversation");
	scene->AddSeperator();
	auto load_conv = scene->AddItem("Load Conversation");
	auto save_conv = scene->AddItem("Save Conversation");
	scene->AddSeperator();
	auto close_ed = scene->AddItem("Return to Main");

	close_ed->OnClick = [&]() {

		SynApp::This->PushState(new GeneralOSState);

		};

	new_conv->OnClick = [&]() {

		ConvEditor_Global::NewConv();

		};
}