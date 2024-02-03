#include "QueueRenderEntity.h"
#include "Renderer.h"

void QueueRenderEntity::Render(Renderer* renderer)
{

	if (_BasicRender && _Enabled) {

		renderer->RenderEntityBasic(_Entity);

	}

}