#include "SE_Global.h"
#include "SceneGraph.h"

EditorMode SE_Global::_EditMode = EM_Translate;
SpaceMode SE_Global::_SpaceMode = SM_Local;
PlayMode SE_Global::_PlayMode = PM_None;
SceneGraph* SE_Global::_EditGraph = nullptr;


void SE_Global::PlayScene() {

	if (_PlayMode == PM_Playing) {
		return;
	}
	int b = 5;
	_PlayMode = PM_Playing;
	_EditGraph->BeginPlay();

}

void SE_Global::StopScene() {

	if (_PlayMode != PM_Playing) return;
	_PlayMode = PM_None;
	_EditGraph->StopPlay();

}


void SE_Global::UpdateScene(float dt)
{

	if (_PlayMode != PM_Playing) {
		return;
	}

	_EditGraph->UpdatePlay(dt);

}