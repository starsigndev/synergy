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
#include "IVMenu.h"
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
#include "NewResourcesWindow.h"
#include "GameResources.h"
#include "SynResources.h"
#include "ResourceGroup.h"
#include "Resource.h"
#include "PathHelper.h"
#include "IPreview3D.h"
#include "Importer.h"
#include "Import3DWindow.h"

ResourcesEditorState* ResourcesEditorState::Editor = nullptr;



namespace fs = std::filesystem;
void ResourcesEditorState::InitState() {
	Editor = this;
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

	_PreviewWin = prev_res;

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

	_ResTree = list_tree;

	auto tree_menu = new IVMenu;

//	tree_menu->AddItem("Import 3D");
	auto imp_med = tree_menu->AddItem("Import Media");



	list_tree->SetContextControl(tree_menu);

	imp_med->OnClick = [&]() {

		auto req = new IFileRequestor(GameProject::_ProjectPath+"\\raw\\");
		SynUI::This->SetTop(req);
		req->SetPosition(glm::vec2(200, 200));
		req->SetText("Import Media");

		req->FileSelected = [&](std::string path) {

			auto active = _ResTree->GetActiveItem();

			if (active) {
				auto group = (ResourceGroup*)_ResTree->GetActiveItem()->Data;

				if (group) {

					if (PathHelper::getFileExtension(path) == "fbx") {

						SynUI::This->SetTop(nullptr);

						Import3DWindow* imp_win = new Import3DWindow(path,group);
						SynUI::This->AddControl(imp_win);

						return;

						//int b = 5;


					}

					

					RebuildUI();

				}
			}

			SynUI::This->SetTop(nullptr);

			};

		};

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
	
	auto new_res = res_m->AddItem("New Resources");
	auto load_res = res_m->AddItem("Load Resource");

	auto save_res = res_m->AddItem("Save Resources");
	
	save_res->OnClick = [&]() {

		GameResources::Resources->GetResources()->SaveContent();
		GameResources::Resources->GetResources()->SaveIndex();
		SynResources::SaveDefault(GameResources::Resources->GetResources());
		RebuildUI();
		

		};


	new_res->OnClick = [&]() {

		auto new_res = new NewResourcesWindow;
		_UI->SetTop(new_res);
		//_UI->AddControl(new_res);


		};

	load_res->OnClick = [&]() {

		auto req = new IFileRequestor(GameProject::_ProjectPath+"\\project\\resources\\");
		req->SetPosition(glm::vec2(200, 200));
		req->SetText("Select resources file");
		_UI->SetTop(req);


		req->FileSelected = [&](std::string path) {

			auto new_Res = new SynResources(PathHelper::removeFileExtension(path));
			GameResources::Resources->SetResources(new_Res);
			RebuildUI();
			SynResources::SaveDefault(new_Res);


			};


		};

	auto group_m = mb->AddItem("Groups");

	auto new_group = group_m->AddItem("New Group");
	group_m->AddItem("Delete Group");

	//Resource modifiers = res_<filename>

	_Root = root;

//	auto new_group = res_m->AddItem("New Group...");
	new_group->OnClick = [&]() {

		auto new_group_win = new NewGroupWindow;
		_UI->SetTop(new_group_win);
		//_UI->AddControl(new_group_win);


	};




	SynResources::LoadDefault();
	RebuildUI();


}

void ResourcesEditorState::UpdateState(float dt) {
	_UI->UpdateUI(dt);

}

void ResourcesEditorState::RenderState() {
	_UI->RenderUI();
}


void ResourcesEditorState::NewGroup(std::string name) {


	ResourceGroup* group = new ResourceGroup(name);

	
	GameResources::Resources->GetResources()->AddGroup(group);

	Editor->RebuildUI();
	//Editor->_Root->AddItem(name + "(" + type + ")");



}

void ResourcesEditorState::RebuildUI() {

	Editor->_Root->Items.clear();
	if(GameResources::Resources->GetResources()){
		for (auto const& group : GameResources::Resources->GetResources()->GetGroups()) {

			TreeItem* item = Editor->_Root->AddItem(group->GetName());

			item->Data = (void*)group;

			for (auto const& res : group->GetResources()) {

				TreeItem* res_item = item->AddItem(res->GetName());
				res_item->Path = res->GetPath();

				res_item->ItemSelected = [&](TreeItem* item) {

					_PreviewWin->GetContent()->ClearControls();
					std::string path = item->Path;

					auto ext = PathHelper::getFileExtension(path);

					if (ext == "fbx")
					{

						auto imp = new Importer;

						auto entity = (Entity*)imp->ImportNode(path);

						auto prev = new IPreview3D(entity);
						int b = 5;
						_PreviewWin->GetContent()->AddControl(prev);
						prev->Set(glm::vec2(10, 60), glm::vec2(600, 600), "");


					}
					if (ext == "png" || ext == "bmp" || ext == "jpg")
					{

						auto tex = new Texture2D(path, true);

						auto img = new IImage(tex);


						_PreviewWin->GetContent()->AddControl(img);

						auto lab = new ILabel(PathHelper::ExtractFileName(path));

						lab->SetPosition(glm::vec2(15, 30));

						_PreviewWin->GetContent()->AddControl(lab);

						img->Set(glm::vec2(10, 60), glm::vec2(tex->GetWidth(), tex->GetHeight()), "");


					}




					};


			}

		}
	};


}