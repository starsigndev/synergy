#pragma once
#include "glm/glm.hpp"
#include <vector>

class Pipeline2D;
class Texture2D;
class Mesh;

struct DrawInfo {

	float* x;
	float* y;
	//glm::vec4 uv;
	float* u;
	float* v;

	float z;
	glm::vec4 color;
	glm::vec4 scissor;
	float blurx, blury;

};

struct InfoList {

	Texture2D* tex;
	std::vector<DrawInfo*> infos;

};

class SmartDraw
{
public:

	SmartDraw();
	void SetView(int width, int height) {
		_displaywidth = width;
		_displayheight = height;
	}

	InfoList* GetList(Texture2D* tex);
	void Begin();
	void DrawQuad(Texture2D* tex, glm::vec2 position, glm::vec2 size, glm::vec4 color,glm::vec4 u,glm::vec4 v, float blurx = 0, float blury = 0);
	void DrawQuad(Texture2D* tex, glm::vec2 position, glm::vec2 size, glm::vec4 uv, glm::vec4 color, float blurx = 0,float blury=0);
	void DrawQuad(Texture2D* tex,glm::vec2 position, glm::vec2 size, glm::vec4 color,float blurx=0,float blury=0);
	void DrawLine(Texture2D* tex,glm::vec2 pos1, glm::vec2 pos2, glm::vec4 color,float width=0.1f);
	void End(Pipeline2D* pp=nullptr);
	//void SetScissor(glm::vec4 scissor);
	void PushScissor(glm::vec4 scissor);
	void ResetScissor();
	glm::vec4 GetScissor();
	glm::vec4 PopScissor();
private:

	int _displaywidth;
	int _displayheight;
	Pipeline2D* _drawmat;
	std::vector<glm::vec4> _Scissor;

	float _z = 0;
	std::vector<InfoList*> _infos;
	Mesh* _Mesh;
	
};

