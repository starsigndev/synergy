#include "SE_MainMenubar.h"
#include "SynApp.h"
#include "GeneralOSState.h"
#include "ImportMedia.h"
#include "SynUI.h"

SE_MainMenubar::SE_MainMenubar() {

	SetPosition(glm::vec2(1, 1));
	SetSize(glm::vec2(SynApp::This->GetWidth() - 2, 24));

	auto scene = AddItem("Scene");
	auto edit = AddItem("Edit");
	auto import = AddItem("Import");

	auto imp_entity = import->AddItem("Import Entity");
	import->AddItem("Import Actor");

	imp_entity->OnClick = [&] {

		auto imp = new ImportMedia;
		SynUI::This->AddControl(imp);

		};


	scene->AddItem("New Scene");
	scene->AddSeperator();
	scene->AddItem("Load Scene");
	scene->AddItem("Save Scene");
	scene->AddSeperator();
	auto exit_edit = scene->AddItem("Exit Scene Editor");

	exit_edit->OnClick = [&]() {

		SynApp::This->PushState(new GeneralOSState);

		};


}