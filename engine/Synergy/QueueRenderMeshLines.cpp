#include "QueueRenderMeshLines.h"
#include "MeshLines.h"
#include "Renderer.h"

QueueRenderMeshLines::QueueRenderMeshLines(MeshLines* mesh) {

	_MeshLines = mesh;

}

void QueueRenderMeshLines::Render(Renderer* renderer) {

	renderer->RenderMeshLines(_MeshLines);

}