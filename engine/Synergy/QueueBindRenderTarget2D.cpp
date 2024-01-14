#include "QueueBindRenderTarget2D.h"

#include "RenderTarget2D.h"

QueueBindRenderTarget2D::QueueBindRenderTarget2D(RenderTarget2D* target)
{
	_RenderTarget = target;
}

void QueueBindRenderTarget2D::Render(Renderer* renderer) {

	_RenderTarget->Bind();

}