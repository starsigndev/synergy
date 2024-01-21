#include "IVScroller.h"
#include <limits>
#include "SynUI.h"
#include "ITheme.h"
#include <iostream>
IVScroller::IVScroller() {

    _MaxValue = 1000;

}

void IVScroller::SetMaxValue(int value) {

	_MaxValue = value;

}

float IVScroller::GetValue() {

    float yi, hd, av, ov;
    float nm = 0;
    float ay = 0;
    float max_V = 0;
    yi = hd = av = ov = av2 = 0.0f;
    dh = 0;

    ov = (float)(_Size.y - (float)_MaxValue) / (float)(_MaxValue);

    if (ov > 0.95)
    {

        ov = 0.95f;
    }
    if (ov < 0.35)
    {
        ov = 0.35f;
    }





    dh = (int)(_Size.y * ov);






    if (_CurrentValue + dh > _Size.y)
    {
        if (dh != std::numeric_limits<float>::infinity())
        {
            _CurrentValue = _Size.y - (int)dh;
            if (_CurrentValue < 0) _CurrentValue = 0;
        }
    }



    max_V = _Size.y - (dh);


    av2 = (((float)_CurrentValue) / max_V);

    return av2;


}

void IVScroller::Render() {

    float v= GetValue();


    auto pos = GetRenderPosition();
    SynUI::Draw(SynUI::Theme->_Frame, pos+glm::vec2(-1,-1), GetSize()+glm::vec2(2,2), glm::vec4(5, 5, 5, 1));
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
}

void IVScroller::OnMouseDrag(glm::vec2 pos,glm::vec2 delta) {
    
    if (_Dragging) {
        int cy = _CurrentValue;
        _CurrentValue += delta.y;
        if (_CurrentValue < 0) {
            _CurrentValue = 0;
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