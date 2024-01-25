#pragma once
#include "IControl.h"

class Texture2D;

class IDial :
    public IControl
{
public:

    IDial();
    void Render();
    float GetValue();
    void SetValue(float value);
    void OnMouseDown(int button);
    void OnMouseUp(int button);
    void OnMouseMove(glm::vec2 pos, glm::vec2 delta);

private:

    float _Value = 0.0f;
    Texture2D* _LineTex;
    bool _Dragging = false;
//Remember to do feathered window tabs.

};

