#include "ConvEditorState.h"
#include "SynUI.h"
#include "IMenuBar.h"
#include "IToolbar.h"
#include "SynApp.h"
#include "GeneralOSState.h"
#include "CE_MainMenuBar.h"
#include "CE_ConvNavigator.h"
#include "IWindowDock.h"
#include "IWindow.h"
#include "CE_MainEditor.h"


void ConvEditorState::InitState() {
	_UI->GetMenuBar()->SetText("Synergy Tools - Scene Editor");

	auto mb = _UI->GetMenuBar();
	auto main = mb->AddItem("Conversation Editor");

	auto close_ed = main->AddItem("Close Editor");

	close_ed->OnClick = [&]() {

	

		};

	_MainMenubar = new CE_MainMenubar;

	_UI->SetMenubar(_MainMenubar);

	//
	_ConvNavigator = new CE_ConvNavigator;


	_UI->AddControl(_ConvNavigator);
	_UI->GetDock()->DockWindow(_ConvNavigator, AreaName::AreaLeft);   //GetDock(AreaName::AreaCentral);

	_ConvEditor = new CE_MainEditor;
	_UI->AddControl(_ConvEditor);
	_UI->GetDock()->DockWindow(_ConvEditor, AreaName::AreaCentral);


}

void ConvEditorState::UpdateState(float dt) {

	_UI->UpdateUI(dt);

}

void ConvEditorState::RenderState() {

	_UI->RenderUI();

}