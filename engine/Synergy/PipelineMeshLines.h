#pragma once
#include "PipelineBase.h"
class PipelineMeshLines :
    public PipelineBase
{
public:

    PipelineMeshLines();
    void Set(glm::mat4 mvp);
    void Bind(bool sp);

};

