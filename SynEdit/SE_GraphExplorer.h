#pragma once
#include <IWindow.h>

class ITextBox;
class ITreeView;

class SE_GraphExplorer :
    public IWindow
{
public:

    SE_GraphExplorer();
    void SizeChanged();

private:
    ITextBox* _SearchBar;
    ITreeView* _SceneTree;
};

