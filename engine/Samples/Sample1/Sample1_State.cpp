#include "Sample1_State.h"
#include <iostream>
#include "Texture2D.h"
#include "SmartDraw.h"
#include "SynApp.h"
#include "RndNum.h"
#include "SceneGraph.h"
#include "Entity.h"
#include "Importer.h"
#include "Renderer.h"
#include "RenderQueue.h"
#include "QueueSetCamera.h"
#include "QueueSetLights.h"
#include "QueueRenderScene.h"
#include "Light.h"
#include "Camera.h"
#include "AppInput.h"

glm::vec3 rot;

glm::vec3 cam_rot;

void Sample1_State::InitState() {

	cam_rot = glm::vec3(0, 0, 0);
	std::cout << "State initialized." << std::endl;
	_tex1 = new Texture2D("test/test1.png");
	_draw = new SmartDraw;
	_graph1 = new SceneGraph;
	_imp = new Importer;
	_ent1 = (Entity*)_imp->ImportNode("test/ent1.fbx");
	_render = new Renderer;
	_renderQueue = new RenderQueue;
	_graph1->AddNode(_ent1);
	
	auto _light1 = new Light;

	_lights1.push_back(_light1);
	_cam1 = new Camera;

	auto setCamera = new QueueSetCamera(_cam1);
	auto setLights = new QueueSetLights(_lights1);
	auto renderScene = new QueueRenderScene(_graph1);

	_renderQueue->AddNode(setCamera);
	_renderQueue->AddNode(setLights);
	_renderQueue->AddNode(renderScene);

	_cam1->SetPosition(glm::vec3(0, 0, 10));

	rot = glm::vec3(0, 0, 0);

}

void Sample1_State::UpdateState() {

}

void Sample1_State::RenderState() {

	rot.y = rot.y + 0.1f;
	cam_rot.x -= AppInput::_MouseDelta.y * 0.1f;
	cam_rot.y -= AppInput::_MouseDelta.x * 0.1f;

	if (AppInput::_KeyState[GLFW_KEY_W])
	{
		_cam1->Move(glm::vec3(0, 0, -0.1f));
	}

	if (AppInput::_KeyState[GLFW_KEY_S])
	{
		_cam1->Move(glm::vec3(0, 0, 0.1f));
	}

	if (AppInput::_KeyState[GLFW_KEY_A])
	{
		_cam1->Move(glm::vec3(-0.1f, 0,0));
	}

	if (AppInput::_KeyState[GLFW_KEY_D])
	{
		_cam1->Move(glm::vec3(0.1f, 0, 0));
	}

	_ent1->SetPosition(glm::vec3(3, 0, 0));
	_ent1->Rotate(rot);

	_cam1->Rotate(cam_rot);

	_draw->SetView(SynApp::This->GetWidth(), SynApp::This->GetHeight());

	_render->Render(_renderQueue);


}