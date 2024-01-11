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

private:

	//Graph
	Node3D* _RootNode;

	//General
	std::string _Name;

};

