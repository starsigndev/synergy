#pragma once
#include <IWindow.h>
#include "ITreeView.h"

class ITextBox;
class ITreeView;
class Node3D;

class SE_GraphExplorer :
    public IWindow
{
public:

    SE_GraphExplorer();
    void SizeChanged();
    void RebuildUI();
    void AddNodes(TreeItem* item, Node3D* node);
    void AddNodesSearch(TreeItem* item, Node3D* node, std::string term);
    void SearchDisable();
    void SearchFor(std::string term);
    void DisableNodes(TreeItem* item, std::string term);

    static SE_GraphExplorer* This;

private:
    ITextBox* _SearchBox;
    ITreeView* _SceneTree;
};

