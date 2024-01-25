#pragma once
#include "IControl.h"
class IAngleSelect :
    public IControl
{
public:

    IAngleSelect();
    void Render();
    void OnMouseMove(glm::vec2 pos, glm::vec2 delta);
    void OnMouseDown(int button);
    void OnMouseUp(int button);
private:


    float _Angle = 0.0f;
    float _EditAngle = 0.0f;
    Texture2D* _LineTex;
    bool _Dragging = false;
};

