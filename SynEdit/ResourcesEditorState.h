#pragma once
#include <AppState.h>
class ResourcesEditorState :
    public AppState
{
public:
public:
	ResourcesEditorState() {};
	void InitState();
	void UpdateState(float dt);
	void RenderState();
};

