#pragma once

#include "PipelineBase.h"

class Pipeline2D : public PipelineBase
{
public:
	Pipeline2D();

	void Bind(bool second_pass);

};

