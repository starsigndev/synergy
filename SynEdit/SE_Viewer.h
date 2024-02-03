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
class SE_Viewport;
class Entity;

class SE_Viewer :
    public IWindow
{
public:
    SE_Viewer();
    void PreRender();
    void SizeChanged();
    void Update(float dt);
private:

    SceneGraph* _Graph;
   


};

