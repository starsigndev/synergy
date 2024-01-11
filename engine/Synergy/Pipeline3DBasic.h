#pragma once
#include "PipelineBase.h"

class Material;

class Pipeline3DBasic :
    public PipelineBase
{
public:
    Pipeline3DBasic();
    void Set(Material* material,glm::mat4 mvp);
    void Bind(bool second_pass);

private:
    
    Material* _Material;

};

