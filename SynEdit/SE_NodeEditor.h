#pragma once
#include <IWindow.h>

class ISelector;
class Node3D;
class IVec3;
class ITextBox;

class SE_NodeEditor :
    public IWindow
{
public:
    SE_NodeEditor();
    void SetNode(Node3D* node);
    void RebuildUI();

    static SE_NodeEditor* This;
private:

    Node3D* _EditNode;
    ITextBox* _NodeName;
    IVec3* _NodePosition;
    IVec3* _NodeRotation;
    IVec3* _NodeScale;
    ISelector* _NodePhysics;
    IButton* _AddScript;
};

