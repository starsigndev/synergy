#include "SceneGraph.h"
#include "Node3D.h"
#include "StringHelper.h"

int graph_index = 0;

SceneGraph::SceneGraph() {

	graph_index++;
	_Name = StringHelper::AddToString("SceneGraph", graph_index);
	_RootNode = new Node3D;

}

void SceneGraph::AddNode(Node3D* node) {

	_RootNode->AddNode(node);

}

Node3D* SceneGraph::GetRootNode() {

	return _RootNode;

}

void SceneGraph::Update(float dt) {

	UpdateNode(_RootNode,dt);

}

void SceneGraph::UpdateNode(Node3D* node, float dt)
{

	node->UpdateNode(dt);

	for (auto const& sub : node->GetChildren()) {

		UpdateNode(sub, dt);

	}

}