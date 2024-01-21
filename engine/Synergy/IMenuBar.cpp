#include "IMenuBar.h"
#include "ITheme.h"
#include "SynUI.h"
#include "IVMenu.h"

IMenuBar::IMenuBar() {

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
				break;
			}
		}

		dx = dx + SynUI::StrW(item->Text) + 30;

	}
}

void IMenuBar::OnMouseDown(int button) {

	if (_OverItem) {
		if (_OverItem->Items.size() == 0) {
			return;
		}
		if (_OpenItem != nullptr) {

			RemoveControl(_OpenMenu);
			if (_OpenItem == _OverItem) {
				_OpenItem = nullptr;
				_OpenMenu = nullptr;
				return;

			}
		}
		_OpenItem = _OverItem;
		auto n_menu = new IVMenu(_OpenItem->Items);
		AddControl(n_menu);
		n_menu->SetPosition(glm::vec2(_OpenItem->DrawX+1, _OpenItem->DrawY));
		_OpenMenu = n_menu;
	}
}

void IMenuBar::Render() {

	auto pos = GetRenderPosition();
	SynUI::Draw(SynUI::Theme->_DarkFrame, glm::vec2(0, 0), glm::vec2(_Size.x, 25),glm::vec4(1,1,1,1));
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