#pragma once
#include "Node3D.h"

class Mesh;

class Entity : public Node3D
{
public:

	Entity();

	//Meshes
	void AddMesh(Mesh* mesh);
	int MeshCount();
	Mesh* GetMesh(int index);
	void UpdateNode() {};


private:

	std::vector<Mesh*> _Meshes;

};

