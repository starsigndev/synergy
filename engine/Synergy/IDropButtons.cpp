#include "IDropButtons.h"
#include "IButton.h"
#include "SynUI.h"

IDropButtons::IDropButtons(std::string kind) {

	_DropButton = new IButton;
	_DropButton->SetText(kind);
	SetSize(glm::vec2(40+SynUI::StrW(kind), 32));
	_DropButton->SetSize(glm::vec2(40+SynUI::StrW(kind), 32));
	AddControl(_DropButton);
	
	_DropButton->OnClick = [&](IControl* c, void* data) {

		if (_DropZone)
		{
			RemoveControl(_DropZone);
		//	delete _DropZone;
			_DropZone = nullptr;
		}
		else {

			_DropZone = new IControl;
			_DropZone->SetPosition(glm::vec2(0, GetSize().y + 1));
			_DropZone->SetSize(glm::vec2(128, _Items.size() * 30));
			AddControl(_DropZone);

			int iy = 0;

			for (auto const& item : _Items) {

				auto but = new IButton;
				but->SetPosition(glm::vec2(0, iy));
				but->SetSize(glm::vec2(128, 30));
				but->SetText(item->Text);
				_DropZone->AddControl(but);
				iy = iy + 30;

				but->OnClick = [&](IControl* c, void* data) {

					_DropButton->SetText(item->Text);
					RemoveControl(_DropZone);
				//	delete _DropZone;
					_DropZone = nullptr;

					};

			}

		}

		};


}

ListItem* IDropButtons::AddItem(std::string name, void* data) {

	ListItem* item = new ListItem;
	item->Text = name;
	item->Data = data;
	_Items.push_back(item);
	return item;

}
