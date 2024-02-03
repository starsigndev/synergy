#pragma once

#include <ctype.h>
#include "PxPhysicsAPI.h"
using namespace physx;

class PhysicsWorld
{
public:


	PhysicsWorld();
	void UpdateWorld(float dt);

	static PhysicsWorld* This;


	 PxDefaultAllocator		gAllocator;
	 PxDefaultErrorCallback	gErrorCallback;
	 PxFoundation* gFoundation = NULL;
	 PxPhysics* gPhysics = NULL;
	 PxDefaultCpuDispatcher* gDispatcher = NULL;
	 PxScene* gScene = NULL;
	PxMaterial* gMaterial = NULL;
	PxPvd* gPvd = NULL;


};

