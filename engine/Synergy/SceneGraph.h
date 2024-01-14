#pragma once
#include <vector>
#include <string>

class Node3D;

class SceneGraph
{
public:

	//Constructors
	SceneGraph();

	//Graph
	void AddNode(Node3D* node);
	Node3D* GetRootNode();
	void Update(float dt);
	void UpdateNode(Node3D* node, float dt);

private:

	//Graph
	Node3D* _RootNode;

	//General
	std::string _Name;

};

