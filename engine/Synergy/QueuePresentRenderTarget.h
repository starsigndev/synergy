#pragma once
#include "QueueNode.h"

class RenderTarget2D;
class SmartDraw;

class QueuePresentRenderTarget :
    public QueueNode
{
public:

    QueuePresentRenderTarget(RenderTarget2D* target);
    void Render(Renderer* renderer);


private:

    RenderTarget2D* _Target;
    SmartDraw* _Draw;

};

