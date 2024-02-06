#pragma once
#include "AppState.h"

class CE_MainMenubar;
class CE_ConvNavigator;
class CE_MainEditor;

class ConvEditorState :
    public AppState
{
public:

	void InitState();
	void UpdateState(float dt);
	void RenderState();
	void RebuildUI();
private:
	CE_MainMenubar* _MainMenubar;
	CE_ConvNavigator* _ConvNavigator;
	CE_MainEditor* _ConvEditor;
};

