#pragma once
#include <IWindowContent.h>

class RenderTarget2D;
class IImage;
class SceneGraph;
class RenderQueue;
class Renderer;
class Camera;
class QueueBindRenderTarget2D;
class QueueReleaseRenderTarget2D;
class QueueRenderEntity;
class MeshLines;
class SE_Viewport;
class Entity;
class Node3D;

class SE_Viewport :
    public IWindowContent
{
public:

    SE_Viewport();
    void PreRender();
    void SizeChanged();
    void Update(float dt);
    void Render();
    void OnMouseDown(int button);
    void OnMouseUp(int button);
    void OnMouseMove(glm::vec2 pos, glm::vec2 delta);
    void OnMouseLeave();
    void KeyPressed(int i);
    void SetShift(bool enable)
    {
        _Shift = enable;
    }
private:
    RenderTarget2D* _RT;
    IImage* _Output;
    float _TimeDelta;
    SceneGraph* _Graph;
    RenderQueue* _RenderQueue;
    Renderer* _Renderer;
    Camera* _EditCam;
    QueueBindRenderTarget2D* _BindRT;
    QueueReleaseRenderTarget2D* _ReleaseRT;
    QueueRenderEntity* _RenderGizmo;
    SE_Viewport* _Viewport;
    glm::vec2 mousePos;
    //Grid
    MeshLines* _ViewGrid;
    bool _Drag = false;
    bool _Shift = false;
    //Cam
    float _CamYaw = 0, _CamPitch = 0;
    Entity* _GizTranslate;
    Entity* _GizRotate;
    Entity* _GizScale;
    Entity* _CurrentGizmo;
    Node3D* _SelectedNode = nullptr;
    bool _GX=false, _GY=false, _GZ = false;

};

