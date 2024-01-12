#pragma once
#include <vector>
class RenderQueue;
class Entity;
class Light;
class Pipeline3DBasic;
class Camera;

class Renderer
{
public:

	Renderer();
	void Render(RenderQueue* queue);
	void RenderEntity(Entity* entity);
	void RenderEntityBasic(Entity* entity);
	void SetLights(std::vector<Light*> lights);
	void SetCamera(Camera* camera);

private:

	//scene
	std::vector<Light*> _Lights;
	Camera* _Camera;

	//pipelines
	Pipeline3DBasic* _PLBasic3D;

};

