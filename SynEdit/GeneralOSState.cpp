#include "GeneralOSState.h"
#include "SynUI.h"
#include "IWindow.h"
#include "IWindowDock.h"
#include "IButton.h"
#include "IWindowContent.h"
#include "IFrame.h"
#include "SynApp.h"
#include "ProjectEditorState.h"
#include "IImage.h"
#include "Texture2D.h"
#include "ResourcesEditorState.h"
#include "IMenuBar.h"
#include "ResourcesTesterState.h"
#include "SceneEditorState.h"

void GeneralOSState::InitState() {


	//auto bg = new IImage(new Texture2D("edit/bg/SynergyTools.png",true));

	//_UI->AddControl(bg);
	//bg->SetSize(_UI->GetRootControl()->GetSize());

	_UI->GetMenuBar()->SetText("Synergy Tools - Main Menu");
	_ToolWindow = new IWindow(true);
	_ToolWindow->SetPosition(glm::vec2(50, 50));
	_ToolWindow->SetSize(glm::vec2(512, 300));
	_ToolWindow->SetText("Synergy - Tools");

	_UI->AddControl(_ToolWindow);

	_UI->GetDock()->SetImage(new Texture2D("edit/bg/synergytools.png", true));
	
	_UI->GetDock()->DockWindow(_ToolWindow, AreaName::AreaCentral);   //GetDock(AreaName::AreaCentral);

	auto general = new IFrame;
	general->SetName("General");
	general->Set(glm::vec2(30, 35), glm::vec2(700, 160), "");

	_ToolWindow->GetContent()->AddControl(general);

	_ProjectEditor = new IButton;

	_ProjectEditor->Set(glm::vec2(15,15), glm::vec2(120, 30), "Project Editor");

	general->AddControl(_ProjectEditor);
	general->SetOutline(true);

	_ProjectEditor->OnClick = [&](IControl* c, void* data) {

		SynApp::This->PushState(new ProjectEditorState);

		};

	_ResourceEditor = new IButton;
	_ResourceEditor->Set(glm::vec2(140, 15), glm::vec2(120, 30), "Resources Editor");
	general->AddControl(_ResourceEditor);
	_ResourceEditor->OnClick = [&](IControl* c, void* d) {

		SynApp::This->PushState(new ResourcesEditorState);

		};

	_ResourceTester = new IButton;
	_ResourceTester->Set(glm::vec2(265, 15), glm::vec2(120, 30), "Test Resources");
	general->AddControl(_ResourceTester);

	_ResourceTester->OnClick = [&](IControl* c, void* d) {

		SynApp::This->PushState(new ResourcesTesterState);

		};


	//

	auto content = new IFrame;
	content->SetName("Content");
	content->Set(glm::vec2(30, 230), glm::vec2(700, 160), "");

	_ToolWindow->GetContent()->AddControl(content);

	_SceneEditor = new IButton;

	_SceneEditor->Set(glm::vec2(15, 15), glm::vec2(120, 30), "Scene Editor");

	content->AddControl(_SceneEditor);
	content->SetOutline(true);

	_SceneEditor->OnClick = [&](IControl* c, void* data) {

		SynApp::This->PushState(new SceneEditorState);

		};



	_ActorEditor = new IButton;
	_ActorEditor->Set(glm::vec2(140, 15), glm::vec2(120, 30), "Actor Editor");
	content->AddControl(_ActorEditor);

	//_UI->GetDock()->SetDockArea(dock, _ToolWindow, true);
	//_ToolWindow->SetDock(_UI->GetDock());



	//->GetRootControl()->RemoveControl(win);
	//win->GetRootControl()->InsertControl(win, 2);

//	_ToolWindow


}

void GeneralOSState::UpdateState(float dt) {
	_UI->UpdateUI(dt);
}

void GeneralOSState::RenderState() {

	_UI->RenderUI();


}