#include "Mesh.h"

#include "RefCntAutoPtr.hpp"
#include "RenderDevice.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "RenderStateNotationLoader.h"
#include "BasicMath.hpp"
#include "SynApp.h"
#include "Material.h"
#include "Entity.h"

using namespace Diligent;

Mesh::Mesh() {

	_Material = new Material;

}

Mesh::Mesh(int vertices, int triangles) {

	for (int i = 0; i < vertices; i++) {

		_Vertices.push_back(Vertex());

	}

	for (int i = 0; i < triangles; i++) {
		_Triangles.push_back(Triangle());
	}

	CreateBuffersDynamic();

	_Vertices.clear();
	_Triangles.clear();

}

void Mesh::AddVertex( Vertex vertex)
{
//	vertex.color = glm::vec4(1, 1, 1, 1);
	_Vertices.push_back(vertex);

}

void Mesh::AddTriangle(Triangle tri) {

	_Triangles.push_back(tri);

}

void Mesh::UpdateBuffers() {

	SynApp::This->GetContext()->UpdateBuffer(_Vertexbuffer, 0, _Vertices.size()*sizeof(Vertex), _Vertices.data(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	SynApp::This->GetContext()->UpdateBuffer(_Indexbuffer, 0, _Triangles.size()*sizeof(Triangle), _Triangles.data(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

}

void Mesh::Clear() {

	_Vertices.clear();
	_Triangles.clear();

}

void Mesh::CreateBuffersDynamic() {

	BufferDesc vbuf;
	vbuf.Name = "Mesh VB";
	vbuf.Usage = USAGE_DEFAULT;
	vbuf.BindFlags = BIND_VERTEX_BUFFER;
	vbuf.Size = (sizeof(Vertex) * _Vertices.size());
//	vbuf.CPUAccessFlags = CPU_ACCESS_WRITE;
	BufferData vdata;

	vdata.pData = nullptr;//_Vertices.data();
	vdata.DataSize = sizeof(Vertex) * _Vertices.size();

	SynApp::This->GetDevice()->CreateBuffer(vbuf, &vdata, &_Vertexbuffer);

	BufferDesc ibuf;
	ibuf.Name = "Mesh IB";
	ibuf.Usage = USAGE_DEFAULT;
	ibuf.BindFlags = BIND_INDEX_BUFFER;
//	ibuf.CPUAccessFlags = CPU_ACCESS_WRITE;
	ibuf.Size = sizeof(Triangle) * _Triangles.size();

	BufferData idata;
	idata.pData = nullptr;// _Triangles.data();
	idata.DataSize = sizeof(Triangle) * _Triangles.size();

	SynApp::This->GetDevice()->CreateBuffer(ibuf, &idata, &_Indexbuffer);

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

void Mesh::SetOwner(Entity* owner) {

	_Owner = owner;

}

Entity* Mesh::GetOwner() {

	return _Owner;

}