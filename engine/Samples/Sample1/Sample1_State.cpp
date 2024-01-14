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
#include "QueueRenderShadows.h"
#include "Light.h"
#include "Camera.h"
#include "Actor.h"
#include "QueueBindRenderTarget2D.h"
#include "QueueReleaseRenderTarget2D.h"
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
	_act1 = (Actor*)_imp->ImportActor("test/walk1.fbx");
	_render = new Renderer;
	_renderQueue = new RenderQueue;
	_graph1->AddNode(_ent1);
	_graph1->AddNode(_act1);
	_act1->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	
	 _light1 = new Light;
	 auto _light2 = new Light;


	_light1->SetPosition(glm::vec3(0, 10, 4));
	_light2->SetPosition(glm::vec3(2, 10, -10));

	_lights1.push_back(_light1);
	_lights1.push_back(_light2);

	
	_cam1 = new Camera;

	_light1->SetDiffuseColor(glm::vec3(1, 1, 1));
	_light2->SetDiffuseColor(glm::vec3(1, 3, 3));

	_rt1 = new RenderTarget2D(512, 512);

	auto setCamera = new QueueSetCamera(_cam1);
	auto setLights = new QueueSetLights(_lights1);
	auto renderScene = new QueueRenderScene(_graph1);
	auto renderShadows = new QueueRenderShadows(_graph1);
	auto bindRT = new QueueBindRenderTarget2D(_rt1);
	auto relRT = new QueueReleaseRenderTarget2D(_rt1);

	_renderQueue->AddNode(setCamera);
	_renderQueue->AddNode(setLights);
	_renderQueue->AddNode(renderShadows);
	_renderQueue->AddNode(bindRT);
	_renderQueue->AddNode(renderScene);
	_renderQueue->AddNode(relRT);

	_cam1->SetPosition(glm::vec3(0, 0, 10));

	rot = glm::vec3(0, 0, 0);



}

void Sample1_State::UpdateState(float dt) {

	_graph1->Update(dt);
	rot.y = rot.y + 0.1f;
	cam_rot.x -= AppInput::_MouseDelta.y * 0.25f;// *dt;
	cam_rot.y -= AppInput::_MouseDelta.x * 0.25f;// *dt;

	if (AppInput::_KeyState[GLFW_KEY_W])
	{
		_cam1->Move(glm::vec3(0, 0, -16.0f*dt));
	}

	if (AppInput::_KeyState[GLFW_KEY_S])
	{
		_cam1->Move(glm::vec3(0, 0, 16.0f*dt));
	}

	if (AppInput::_KeyState[GLFW_KEY_A])
	{
		_cam1->Move(glm::vec3(-16.0f*dt, 0, 0));
	}

	if (AppInput::_KeyState[GLFW_KEY_D])
	{
		_cam1->Move(glm::vec3(16.0f*dt, 0, 0));
	}

	if (AppInput::_KeyState[GLFW_KEY_SPACE]) {

		_light1->SetPosition(_cam1->GetPosition());

	}

	//	_ent1->SetPosition(glm::vec3(3, 0, 0));
	//	_ent1->Rotate(rot);

	_cam1->Rotate(cam_rot);

}

void Sample1_State::RenderState() {

	
	_draw->SetView(SynApp::This->GetWidth(), SynApp::This->GetHeight());

	_render->Render(_renderQueue);

	
	auto tex = _rt1->GetTexture2D();


	
	_draw->Begin();

	_draw->DrawQuad(tex, glm::vec2(0, 0), glm::vec2(512, 512), glm::vec4(1, 1, 1, 1));

	_draw->End();


}