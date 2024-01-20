#pragma once
#include "glm/glm.hpp"
#include <vector>

class Pipeline2D;
class Texture2D;
class Mesh;

struct DrawInfo {

	float* x;
	float* y;
	float z;
	glm::vec4 color;
	glm::vec4 scissor;

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
	void DrawQuad(Texture2D* tex,glm::vec2 position, glm::vec2 size, glm::vec4 color);
	void End(Pipeline2D* pp=nullptr);
	void SetScissor(glm::vec4 scissor);
	void ResetScissor();
private:

	int _displaywidth;
	int _displayheight;
	Pipeline2D* _drawmat;
	glm::vec4 _Scissor;
	float _z = 0;
	std::vector<InfoList*> _infos;
	Mesh* _Mesh;
	
};

