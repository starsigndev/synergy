#include "MeshLines.h"
#include "SynApp.h"

void MeshLines::AddVertex(LineVertex vertex) {

	_Vertices.push_back(vertex);

}

void MeshLines::AddLine(Line line) {

	_Lines.push_back(line);

}

void MeshLines::CreateBuffer() {

	BufferDesc desc;
	desc.Name = "Mesh Lines Vertex Buffer";
	desc.Usage = USAGE::USAGE_IMMUTABLE;
	desc.BindFlags = BIND_VERTEX_BUFFER;
	desc.Size = sizeof(LineVertex) * _Vertices.size();
	//desc.ElementByteStride = sizeof(LineVertex);
	//desc.Mode = BUFFER_MODE_STRUCTURED;
	
	BufferData data;
	data.pData = _Vertices.data();
	data.DataSize = sizeof(LineVertex) * _Vertices.size();


	SynApp::This->GetDevice()->CreateBuffer(desc, &data, &_Vertexbuffer);


	BufferDesc idesc;
	idesc.Name = "Mesh Lines Index Buffer";
	idesc.Usage = USAGE_IMMUTABLE;
	idesc.BindFlags = BIND_INDEX_BUFFER;
	idesc.Size = sizeof(Line) * _Lines.size();
	//idesc.ElementByteStride = sizeof(Line);
	BufferData bdata;
	bdata.pData = _Lines.data();
	bdata.DataSize = sizeof(Line) * _Lines.size();

	SynApp::This->GetDevice()->CreateBuffer(idesc, &bdata, &_IndexBuffer);



}