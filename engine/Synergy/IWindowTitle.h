#pragma once
#include "IButton.h"

class IWindow;

class IWindowTitle :
    public IButton
{
public:

    IWindowTitle();
    void SetWindow(IWindow* window);
    IWindow* GetWindow();
    void Render();
    void RenderTab(std::string text, int dx,int w);

private:

    IWindow* _Window;

};

