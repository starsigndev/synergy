#include "Entity.h"
#include "Mesh.h"
#include "PhysicsWorld.h"
#include "glm/glm.hpp"
#include "glm/ext/quaternion_common.hpp"
#include "glm/gtc/quaternion.hpp"

Entity::Entity() {


}

void Entity::AddMesh(Mesh* mesh) {

	_Meshes.push_back(mesh);
	mesh->SetOwner(this);

}

int Entity::MeshCount() {

	return _Meshes.size();

}

Mesh* Entity::GetMesh(int index) {

	return _Meshes[index];

}

glm::vec3 Entity::GetBounds() {

	int sx = 10000;
	int sy = 10000;
	int sz = 10000;
	int bx = -sx;
	int by = -sy;
	int bz = -sz;

	for (auto const& mesh : _Meshes)
	{

		for (auto const& vertex : mesh->GetVertices())
		{
			if (vertex.position.x < sx) sx = vertex.position.x;
			if (vertex.position.y < sy) sy = vertex.position.y;
			if (vertex.position.z < sz) sz = vertex.position.z;
			if (vertex.position.x > bx) bx = vertex.position.x;
			if (vertex.position.y > by) by = vertex.position.y;
			if (vertex.position.z > bz) bz = vertex.position.z;
		}

	}

	return glm::vec3(bx - sx, by - sy, bz - sz);

}



// Setup common cooking params
void setupCommonCookingParams(PxCookingParams& params, bool skipMeshCleanup, bool skipEdgeData)
{
	// we suppress the triangle mesh remap table computation to gain some speed, as we will not need it 
// in this snippet
	params.suppressTriangleMeshRemapTable = true;

	// If DISABLE_CLEAN_MESH is set, the mesh is not cleaned during the cooking. The input mesh must be valid. 
	// The following conditions are true for a valid triangle mesh :
	//  1. There are no duplicate vertices(within specified vertexWeldTolerance.See PxCookingParams::meshWeldTolerance)
	//  2. There are no large triangles(within specified PxTolerancesScale.)
	// It is recommended to run a separate validation check in debug/checked builds, see below.

	if (!skipMeshCleanup)
		params.meshPreprocessParams &= ~static_cast<PxMeshPreprocessingFlags>(PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH);
	else
		params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH;

	// If eDISABLE_ACTIVE_EDGES_PRECOMPUTE is set, the cooking does not compute the active (convex) edges, and instead 
	// marks all edges as active. This makes cooking faster but can slow down contact generation. This flag may change 
	// the collision behavior, as all edges of the triangle mesh will now be considered active.
	if (!skipEdgeData)
		params.meshPreprocessParams &= ~static_cast<PxMeshPreprocessingFlags>(PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE);
	else
		params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE;
}
PxQuat glmQuatToPxQuat(const glm::quat& glmQuat) {
	return PxQuat(glmQuat.x, glmQuat.y, glmQuat.z, glmQuat.w);
}
glm::quat mat4ToQuat2(const glm::mat4& rotationMatrix) {
	return glm::quat_cast(rotationMatrix);
}
glm::mat4 physxQuatToMat4(const PxQuat& physxQuat) {
	glm::quat glmQuat(physxQuat.w, physxQuat.x, physxQuat.y, physxQuat.z);
	return glm::mat4_cast(glmQuat);
}
void Entity::CreatePhysics() {

	auto gMaterial = PhysicsWorld::This->gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	auto size = GetBounds();

	switch (_PhysicsType) {
	case PT_Sphere:
	{
		PxQuat rot = glmQuatToPxQuat(mat4ToQuat2(_Rotation));
		_PyShape = PhysicsWorld::This->gPhysics->createShape(PxSphereGeometry(size.x), *gMaterial);
		PxTransform localTm(_Position.x, _Position.y, _Position.z, rot);
		_PyBody = PhysicsWorld::This->gPhysics->createRigidDynamic(localTm);
		_PyBody->attachShape(*_PyShape);
		PxRigidBodyExt::updateMassAndInertia(*_PyBody, 10.0f);
		PhysicsWorld::This->gScene->addActor(*_PyBody);
	}
		break;
	case PT_Box:
	{

		PxQuat rot = glmQuatToPxQuat(mat4ToQuat2(_Rotation));
		_PyShape = PhysicsWorld::This->gPhysics->createShape(PxBoxGeometry(size.x / 2, size.y / 2, size.z / 2), *gMaterial);
		PxTransform localTm(_Position.x,_Position.y,_Position.z, rot);
		_PyBody = PhysicsWorld::This->gPhysics->createRigidDynamic(localTm);
		_PyBody->attachShape(*_PyShape);
		PxRigidBodyExt::updateMassAndInertia(*_PyBody, 10.0f);
		PhysicsWorld::This->gScene->addActor(*_PyBody);

	}
		break;
	case PT_Mesh:
	{
		Mesh* mesh = CreateSingleMesh();
		auto vdata = mesh->GetVertices();
		auto tdata = mesh->GetTriangles();

		PxVec3* vertices = new PxVec3[mesh->GetVertices().size()];
		PxU32* indices = new PxU32[mesh->GetTriangles().size() * 3];

		int i = 0;

		for (auto const& v : mesh->GetVertices()) {

			vertices[i] = PxVec3(v.position.x, v.position.y, v.position.z);

			i++;
		}
		
		i = 0;
		for (auto const& t : mesh->GetTriangles()) {

			indices[i++] = (PxU32)t.V0;
			indices[i++] = (PxU32)t.V1;
			indices[i++] = (PxU32)t.V2;


		}
		
		PxQuat rot = PxQuat(physx::PxIdentity);
		PxTransform localTm(0, 0, 0, rot);
		PxTriangleMeshDesc desc;
		desc.points.count = mesh->GetVertices().size();
		desc.points.stride = sizeof(PxVec3);
		desc.points.data = vertices;

		desc.triangles.count = mesh->GetTriangles().size();
		desc.triangles.stride = 3 * sizeof(PxU32);
		desc.triangles.data = indices;

		PxTolerancesScale scale;
		PxCookingParams params(scale);
		params.midphaseDesc = PxMeshMidPhase::eBVH33;

		// setup common cooking params
		setupCommonCookingParams(params, true, false);

		params.midphaseDesc.mBVH33Desc.meshCookingHint = PxMeshCookingHint::eSIM_PERFORMANCE;

		auto tris = PxCreateTriangleMesh(params, desc, PhysicsWorld::This->gPhysics->getPhysicsInsertionCallback());



		PxTriangleMeshGeometry trigeo = PxTriangleMeshGeometry(tris);


		_PyStaticBody = PhysicsWorld::This->gPhysics->createRigidStatic(localTm);
		_PyShape = PhysicsWorld::This->gPhysics->createShape(trigeo,*gMaterial);

		_PyStaticBody->attachShape(*_PyShape);

		PhysicsWorld::This->gScene->addActor(*_PyStaticBody);





		 //PxCreateStatic(PhysicsWorld::This->gPhysics,localTm, PxTriangleMeshGeometry(tris));

		 




//		Physics::GetCooking()->setParams(params);

		//auto res = Physics::GetCooking()->validateTriangleMesh(meshDesc);

		//triMesh = Physics::GetCooking()->createTriangleMesh(meshDesc, Physics::GetSDK()->getPhysicsInsertionCallback());



		//PxTriangleMesh* triMesh = PhysicsWorld::This->gPhysics->createTriangleMesh(desc);

		//PxCreateStatic(*PhysicsWorld::This->gPhysics, localTm, *triMesh);

		int b = 5;

	}
		break;
	}

}

Mesh* Entity::CreateSingleMesh() {

	Mesh* res = new Mesh;

	for (auto const& mesh : _Meshes) {

		int tc = 0;

		for (auto const& v : mesh->GetVertices()) {

			res->AddVertex(v);
			

		}

		for (auto const& t : mesh->GetTriangles()) {

			Triangle nt;

			nt.V0 = tc + t.V0;
			nt.V1 = tc + t.V1;
			nt.V2 = tc + t.V2;

			res->AddTriangle(nt);

		}

		tc = tc + mesh->GetVertices().size();


	}

	return res;

}

void Entity::BeginPlay() {

	PushDetails();
	CreatePhysics();

}

void Entity::StopPlay() {

	PopDetails();
	switch (_PhysicsType) {
	case PT_Sphere:
	case PT_Box:
		
		PhysicsWorld::This->gScene->removeActor(*_PyBody);
		_PyBody->release();
		_PyBody = nullptr;

		break;
	case PT_Mesh:
		PhysicsWorld::This->gScene->removeActor(*_PyStaticBody);
		_PyStaticBody->release();
		_PyStaticBody = nullptr;
		break;
	}
	int b = 5;

}

void Entity::UpdateNode(float dt)
{

	Node3D::UpdateNode(dt);

	if (_PyBody) {

		auto pose = _PyBody->getGlobalPose();

		_Position = glm::vec3(pose.p.x, pose.p.y, pose.p.z);
		_Rotation = physxQuatToMat4(pose.q);
	}

	int b = 5;

}