#include "ResourcesTesterState.h"
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
#include "Entity.h"
#include "Importer.h"

ResourcesTesterState* ResourcesTesterState::Editor = nullptr;



void ResourcesTesterState::InitState() {
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

	_UI->GetMenuBar()->SetText("Synergy Tools - Resources Tester");

	auto mb = _UI->GetMenuBar();

	//-------

	auto list_res = new IWindow(true);
	auto prev_res = new IWindow(true);

	list_res->SetText("Resources");
	//edit_res->SetText("Edit Resource");
	prev_res->SetText("Preview Resource");

//	_UI->AddControl(edit_res);
//	_UI->GetDock()->DockWindow(edit_res, AreaName::AreaBottom);   //GetDock(AreaName::AreaCentral);
	_UI->AddControl(list_res);
	_UI->GetDock()->DockWindow(list_res, AreaName::AreaLeft);   //GetDock(AreaName::AreaCentral);
	_UI->AddControl(prev_res);
	_UI->GetDock()->DockWindow(prev_res, AreaName::AreaCentral);   //GetDock(AreaName::AreaCentral);

	_PreviewWin = prev_res;

	auto list_tree = new ITreeView;

	_ResTree = list_tree;

	list_res->GetContent()->AddControl(list_tree);

	list_tree->Expand();

	auto root = list_tree->GetRootItem();
	root->Text = "Resources";
	_Root = root;


	SynResources::LoadDefault();
	RebuildUI();

}

void ResourcesTesterState::UpdateState(float dt) {
	_UI->UpdateUI(dt);
}

void ResourcesTesterState::RenderState() {

	_UI->RenderUI();

}


void ResourcesTesterState::RebuildUI() {

	Editor->_Root->Items.clear();

	for (auto const& group : GameResources::Resources->GetResources()->GetGroups()) {

		TreeItem* item = Editor->_Root->AddItem(group->GetName());

		item->Data = (void*)group;

		for (auto const& res : group->GetResources()) {

			TreeItem* res_item = item->AddItem(res->GetName());
			res_item->Path = res->GetPath();
			res_item->Data = res;

			res_item->ItemSelected = [&](TreeItem* item) {
			
				_PreviewWin->GetContent()->ClearControls();
				
				std::string path = item->Path;

				auto ext = PathHelper::getFileExtension(path);

				Resource* resource = (Resource*) item->Data;
				glm::vec3 scale = resource->GetScale();
				resource->Load();

		
				if (ext == "fbx")
				{

					auto imp = new Importer;

					auto entity = (Entity*)imp->ImportNodeFromResource(resource);
					entity->SetScale(scale);

					auto prev = new IPreview3D(entity);
					int b = 5;
					_PreviewWin->GetContent()->AddControl(prev);
					prev->Set(glm::vec2(10, 60), glm::vec2(600, 600), "");


				}
				if (ext == "png")
				{

					auto tex = new Texture2D(resource->GetSize(), resource->GetData());

					auto img = new IImage(tex);


					_PreviewWin->GetContent()->AddControl(img);

					auto lab = new ILabel(PathHelper::ExtractFileName(path));

					lab->SetPosition(glm::vec2(15, 30));

					_PreviewWin->GetContent()->AddControl(lab);

					img->Set(glm::vec2(10, 60), glm::vec2(tex->GetWidth(), tex->GetHeight()), "");


				}




				};


		}

	};


}