#include "SmartDraw.h"
#include "Mesh.h"
#include "Material2D.h"
#include "glm/gtc/matrix_transform.hpp"

SmartDraw::SmartDraw() {

	_drawmat = new Material2D;

}

void SmartDraw::DrawQuad(Texture2D* tex,glm::vec2 pos, glm::vec2 size, glm::vec4 color)
{

	Vertex v1, v2, v3, v4;

	v1.position = glm::vec3(pos.x, pos.y, 0);
	v2.position = glm::vec3(pos.x + size.x, pos.y, 0);
	v3.position = glm::vec3(pos.x + size.x, pos.y + size.y,0);
	v4.position = glm::vec3(pos.x, pos.y + size.y, 0);

	v1.color = color;
	v2.color = color;
	v3.color = color;
	v4.color = color;

	v1.texcoord = glm::vec3(0, 0, 0);
	v2.texcoord = glm::vec3(1, 0, 0);
	v3.texcoord = glm::vec3(1, 1, 0);
	v4.texcoord = glm::vec3(0, 1, 0);

	Triangle t1, t2;

	t1.V0 = 0;
	t1.V1 = 1;
	t1.V2 = 2;

	t2.V0 = 2;
	t2.V1 = 3;
	t2.V2 = 0;

	Mesh* mesh = new Mesh;

	mesh->AddVertex(v1);
	mesh->AddVertex(v2);
	mesh->AddVertex(v3);
	mesh->AddVertex(v4);

	mesh->AddTriangle(t1);
	mesh->AddTriangle(t2);

	mesh->CreateBuffers();

	glm::mat4 mvp = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, 1.0f, -1.0f);

	_drawmat->SetMVP(glm::transpose(mvp));

	_drawmat->SetColorTex(tex);

	_drawmat->Bind(false);
	
	auto dc = SynApp::This->GetContext();

	const Uint64 offset = 0;

	IBuffer* pBuffs[] = { mesh->GetVertexBuffer() };

	dc->SetVertexBuffers(0, 1, pBuffs, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
	dc->SetIndexBuffer(mesh->GetIndexBuffer(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	dc->SetPipelineState(_drawmat->GetPipelineState());

	dc->CommitShaderResources(_drawmat->GetSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	DrawIndexedAttribs DrawAttrs;     // This is an indexed draw call
	DrawAttrs.IndexType = VT_UINT32; // Index type
	DrawAttrs.NumIndices = 12;
	// Verify the state of vertex and index buffers
	DrawAttrs.Flags = DRAW_FLAG_VERIFY_ALL;
	dc->DrawIndexed(DrawAttrs);



}