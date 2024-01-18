#include "PPBloom.h"
#include "SynApp.h"
#include "PipelineColorLimit.h"
#include "PipelineBlur.h"
#include "PipelineCombine.h"

PPBloom::PPBloom() {

	//CreateTargets(SynApp::This->GetWidth()/4, SynApp::This->GetHeight()/4, 3);
	AddTarget(512, 512);
	AddTarget(512, 512);
	AddTarget(SynApp::This->GetWidth(), SynApp::This->GetHeight());
	_ColorLimit = new PipelineColorLimit;

	_Blur = new PipelineBlur;
	_Combine = new PipelineCombine;
	_Output = GetTarget(2);

}

void PPBloom::Process() {

	
	_ColorLimit->SetColorLimit(glm::vec4(0.93f, 0.93f, 0.93f, 1.0f));
	_Blur->SetBlur(0.0035f);

	

	
	BindTarget(0);
	
	Present(_Input,(Pipeline2D*)_ColorLimit);

	ReleaseTarget(0);

	//return;

	BindTarget(1);

	Present(GetTarget(0), (Pipeline2D*)_Blur);

	ReleaseTarget(1);

	
	

	_Combine->SetAuxTex(_Input->GetTexture2D());

	BindTarget(2);

	Present(GetTarget(1), (Pipeline2D*)_Combine);

	ReleaseTarget(2);

	return;

	

}