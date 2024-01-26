#pragma once
#include "IControl.h"
#include <string>

class IToggle :
    public IControl
{
public:

    IToggle();
    void OnMouseDown(int button);
    void Render();
    void SetEnabled(bool enable);
    bool GetEnabled();
    void SetLabel(std::string label);


private:

    bool _Enabled = false;
    std::string _Label = "";

};

