#pragma once
#include "IControl.h"
class ILabel :
    public IControl
{
public:

    ILabel(std::string text = "");
    void Render();

};

