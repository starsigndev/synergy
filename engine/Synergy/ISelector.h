#pragma once
#include "IControl.h"
#include "MenuData.h"

class IList;


class ISelector :
    public IControl
{
public:

    ISelector();
    void AddItems(std::initializer_list<std::string> strings);
    ListItem* AddItem(std::string text, void* data=nullptr);
    void OnMouseDown(int button);
    void Render();
    void OnDeactivate();
    std::string GetType();

    std::function<void(ListItem*)> ItemSelected;
private:

    IList* _OpenList = nullptr;
    std::vector<ListItem*> _Items;
    ListItem* _CurrentItem = nullptr;

};

