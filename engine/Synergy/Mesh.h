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

	void AddVertex(Vertex& vertex);
	void AddTriangle(Triangle& triangle);
	void CreateBuffers();
	void Delete() {
	//	_vertexbuffer.Detach();
	//	_indexbuffer.Detach();

		_Vertexbuffer.Release();
		_Indexbuffer.Release();
		
	}

	RefCntAutoPtr<IBuffer> GetVertexBuffer() {
		return _Vertexbuffer;
	}

	RefCntAutoPtr<IBuffer> GetIndexBuffer() {
		return _Indexbuffer;
	}
	int TriCount() {
		return _Triangles.size();
	}

	//Material

	void SetMaterial(Material* material);
	Material* GetMaterial();

private:

	//Data
	std::vector<Vertex> _Vertices;
	std::vector<Triangle> _Triangles;
	RefCntAutoPtr<IBuffer> _Vertexbuffer;
	RefCntAutoPtr<IBuffer> _Indexbuffer;

	//Material
	Material* _Material;

};

