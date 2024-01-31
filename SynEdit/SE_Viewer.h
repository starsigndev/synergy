#pragma once
#include <IWindow.h>

class RenderTarget2D;
class IImage;
class SceneGraph;
class RenderQueue;
class Renderer;
class Camera;
class QueueBindRenderTarget2D;
class QueueReleaseRenderTarget2D;
class MeshLines;

class SE_Viewer :
    public IWindow
{
public:
    SE_Viewer();
    void PreRender();
    void SizeChanged();
    void Update(float dt);
private:

    RenderTarget2D* _RT;
    IImage* _Output;

    SceneGraph* _Graph;
    RenderQueue* _RenderQueue;
    Renderer* _Renderer;
    Camera* _EditCam;
    QueueBindRenderTarget2D* _BindRT;
    QueueReleaseRenderTarget2D* _ReleaseRT;

    //Grid
    MeshLines* _ViewGrid;

    //Cam
    float _CamYaw=0, _CamPitch = 0;


};

