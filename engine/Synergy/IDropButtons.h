#pragma once
#include "IControl.h"
#include "MenuData.h"

class IButton;

class IDropButtons : public IControl
{
public:

	IDropButtons(std::string kind);
	//void Render();
	ListItem* AddItem(std::string text, void* data = nullptr);

private:

	IButton* _DropButton = nullptr;
	IControl* _DropZone = nullptr;
	std::vector<ListItem*> _Items;

};

