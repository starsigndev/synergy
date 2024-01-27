#pragma once
#include "AppState.h"
class MainEditorState : public AppState
{
public:

	MainEditorState() {};
	void InitState();
	void UpdateState(float dt);
	void RenderState();


};

