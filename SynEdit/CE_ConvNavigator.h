#pragma once
#include "IWindow.h"

class ITreeView;

class CE_ConvNavigator :
    public IWindow
{
public:

    CE_ConvNavigator();

private:

    ITreeView* _ConvTree;

};

