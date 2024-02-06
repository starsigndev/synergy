#pragma once

class SceneGraph;
class Node3D;

enum EditorMode {
	EM_Translate, EM_Rotate, EM_Scale
};

enum SpaceMode
{
	SM_Local,SM_Global
};

enum PlayMode {
	PM_None,PM_Playing,PM_Paused
};

class SE_Global
{
public:

	static SpaceMode _SpaceMode;
	static EditorMode _EditMode;
	static SceneGraph* _EditGraph;
	static Node3D* _SelectedNode;
	static PlayMode _PlayMode;
	static void PlayScene();
	static void StopScene();
	static void UpdateScene(float dt);


};

