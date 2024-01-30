#pragma once
#include <AppState.h>

#include "ITreeView.h"

class IWindow;

class ResourcesTesterState :
    public AppState
{
public:
	ResourcesTesterState() {};
	void InitState();
	void UpdateState(float dt);
	void RenderState();
	void RebuildUI();
private:

	TreeItem* _Root;
	ITreeView* _ResTree = nullptr;

	static ResourcesTesterState* Editor;

	IWindow* _PreviewWin;

};

