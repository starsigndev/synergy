#include "IMenuBar.h"
#include "ITheme.h"
#include "SynUI.h"
#include "IVMenu.h"
#include "SynApp.h"
#include "IButton.h"

IMenuBar::IMenuBar() {
	_Outline = true;
	_Minimize = new IButton;
	_Maximize = new IButton;
	_CloseApp = new IButton;
	_Minimize->SetSize(glm::vec2(17, 15));
	_Maximize->SetSize(glm::vec2(17, 15));
	_CloseApp->SetSize(glm::vec2(17, 15));
	AddControl(_Minimize);
	
	AddControl(_Maximize);
	AddControl(_CloseApp);
	_Minimize->SetIcon(SynUI::Theme->_Minimize);
	_Maximize->SetIcon(SynUI::Theme->_Maximize);
	_CloseApp->SetIcon(SynUI::Theme->_CloseApp);
	_Minimize->OnClick = [](IControl* c, void* data) {

		SynApp::This->Minimize();

		};

	_Maximize->OnClick = [](IControl* c, void* data) {

		SynApp::This->Maximize();

		};

	_CloseApp->OnClick = [](IControl* c, void* data) {

		exit(1);

		};
}

void IMenuBar::AddItem(MenuItem* item) {

	_Items.push_back(item);

}

MenuItem* IMenuBar::AddItem(std::string text, void* data) {

	auto item = new MenuItem(text, data);
	_Items.push_back(item);
	return item;

}

void IMenuBar::OnMouseMove(glm::vec2 pos, glm::vec2 delta)
{

	_OverItem = nullptr;

	
	int dx = 30;

	for (auto const& item : _Items) {

		int ax = dx;
		int ay = 2;

		if (pos.x >= ax && pos.x <= ax + SynUI::StrW(item->Text) + 30) {
			if (pos.y >= 0 && pos.y <= 25)
			{
				_OverItem = item;
				if (_OverItem != _OpenItem) {

					RemoveControl(_OpenMenu);
					if (_OpenItem == _OverItem) {
						_OpenItem = nullptr;
						_OpenMenu = nullptr;
						return;

					}

				}
				break;
			}
		}

		dx = dx + SynUI::StrW(item->Text) + 30;

	}
}

void IMenuBar::SizeChanged() {

	_Minimize->SetPosition(glm::vec2(_Size.x - 95, 5));
	_Maximize->SetPosition(glm::vec2(_Size.x - 65, 5));
	_CloseApp->SetPosition(glm::vec2(_Size.x - 35, 5));
}

void IMenuBar::ClearMenus() {

	if (HasControl((IControl*)_OpenMenu)) {

		RemoveControl(_OpenMenu);
		if (_OpenItem == _OverItem) {
			_OpenItem = nullptr;
			_OpenMenu = nullptr;
			return;

		}
	}
	else {
		_OpenItem = nullptr;

	}

}

void IMenuBar::OnMouseDown(int button) {

	if (_OverItem) {
		if (_OverItem->Items.size() == 0) {
			return;
		}
		if (_OpenItem != nullptr) {

			if (HasControl((IControl*)_OpenMenu)) {

				RemoveControl(_OpenMenu);
				if (_OpenItem == _OverItem) {
					_OpenItem = nullptr;
					_OpenMenu = nullptr;
					return;

				}
			}
			else {
				_OpenItem = nullptr;

			}
		}
		_OpenItem = _OverItem;
		auto n_menu = new IVMenu(_OpenItem->Items);
		AddControl(n_menu);
		n_menu->SetPosition(glm::vec2(_OpenItem->DrawX+1, _OpenItem->DrawY));
		_OpenMenu = n_menu;
		n_menu->SetOwner(this);
	}
}

void IMenuBar::OnMouseDrag(glm::vec2 pos, glm::vec2 delta) {

	if (_OverItem) {
		return;
	}
	SynApp::This->SetWindow(SynApp::This->GetWindowPos() + delta);

}

void IMenuBar::OnMouseLeave() {

	_OverItem = nullptr;
	

}

void IMenuBar::Render() {

	auto pos = GetRenderPosition();
	SynUI::Draw(_Image, pos, glm::vec2(_Size.x, _Size.y), _UV, glm::vec4(1, 1, 1, 1),0.00045f,0.0000004f);
	SynUI::Draw(SynUI::Theme->_AppFrame,pos, glm::vec2(_Size.x,_Size.y),glm::vec4(1,1,1,0.78f));
	SynUI::Draw(_AppIcon, glm::vec2(2, 2), glm::vec2(24, 24), glm::vec4(1, 1, 1, 1));

	int dx = 30;

	for (auto const& item : _Items)
	{

		int ax = pos.x + dx;
		int ay = pos.y + 2;

		if (item == _OverItem) {
			SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(ax-1, ay-1), glm::vec2(SynUI::StrW(item->Text) + 32, 27), glm::vec4(5, 5, 5, 1));

			SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(ax, ay), glm::vec2(SynUI::StrW(item->Text)+30, 25), glm::vec4(2, 2, 2, 1));

		}
		SynUI::DrawStr(item->Text, glm::vec2(ax+15, ay+2), glm::vec4(1, 1, 1, 1));

		item->DrawX = ax;
		item->DrawY = ay + 25;

		dx = dx + SynUI::StrW(item->Text) + 30;
		

	}

}