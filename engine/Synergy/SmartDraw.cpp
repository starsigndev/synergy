#include "SmartDraw.h"
#include "Mesh.h"
#include "Pipeline2D.h"
#include "glm/gtc/matrix_transform.hpp"

Vertex v1, v2, v3, v4;
Triangle t1, t2;

SmartDraw::SmartDraw() {

	_drawmat = new Pipeline2D;
	v1.texcoord = glm::vec3(0, 0, 0);
			v2.texcoord = glm::vec3(1, 0, 0);
			v3.texcoord = glm::vec3(1, 1, 0);
			v4.texcoord = glm::vec3(0, 1, 0);
			_Mesh = new Mesh(10240, 10240);
}

InfoList* SmartDraw::GetList(Texture2D* tex) {

	for (const auto& value : _infos) {
		
		if (value->tex == tex) {
			return value;
		}
		//std::cout << value << std::endl;

	}

	InfoList* list = new InfoList;
	list->tex = tex;
	_infos.push_back(list);
	return list;

}

void SmartDraw::Begin() {
	_z = -0.9f;
	for (const auto& value : _infos) {
		
		for (const auto& inf : value->infos) {
		
			delete inf->x;
			delete inf->y;
			
			delete inf;

		}

		value->infos.clear();
		delete value;
	}
	_infos.clear();
}

void SmartDraw::End(Pipeline2D* pp) {

	
	for (const auto& value : _infos) {


	
		_Mesh->Clear();


		int vi = 0;
		//d::cout << value << std::endl;
		for (const auto& draw : value->infos)
		{

			//Vertex v1, v2, v3, v4;

			v1.position = glm::vec3(draw->x[0],draw->y[0], draw->z);
			v2.position = glm::vec3(draw->x[1],draw->y[1], draw->z);
			v3.position = glm::vec3(draw->x[2], draw->y[2], draw->z);
			v4.position = glm::vec3(draw->x[3],draw->y[3], draw->z);

			v1.color = draw->color;
			v2.color = draw->color;
			v3.color = draw->color;
			v4.color = draw->color;
			v1.weights = draw->scissor;
			v2.weights = draw->scissor;
			v3.weights = draw->scissor;
			v4.weights = draw->scissor;
		//	v1.texcoord = glm::vec3(0, 0, 0);
	//		v2.texcoord = glm::vec3(1, 0, 0);
	//		v3.texcoord = glm::vec3(1, 1, 0);
	//		v4.texcoord = glm::vec3(0, 1, 0);

		

			t1.V0 = vi+0;
			t1.V1 = vi+1;
			t1.V2 = vi+2;

			t2.V0 = vi+2;
			t2.V1 = vi+3;
			t2.V2 = vi+0;

			_Mesh->AddVertex(v1);
			_Mesh->AddVertex(v2);
			_Mesh->AddVertex(v3);
			_Mesh->AddVertex(v4);

			_Mesh->AddTriangle(t1);
			_Mesh->AddTriangle(t2);

			vi = vi + 4;

		}


		//return;

		_Mesh->UpdateBuffers();
		


		//return;

		glm::mat4 mvp = glm::ortho(0.0f, (float)_displaywidth, (float)_displayheight, 0.0f,-1.0f, 1.0f);

		if (pp == nullptr) {

			_drawmat->SetMVP(glm::transpose(mvp));

			_drawmat->SetColorTex(value->tex);

			_drawmat->Bind(false);

		}
		else {

			pp->SetMVP(glm::transpose(mvp));

			pp->SetColorTex(value->tex);

			pp->Bind(false);

		}

		auto dc = SynApp::This->GetContext();
	
		const Uint64 offset = 0;

		IBuffer* pBuffs[] = { _Mesh->GetVertexBuffer() };

		dc->SetVertexBuffers(0, 1, pBuffs, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
		dc->SetIndexBuffer(_Mesh->GetIndexBuffer(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);


		if (pp == nullptr) {
			dc->SetPipelineState(_drawmat->GetPipelineState());

			dc->CommitShaderResources(_drawmat->GetSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

		}
		else {

			dc->SetPipelineState(pp->GetPipelineState());

			dc->CommitShaderResources(pp->GetSRB(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);


		}

		DrawIndexedAttribs DrawAttrs;     // This is an indexed draw call
		DrawAttrs.IndexType = VT_UINT32; // Index type
		DrawAttrs.NumIndices = _Mesh->TriCount() * 3;
		// Verify the state of vertex and index buffers
		DrawAttrs.Flags = DRAW_FLAG_DYNAMIC_RESOURCE_BUFFERS_INTACT;

		dc->DrawIndexed(DrawAttrs);

		//mesh->Delete();
		//delete mesh;

	}

}

void SmartDraw::SetScissor(glm::vec4 scissor) {

	_Scissor = scissor;


}

void SmartDraw::ResetScissor() {
	_drawmat->Scissor = glm::vec4(-1, -1, -1, -1);
}

void SmartDraw::DrawQuad(Texture2D* tex,glm::vec2 pos, glm::vec2 size, glm::vec4 color)
{

	auto list = GetList(tex);

	DrawInfo* info = new DrawInfo;
	info->x = new float[4];
	info->y = new float[4];
	info->x[0] = pos.x;
	info->y[0] = pos.y;
	info->x[1] = pos.x + size.x;
	info->y[1] = pos.y;
	info->x[2] = pos.x + size.x;
	info->y[2] = pos.y + size.y;
	info->x[3] = pos.x;
	info->y[3] = pos.y + size.y;
	info->color = color;
	info->z =_z;
	info->scissor = _Scissor;
	list->infos.push_back(info);
	_z += 0.00001f;

	return;


	
	/*
	mesh->CreateBuffers();

	glm::mat4 mvp = glm::ortho(0.0f,(float)_displaywidth,(float)_displayheight, 0.0f, -1.0f, 1.0f);

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

	*/

}