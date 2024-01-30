#pragma once
#include "IFrame.h"

class IWindow;

class IWindowContent :
    public IFrame
{
public:
    IWindowContent();
    void Render();
    void SetDocked(bool state) {
        _Docked = state;
    }
    void SetWindow(IWindow* window);
    void OnMouseWheel(float y);
private:
    bool _Docked = false;
    IWindow* _Window = nullptr;
};

