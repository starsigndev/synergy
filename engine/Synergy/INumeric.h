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

private:

    ITextBox* _Number;
    IButton* _Up, * _Down;
    float _Increment = 1.0f;

};

