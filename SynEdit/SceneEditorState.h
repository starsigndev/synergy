#pragma once
#include <AppState.h>

class SE_GraphExplorer;
class SE_MainToolbar;
class SE_Viewer;
class SE_MainMenubar;
class SE_NodeEditor;

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
	SE_Viewer* _SceneViewer;
	SE_MainMenubar* _MainMenubar;
	SE_NodeEditor* _NodeEditor;


};

