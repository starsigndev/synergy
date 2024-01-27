#pragma once
#include "AppState.h"

class GeneralOSState : public AppState
{
public:
	GeneralOSState() {};
	void InitState();
	void UpdateState(float dt);
	void RenderState();
};

