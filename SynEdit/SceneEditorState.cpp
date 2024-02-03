#include "SceneEditorState.h"
#include "SynUI.h"
#include "IButton.h"
#include "SynApp.h"
#include "Texture2D.h"
#include "IToolbar.h"
#include "IWindowDock.h"
#include "IMenuBar.h"
#include "GeneralOSState.h"
#include "SE_GraphExplorer.h"
#include "SE_MainToolbar.h"
#include "SE_Viewer.h"
#include "SE_MainMenubar.h"
#include "SynResources.h"
#include "SE_NodeEditor.h"

void SceneEditorState::InitState() {

	auto back = new IButton;
	back->Set(glm::vec2(10, SynApp::This->GetHeight() - 115), glm::vec2(30, 30), "");
	back->SetIcon(new Texture2D("edit/icon/exitdoor.png", true));
//	_UI->GetToolbar()->Add(back);
	_UI->GetDock()->SetImage(new Texture2D("edit/bg/synergytools.png", true));
	back->OnClick = [](IControl* c, void* d)
		{
			SynApp::This->PushState(new GeneralOSState);
		};

	_UI->GetMenuBar()->SetText("Synergy Tools - Scene Editor");

	auto mb = _UI->GetMenuBar();

	

	_GraphExplorer = new SE_GraphExplorer;

	_UI->AddControl(_GraphExplorer);
	_UI->GetDock()->DockWindow(_GraphExplorer, AreaName::AreaLeft);   //GetDock(AreaName::AreaCentral);

	_MainToolbar = new SE_MainToolbar;

	_UI->SetToolbar(_MainToolbar);

	_MainMenubar = new SE_MainMenubar;

	_UI->SetMenubar(_MainMenubar);

	_SceneViewer = new SE_Viewer;

	  //GetDock(AreaName::AreaCentral);

	_GraphExplorer->RebuildUI();

	SynResources::LoadDefault();

	_NodeEditor = new SE_NodeEditor;

	_UI->AddControl(_NodeEditor);
	_UI->GetDock()->DockWindow(_NodeEditor, AreaName::AreaRight);

	_UI->AddControl(_SceneViewer);
	_UI->GetDock()->DockWindow(_SceneViewer, AreaName::AreaCentral);
}

void SceneEditorState::UpdateState(float dt){

	_UI->UpdateUI(dt);

}

void SceneEditorState::RenderState() {

	_UI->RenderUI();

}