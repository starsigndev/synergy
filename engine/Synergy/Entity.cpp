#include "Entity.h"

Entity::Entity() {


}

void Entity::AddMesh(Mesh* mesh) {

	_Meshes.push_back(mesh);

}

int Entity::MeshCount() {

	return _Meshes.size();

}

Mesh* Entity::GetMesh(int index) {

	return _Meshes[index];

}
