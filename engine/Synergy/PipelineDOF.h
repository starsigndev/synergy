#pragma once
#include "Pipeline2D.h"
class PipelineDOF :
    public Pipeline2D
{
public:

    PipelineDOF();
    void Bind(bool sp);
    void SetDOF(float focus, float range, float blur)
    {
        _DOF = glm::vec4(focus, range, blur, 0);
    }

private:

    glm::vec4 _DOF;

};

