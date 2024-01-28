#pragma once
#include "IWindow.h"
#include <vector>
#include "MenuData.h"
class IList;
class ITextBox;


class IFileRequestor :
    public IWindow
{
public:

    IFileRequestor(std::string path);
    void BrowsePath(std::string);
    std::function<void(std::string)> FileSelected;
private:

    Texture2D* _FileIcon;
    Texture2D* _FolderIcon;
    IList* _FileList;
    ITextBox* _FileBox;
    ITextBox* _FolderBox;
    IButton* _Back;
    ListItem* _SelectedItem;
    std::vector<std::string> _Paths;

};

