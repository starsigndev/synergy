#pragma once
#include "QueueNode.h"

class Renderer;

class QueueClearZ :
    public QueueNode
{
public:

    void Render(Renderer* renderer);

};

