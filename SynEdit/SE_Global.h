#pragma once

class SceneGraph;

enum EditorMode {
	EM_Translate, EM_Rotate, EM_Scale
};

class SE_Global
{
public:

	static EditorMode _EditMode;
	static SceneGraph* _EditGraph;


};

