#pragma once
#include "Pipeline2D.h"
class PipelineColorLimit :
    public Pipeline2D
{
public:

    PipelineColorLimit();
    void Bind(bool second_pass);
    void SetColorLimit(glm::vec4 color);

private:

    glm::vec4 _ColorLimit;

};

