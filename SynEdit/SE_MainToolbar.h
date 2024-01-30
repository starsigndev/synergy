#pragma once
#include <IToolbar.h>

class IButton;

class SE_MainToolbar :
    public IToolbar
{
public:

    SE_MainToolbar();

private:

    IButton* _TranslateButton, * _RotateButton, * _ScaleButton;

};

