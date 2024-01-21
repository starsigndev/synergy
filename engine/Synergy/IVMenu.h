#pragma once
#include "IControl.h"
#include <vector>
#include "MenuData.h"


class IVMenu :
    public IControl
{
public:

    IVMenu(std::vector<MenuItem*> items);
    void Render();
    void OnMouseMove(glm::vec2 pos, glm::vec2 delta);
    void OnMouseDown(int button);

private:

    std::vector<MenuItem*> _Items;
    MenuItem* _OverItem = nullptr;
    MenuItem* _OpenItem = nullptr;
    IVMenu* _OpenMenu = nullptr;
};

