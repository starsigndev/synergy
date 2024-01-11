#pragma once

#include "QueueNode.h"

class SceneGraph;
class Renderer;
class Node3D;
class Entity;

class QueueRenderScene : public QueueNode
{
public:

	QueueRenderScene(SceneGraph* graph);
	void Render(Renderer* renderer);

private:

	void RenderNode(Renderer* renderer,Node3D* node);

	SceneGraph* _Graph;

};

