#pragma once
#include "IWindow.h"

class ITextBox;

class NewConversationWindow :
    public IWindow
{
public:
    NewConversationWindow();
private:

    ITextBox* _TitleBox;

};

