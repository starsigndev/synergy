#include "SmartDraw.h"
#include "Mesh.h"
#include "Pipeline2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>
#include "glm/glm.hpp"
Vertex v1, v2, v3, v4;
Triangle t1, t2;

SmartDraw::SmartDraw() {

	_drawmat = new Pipeline2D;
	v1.texcoord = glm::vec3(0, 0, 0);
			v2.texcoord = glm::vec3(1, 0, 0);
			v3.texcoord = glm::vec3(1, 1, 0);
			v4.texcoord = glm::vec3(0, 1, 0);
			_Mesh = new Mesh(10240, 10240);
			PushScissor(glm::vec4(-1, -1, -1, -1));
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
	_z = 2.99f;
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

glm::mat4 createLeftHandedOrtho(float left, float right, float bottom, float top, float nearVal, float farVal) {
	glm::mat4 ortho = glm::mat4(1.0f);
	ortho[0][0] = 2.0f / (right - left);
	ortho[1][1] = 2.0f / (top - bottom);
	ortho[2][2] = 2.0f / (farVal - nearVal); // Depth range is now farVal - nearVal
	ortho[3][0] = -(right + left) / (right - left);
	ortho[3][1] = -(top + bottom) / (top - bottom);
	ortho[3][2] = -(farVal + nearVal) / (farVal - nearVal);
	return ortho;
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
	//	draw->scissor = glm::vec4(-1, -1, -1, -1);
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

		glm::mat4 mvp = createLeftHandedOrtho(0, (float)SynApp::This->GetWidth(), (float)SynApp::This->GetHeight(), 0,0.01f, 3.0f);////glm::ortho(0.0f, (float)SynApp::This->GetWidth(), (float)SynApp::This->GetHeight(), 0.0f, -5.0f,  5.0f);

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
		DrawAttrs.Flags = DRAW_FLAG_NONE;

		dc->DrawIndexed(DrawAttrs);

		//mesh->Delete();
		//delete mesh;

	}

}

void SmartDraw::PushScissor(glm::vec4 scissor) {

	_Scissor.push_back(scissor);

}

glm::vec4 SmartDraw::GetScissor() {

	if (_Scissor.size() == 1)
	{
		return _Scissor[0];
	}
	glm::vec4 last = _Scissor[_Scissor.size() - 1];
	glm::vec4 secondLast = _Scissor[_Scissor.size() - 2];

	if (secondLast.x < 0 && secondLast.y < 0 && secondLast.z < 0 && secondLast.w < 0)
	{
		return last;
	}
	else {

		

		if (last.x < secondLast.x)
		{
			int iw = secondLast.x - last.x;
			last.x = secondLast.x;
			last.z -= iw;

		}
		if (last.y < secondLast.y) {

			int ih = secondLast.y - last.y;
			last.y = secondLast.y;
			last.w -= ih;

		}

		if (last.x + last.z > secondLast.x + secondLast.z) {

			int w = (secondLast.x + secondLast.z) - (last.x + last.z);
			last.z += w;

		}

		if (last.y + last.w > secondLast.y + secondLast.w) {

			int h= (secondLast.y + secondLast.w) - (last.y + last.w);
			last.w += h;

		}

		if (last.x > secondLast.x+secondLast.z)
		{
			last = glm::vec4(5, 5, 5, 5);
		}

		if (last.y > secondLast.y+secondLast.w)
		{
			last = glm::vec4(5, 5, 5, 5);
		}

		return last;


	}
	return last;

	//return _Scissor.back();


}

glm::vec4 SmartDraw::PopScissor() {

	auto r = GetScissor();

	_Scissor.pop_back();

	return r;

}

void SmartDraw::ResetScissor() {
	_drawmat->Scissor = glm::vec4(-1, -1, -1, -1);
}


void SmartDraw::DrawLine(Texture2D* tex,glm::vec2 pos1, glm::vec2 pos2, glm::vec4 color) {

	auto list = GetList(tex);

	DrawInfo* info = new DrawInfo;
	info->x = new float[4];
	info->y = new float[4];

	// Calculate the angle of the line
	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	float angle = std::atan2(dy, dx);

	// Define the thickness of the line
	float thickness = 3.0f; // You can adjust this value

	// Calculate the offset for the thickness
	float offsetX = thickness * std::sin(angle);
	float offsetY = thickness * std::cos(angle);

	// Set the vertices for the line with thickness
	info->x[0] = pos1.x + offsetX;
	info->y[0] = pos1.y - offsetY;
	info->x[1] = pos2.x + offsetX;
	info->y[1] = pos2.y - offsetY;
	info->x[2] = pos2.x - offsetX;
	info->y[2] = pos2.y + offsetY;
	info->x[3] = pos1.x - offsetX;
	info->y[3] = pos1.y + offsetY;

	info->color = color;
	info->z = _z;

	info->scissor = GetScissor();
	list->infos.push_back(info);
	_z -= 0.003f;
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

	info->scissor = GetScissor();
	list->infos.push_back(info);
	_z -= 0.003f;

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