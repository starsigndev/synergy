#pragma once
#include "PipelineBase.h"

#include "glm/glm.hpp"

class Camera;
class Node3D;


class PipelineActorDepth :
    public PipelineBase
{
public:
    PipelineActorDepth();
    void Set(Camera* camera, glm::mat4 mvp);
    void Set(Camera* cam, Node3D* node, glm::mat4 mvp, const glm::mat4* bones);
    void Bind(bool second_pass);
private:

    Camera* _Camera;
    glm::mat4 _MVP;
    //Camera* _Camera;
    Node3D* _Node;
    glm::mat4 _BoneMatrices[100];

};

