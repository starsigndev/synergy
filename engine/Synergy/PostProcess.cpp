#include "PostProcess.h"
#include "RenderTarget2D.h"
#include "SmartDraw.h"
#include "SynApp.h"
#include "PipelineBase.h"

PostProcess::PostProcess() {

	_Draw = new SmartDraw;

}

void PostProcess::SetInput(RenderTarget2D* input) {

	_Input = input;

}

void PostProcess::CreateTargets(int width,int height,int num) {

	for (int i = 0; i < num; i++) {

		_Targets.push_back(new RenderTarget2D(width, height));

	}

}

void PostProcess::AddTarget(int width, int height) {

	_Targets.push_back(new RenderTarget2D(width, height));

}

void PostProcess::BindTarget(int index) {

	_Targets[index]->Bind();

}

void PostProcess::ReleaseTarget(int index) {

	_Targets[index]->Release();

}

RenderTarget2D* PostProcess::GetOutput() {

	return _Output;

}

void PostProcess::Present(int index,Pipeline2D* pipeline) {

	_Draw->Begin();
	_Draw->DrawQuad(_Targets[index]->GetTexture2D(), glm::vec2(0, 0), glm::vec2(SynApp::This->GetWidth(), SynApp::This->GetHeight()), glm::vec4(1, 1, 1, 1));
	_Draw->End(pipeline);

}

void PostProcess::Present(RenderTarget2D* target,Pipeline2D* pipeline)
{


	_Draw->SetView(SynApp::This->GetWidth(), SynApp::This->GetHeight());
	_Draw->Begin();
	_Draw->DrawQuad(target->GetTexture2D(), glm::vec2(0, 0), glm::vec2(SynApp::This->GetWidth(), SynApp::This->GetHeight()), glm::vec4(1, 1, 1, 1));
	_Draw->End(pipeline);


}

void PostProcess::Process() {


}

RenderTarget2D* PostProcess::GetTarget(int index) {

	return _Targets[index];

}