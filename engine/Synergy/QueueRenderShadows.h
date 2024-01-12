#pragma once
#include "QueueNode.h"

class Renderer;
class SceneGraph;

class QueueRenderShadows :
    public QueueNode
{
public:

    QueueRenderShadows(SceneGraph* graph);
    void Render(Renderer* renderer);

private:

    SceneGraph* _Graph;

};

