#include "IVScroller.h"
#include <limits>
#include "SynUI.h"
#include "ITheme.h"
#include <iostream>

template<typename T>
const T& clamp(const T& v, const T& lo, const T& hi) {
    assert(!(hi < lo));
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

IVScroller::IVScroller() {

    _MaxValue = 1000;
    _CanActivate = false;
    AddTag("Cursor", "UpDown");

}

void IVScroller::SetMaxValue(int value) {

	_MaxValue = value;

}

bool IVScroller::InBounds(glm::vec2 position) {

    if (GetMaxValue() < 0)
    {
        
        _Outline = false;
        return false;
        
    }
    else {
        _Outline = true;
    }


    auto rpos = GetRenderPosition();
    auto rsize = GetSize();

    if (position.x >= rpos.x && position.y >= rpos.y && position.x <= (rpos.x + rsize.x) && position.y <= (rpos.y + rsize.y)) {
        return true;
    }

    return false;
}
float IVScroller::GetValue() {

    // Constants for minimum and maximum handle sizes
    const float minHandleSize = 20.0f;  // Minimum handle size
    const float maxHandleSize = _Size.y;  // Maximum handle size is the height of the scroller

    // Ensure _maxValue is not zero to avoid division by zero
    if (_MaxValue == 0) {
        dh = maxHandleSize;
        return 0.0f;
    }

    // Calculate the proportion of the content visible in the scroll area
    float contentRatio = static_cast<float>(_Size.y) / _MaxValue;

    // Cap content ratio if needed
    const float maxContentRatio = 0.92f;
    contentRatio = std::min(contentRatio, maxContentRatio);

    // Calculate the handle size based on content ratio
    float handleSize = contentRatio * _Size.y;

    if (handleSize == 0) return 0.0f;
    // Clamp the handle size to be within minimum and maximum bounds
    dh = clamp(handleSize, minHandleSize, maxHandleSize);

    // Calculate and return the current value based on the clamped handle size
    float maxScrollableHeight = _Size.y - dh;

    // Ensure avoiding division by zero
    if (maxScrollableHeight == 0) {
        return 0.0f;
    }

    // Adjust current value if needed
    if (_CurrentValue + dh > _Size.y) {
        _CurrentValue -= ((_CurrentValue + dh) - _Size.y);
    }

    // Calculate and return the normalized current value
    return clamp(static_cast<float>(_CurrentValue) / maxScrollableHeight, 0.0f, 1.0f);
}

void IVScroller::Render() {


    if (GetMaxValue() < 0)
    {
      
        _Outline = false;
        _CurrentValue = 0;
        if (OnValueChanged) {
            OnValueChanged(GetValue());
        }
        return;
        
    }
    else {
        _Outline = true;
    }

    float v= GetValue();

    if (v > 1.0f)
    {
     //   float maxScrollableHeight = _Size.y - dh;
    //    _CurrentValue = maxScrollableHeight;
    }

    auto pos = GetRenderPosition();

    //SynUI::Draw(SynUI::Theme->_Frame, pos+glm::vec2(-1,-1), GetSize()+glm::vec2(2,2), glm::vec4(5, 5, 5, 1));
    SynUI::Draw(SynUI::Theme->_DarkFrame, pos, GetSize(), glm::vec4(1,1,1, 1));
    SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(pos.x, pos.y + _CurrentValue), glm::vec2(_Size.x, dh),glm::vec4(1.75f,2,2,1));




}

void IVScroller::OnMouseDown(int but) {
    if (over_drag) {
        _Dragging = true;
    }
}

void IVScroller::OnMouseUp(int but) {
    _Dragging = false;
    over_drag = false;
}

void IVScroller::OnMouseLeave() {
    _Dragging = false;
    over_drag = false;
    if (HasTag("UpDownCursor")) {
 //       RemoveTag("UpDownCursor");
    }
}

void IVScroller::OnMouseDrag(glm::vec2 pos,glm::vec2 delta) {
    
    if (dh >= _Size.y-1){
        return;
    }

    if (_Dragging) {
        int cy = _CurrentValue;
        _CurrentValue += delta.y;
        if (_CurrentValue < 0) {
            _CurrentValue = 0;
        }
        if (_CurrentValue >= _MaxValue) {
            _CurrentValue = _MaxValue - 1;
        }
        if (OnValueChanged)
        {
            OnValueChanged(GetValue());
        }
    }
    else {
        
        if (pos.x >= 0 && pos.x <= _Size.x && pos.y >= _CurrentValue && pos.y <= _CurrentValue+dh)
        {
            over_drag = true;
            //std::cout << "OVER TRUE" << std::endl;
            _Dragging = true;

        }
        else {
            over_drag = false;

            //std::cout << "OVER FALSE" << std::endl; 
        }

    }

}

void IVScroller::OnMouseMove(glm::vec2 pos, glm::vec2 delta) {

    if (pos.x >= 0 && pos.x <= _Size.x && pos.y >= _CurrentValue && pos.y <= _CurrentValue + dh)
    {
     
        //over_drag = true;
        //std::cout << "OVER TRUE" << std::endl;
        //_Dragging = true;

    }
    else {

     
    }

}