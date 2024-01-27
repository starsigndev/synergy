#pragma once
#include "IControl.h"

#include <vector>
#include <string>

class Texture2D;

enum AreaName {

    AreaLeft,AreaRight,AreaTop,AreaBottom,AreaCentral

};

struct DockArea {

    glm::vec2 Position;
    glm::vec2 Size;
    glm::vec2 AreaPosition;
    glm::vec2 AreaSize;
    AreaName Name;
    IControl* Docked = nullptr;
    bool _Taken[3][3];
    void Reset() {
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                _Taken[x][y] = false;
            }
        }
    }



};

class IWindowDock :
    public IControl
{
public:

    IWindowDock();
    void SizeChanged();
    void CreateInitialAreas();
    void Render();
    void WindowOver(IWindow* window);
    void WindowDropped(IWindow* window);
    DockArea* GetArea(glm::vec2 pos);
    DockArea* GetAreaDock(glm::vec2 pos);
    DockArea* GetDock(AreaName area);
    void DockWindow(IWindow* window, AreaName name);
    void ClearDocked(IWindow* win);
    void SetDockArea(DockArea* area, IWindow* win,bool change);
private:


    std::vector<DockArea*> _Areas;

    DockArea* _ATop, * _ABottom, * _ALeft, * _ARight, * _ACentral;
    Texture2D* _WhiteTex;
    DockArea* _OverArea = nullptr;
    DockArea* _OverAreaDock = nullptr;
    bool _Used[3][3];

};

