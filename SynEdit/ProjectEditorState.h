#pragma once
#include "AppState.h"

class IImage;
class ITextBox;
class IVideo;

class ProjectEditorState : public AppState
{
public:
	ProjectEditorState() {};
	void InitState();
	void UpdateState(float dt);
	void RenderState();
private:

	IVideo* _MovVid;
	ITextBox* _MovPath;
	IImage* _ProjImg;

};

