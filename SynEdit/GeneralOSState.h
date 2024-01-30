#pragma once
#include "AppState.h"

class IWindow;
class IButton;

class GeneralOSState : public AppState
{
public:
	GeneralOSState() {};
	void InitState();
	void UpdateState(float dt);
	void RenderState();

private:

	IWindow* _ToolWindow;
	
	//Tools
	IButton* _ProjectEditor;
	IButton* _ResourceEditor;
	IButton* _ResourceTester;
	IButton* _SceneEditor;


};

