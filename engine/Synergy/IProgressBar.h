#pragma once
#include "IControl.h"
class IProgressBar :
    public IControl
{
public:

    IProgressBar();
    void Render();
    void SetValue(float value);
    float GetValue();

private:

    float _Value = 0.0f;

};

