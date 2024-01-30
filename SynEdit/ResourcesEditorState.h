#pragma once
#include <AppState.h>

#include "ITreeView.h"

class IWindow;

class ResourcesEditorState :
    public AppState
{

public:
	ResourcesEditorState() {};
	void InitState();
	void UpdateState(float dt);
	void RenderState();
	void RebuildUI();
	static void NewGroup(std::string name);

	TreeItem* _Root;
	ITreeView* _ResTree = nullptr;

	static ResourcesEditorState* Editor;

	IWindow* _PreviewWin;
};



