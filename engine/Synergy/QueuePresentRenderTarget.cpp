#include "QueuePresentRenderTarget.h"
#include "RenderTarget2D.h"
#include "SmartDraw.h"
#include "SynApp.h"

QueuePresentRenderTarget::QueuePresentRenderTarget(RenderTarget2D* target)
{

	_Target = target;
	_Draw = new SmartDraw();
	}

void QueuePresentRenderTarget::Render(Renderer* renderer) {

	_Draw->SetView(SynApp::This->GetWidth(), SynApp::This->GetHeight());
	_Draw->Begin();
	_Draw->DrawQuad(_Target->GetTexture2D(), glm::vec2(0, 0), glm::vec2(SynApp::This->GetWidth(), SynApp::This->GetHeight()), glm::vec4(1, 1, 1, 1));
	_Draw->End();

}