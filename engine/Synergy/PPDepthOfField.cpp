#include "PPDepthOfField.h"
#include "SynApp.h"
#include "RenderTarget2D.h"
#include "Renderer.h"
#include "PipelineDOF.h"

PPDepthOfField::PPDepthOfField() {


	_DOF = new PipelineDOF;

	CreateTargets(SynApp::This->GetWidth(),SynApp::This->GetHeight(), 2);

	_Output = GetTarget(1);
	
	//_Output = _Input;


}

void PPDepthOfField::PreRender(Renderer* renderer)
{

	BindTarget(0);


	renderer->RenderGraphDepth(renderer->GetGraph());

	ReleaseTarget(0);




}

void PPDepthOfField::Process() {


	//_Output = _Input;
	_DOF->SetAuxTex(_Input->GetTexture2D());


	BindTarget(1);


	Present(GetTarget(0), _DOF);

	ReleaseTarget(1);

}