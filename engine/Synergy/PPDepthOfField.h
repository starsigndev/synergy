#pragma once
#include "PostProcess.h"

class PipelineDOF;

class PPDepthOfField :
    public PostProcess
{
public:
    PPDepthOfField();
    void Process();
    void PreRender(Renderer* renderer);
private:
    
    PipelineDOF* _DOF;

};

