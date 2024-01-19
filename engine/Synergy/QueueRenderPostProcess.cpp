#include "QueueRenderPostProcess.h"
#include "RenderTarget2D.h"
#include "PostProcess.h"

QueueRenderPostProcess::QueueRenderPostProcess(RenderTarget2D* target,PostProcess* pp)
{

	_Target = target;
	_PP = pp;

}

void QueueRenderPostProcess::Render(Renderer* renderer) {

	
	_PP->SetInput(_Target);
	_PP->PreRender(renderer);
	_PP->Process();

}

RenderTarget2D* QueueRenderPostProcess::GetTarget() {

	return nullptr;

}