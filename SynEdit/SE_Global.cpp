#include "SE_Global.h"
#include "SceneGraph.h"

EditorMode SE_Global::_EditMode = EM_Translate;
SpaceMode SE_Global::_SpaceMode = SM_Local;
SceneGraph* SE_Global::_EditGraph = nullptr;