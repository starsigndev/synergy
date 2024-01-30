#include "ISelector.h"
#include "SynUI.h"
#include "ITheme.h"
#include "IList.h"

ISelector::ISelector() {

	_ScissorTest = true;
	//_WholeScissor = true;
	_ScissorChildren = false;

}

void ISelector::AddItems(std::initializer_list<std::string> strings)
{

	for (auto const& str : strings) {

		AddItem(str, nullptr);

	}

}

ListItem* ISelector::AddItem(std::string text, void* data)
{

	ListItem* new_item = new ListItem;
	new_item->Text = text;
	new_item->Data = data;
	_Items.push_back(new_item);
	return new_item;

}

void ISelector::OnMouseDown(int button) {

	if (_OpenList) {
		RemoveControl(_OpenList);
		_OpenList = nullptr;
		return;
	}

	_OpenList = new IList;
	_OpenList->Set(glm::vec2(0, _Size.y + 1), glm::vec2(_Size.x, 120),"");
	for (auto const& item : _Items) {
		_OpenList->AddItem(item->Text, item->Data);

	}
	_OpenList->ItemSelected = [&](ListItem* item) {
		if (item == nullptr) {
			RemoveControl(_OpenList);
			_OpenList = nullptr;
			return;
		}
		for (auto const& it : _Items) {
			if (it->Text == item->Text) {
				_CurrentItem = it;
				break;
			}
		}
		RemoveControl(_OpenList);
		_OpenList = nullptr;
		if (ItemSelected) {
			ItemSelected(_CurrentItem);
		}
		};
	AddControl(_OpenList);


}

void ISelector::OnDeactivate() {

	if (_OpenList) {
		RemoveControl(_OpenList);
		_OpenList = nullptr;
		return;
	}

}

void ISelector::Render() {

	if (_CurrentItem == nullptr) {
		_CurrentItem = _Items.at(0);
	}
	SynUI::Draw(SynUI::Theme->_DarkFrame, GetRenderPosition(), GetSize(), glm::vec4(1, 1, 1, 1));
	if (_CurrentItem) {
		SynUI::DrawStr(_CurrentItem->Text, GetRenderPosition() + (GetSize()*0.5f)-glm::vec2(SynUI::StrW(_CurrentItem->Text)/2,SynUI::StrH(_CurrentItem->Text)/2), glm::vec4(1, 1, 1, 1));
	}
}

std::string ISelector::GetType() {

	return _CurrentItem->Text;

}