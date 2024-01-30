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


}

void SceneEditorState::UpdateState(float dt){

	_UI->UpdateUI(dt);

}

void SceneEditorState::RenderState() {

	_UI->RenderUI();

}