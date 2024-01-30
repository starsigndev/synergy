#pragma once
#include <IWindow.h>

class IWindow;
class ITextBox;

class NewResourcesWindow :
    public IWindow
{
public:
    NewResourcesWindow();

private:

    ITextBox* _NameBox;

};

