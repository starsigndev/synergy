#include "SE_Viewer.h"
#include "RenderTarget2D.h"
#include "IWindowContent.h"
#include "IImage.h"
#include "SceneGraph.h"
#include "RenderQueue.h"
#include "Renderer.h"
#include "Camera.h"
#include "QueueSetCamera.h"
#include "QueueSetLights.h"
#include "QueueRenderScene.h"
#include "QueueRenderShadows.h"
#include "QueueBindRenderTarget2D.h"
#include "QueueReleaseRenderTarget2D.h"
#include "QueueRenderPostProcess.h"
#include "QueuePresentRenderTarget.h"
#include "QueueRenderMeshLines.h"
#include "Light.h"
#include "MeshLines.h"
#include "AppInput.h"
#include "SE_Global.h"

SE_Viewer::SE_Viewer() {


	SetText("Scene Viewer");
	_Graph = new SceneGraph;
	_RenderQueue = new RenderQueue;
	_Renderer = new Renderer;
	_EditCam = new Camera;
	auto l1 = new Light;
	SE_Global::_EditGraph = _Graph;
	std::vector<Light*> lights;

	l1->SetPosition(glm::vec3(1, 10, 2));
	l1->SetDiffuseColor(glm::vec3(0, 2, 2));

	lights.push_back(l1);


	//grid

	auto mesh = new MeshLines;

	int siz = 40;

	int vi = 0;

	for (int x = -siz; x < siz; x++) {

		LineVertex l1, l2;

		l1.position = glm::vec3(-x, 0, -siz);
		l2.position = glm::vec3(-x, 0, siz);
		l1.color = glm::vec4(0.4,0.4, 0.4, 1);
		l2.color = glm::vec4(0.4,0.4,0.4, 1);

		mesh->AddVertex(l1);
		mesh->AddVertex(l2);

		Line l;
		l.V0 = vi;
		l.V1 = vi + 1; 

		mesh->AddLine(l);

		vi += 2;

	}

	for (int z = -siz; z < siz; z++) {

		LineVertex l1, l2;

		l1.position = glm::vec3(-siz, 0,z);
		l2.position = glm::vec3(siz, 0, z);
		l1.color = glm::vec4(0.4,0.4,0.4, 1);
		l2.color = glm::vec4(0.4,0.4,0.4, 1);

		mesh->AddVertex(l1);
		mesh->AddVertex(l2);

		Line l;
		l.V0 = vi;
		l.V1 = vi + 1;

		mesh->AddLine(l);

		vi += 2;

	}

	for (int x = -siz; x < siz; x+=4) {

		LineVertex l1, l2;

		l1.position = glm::vec3(-x, 0, -siz);
		l2.position = glm::vec3(-x, 0, siz);
		l1.color = glm::vec4(1, 1, 1, 1);
		l2.color = glm::vec4(1, 1, 1, 1);

		mesh->AddVertex(l1);
		mesh->AddVertex(l2);

		Line l;
		l.V0 = vi;
		l.V1 = vi + 1;

		mesh->AddLine(l);

		vi += 2;

	}

	for (int z = -siz; z < siz; z += 4) {

		LineVertex l1, l2;

		l1.position = glm::vec3(-siz, 0, z);
		l2.position = glm::vec3(siz, 0, z);
		l1.color = glm::vec4(1, 1, 1, 1);
		l2.color = glm::vec4(1, 1, 1, 1);

		mesh->AddVertex(l1);
		mesh->AddVertex(l2);

		Line l;
		l.V0 = vi;
		l.V1 = vi + 1;

		mesh->AddLine(l);

		vi += 2;

	}


	mesh->CreateBuffer();

	//

	auto setCamera = new QueueSetCamera(_EditCam);
	auto setLights = new QueueSetLights(lights);
	auto renderScene = new QueueRenderScene(_Graph);
	auto renderShadows = new QueueRenderShadows(_Graph);
	auto renderGrid = new QueueRenderMeshLines(mesh);
	_BindRT = new QueueBindRenderTarget2D(_RT);
	_ReleaseRT = new QueueReleaseRenderTarget2D(_RT);


	_EditCam->SetPosition(glm::vec3(0, 5, 10));

	//auto renPP = new QueueRenderPostProcess(_rt1, _ppDOF);
//	auto pRT = new QueuePresentRenderTarget(_ppDOF->GetOutput());

	_RenderQueue->AddNode(setCamera);
	_RenderQueue->AddNode(setLights);
	_RenderQueue->AddNode(renderShadows);
	_RenderQueue->AddNode(_BindRT);
	_RenderQueue->AddNode(renderGrid);
	_RenderQueue->AddNode(renderScene);
	_RenderQueue->AddNode(_ReleaseRT);
	//_RenderQueue->AddNode(renPP);
	//_RenderQueue->AddNode(pRT);



}

void SE_Viewer::SizeChanged() {

	IWindow::SizeChanged();

	_RT = new RenderTarget2D(_Size.x, _Size.y);

	_BindRT->BindRT(_RT);
	_ReleaseRT->BindRT(_RT);

	_Content->ClearControls();

	_Output = new IImage(_RT->GetTexture2D());

	_Content->AddControl(_Output);
	_Output->Set(glm::vec2(0, 0), glm::vec2(_Size.x, _Size.y), "");



}

void SE_Viewer::PreRender() {

	_Renderer->Render(_RenderQueue);

	//	_RT->Bind();

		//_RT->Release();


}

void SE_Viewer::Update(float dt) {

	if (InBounds(AppInput::_MousePosition))
	{
		if (AppInput::_ButtonState[1])
		{

			_CamPitch -= AppInput::_MouseDelta.y * 0.25f;
			_CamYaw -= AppInput::_MouseDelta.x * 0.25f;

			_EditCam->Rotate(_CamPitch, _CamYaw, 0);

		}
	}

}