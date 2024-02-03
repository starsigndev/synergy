#pragma once
#include "IControl.h"

class IButton;

class IToolbar :
    public IControl
{
public:

    void Render();
    IButton* AddButton(std::string text);
    IButton* AddButton(Texture2D* icon);
    void AddSpace(float x);
    void Add(IControl* control);

private:

    int _CurrentX = 15;

};

