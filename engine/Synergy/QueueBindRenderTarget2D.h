#pragma once
#include "QueueNode.h"

class RenderTarget2D;

class QueueBindRenderTarget2D :
    public QueueNode
{
public:

    QueueBindRenderTarget2D(RenderTarget2D* target);
    void Render(Renderer* renderer);
    void BindRT(RenderTarget2D* target)
    {
        _RenderTarget = target;
    }
private:

    RenderTarget2D* _RenderTarget;

};

