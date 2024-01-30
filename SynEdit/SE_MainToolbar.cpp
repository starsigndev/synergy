#include "SE_MainToolbar.h"

#include "Texture2D.h"
#include "SynApp.h"
#include "IButton.h"

SE_MainToolbar::SE_MainToolbar() {

	SetPosition(glm::vec2(0, 27));
	SetSize(glm::vec2(SynApp::This->GetWidth(), 45));
	_TranslateButton = AddButton(new Texture2D("edit/icon/translate.png", true));
	_RotateButton = AddButton(new Texture2D("edit/icon/rotate.png", true));
	_ScaleButton = AddButton(new Texture2D("edit/icon/scale.png", true));

	_TranslateButton->SetToolTip("Translate(Move) an entity within the scene.", _TranslateButton->GetIcon());
	_RotateButton->SetToolTip("Rotate an entity within the scene.", _RotateButton->GetIcon());
	_ScaleButton->SetToolTip("Scale an entity within the scene.", _ScaleButton->GetIcon());

	_TranslateButton->SetOutline(true);

	_TranslateButton->OnClick = [&](IControl* c, void* d) {

		_TranslateButton->SetOutline(true);
		_RotateButton->SetOutline(false);
		_ScaleButton->SetOutline(false);

		};

	_RotateButton->OnClick = [&](IControl* c, void*) {

		_TranslateButton->SetOutline(false);
		_RotateButton->SetOutline(true);
		_ScaleButton->SetOutline(false);

		};

		_ScaleButton->OnClick = [&](IControl* c, void*) {

			_TranslateButton->SetOutline(false);
			_RotateButton->SetOutline(false);
			_ScaleButton->SetOutline(true);

			};


}