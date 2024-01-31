#pragma once
#include "QueueNode.h"

class RenderTarget2D;

class QueueReleaseRenderTarget2D :
    public QueueNode
{
public:

    QueueReleaseRenderTarget2D(RenderTarget2D* target);
        void Render(Renderer* renderer);
        void BindRT(RenderTarget2D* target)
        {
            _RenderTarget = target;
        }
private:

    RenderTarget2D* _RenderTarget;

};

