#pragma once
#include "IControl.h"
class IVScroller :
    public IControl
{
public:

    IVScroller();
    void SetMaxValue(int value);
    float GetValue();
    void Render();
    void OnMouseDown(int button);
    void OnMouseUp(int button);
    void OnMouseDrag(glm::vec2 pos,glm::vec2 delta);
    void OnMouseMove(glm::vec2 pos, glm::vec2 delta);
    void OnMouseLeave();
    int GetMaxValue() {
        return _MaxValue;
    }
    void SetValue(int value) {
        _CurrentValue += (-value);
        if (_CurrentValue < 0) _CurrentValue = 0;
        if (_CurrentValue + dh > _Size.y)
        {
            _CurrentValue -= (_Size.y - (_CurrentValue + dh));
        }

    }
    void Scroll(float y) {

        _CurrentValue += (-y);
        if (_CurrentValue < 0) _CurrentValue = 0;
        if (_CurrentValue + dh > _Size.y)
        {
            _CurrentValue -= (_Size.y - (_CurrentValue + dh));
        }
        if (OnValueChanged)
        {
            OnValueChanged(GetValue());
        }
    }
    bool InBounds(glm::vec2 pos);
private:


    int _MaxValue = 0;
    int _CurrentValue = 0;
    float _Value;
    float av2 = 0;
    int dh = 0;
    bool _Dragging = false;
    bool over_drag = false;

};

