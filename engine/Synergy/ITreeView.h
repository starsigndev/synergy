#pragma once
#include "IControl.h"
#include <vector>
#include <string>

class IVScroller;

struct TreeItem {

    TreeItem(std::string text,void* data=nullptr) {
        Text = text;
        Data = data;
        Root = nullptr;

    }
    TreeItem* AddItem(std::string text, void* data=nullptr) {
        TreeItem* item = new TreeItem(text, data);
        Items.push_back(item);
        item->Root = this;
        return item;
    }
    void RemoveItem(TreeItem* item) {
        auto it = std::find(Items.begin(), Items.end(), item);
        if (it != Items.end()) {
           // delete* it;  // Delete the item and its children
            Items.erase(it);  // Remove the item from the vector
        }
    }
    bool Contains(TreeItem* item) {

        for (auto const& i : Items) {
            if (i == item) return true;
        }
        return false;

    }

    std::string Text;
    void* Data;
    std::vector<TreeItem*> Items;
    TreeItem* Root;
    bool Open = false;
    std::function<void(TreeItem*)> ItemSelected;
    std::string Path;
    bool Disabled = false;
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
    TreeItem* GetRootItem() { return _RootItem; }
    TreeItem* GetActiveItem();
    DragInfo BeginDrag();
    void DragOver(DragInfo info);
    void CompleteDrag(DragInfo info);
private:

    IVScroller* _VScroller;
    TreeItem* _RootItem = nullptr;
    TreeItem* _OverItem = nullptr;
    TreeItem* _ActiveItem = nullptr;
    int _MaxY = 0;

};

