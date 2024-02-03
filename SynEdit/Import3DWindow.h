#pragma once
#include <IWindow.h>

class ITextBox;
class INumeric;
class IVec3;
class ResourceGroup;

class Import3DWindow :
    public IWindow
{
public:
    Import3DWindow(std::string path,ResourceGroup* group);
private:

    ITextBox* _EntityName;
    IVec3* _EntityScale;
    ResourceGroup* _Group;
    std::string _Path;

};

