#pragma once
#include "PipelineBase.h"
class Material;
class Light;
class Camera;
class Node3D;

class Pipeline3DLight :
    public PipelineBase
{
public:
    Pipeline3DLight();
    void Set(Material* material, Light* light, Camera* cam,Node3D* node, glm::mat4 mvp);
    void Bind(bool second_pass);

private:
    Material* _Material;
    Light* _Light;
    Camera* _Camera;
    Node3D* _Node;
};

