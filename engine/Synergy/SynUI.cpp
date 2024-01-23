#include "SynUI.h"
#include "SynApp.h"
#include "SmartDraw.h"
#include "AppInput.h"
#include "Texture2D.h"
#include "ITheme.h"
#include "FontRender.h"
#include "IMenuBar.h"
#include "IWindow.h"
#include "IWindowDock.h"
#include "IWindowTitle.h"
#include "IWindowContent.h"
ITheme* SynUI::Theme = nullptr;
SmartDraw* SynUI::_Draw = nullptr;

SynUI* SynUI::This = nullptr;

SynUI::SynUI() {

	This = this;

	_RootControl = new IControl();
	_RootControl->SetPosition(glm::vec2(0, 25));
	_RootControl->SetSize(glm::vec2(SynApp::This->GetWidth(), SynApp::This->GetHeight() - 25));
	_WindowDock = new IWindowDock;

	_RootControl->AddControl(_WindowDock);
	_WindowDock->SetSize(_RootControl->GetSize());
	_WindowDock->SetOutline(false);

	_MenuBar = new IMenuBar;
	_MenuBar->SetSize(glm::vec2(SynApp::This->GetWidth(), 25));
	
	_Draw = new SmartDraw;
	_Draw->SetView(SynApp::This->GetWidth(), SynApp::This->GetHeight());
	_Cursor = new Texture2D("ui/theme/arc/cursor_normal.png");
	
}

void SynUI::Resize(int w, int h) {

	_RootControl->SetSize(glm::vec2(w, h));
	_MenuBar->SetSize(glm::vec2(w, 25));
	_WindowDock->SetSize(glm::vec2(w, h - 25));
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


	UpdateMouse();
	UpdateKB();

	if (_Active) {

	}

}

bool used[512];

void SynUI::UpdateKB() {

	int pkey = _CurrentKey;


	for (int i = 0; i < 512; i++) {

		if (i == GLFW_KEY_LEFT_SHIFT) {
			continue;
		}
		if (i == GLFW_KEY_RIGHT_SHIFT) {
			continue;
		}
		if (AppInput::_KeyState[i] && used[i] == false)
		{
			if (i != _CurrentKey) {
				_FirstKey = true;
			}
			_CurrentKey = i;
			used[i] = true;
		}
		else if (AppInput::_KeyState[i]==false && used[i]) {
			used[i] = false;
		}

	}

	if (AppInput::_KeyState[GLFW_KEY_LEFT_SHIFT] || AppInput::_KeyState[GLFW_KEY_RIGHT_SHIFT])
	{
		if (_Active != nullptr) {
			_Active->SetShift(true);
		}
	}
	else {
		if (_Active != nullptr) {
			_Active->SetShift(false);
		}
	}

	if (_CurrentKey != -1 && AppInput::_KeyState[_CurrentKey] == false)
	{
		_CurrentKey = -1;
		_FirstKey = true;
		
	}

	if (_Active != nullptr) {

		if (_CurrentKey != -1)
		{
			if (_FirstKey) {
				_Active->OnKey(_CurrentKey);
				_FirstKey = false;
				_NextKey = clock() + 500;
			}
			else {
				int time = clock();
				if (time > _NextKey)
				{
					_Active->OnKey(_CurrentKey);
					_NextKey = time + 100;
				}
			}
		}

	}

}


void SynUI::UpdateMouse() {
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
				if (_Active != _Over) {
					_Active = _Over;
					_Active->OnActivate();
				}
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

		if (_WindowOver) {

			_WindowBelow->WindowDropped((IWindow*)_WindowOver);
			_WindowOver = nullptr;
			_WindowBelow = nullptr;

		}

		if (_Pressed != nullptr) {

			_Pressed->OnMouseUp(0);
			if (MouseOver(_MousePosition) != _Pressed)
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

		_Pressed->OnMouseDrag(_MousePosition-_Pressed->GetRenderPosition(), _MouseDelta);

	}

	if (_Over) {

		_Over->OnMouseMove(_MousePosition - _Over->GetRenderPosition(), _MouseDelta);

	}

	if (_Pressed) {

		if (_Pressed->GetRootControl()) {



			auto root = _Pressed->GetRootControl();
			IWindow* win = dynamic_cast<IWindow*>(root);
			IWindowTitle* title = dynamic_cast<IWindowTitle*>(_Pressed);

			if (title) {

				_Ignore.clear();
				AddToIgnore(win);

				_WindowDock->ClearDocked(win);
				auto below = MouseOver(_MousePosition);

				if (below != nullptr) {
					_Ignore.clear();

					below->WindowOver(win);
					_WindowBelow = below;
					_WindowOver = win;
				}
				else {
					_WindowBelow = nullptr;
					_WindowOver = nullptr;
				}

			}





			if (win) {



				//


				if (!win->GetDock()) {
					auto win_root = win->GetRootControl();
					win_root->RemoveControl(win);
					win_root->AddControl(win);

				}

				//				if (below == _WindowDock) {

								//	_WindowDock->Wi

								//}


			}
		}

	}


}

void SynUI::AddToIgnore(IControl* control) {

	_Ignore.push_back(control);
	for (auto const& sub : control->GetControls()) {
		AddToIgnore(sub);
	}
	//_Ignore.clear();



}

bool SynUI::Ignored(IControl* con)
{
	for (auto const& ig : _Ignore) {
		if (ig == con) return true;
	}
	return false;
}

IControl* SynUI::ControlBeneath(IControl* control) {

	//auto control = MouseOver(pos);

	auto list = GetListBackward();

	IControl* prev = nullptr;
	bool next = false;

	for (auto const& sub : list) {

		if (next) {
			prev = sub;
			break;
		}
		if (control == sub) {

			next = true;
			int b = 5;

		}
		prev = sub;

	}

	return prev;


}

std::vector<IControl*> SynUI::GetListForward() {

	std::vector<IControl*> rootList;
	rootList = AddControlToList(rootList, _RootControl);
	rootList = AddControlToList(rootList, _MenuBar);
	//rootList.push_back(_MenuBar);

	return rootList;

}

std::vector<IControl*> SynUI::AddControlToList(std::vector<IControl*> list, IControl* control) {

	if (Ignored(control) == false) {
		list.push_back(control);
		auto controls = control->GetControls();

		for (const auto& con : controls) {

			list = AddControlToList(list, con);

		}
	}
	return list;

}


void SynUI::RenderUI() {

	_Draw->Begin();

	//auto list = GetListForward();

	//RenderList(list);
	_Draw->SetScissor(glm::vec4( - 1, -1, -1, -1));
	RenderControl(_RootControl);
	RenderControl(_MenuBar);

	DrawCursor();
	_Draw->End();
}

void SynUI::RenderControl(IControl* control) {

	if (control->GetOutline()) {
		if (control != _RootControl) {
			Draw(Theme->_Frame, control->GetRenderPosition() + glm::vec2(-1, -1), control->GetSize() + glm::vec2(2, 2), glm::vec4(5, 5, 5, 1));
		}
	}
	control->Render();
	IWindowContent* title = dynamic_cast<IWindowContent*>(control);
	
	if (title) {

		_Draw->SetScissor(control->GetScissor());

	}

	for (auto const& sub : control->GetControls()) {

		RenderControl(sub);

	}

	if (title) {
		_Draw->SetScissor(glm::vec4(-1, -1, -1, -1));

	}


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


}

void SynUI::DrawCursor() {

	//_Draw->Begin();
	_Draw->DrawQuad(Theme->_Cursor, _MousePosition, glm::vec2(32, 32), glm::vec4(1, 1, 1, 0.8f));
	//_Draw->End();

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