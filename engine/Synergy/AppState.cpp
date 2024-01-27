#include "AppState.h"
#include "SynUI.h"
#include "IMenuBar.h"
#include "Texture2D.h"

AppState::AppState() {

	_UI = new SynUI;
//	_Theme = _UI->Theme;
	_MenuBar = _UI->GetMenuBar();

	auto icon = new Texture2D("ui/icon/synergyicon.png");

	_MenuBar->SetIcon(icon);

}