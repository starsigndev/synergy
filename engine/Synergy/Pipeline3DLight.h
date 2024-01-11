#pragma once
#include "PipelineBase.h"
class Pipeline3DLight :
    public PipelineBase
{
public:
    Pipeline3DLight();

    void Bind(bool second_pass);
};

