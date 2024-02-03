#pragma once

class SceneGraph;

enum EditorMode {
	EM_Translate, EM_Rotate, EM_Scale
};

enum SpaceMode
{
	SM_Local,SM_Global
};

class SE_Global
{
public:

	static SpaceMode _SpaceMode;
	static EditorMode _EditMode;
	static SceneGraph* _EditGraph;


};

