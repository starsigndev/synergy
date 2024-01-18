#pragma once
#include "PostProcess.h"

class PipelineColorLimit;
class PipelineBlur;
class PipelineCombine;

class PPBloom : public PostProcess
{
public:

	PPBloom();
	void Process();

private:

	PipelineColorLimit* _ColorLimit;
	PipelineBlur* _Blur;
	PipelineCombine* _Combine;
};

