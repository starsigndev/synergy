#include "QueueReleaseRenderTarget2D.h"

#include "RenderTarget2D.h"

QueueReleaseRenderTarget2D::QueueReleaseRenderTarget2D(RenderTarget2D* target)
{

	_RenderTarget = target;

}

void QueueReleaseRenderTarget2D::Render(Renderer* renderer) {

	_RenderTarget->Release();

}