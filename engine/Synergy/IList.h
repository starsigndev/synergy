#pragma once
#include "IControl.h"
#include "MenuData.h"

class IVScroller;



class IList : public IControl
{
public:

	IList();
	void AddItem(ListItem* item);
	void SizeChanged();
	void OnMouseMove(glm::vec2 pos, glm::vec2 delta);
	void OnMouseDown(int button);
	void AddItem(std::initializer_list<std::string> strings);
	ListItem* AddItem(std::string text, void* data = nullptr);

	ListItem* AddItem(Texture2D* icon,std::string text, void* data = nullptr);
	void Render();
	void Clear() {
		_Items.clear();
	}
	std::function<void(ListItem*)> ItemSelected;
private:

	IVScroller* _Scroller;
	std::vector<ListItem*> _Items;
	ListItem* _OverItem = nullptr;
	ListItem* _ActiveItem = nullptr;

};

