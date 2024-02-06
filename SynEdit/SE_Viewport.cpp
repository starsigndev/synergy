#include "SE_Viewport.h"
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
#include "QueueRenderEntity.h"
#include "QueueClearZ.h"
#include "Light.h"
#include "Entity.h"
#include "SE_NodeEditor.h"
#include "MeshLines.h"
#include "AppInput.h"
#include "SE_Global.h"
#include "SynUI.h"
#include "Importer.h"
#include "GLFW/glfw3.h"

SE_Viewport::SE_Viewport() {

	

	Importer* imp = new Importer;

	_GizTranslate = (Entity*)imp->ImportNode("project/gizmo/translate1.fbx");
	_GizRotate = (Entity*)imp->ImportNode("project/gizmo/rotate1.fbx");
	_GizScale = (Entity*)imp->ImportNode("project/gizmo/scale1.fbx");
	_CurrentGizmo = _GizTranslate;

	_Graph = new SceneGraph;
	SE_Global::_EditGraph = _Graph;
	_RenderQueue = new RenderQueue;
	_Renderer = new Renderer;
	_EditCam = new Camera;
	auto l1 = new Light;
	
	std::vector<Light*> lights;

//	_Viewport = new SE_Viewport;

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
		l1.color = glm::vec4(0.4, 0.4, 0.4, 1);
		l2.color = glm::vec4(0.4, 0.4, 0.4, 1);

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

		l1.position = glm::vec3(-siz, 0, z);
		l2.position = glm::vec3(siz, 0, z);
		l1.color = glm::vec4(0.4, 0.4, 0.4, 1);
		l2.color = glm::vec4(0.4, 0.4, 0.4, 1);

		mesh->AddVertex(l1);
		mesh->AddVertex(l2);

		Line l;
		l.V0 = vi;
		l.V1 = vi + 1;

		mesh->AddLine(l);

		vi += 2;

	}

	for (int x = -siz; x < siz; x += 4) {

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
	_RenderGizmo = new QueueRenderEntity(nullptr);

	_EditCam->SetPosition(glm::vec3(0, 5, 10));

	//auto renPP = new QueueRenderPostProcess(_rt1, _ppDOF);
//	auto pRT = new QueuePresentRenderTarget(_ppDOF->GetOutput());

	_RenderQueue->AddNode(setCamera);
	_RenderQueue->AddNode(setLights);
	_RenderQueue->AddNode(renderShadows);
	_RenderQueue->AddNode(_BindRT);
	_RenderQueue->AddNode(renderGrid);
	_RenderQueue->AddNode(renderScene);
	_RenderQueue->AddNode(new QueueClearZ);
	_RenderQueue->AddNode(_RenderGizmo);
	_RenderQueue->AddNode(_ReleaseRT);
	//_RenderQueue->AddNode(renPP);
	//_RenderQueue->AddNode(pRT);
	_RenderGizmo->SetEntity(_GizTranslate);

}

void SE_Viewport::SizeChanged() {

	if (_Size.x == 0 || _Size.y == 0) {

		return;

	}
	IWindowContent::SizeChanged();
	_RT = new RenderTarget2D(_Size.x, _Size.y);

	_BindRT->BindRT(_RT);
	_ReleaseRT->BindRT(_RT);

	//ClearControls();

//	_Output = new IImage(_RT->GetTexture2D());

//	_Content->AddControl(_Output);
	//_Output->Set(glm::vec2(0, 0), glm::vec2(_Size.x, _Size.y), "");




}

void SE_Viewport::PreRender() {


	_Renderer->Render(_RenderQueue);

}

void SE_Viewport::Update(float dt) {

	SE_Global::UpdateScene(dt);

	switch (SE_Global::_EditMode) {
	case EditorMode::EM_Translate:
		
		_CurrentGizmo = _GizTranslate;
		
		break;
	case EditorMode::EM_Rotate:
		
		_CurrentGizmo = _GizRotate;

		break;
	case EditorMode::EM_Scale:
		
		_CurrentGizmo = _GizScale;

		break;
	}

	_RenderGizmo->SetEntity(_CurrentGizmo);

	_TimeDelta = dt;
	if (_SelectedNode != nullptr) {
		_CurrentGizmo->SetPosition(_SelectedNode->GetPosition());
		if (SE_Global::_SpaceMode == SM_Local)
		{
			_CurrentGizmo->SetRotation(_SelectedNode->GetRotation());
		}
		else {
			_CurrentGizmo->Rotate(0, 0, 0);
		}
		_RenderGizmo->Enable();
	}
	else {
		_RenderGizmo->Disable();
	}
}

void SE_Viewport::Render() {

	SynUI::Draw(_RT->GetTexture2D(), GetRenderPosition(), GetSize(), glm::vec4(1, 1, 1, 1));

}

void SE_Viewport::OnMouseDown(int button) {

	if (button == 1) {
		_Drag = true;
	}
	if (button == 0) {



		_RT->Bind2();
		auto res = SE_Global::_EditGraph->MouseRaycast(mousePos, _EditCam, GetSize().x, GetSize().y, _CurrentGizmo);
		_RT->Release2();
		if (res.hit && _SelectedNode) {
			//std::cout << "Hit!" << std::endl;
			if (res.entity == _CurrentGizmo) {


				if (_CurrentGizmo == _GizTranslate) {
					//Z
					if (res.mesh == _CurrentGizmo->GetMesh(0)) {
						int b = 5;
						_GZ = true;
						_GY = false;
						_GX = false;
					}

					//X
					if (res.mesh == _CurrentGizmo->GetMesh(1)) {

						int b = 5;
						_GX = true;
						_GY = false;
						_GZ = false;
					}

					//Y 
					if (res.mesh == _CurrentGizmo->GetMesh(2)) {
						_GY = true;
						_GX = false;
						_GZ = false;
					}

				}
				else if (_CurrentGizmo == _GizRotate) {

					//Y
					if (res.mesh == _CurrentGizmo->GetMesh(0)) {
						int b = 5;
						_GZ = false;
						_GY = true;
						_GX = false;
					}

					//z
					if (res.mesh == _CurrentGizmo->GetMesh(1)) {
						int b = 5;
						_GZ = true;
						_GY = false;
						_GX = false;
					}


					//X
					if (res.mesh == _CurrentGizmo->GetMesh(2)) {
						int b = 5;
						_GZ = false;
						_GY = false;
						_GX = true;
					}

				}

				//int b = 5;
			}

		}
		else {
			//			std::cout << "Not Hit!" << std::endl;


					//else {

			_RT->Bind2();
			auto res = SE_Global::_EditGraph->MouseRaycast(mousePos, _EditCam, GetSize().x, GetSize().y);
			_RT->Release2();

			if (res.hit) {



				_SelectedNode = res.node;
				SE_Global::_SelectedNode = res.node;
				SE_NodeEditor::This->SetNode(_SelectedNode);

			}
			else {
				_SelectedNode = nullptr;
				SE_Global::_SelectedNode = nullptr;
				SE_NodeEditor::This->SetNode(nullptr);
			}

			//}


		}
	}

}

void SE_Viewport::OnMouseUp(int button) {

	if (button == 1) {
		_Drag = false;
	}
	if (button == 0) {
		_GX = _GY = _GZ = false;
	}
}

void SE_Viewport::OnMouseMove(glm::vec2 pos, glm::vec2 delta) {

	mousePos = pos;

	auto space = SE_Global::_SpaceMode;

	if (_GX || _GY || _GZ) {

		float mspeed = 0.05f;
		if (_CurrentGizmo == _GizTranslate) {

			if (space == SM_Local) {

				if (_GX) {

					if (_SelectedNode) {
						_SelectedNode->Move(glm::vec3(delta.x * mspeed, 0, 0));
					}
				}
				if (_GY) {

					if (_SelectedNode) {
						_SelectedNode->Move(glm::vec3(0, -delta.y * mspeed, 0));
					}
				}
				if (_GZ) {

					if (_SelectedNode) {
						_SelectedNode->Move(glm::vec3(0, 0, -delta.x * mspeed));
					}
				}
			}
			else {
				if (_GX) {

					if (_SelectedNode) {
						_SelectedNode->SetPosition(_CurrentGizmo->GetPosition() + glm::vec3(delta.x * mspeed, 0, 0));
					}
				}
				if (_GY) {

					if (_SelectedNode) {
						_SelectedNode->SetPosition(_CurrentGizmo->GetPosition() + glm::vec3(0, -delta.y * mspeed, 0));
					}
				}
				if (_GZ) {

					if (_SelectedNode) {
						_SelectedNode->SetPosition(_CurrentGizmo->GetPosition() + glm::vec3(0, 0, -delta.x * mspeed));
					}
				}
			}
		}
		else if (_CurrentGizmo == _GizRotate) {

			bool local = false;
			if (space == SM_Local)
			{
				local = true;
			}
			else {
				local = false;
			}

			if (_GX) {

				if (_SelectedNode) {
					_SelectedNode->Rotate( glm::vec3(delta.x * mspeed, 0, 0),local);
				}
			}
			if (_GY) {

				if (_SelectedNode) {
					_SelectedNode->Rotate(glm::vec3(0, -delta.x * mspeed, 0),local);
				}
			}
			if (_GZ) {

				if (_SelectedNode) {
					_SelectedNode->Rotate(glm::vec3(0, 0, -delta.x * mspeed),local);
				}
			}

		}
		return;
	}

	if (_Drag) {

		_CamPitch -= delta.y * 0.2f;
		_CamYaw -= delta.x * 0.2f;

		_EditCam->Rotate(_CamPitch, _CamYaw, 0);
		mousePos = pos;
	}

}

void SE_Viewport::OnMouseLeave() {

	_Drag = false;

}

void SE_Viewport::KeyPressed(int key) {

	glm::vec3 move = glm::vec3(0, 0, 0);
	float speed = 10.0f;

	if (_Shift) speed = 20.0f;

	switch (key)
	{
	case GLFW_KEY_W:
		move.z = -1.0 * speed * _TimeDelta;
		break;
	case GLFW_KEY_S:
		move.z = 1.0 * speed * _TimeDelta;
		break;
	case GLFW_KEY_A:
		move.x = -1.0 * speed * _TimeDelta;
		break;
	case GLFW_KEY_D:
		move.x = 1.0f * speed * _TimeDelta;
		break;
	}

	_EditCam->Move(move);

}