#pragma once
#include "Pipeline2D.h"
#include "glm/glm.hpp"
class Texture2D;

class PipelineCombine :
    public Pipeline2D
{
public:
    
    PipelineCombine();
    void Bind(bool second_pass);
    void SetCombine(glm::vec2 combine) {
        _Combine = combine;
    }

private:

    glm::vec2 _Combine;
    Texture2D* _Tex2;

};

