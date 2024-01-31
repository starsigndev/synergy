#pragma once
#include <vector>
#include "Triangle.h"
#include "Vertex3D.h"
#include "glm/glm.hpp"

#include "RefCntAutoPtr.hpp"
#include "RenderDevice.h"
#include "DeviceContext.h"
#include "SwapChain.h"

using namespace Diligent;
class MeshLines
{
public:

	void AddVertex(LineVertex vertex);
	void AddLine(Line line);
	void CreateBuffer();
	IBuffer* GetVertexBuffer() {
		return _Vertexbuffer;
	}
	IBuffer* GetIndexBuffer() {
		return _IndexBuffer;
	}
	int GetLinesCount() {
		return _Lines.size();
	}

private:

	std::vector<LineVertex> _Vertices;
	std::vector<Line> _Lines;
	IBuffer* _Vertexbuffer;
	IBuffer* _IndexBuffer;

};

