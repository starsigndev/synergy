#pragma once
#include "IControl.h"

class ITextBox;
class IButton;

class INumeric :
    public IControl
{
public:

    INumeric();
    void SizeChanged();
    void SetNumber(float value);
    float GetNumber();
    void SetIncrement(float inc) {
        _Increment = inc;
    }
    std::function<void(float)> ValueChanged;
private:

    ITextBox* _Number;
    IButton* _Up, * _Down;
    float _Increment = 1.0f;

};

