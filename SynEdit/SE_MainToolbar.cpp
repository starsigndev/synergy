#include "SE_MainToolbar.h"
#include "SynUI.h"
#include "ITheme.h"
#include "Texture2D.h"
#include "SynApp.h"
#include "IButton.h"
#include "ISelector.h"
#include "SE_Global.h"

SE_MainToolbar::SE_MainToolbar() {

	SetPosition(glm::vec2(0, 27));
	SetSize(glm::vec2(SynApp::This->GetWidth(), 45));
	_TranslateButton = AddButton(new Texture2D("edit/icon/translate.png", true));
	_RotateButton = AddButton(new Texture2D("edit/icon/rotate.png", true));
	_ScaleButton = AddButton(new Texture2D("edit/icon/scale.png", true));
	_SelectSpace = new ISelector;
	_SelectSpace->AddItems({ "Local","Global" });
	_SelectSpace->SetSize(glm::vec2(120, 29));
	Add(_SelectSpace);

	_RunButton = new  IButton;
	_RunButton->SetSize(glm::vec2(32, 29));
	_RunButton->SetIcon(SynUI::Theme->_RunGame);
	AddSpace(256);
	Add(_RunButton);

	_RunButton->SetOutline(false);

	_RunButton->OnClick = [&](IControl* c, void* data)
		{

			SE_Global::PlayScene();

		};

	_StopButton = new IButton;
	_StopButton->SetSize(glm::vec2(32, 29));
	_StopButton->SetIcon(SynUI::Theme->_StopGame);
	Add(_StopButton);
	_StopButton->SetOutline(false);
	_StopButton->OnClick = [&](IControl* c, void* d)
		{
			SE_Global::StopScene();
		};



	_SelectSpace->ItemSelected = [&](ListItem* item) {

		if (item->Text == "Local")
		{
			SE_Global::_SpaceMode = SM_Local;
		}
		if (item->Text == "Global")
		{
			SE_Global::_SpaceMode = SM_Global;
		}

		};


	_TranslateButton->SetToolTip("Translate(Move) an entity within the scene.", _TranslateButton->GetIcon());
	_RotateButton->SetToolTip("Rotate an entity within the scene.", _RotateButton->GetIcon());
	_ScaleButton->SetToolTip("Scale an entity within the scene.", _ScaleButton->GetIcon());

	_TranslateButton->SetOutline(true);

	_TranslateButton->OnClick = [&](IControl* c, void* d) {

		_TranslateButton->SetOutline(true);
		_RotateButton->SetOutline(false);
		_ScaleButton->SetOutline(false);
		SE_Global::_EditMode = EditorMode::EM_Translate;

		};

	_RotateButton->OnClick = [&](IControl* c, void*) {

		_TranslateButton->SetOutline(false);
		_RotateButton->SetOutline(true);
		_ScaleButton->SetOutline(false);
		SE_Global::_EditMode = EditorMode::EM_Rotate;

		};

		_ScaleButton->OnClick = [&](IControl* c, void*) {

			_TranslateButton->SetOutline(false);
			_RotateButton->SetOutline(false);
			_ScaleButton->SetOutline(true);
			SE_Global::_EditMode = EditorMode::EM_Scale;

			};


		SE_Global::_SpaceMode = SM_Local;
		SE_Global::_EditMode = EM_Translate;


}