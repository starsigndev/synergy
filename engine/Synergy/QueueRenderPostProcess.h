#pragma once
#include "QueueNode.h"

class RenderTarget2D;
class PostProcess;

class QueueRenderPostProcess : public QueueNode
{
public:

	QueueRenderPostProcess(RenderTarget2D* target,PostProcess* pp);
	void Render(Renderer* renderer);
	RenderTarget2D* GetTarget();


private:

	RenderTarget2D* _Target;
	PostProcess* _PP;

};

