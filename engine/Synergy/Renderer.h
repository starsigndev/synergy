#pragma once
#include <vector>
class RenderQueue;
class Entity;
class Light;
class Pipeline3DBasic;
class Pipeline3DLight;
class PipelineDepth;
class PipelineActorDepth;
class Pipeline3DActorLight;
class Camera;
class RenderTargetCube;
class Node3D;
class SceneGraph;
class Actor;
class PipelineMeshLines;
class MeshLines;


class Renderer
{
public:

	Renderer();
	void Render(RenderQueue* queue);
	void RenderEntity(Entity* entity);
	void RenderActor(Actor* actor);
	void RenderMeshLines(MeshLines* mesh);
	void RenderEntityBasic(Entity* entity);
	void RenderEntityDepth(Entity* entity);
	void RenderActorDepth(Actor* actor);
	void RenderGraph(SceneGraph* graph);
	void RenderGraphDepth(SceneGraph* graph);
	void RenderNodeDepth(Node3D* node);
	void RenderShadows(SceneGraph* graph);
	void SetLights(std::vector<Light*> lights);
	void SetCamera(Camera* camera);
	void SetGraph(SceneGraph* graph) {
		_Graph = graph;
	}
	SceneGraph* GetGraph() {
		return _Graph;
	}


private:

	SceneGraph* _Graph;
	//scene
	std::vector<Light*> _Lights;
	Camera* _Camera;

	//pipelines
	Pipeline3DBasic* _PLBasic3D;
	Pipeline3DLight* _PLLight3D;
	Pipeline3DActorLight* _PLActorLight3D;
	PipelineMeshLines* _PLMeshLines;
	PipelineDepth* _PLDepth;
	PipelineActorDepth* _PLActorDepth;
	RenderTargetCube* _ShadowRT;
};

