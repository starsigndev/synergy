#include "QueueRenderScene.h"
#include "Renderer.h"
#include "SceneGraph.h"
#include "Entity.h"
#include "Actor.h"
QueueRenderScene::QueueRenderScene(SceneGraph* graph) {

	_Graph = graph;

}

void QueueRenderScene::Render(Renderer* renderer)
{

	int a = 5;
	RenderNode(renderer,_Graph->GetRootNode());



}

void QueueRenderScene::RenderNode(Renderer* renderer,Node3D* node) {

    Entity* entity = dynamic_cast<Entity*>(node);
    if (entity) {


        renderer->RenderEntity(entity);

        // node is actually of type Entity
  //      std::cout << "Node is an Entity." << std::endl;
    }
    else {
        Actor* actor = dynamic_cast<Actor*>(node);
        if (actor) {
            // node is just a Node3D
            renderer->RenderActor(actor);
        }

    }
    for (int i = 0;i < node->NodeCount();i++) {
        RenderNode(renderer,node->GetNode(i));
    }
}