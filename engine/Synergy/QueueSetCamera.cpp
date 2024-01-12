#include "QueueSetCamera.h"
#include "Renderer.h"

QueueSetCamera::QueueSetCamera(Camera* camera) {

	_Camera = camera;

}

void QueueSetCamera::Render(Renderer* renderer)
{

	renderer->SetCamera(_Camera);

}