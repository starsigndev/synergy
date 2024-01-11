#pragma once
#include <vector>
class RenderQueue;
class Entity;
class Light;
class Pipeline3DBasic;

class Renderer
{
public:

	Renderer();
	void Render(RenderQueue* queue);
	void RenderEntity(Entity* entity);
	void RenderEntityBasic(Entity* entity);
	void SetLights(std::vector<Light*> lights);


private:

	std::vector<Light*> _Lights;

	//pipelines
	Pipeline3DBasic* _PLBasic3D;

};

