#include "Mesh.h"

#include "RefCntAutoPtr.hpp"
#include "RenderDevice.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "RenderStateNotationLoader.h"
#include "BasicMath.hpp"
#include "SynApp.h"
#include "Material.h"

using namespace Diligent;

Mesh::Mesh() {

	_Material = new Material;

}

void Mesh::AddVertex( Vertex& vertex)
{
	vertex.color = glm::vec4(1, 1, 1, 1);
	_Vertices.push_back(vertex);

}

void Mesh::AddTriangle(Triangle& tri) {

	_Triangles.push_back(tri);

}

void Mesh::CreateBuffers() {

	BufferDesc vbuf;
	vbuf.Name = "Mesh VB";
	vbuf.Usage = USAGE_IMMUTABLE;
	vbuf.BindFlags = BIND_VERTEX_BUFFER;
	vbuf.Size = (sizeof(Vertex) * _Vertices.size());

	BufferData vdata;

	vdata.pData = _Vertices.data();
	vdata.DataSize = vbuf.Size;
	
	SynApp::This->GetDevice()->CreateBuffer(vbuf,&vdata, &_Vertexbuffer);

	BufferDesc ibuf;
	ibuf.Name = "Mesh IB";
	ibuf.Usage = USAGE_IMMUTABLE;
	ibuf.BindFlags = BIND_INDEX_BUFFER;
	ibuf.Size = sizeof(Triangle) * _Triangles.size();

	BufferData idata;
	idata.pData = _Triangles.data();
	idata.DataSize = sizeof(Triangle) * _Triangles.size();

	SynApp::This->GetDevice()->CreateBuffer(ibuf, &idata, &_Indexbuffer);
	


}


//Material

void Mesh::SetMaterial(Material* material) {

	_Material = material;

}

Material* Mesh::GetMaterial() {

	return _Material;

}