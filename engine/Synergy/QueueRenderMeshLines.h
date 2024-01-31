#pragma once
#include "QueueNode.h"

class MeshLines;
class Renderer;

class QueueRenderMeshLines : public QueueNode
{
public:

	QueueRenderMeshLines(MeshLines* mesh);
	void Render(Renderer* renderer);

private:

	MeshLines* _MeshLines;

};

