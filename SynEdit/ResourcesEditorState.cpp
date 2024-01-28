#include "ResourcesEditorState.h"
#include "SynUI.h"
#include "IButton.h"
#include "SynApp.h"
#include "Texture2D.h"
#include "IWindowDock.h"
#include "IToolbar.h"
#include "IWindow.h"
#include "ILabel.h"
#include "ITextBox.h"
#include "IImage.h"
#include "IWindowContent.h"
#include "GameProject.h"
#include "IFileRequestor.h"
#include "IVideo.h"
#include <iostream>
#include <filesystem>
#include "GeneralOSState.h"
#include "ITreeView.h"
#include "IMenuBar.h"
#include "NewGroupWindow.h"

namespace fs = std::filesystem;
void ResourcesEditorState::InitState() {
	auto back = new IButton;
	back->Set(glm::vec2(10, SynApp::This->GetHeight() - 115), glm::vec2(30, 30), "");
	back->SetIcon(new Texture2D("edit/icon/exitdoor.png", true));
	_UI->GetToolbar()->Add(back);
	_UI->GetDock()->SetImage(new Texture2D("edit/bg/synergytools.png", true));
	back->OnClick = [](IControl* c, void* d)
		{
			SynApp::This->PushState(new GeneralOSState);
		};

	auto list_res = new IWindow(true);
	auto prev_res = new IWindow(true);
	auto edit_res = new IWindow(true);

	list_res->SetText("Resources");
	edit_res->SetText("Edit Resource");
	prev_res->SetText("Preview Resource");
	

	_UI->AddControl(edit_res);
	_UI->GetDock()->DockWindow(edit_res, AreaName::AreaBottom);   //GetDock(AreaName::AreaCentral);
	_UI->AddControl(list_res);
	_UI->GetDock()->DockWindow(list_res, AreaName::AreaLeft);   //GetDock(AreaName::AreaCentral);
	_UI->AddControl(prev_res);
	_UI->GetDock()->DockWindow(prev_res, AreaName::AreaCentral);   //GetDock(AreaName::AreaCentral);

	auto list_tree = new ITreeView;

	list_res->GetContent()->AddControl(list_tree);

	list_tree->Expand();

	auto root = list_tree->GetRootItem();
	root->Text = "Resource Groups";

	//list_tree->AddItem("3D Entities");
	//list_tree->AddItem("Textures");
	//list_tree->AddItem("Audio");
	//list_tree->AddItem("Videos");
	//list_tree->AddItem("Texts");


	_UI->GetMenuBar()->SetText("Synergy Tools - Resources Editor");

	auto mb = _UI->GetMenuBar();

	auto res_m = mb->AddItem("Resources");
	
	res_m->AddItem("New Resources");
	res_m->AddItem("Load Resource");
	res_m->AddItem("Save Resources");
	
	auto group_m = mb->AddItem("Groups");

	auto new_group = group_m->AddItem("New Group");
	group_m->AddItem("Delete Group");
	

//	auto new_group = res_m->AddItem("New Group...");
	new_group->OnClick = [&]() {

		auto new_group_win = new NewGroupWindow;
		_UI->AddControl(new_group_win);
	};






}

void ResourcesEditorState::UpdateState(float dt) {
	_UI->UpdateUI(dt);

}

void ResourcesEditorState::RenderState() {
	_UI->RenderUI();
}