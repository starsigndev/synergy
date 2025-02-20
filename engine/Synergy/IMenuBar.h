#pragma once
#include "IControl.h"
#include <vector>
#include <string>
#include "MenuData.h"

class IVMenu;
class Texture2D;
class IButton;

class IMenuBar : public IControl
{
public:

    IMenuBar();
    void Render();
    void AddItem(MenuItem* item);
    void OnMouseMove(glm::vec2 pos, glm::vec2 delta);
    void OnMouseDown(int button);
    void OnMouseDrag(glm::vec2 pos,glm::vec2 delta);
    void OnMouseLeave();
    MenuItem* AddItem(std::string text, void* data = nullptr);
    void SetIcon(Texture2D* icon) {
        _AppIcon = icon;
    }
    void ClearMenus();
    void SizeChanged();
private:

    std::vector<MenuItem*> _Items;
    MenuItem* _OverItem = nullptr;
    MenuItem* _OpenItem = nullptr;
    IVMenu* _OpenMenu;
    Texture2D* _AppIcon = nullptr;
    IButton* _Minimize, * _Maximize;
    IButton* _CloseApp;
};

