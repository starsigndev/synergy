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

class Mesh
{
public:

	void AddVertex(Vertex vertex);
	void AddTriangle(Triangle triangle);
	void CreateBuffers();

private:

	std::vector<Vertex> _vertices;
	std::vector<Triangle> _triangles;
	RefCntAutoPtr<IBuffer> _vertexbuffer;
	RefCntAutoPtr<IBuffer> _indexbuffer;


};

