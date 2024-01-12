#pragma once
#include "QueueNode.h"

class Camera;

class QueueSetCamera :
    public QueueNode
{
public:
    QueueSetCamera(Camera* camera);
    void Render(Renderer* renderer);

private:

    Camera* _Camera;

};

