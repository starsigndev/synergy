#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "Vertex3D.h"
#include "Triangle.h"

#include "RefCntAutoPtr.hpp"
#include "RenderDevice.h"
#include "DeviceContext.h"
#include "SwapChain.h"

using namespace Diligent;

class Material;

class Mesh
{
public:

	Mesh();
	Mesh(int vertices, int triangles);
	void AddVertex(Vertex& vertex);
	void AddTriangle(Triangle& triangle);
	void CreateBuffers();
	void CreateBuffersDynamic();
	void UpdateBuffers();
	void Clear();
	void Delete() {
	//	_vertexbuffer.Detach();
	//	_indexbuffer.Detach();

		_Vertexbuffer->Release();
		_Indexbuffer->Release();
		
	}

	IBuffer* GetVertexBuffer() {
		return _Vertexbuffer;
	}

	IBuffer* GetIndexBuffer() {
		return _Indexbuffer;
	}
	int TriCount() {
		return _Triangles.size();
	}

	//Material

	void SetMaterial(Material* material);
	Material* GetMaterial();

	int VertexCount() {
		return _Vertices.size();
	}

	Vertex GetVertex(int index)
	{
		return _Vertices[index];
	}

	void SetVertex(int ID, Vertex vertex) {

		_Vertices[ID] = vertex;

	}


private:

	//Data
	std::vector<Vertex> _Vertices;
	std::vector<Triangle> _Triangles;
	IBuffer* _Vertexbuffer;
	IBuffer* _Indexbuffer;

	//Material
	Material* _Material;

};

