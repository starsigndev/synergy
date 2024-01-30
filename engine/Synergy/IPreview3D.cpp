#include "IPreview3D.h"
#include "SceneGraph.h"
#include "RenderQueue.h"
#include "Renderer.h"
#include "Camera.h"
#include "Light.h"
#include "Entity.h"
#include "SynUI.h"
#include "ITheme.h"
#include "RenderTarget2D.h"
#include "QueueSetCamera.h"
#include "QueueSetLights.h"
#include "QueueRenderScene.h"
#include "QueueRenderShadows.h"
#include "QueueBindRenderTarget2D.h"
#include "QueueReleaseRenderTarget2D.h"
#include "QueueRenderPostProcess.h"
#include "QueuePresentRenderTarget.h"
IPreview3D::IPreview3D(Entity* entity) {

	_Graph = new SceneGraph;
	_RenderQueue = new RenderQueue;
	_Renderer = new Renderer;
	_Cam = new Camera;
	_Light1 = new Light;
	_Entity = entity;



	_Graph->AddNode(_Entity);
	_Renderer->SetGraph(_Graph);
	_Light1 = new Light;
	auto _light2 = new Light;


	_Light1->SetPosition(glm::vec3(0, 10, 4));
	_light2->SetPosition(glm::vec3(2, 10, -10));

	std::vector<Light*> _lights1;

	_lights1.push_back(_Light1);
	_lights1.push_back(_light2);
	_Outline = true;

	
	_Cam = new Camera;

	_RT = new RenderTarget2D(1024,1024);

	auto setCamera = new QueueSetCamera(_Cam);
	auto setLights = new QueueSetLights(_lights1);
	auto renderScene = new QueueRenderScene(_Graph);
	auto renderShadows = new QueueRenderShadows(_Graph);
	auto bindRT = new QueueBindRenderTarget2D(_RT);
	auto relRT = new QueueReleaseRenderTarget2D(_RT);
	//auto renPP = new QueueRenderPostProcess(_rt1, _ppDOF);
	//auto pRT = new QueuePresentRenderTarget(_ppDOF->GetOutput());

	_RenderQueue->AddNode(setCamera);
	_RenderQueue->AddNode(setLights);
	_RenderQueue->AddNode(renderShadows);
	_RenderQueue->AddNode(bindRT);
	_RenderQueue->AddNode(renderScene);
	_RenderQueue->AddNode(relRT);

	_Cam->SetPosition(glm::vec3(0, 5, 10));

	_Start = glm::vec3(0, 5, 10);


}

void IPreview3D::PreRender() {

	int b = 5;
	_Renderer->Render(_RenderQueue);

}

void IPreview3D::Render() {

	auto pos = GetRenderPosition();

	SynUI::Draw(_RT->GetTexture2D(), pos, GetSize(), glm::vec4(1, 1, 1, 1));

}

void IPreview3D::OnMouseDown(int button) {

	_Drag = true;

}

void IPreview3D::OnMouseUp(int button)
{

	_Drag = false;

}

void IPreview3D::OnMouseMove(glm::vec2 pos, glm::vec2 delta) {

	
	delta = delta * 0.03f;

	if (_Drag) {

		_Offset = _Offset + glm::vec3(delta.x, delta.y, 0);

		if (_Offset.x < -2)
		{
			_Offset.x = -2;
		}
		if (_Offset.x > 2)
		{
			_Offset.x = 2;
		}
		if (_Offset.y < -2) {
			_Offset.y = -2;
		}
		if (_Offset.y > 2)
		{
			_Offset.y = 2;
		}

	}

}

void IPreview3D::Update(float dt) {

	if (!_Drag) {
		_Offset = _Offset + (glm::vec3(0, 0, 0) - _Offset) * 0.8f * dt;
	}
	_Yaw += 15.0f * dt;
	_Cam->SetPosition(_Start+_Offset);
	_Cam->LookAt(glm::vec3(0, 0, 0));
	_Entity->Rotate(0, _Yaw, 0);



}