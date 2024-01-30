#include "IVMenu.h"
#include "SynUI.h"
#include "ITheme.h"


IVMenu::IVMenu(std::vector<MenuItem*> items) {

	_Items = items;

	int bw = 15;
	int bh = 5;

	for (auto const& item : _Items) {

		int iw = SynUI::StrW(item->Text) + 60;
		if (iw > bw) bw = iw;

		bh = bh + 30;

	}

	//bh = bh - 25;


	//bh += 5;
	SetSize(glm::vec2(bw, bh));
}

IVMenu::IVMenu() {



}

MenuItem* IVMenu::AddItem(std::string text) {

	MenuItem* new_item = new MenuItem(text, nullptr);
	new_item->Text = text;
	
	_Items.push_back(new_item);

	int bw = 15;
	int bh = 5;

	for (auto const& item : _Items) {

		int iw = SynUI::StrW(item->Text) + 60;
		if (iw > bw) bw = iw;

		bh = bh + 30;

	}

	//bh = bh - 25;


	//bh += 5;
	SetSize(glm::vec2(bw, bh));

	return new_item;


}

void IVMenu::OnMouseMove(glm::vec2 pos, glm::vec2 delta) {

	_OverItem = nullptr;

	int dy = 0;

	for (auto const& item : _Items) {

		//SynUI::DrawStr(item->Text, glm::vec2(pos.x + 15, pos.y + dy + 5), glm::vec4(1, 1, 1, 1));

		if (pos.x >= 0 && pos.x <= GetSize().x)
		{
			if (pos.y >= dy && pos.y <= dy+30)
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
				return;
			}
		}

		dy = dy + 30;


	}

}

void IVMenu::OnMouseDown(int button) {

	if (_OverItem) {
		if (_OverItem->Items.size() == 0) {

			if (_OverItem->OnClick) {

				_OverItem->OnClick();

			}

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
		n_menu->SetPosition(glm::vec2(_OpenItem->DrawX + GetSize().x+2, _OpenItem->DrawY));
		_OpenMenu = n_menu;
		n_menu->SetOwner(this);
	}

}

void IVMenu::Render() {

	auto pos = GetRenderPosition();




//	SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(pos.x - 1, pos.y - 1), glm::vec2(GetSize().x + 2, GetSize().y + 2), glm::vec4(2, 2, 2, 1));
	SynUI::Draw(SynUI::Theme->_DarkFrame, pos, GetSize(), glm::vec4(1, 1, 1, 1));

	int dy = 0;

	for (auto const& item : _Items) {

		if (_OverItem == item) {

			SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(pos.x-1, pos.y + dy-1), glm::vec2(GetSize().x+2, 32), glm::vec4(5, 5, 5, 1));

			SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(pos.x+1, pos.y + dy), glm::vec2(GetSize().x-2, 30), glm::vec4(1, 1, 1, 1));

		}

		if (item->Icon) {

			SynUI::Draw(item->Icon, glm::vec2(pos.x + 7, pos.y + dy + 7), glm::vec2(16, 16), glm::vec4(1, 1, 1, 1));

		}

		SynUI::DrawStr(item->Text, glm::vec2(pos.x+30, pos.y+dy + 7), glm::vec4(1, 1, 1, 1));

		if (item->Items.size() > 0) {

			SynUI::Draw(SynUI::Theme->_ArrowRight, glm::vec2(pos.x + 30 + SynUI::StrW(item->Text) + 10, pos.y + dy+8), glm::vec2(16, 16), glm::vec4(1, 1, 1, 1));

		}

		item->DrawX = 0;
		item->DrawY = dy;

		dy = dy + 30;

	}

	

}

void IVMenu::OnMouseLeave() {

	

	//_Owner->RemoveControl(this);


}