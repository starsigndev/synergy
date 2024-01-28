#include "IList.h"
#include "SynUI.h"
#include "ITheme.h"
#include "IVScroller.h"

IList::IList() {

	_Outline = true;
	_Scroller = new IVScroller;
	AddControl(_Scroller);
	_ScissorTest = true;
	_Scroller->SetMaxValue(10);

}

void IList::SizeChanged() {

	_Scroller->SetPosition(glm::vec2(_Size.x - 15, 0));
	_Scroller->SetSize(glm::vec2(15, _Size.y));


}

void IList::AddItem(ListItem* item) {

	_Items.push_back(item);

}

void IList::AddItem(std::initializer_list<std::string> strings)
{

	for (auto const& str : strings) {

		AddItem(str, nullptr);

	}

}

ListItem* IList::AddItem(Texture2D* icon,std::string text, void* data) {


	auto new_item = new ListItem;
	new_item->Text = text;
	new_item->Data = data;
	new_item->Icon = icon;
	_Items.push_back(new_item);
	return new_item;

}

ListItem* IList::AddItem(std::string text, void* data) {


	auto new_item = new ListItem;
	new_item->Text = text;
	new_item->Data = data;
	_Items.push_back(new_item);
	return new_item;

}

void IList::OnMouseMove(glm::vec2 pos, glm::vec2 delta) {

	int dx = 5;
	int dy = 5 - _Scroller->GetValue()* _Scroller->GetMaxValue();

	_OverItem = nullptr;

	for (auto const& item : _Items) {

		if (pos.x >= 0 && pos.x <= _Size.x && pos.y >= dy && pos.y <= dy + SynUI::StrH(item->Text) + 5) {
			_OverItem = item;
			break;
		}
		dy += SynUI::StrH(item->Text) + 5;
	}

}


void IList::OnMouseDown(int button) {

	if (OnClick) {
		OnClick(this,_OverItem->Data);
	}
	if (ItemSelected) {
		ItemSelected(_OverItem);
	}
	_ActiveItem = _OverItem;

}

void IList::Render() {

	SynUI::Draw(SynUI::Theme->_DarkFrame, GetRenderPosition(), GetSize(), glm::vec4(1, 1, 1, 1));

	int dx = 5;
	int dy = 5 - (_Scroller->GetValue() * _Scroller->GetMaxValue());
	int my = 5;


	for (auto const& item : _Items) {



		if (dy >= _Size.y - (SynUI::StrH(item->Text)+5))
		{
	//		break;

		}


		//if (dy > 0) {
			if (item == _OverItem || item == _ActiveItem) {

				SynUI::Draw(SynUI::Theme->_Frame, GetRenderPosition() + glm::vec2(-1, dy - 4), glm::vec2(_Size.x+2, SynUI::StrH(item->Text) + 7), glm::vec4(3, 3, 3, 1));
				SynUI::Draw(SynUI::Theme->_Frame, GetRenderPosition() + glm::vec2(0, dy - 3), glm::vec2(_Size.x, SynUI::StrH(item->Text) + 5), glm::vec4(1, 1, 1, 1));

			}
			if (item->Icon) {
				SynUI::Draw(item->Icon, GetRenderPosition() + glm::vec2(dx, dy), glm::vec2(16, 16), glm::vec4(1, 1, 1, 1));
				SynUI::DrawStr(item->Text, GetRenderPosition() + glm::vec2(+22, dy), glm::vec4(1, 1, 1, 1));
			}
			else {
				SynUI::DrawStr(item->Text, GetRenderPosition() + glm::vec2(dx, dy), glm::vec4(1, 1, 1, 1));
				//}
			}
		dy += SynUI::StrH(item->Text) + 5;
		my += SynUI::StrH(item->Text) + 5;

	}
	//dy = dy - my;
	my = my - _Size.y;

	if (my < _Size.y) {
	//	my = _Size.y + 100;
	}

	if (dy < 10)
	{
		dy = 10;
	}

	_Scroller->SetMaxValue(my);;

}