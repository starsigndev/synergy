#pragma once
#include "IControl.h"
#include <vector>
#include <string>

class IVScroller;

struct TreeItem {

    TreeItem(std::string text,void* data=nullptr) {
        Text = text;
        Data = data;

    }
    TreeItem* AddItem(std::string text, void* data=nullptr) {
        TreeItem* item = new TreeItem(text, data);
        Items.push_back(item);
        return item;
    }
    std::string Text;
    void* Data;
    std::vector<TreeItem*> Items;
    bool Open = false;

};

class ITreeView :
    public IControl
{
public:

    ITreeView();
    void SizeChanged();
    void OnMouseMove(glm::vec2 pos, glm::vec2 delta);
    void OnMouseDown(int button);

    void Render();
    int CheckItem(TreeItem* item, int dx, int dy,glm::vec2 pos);
    int RenderItem(TreeItem* item, int dx, int dy);
    void AddItem(TreeItem* item);
    TreeItem* AddItem(std::string text, void* data = nullptr);
    void Update(float dt);
private:

    IVScroller* _VScroller;
    TreeItem* _RootItem = nullptr;
    TreeItem* _OverItem = nullptr;
    TreeItem* _ActiveItem = nullptr;
    int _MaxY = 0;

};

