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
	std::vector<Mesh*> GetMeshes() {
		return _Meshes;
	}

private:

	std::vector<Mesh*> _Meshes;

};

