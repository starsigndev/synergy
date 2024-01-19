#include "SynUI.h"
#include "SynApp.h"
#include "SmartDraw.h"
#include "AppInput.h"
#include "Texture2D.h"
#include "ITheme.h"
#include "FontRender.h"

ITheme* SynUI::Theme = nullptr;
SmartDraw* SynUI::_Draw = nullptr;

SynUI::SynUI() {

	_RootControl = new IControl();
	_RootControl->SetSize(glm::vec2(SynApp::This->GetWidth(), SynApp::This->GetHeight()));
	_Draw = new SmartDraw;
	_Draw->SetView(SynApp::This->GetWidth(), SynApp::This->GetHeight());
	_Cursor = new Texture2D("ui/theme/arc/cursor_normal.png");
	
}

void SynUI::AddControl(IControl* control) {

	_RootControl->AddControl(control);

}

IControl* SynUI::GetRootControl() {

	return _RootControl;

}

void SynUI::UpdateUI(float dt) {


	_MousePosition = AppInput::_MousePosition;
	_MouseDelta = AppInput::_MouseDelta;
	for (int i = 0; i < 16; i++) {
		_MouseButton[i] = AppInput::_ButtonState[i];
	}

	auto list = GetListForward();

	for (auto const& control : list) {

		control->Update(dt);

	};

	auto over = MouseOver(_MousePosition);

	if (_MouseButton[0]) {

		if (_Over != nullptr) {
			if (_Pressed == nullptr) {
				_Pressed = _Over;
				if (_Active) {
					if (_Active != _Over) {
						_Active->OnDeactivate();
					}
				}
				_Active = _Over;
				_Active->OnActivate();
				_Over->OnMouseDown(0);
			}
		}
		else {
			if (_Pressed == nullptr) {
				if (_Active)
				{
					_Active->OnDeactivate();
					_Active = nullptr;
				}
			}
		}
	}
	else {

		if (_Pressed != nullptr) {

			_Pressed->OnMouseUp(0);
			if(MouseOver(_MousePosition) != _Pressed)
			{
				_Pressed->OnMouseLeave();
			}
			_Pressed = nullptr;


		}

	}


	if (_Pressed == nullptr) {
		if (over != nullptr) {

			if (_Over != nullptr && _Over != over) {

				_Over->OnMouseLeave();

			}

			if (over != _Over) {
				over->OnMouseEnter();
			}
			_Over = over;


			//exit(1);


		}
		else {

			if (_Over != nullptr) {

				_Over->OnMouseLeave();

			}

			_Over = nullptr;

		}
	}

	if (_Pressed != nullptr) {

		_Pressed->OnMouseDrag(_MouseDelta);

	}

	if (_Active) {

	}

}

std::vector<IControl*> SynUI::GetListForward() {

	std::vector<IControl*> rootList;
	rootList = AddControlToList(rootList, _RootControl);
	return rootList;

}

std::vector<IControl*> SynUI::AddControlToList(std::vector<IControl*> list, IControl* control) {

	list.push_back(control);
	auto controls = control->GetControls();
	for (const auto& con : controls) {

		list = AddControlToList(list, con);

	}

	return list;

}


void SynUI::RenderUI() {

	_Draw->Begin();

	auto list = GetListForward();

	RenderList(list);

	_Draw->End();

	DrawCursor();

}

std::vector<IControl*> SynUI::GetListBackward() {

	auto list = GetListForward();
	std::vector<IControl*> back_list;
	for (auto it = list.rbegin(); it != list.rend(); ++it) {
		//std::cout << *it << std::endl;
		back_list.push_back(*it);
	}
	return back_list;
}

void SynUI::RenderList(std::vector<IControl*> controls) {

	for (const auto& con : controls) {

		con->Render();

	}

}

void SynUI::DrawCursor() {

	_Draw->Begin();
	_Draw->DrawQuad(Theme->_Cursor, _MousePosition, glm::vec2(32, 32), glm::vec4(1, 1, 1, 0.8f));
	_Draw->End();

}

void SynUI::Draw(Texture2D* img, glm::vec2 pos, glm::vec2 size, glm::vec4 color)
{

	_Draw->DrawQuad(img, pos, size, color);

}

void SynUI::DrawStr(std::string text, glm::vec2 pos, glm::vec4 color)
{

	Theme->_Font->DrawTextUI(text, pos.x, pos.y,color);

}

int SynUI::StrW(std::string text) {

	return Theme->_Font->Width(text);

}

int SynUI::StrH(std::string text) {

	return Theme->_Font->Height() + 2;

}


IControl* SynUI::MouseOver(glm::vec2 pos)
{

	auto list = GetListBackward();

	for (auto const& control : list) {
		if (control == _RootControl) {
			continue;
		}
		if (control->InBounds(pos))
		{
			return control;
		}

	}
	
	return nullptr;

}