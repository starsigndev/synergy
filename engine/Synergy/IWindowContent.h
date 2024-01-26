#pragma once
#include "IFrame.h"
class IWindowContent :
    public IFrame
{
public:
    IWindowContent();
    void Render();
    void SetDocked(bool state) {
        _Docked = state;
    }
private:
    bool _Docked = false;

};

