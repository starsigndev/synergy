#pragma once
#include "IControl.h"

class SceneGraph;
class RenderQueue;
class Renderer;
class Camera;
class Light;
class Entity;
class RenderTarget2D;

class IPreview3D :
    public IControl
{
public:

    IPreview3D(Entity* entity);
    void PreRender();
    void Render();
    void OnMouseDown(int button);
    void OnMouseMove(glm::vec2 pos, glm::vec2 delta);
    void OnMouseUp(int button);
    void Update(float dt);

private:

    SceneGraph* _Graph;
    RenderQueue* _RenderQueue;
    Renderer* _Renderer;
    Camera* _Cam;
    Light* _Light1;
    Entity* _Entity;
    RenderTarget2D* _RT;// = new RenderTarget2D(SynApp::This->GetWidth(), SynApp::This->GetHeight());
    glm::vec3 _Offset;
    glm::vec3 _Start;
    float _Yaw = 0;
    bool _Drag = false;

};

