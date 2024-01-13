#include "Renderer.h"
#include "RenderQueue.h"
#include "QueueRenderScene.h"
#include "QueueNode.h"
#include "Mesh.h"
#include "Entity.h"
#include "Actor.h"
#include "Light.h"
#include "Camera.h"
#include "Pipeline3DBasic.h"
#include "Pipeline3DLight.h"
#include "PipelineDepth.h"
#include "Pipeline3DActorLight.h"
#include "RenderTargetCube.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "SceneGraph.h"

Renderer::Renderer() {

	_PLBasic3D = new Pipeline3DBasic;
	_PLLight3D = new Pipeline3DLight;
	_PLActorLight3D = new Pipeline3DActorLight;
	_PLDepth = new PipelineDepth;

//	_ShadowRT = new RenderTargetCube(1024, 1024);

}

void Renderer::Render(RenderQueue* queue)
{

	auto list = queue->GetNodes();

	for (const auto& node : list) {

		//int b = 5;
		node->Render(this);

	}

	int b = 5;

}

void Renderer::RenderActor(Actor* actor) {

	actor->UpdateAnimation(0.001f);

	if (actor->MeshCount() == 0) {
		return;
	}
	int a = 5;
	if (actor->MeshCount() == 0) {
		return;
	}

	bool second = false;

	for (auto const& light : _Lights) {
		//glm::mat4 mvp = glm::ortho(0.0f, (float)_displaywidth, (float)_displayheight, 0.0f, -1.0f, 1.0f);
		glm::mat4 proj = _Camera->GetProjectionMatrix();// glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.01f, 100.0f);

		glm::mat4 view = _Camera->GetWorldMatrix();
		glm::mat4 model = actor->GetWorldMatrix();

		glm::mat4 mvp = proj * view * model;

		for (int i = 0; i < actor->MeshCount(); i++) {
	
			auto mesh = actor->GetMesh(i);

			//_drawmat->SetMVP(glm::transpose(mvp));

			auto bones = actor->GetBoneMatrices();

			_PLActorLight3D->Set(mesh->GetMaterial(), light, _Camera, (Node3D*)actor, glm::transpose(mvp),bones);


			//_drawmat->SetColorTex(value->tex);

		//	_drawmat->Bind(false);
			_PLActorLight3D->Bind(second);

			auto dc = SynApp::This->GetContext();

			const Uint64 offset = 0;

			IBuffer* pBuffs[] = { mesh->GetVertexBuffer() };

			dc->SetVertexBuffers(0, 1, pBuffs, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
			dc->SetIndexBuffer(mesh->GetIndexBuffer(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

			if (second)
			{
				dc->SetPipelineState(_PLActorLight3D->GetPipelineStateSP());
				dc->CommitShaderResources(_PLActorLight3D->GetSRBSP(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
			}
			else {
				dc->SetPipelineState(_PLActorLight3D->GetPipelineState());

				dc->CommitShaderResources(_PLActorLight3D->GetSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
			}
			DrawIndexedAttribs DrawAttrs;     // This is an indexed draw call
			DrawAttrs.IndexType = VT_UINT32; // Index type
			DrawAttrs.NumIndices = mesh->TriCount() * 3;
			// Verify the state of vertex and index buffers
			DrawAttrs.Flags = DRAW_FLAG_NONE;
			dc->DrawIndexed(DrawAttrs);

		}

		second = true;

	}

	int b = 0;

}

void Renderer::RenderEntity(Entity* entity) {

	if (entity->MeshCount() == 0) {
		return;
	}
	int a = 5;
	if (entity->MeshCount() == 0) {
		return;
	}

	bool second = false;

	for (auto const& light : _Lights) {
		//glm::mat4 mvp = glm::ortho(0.0f, (float)_displaywidth, (float)_displayheight, 0.0f, -1.0f, 1.0f);
		glm::mat4 proj = _Camera->GetProjectionMatrix();// glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.01f, 100.0f);

		glm::mat4 view = _Camera->GetWorldMatrix();
		glm::mat4 model = entity->GetWorldMatrix();

		glm::mat4 mvp = proj * view * model;



		//_drawmat->SetMVP(glm::transpose(mvp));
		_PLLight3D->Set(entity->GetMesh(0)->GetMaterial(), light, _Camera, (Node3D*)entity, glm::transpose(mvp));

		//_drawmat->SetColorTex(value->tex);

	//	_drawmat->Bind(false);
		_PLLight3D->Bind(second);

		auto dc = SynApp::This->GetContext();

		const Uint64 offset = 0;

		IBuffer* pBuffs[] = { entity->GetMesh(0)->GetVertexBuffer() };

		dc->SetVertexBuffers(0, 1, pBuffs, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
		dc->SetIndexBuffer(entity->GetMesh(0)->GetIndexBuffer(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

		if (second)
		{
			dc->SetPipelineState(_PLLight3D->GetPipelineStateSP());
			dc->CommitShaderResources(_PLLight3D->GetSRBSP(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		}
		else {
			dc->SetPipelineState(_PLLight3D->GetPipelineState());

			dc->CommitShaderResources(_PLLight3D->GetSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		}
		DrawIndexedAttribs DrawAttrs;     // This is an indexed draw call
		DrawAttrs.IndexType = VT_UINT32; // Index type
		DrawAttrs.NumIndices = entity->GetMesh(0)->TriCount() * 3;
		// Verify the state of vertex and index buffers
		DrawAttrs.Flags = DRAW_FLAG_NONE;
		dc->DrawIndexed(DrawAttrs);

		second = true;

	}

	int b = 0;

}


void Renderer::RenderEntityBasic(Entity* entity) {
	
	if (entity->MeshCount() == 0) {
		return;
	}

	//glm::mat4 mvp = glm::ortho(0.0f, (float)_displaywidth, (float)_displayheight, 0.0f, -1.0f, 1.0f);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.01f, 100.0f);

	glm::mat4 view = _Camera->GetWorldMatrix();
	glm::mat4 model = entity->GetWorldMatrix();

	glm::mat4 mvp = proj * view * model;



	//_drawmat->SetMVP(glm::transpose(mvp));
	_PLBasic3D->Set(entity->GetMesh(0)->GetMaterial(), glm::transpose(mvp));

	//_drawmat->SetColorTex(value->tex);

//	_drawmat->Bind(false);
	_PLBasic3D->Bind(false);

	auto dc = SynApp::This->GetContext();

	const Uint64 offset = 0;

	IBuffer* pBuffs[] = { entity->GetMesh(0)->GetVertexBuffer() };

	dc->SetVertexBuffers(0, 1, pBuffs, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
	dc->SetIndexBuffer(entity->GetMesh(0)->GetIndexBuffer(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	dc->SetPipelineState(_PLBasic3D->GetPipelineState());

	dc->CommitShaderResources(_PLBasic3D->GetSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	DrawIndexedAttribs DrawAttrs;     // This is an indexed draw call
	DrawAttrs.IndexType = VT_UINT32; // Index type
	DrawAttrs.NumIndices = entity->GetMesh(0)->TriCount() * 3;
	// Verify the state of vertex and index buffers
	DrawAttrs.Flags = DRAW_FLAG_NONE;
	dc->DrawIndexed(DrawAttrs);



	int b = 0;

}

void Renderer::RenderEntityDepth(Entity* entity) {

	if (entity->MeshCount() == 0) {
		return;
	}


	//glm::mat4 mvp = glm::ortho(0.0f, (float)_displaywidth, (float)_displayheight, 0.0f, -1.0f, 1.0f);
	glm::mat4 proj = _Camera->GetProjectionMatrix();// glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.01f, 100.0f);

	glm::mat4 view = _Camera->GetWorldMatrix();
	glm::mat4 model = entity->GetWorldMatrix();

	glm::mat4 mvp = proj * view * model;

	auto light = _Lights[0];

	//_drawmat->SetMVP(glm::transpose(mvp));
	_PLDepth->Set(_Camera, (Node3D*)entity, glm::transpose(mvp));

	//_drawmat->SetColorTex(value->tex);

//	_drawmat->Bind(false);
	_PLDepth->Bind(false);

	auto dc = SynApp::This->GetContext();

	const Uint64 offset = 0;

	IBuffer* pBuffs[] = { entity->GetMesh(0)->GetVertexBuffer() };

	dc->SetVertexBuffers(0, 1, pBuffs, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
	dc->SetIndexBuffer(entity->GetMesh(0)->GetIndexBuffer(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	dc->SetPipelineState(_PLDepth->GetPipelineState());

	dc->CommitShaderResources(_PLDepth->GetSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	DrawIndexedAttribs DrawAttrs;     // This is an indexed draw call
	DrawAttrs.IndexType = VT_UINT32; // Index type
	DrawAttrs.NumIndices = entity->GetMesh(0)->TriCount() * 3;
	// Verify the state of vertex and index buffers
	DrawAttrs.Flags = DRAW_FLAG_NONE;
	dc->DrawIndexed(DrawAttrs);



	int b = 0;

}


void Renderer::SetLights(std::vector<Light*>lights) {

	_Lights = lights;

}

void Renderer::SetCamera(Camera* camera) {

	_Camera = camera;

}

void Renderer::RenderShadows(SceneGraph* graph) {

	Camera* p_cm = _Camera;
	Camera* s_cam = new Camera();
	_Camera = s_cam;
	int l1 = 0;
	for (auto const& light : _Lights) {

		auto rt = light->GetShadowRT();

		s_cam->SetPosition(light->GetPosition());
		s_cam->SetNearZ(p_cm->GetNearZ());
		s_cam->SetFarZ(light->GetRange());
		s_cam->SetFOV(90.0f);

		for (int i = 0; i < 6; i++) {

			rt->Bind(i);

			switch (i)
			{
			case 1:
				glm::mat4 rot0 = glm::rotate(glm::mat4(1.0f),glm::pi<float>()/2.0f, glm::vec3(0, 1, 0));
				s_cam->SetRotation(rot0);
				break;
			case 0:
				glm::mat4 rot1 = glm::rotate(glm::mat4(1.0f), -glm::pi<float>()/2.0f, glm::vec3(0, 1, 0));
				s_cam->SetRotation(rot1);
				break;
			case 3:
				glm::mat4 rot2 = glm::rotate(glm::mat4(1.0f), -glm::pi<float>()/2.0f, glm::vec3(1, 0, 0));
				s_cam->SetRotation(rot2);
				break;
			case 2 :
				glm::mat4 rot3 = glm::rotate(glm::mat4(1.0f), glm::pi<float>()/2.0f, glm::vec3(1,0, 0));
				s_cam->SetRotation(rot3);
				break;
			case 4:
				glm::mat4 rot4 = glm::rotate(glm::mat4(1.0f), glm::pi<float>(), glm::vec3(0, 1, 0));
				s_cam->SetRotation(glm::mat4(1.0f));
				break;
			case 5:
				glm::mat4 rot5 = glm::rotate(glm::mat4(1.0f), glm::pi<float>(), glm::vec3(0, 1, 0));
				s_cam->SetRotation(rot5);
				break;
	
	//			break;
			}

			RenderGraphDepth(graph);
			

			rt->Release(i);

		}

	};
	_Camera = p_cm;

}

void Renderer::RenderNodeDepth(Node3D* node) {

	Entity* entity = dynamic_cast<Entity*>(node);
	if (entity) {

		RenderEntityDepth(entity);

	}

	for (int i = 0; i < node->NodeCount(); i++) {
		RenderNodeDepth(node->GetNode(i));
	}

}

void Renderer::RenderGraphDepth(SceneGraph* graph) {

	RenderNodeDepth(graph->GetRootNode());

}

void Renderer::RenderGraph(SceneGraph* graph) {

	auto root = graph->GetRootNode();

	//	Render

	//RenderEntityDepth(root);



}