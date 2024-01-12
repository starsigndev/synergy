#include "Renderer.h"
#include "RenderQueue.h"
#include "QueueRenderScene.h"
#include "QueueNode.h"
#include "Mesh.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"
#include "Pipeline3DBasic.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
Renderer::Renderer() {

	_PLBasic3D = new Pipeline3DBasic;

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

void Renderer::RenderEntity(Entity* entity) {

	if (entity->MeshCount() == 0) {
		return;
	}
	int a = 5;

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

void Renderer::SetLights(std::vector<Light*>lights) {

	_Lights = lights;

}

void Renderer::SetCamera(Camera* camera) {

	_Camera = camera;

}