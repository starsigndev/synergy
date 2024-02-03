#pragma once
#include "Node3D.h"
#include "PxPhysicsAPI.h"
using namespace physx;
class Mesh;


enum PhysicsType {
	PT_Box,PT_Sphere,PT_Capsule,PT_Convex,PT_Mesh,PT_None
};


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

	void SetPhysics(PhysicsType type) {
		_PhysicsType = type;
	}
	PhysicsType GetPhysics() {
		return _PhysicsType;
	}
	void CreatePhysics();
	glm::vec3 GetBounds();
	void BeginPlay();
	void StopPlay();
	void UpdateNode(float dt);
	Mesh* CreateSingleMesh();
private:

	std::vector<Mesh*> _Meshes;
	PhysicsType _PhysicsType = PhysicsType::PT_None;
	PxShape* _PyShape;
	PxRigidDynamic* _PyBody;
	PxRigidStatic* _PyStaticBody;




};

