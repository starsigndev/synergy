#pragma once
#include "IControl.h"

class Texture2D;

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
    void OnMouseDrag(glm::vec2 pos,glm::vec2 delta);
    void SetIcon(Texture2D* icon) {
        _Icon = icon;
    }
    Texture2D* GetIcon() {
        return _Icon;
    }

private:

    Texture2D* _Icon = nullptr;

};

