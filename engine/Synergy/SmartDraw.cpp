#include "SmartDraw.h"
#include "Mesh.h"
#include "Material2D.h"


SmartDraw::SmartDraw() {

	_drawmat = new Material2D;

}

void SmartDraw::DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color)
{

	Vertex v1, v2, v3, v4;

	v1.position = glm::vec3(pos.x, pos.y, 0.1f);
	v2.position = glm::vec3(pos.x + size.x, pos.y, 0.1f);
	v3.position = glm::vec3(pos.x + size.x, pos.y + size.y, 0.1f);
	v4.position = glm::vec3(pos.x, pos.y + size.y, 0.1f);

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
	t2.V2 = 2;

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

}