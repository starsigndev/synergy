#include "Renderer.h"
#include "RenderQueue.h"
#include "QueueRenderScene.h"
#include "QueueNode.h"

void Renderer::Render(RenderQueue* queue)
{

	auto list = queue->GetNodes();

	for (const auto& node : list) {

		//int b = 5;
		node->Render(this);

	}

	int b = 5;

}