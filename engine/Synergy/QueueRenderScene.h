#pragma once

#include "QueueNode.h"

class SceneGraph;
class Renderer;

class QueueRenderScene : public QueueNode
{
public:

	QueueRenderScene(SceneGraph* graph);
	void Render(Renderer* renderer);

private:

	SceneGraph* _Graph;

};

