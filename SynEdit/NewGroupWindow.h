#pragma once
#include <IWindow.h>

class ITextBox;
class ISelector;

class NewGroupWindow :
    public IWindow
{
public:
    NewGroupWindow();

    ITextBox* _NameBox;
    ISelector* _Type;
};

