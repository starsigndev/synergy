#include "QueueRenderShadows.h"
#include "Renderer.h"
#include "SceneGraph.h"

QueueRenderShadows::QueueRenderShadows(SceneGraph* graph) {

	_Graph = graph;

}

void QueueRenderShadows::Render(Renderer* renderer)
{

	renderer->RenderShadows(_Graph);

}