#pragma once
#include "Pipeline2D.h"
class PipelineBlur :
    public Pipeline2D
{
public:
    PipelineBlur();
    void Bind(bool second_pass);
    void SetBlur(float blur) {
        _Blur = blur;
    }
private:

    float _Blur;

};

