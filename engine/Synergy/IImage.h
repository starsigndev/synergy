#pragma once
#include "IControl.h"
class IImage :
    public IControl
{
public:

    IImage(Texture2D* image);
    void Render();

private:
};

