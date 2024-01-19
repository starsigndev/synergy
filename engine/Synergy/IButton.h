#pragma once
#include "IControl.h"
class IButton :
    public IControl
{
public:

    IButton();
    void Render();
    void OnMouseEnter();
    void OnMouseLeave();
    void OnMouseDown(int button);
    void OnMouseUp(int button);
    void OnMouseDrag(glm::vec2 delta);
};

