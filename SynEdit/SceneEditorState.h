#pragma once
#include <AppState.h>

class SE_GraphExplorer;
class SE_MainToolbar;

class SceneEditorState :
    public AppState
{
public:

	void InitState();
	void UpdateState(float dt);
	void RenderState();
	void RebuildUI();

private:

	SE_GraphExplorer* _GraphExplorer;
	SE_MainToolbar* _MainToolbar;


};

