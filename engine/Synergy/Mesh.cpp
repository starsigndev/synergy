#include "Mesh.h"

#include "RefCntAutoPtr.hpp"
#include "RenderDevice.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "RenderStateNotationLoader.h"
#include "BasicMath.hpp"
#include "SynApp.h"

using namespace Diligent;

void Mesh::AddVertex( Vertex& vertex)
{

	_vertices.push_back(vertex);

}

void Mesh::AddTriangle(Triangle& tri) {

	_triangles.push_back(tri);

}

void Mesh::CreateBuffers() {

	BufferDesc vbuf;
	vbuf.Name = "Mesh VB";
	vbuf.Usage = USAGE_IMMUTABLE;
	vbuf.BindFlags = BIND_VERTEX_BUFFER;
	vbuf.Size = (sizeof(Vertex) * _vertices.size());

	BufferData vdata;

	vdata.pData = _vertices.data();
	vdata.DataSize = vbuf.Size;
	
	SynApp::This->GetDevice()->CreateBuffer(vbuf,&vdata, &_vertexbuffer);

	BufferDesc ibuf;
	ibuf.Name = "Mesh IB";
	ibuf.Usage = USAGE_IMMUTABLE;
	ibuf.BindFlags = BIND_INDEX_BUFFER;
	ibuf.Size = sizeof(Triangle) * _triangles.size();

	BufferData idata;
	idata.pData = _triangles.data();
	idata.DataSize = sizeof(Triangle) * _triangles.size();

	SynApp::This->GetDevice()->CreateBuffer(ibuf, &idata, &_indexbuffer);
	


}