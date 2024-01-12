#pragma once
#include "AppState.h"
#include <vector>

class Texture2D;
class SmartDraw;
class SceneGraph;
class Entity;
class Importer;
class Renderer;
class RenderQueue;
class Light;
class Camera;

class Sample1_State : public AppState
{
public:

	void InitState();
	void UpdateState(float dt);
	void RenderState();

private:

	Texture2D* _tex1;
	SmartDraw* _draw;
	SceneGraph* _graph1;
	Entity* _ent1;
	Importer* _imp;
	Renderer* _render;
	RenderQueue* _renderQueue;
	std::vector<Light*> _lights1;
	Camera* _cam1;
	Light* _light1;

};

