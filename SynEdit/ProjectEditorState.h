#pragma once
#include "AppState.h"
class ProjectEditorState : public AppState
{
public:
	ProjectEditorState() {};
	void InitState();
	void UpdateState(float dt);
	void RenderState();
private:
};

