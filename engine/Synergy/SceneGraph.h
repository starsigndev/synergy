#pragma once
#include <vector>
#include <string>
#include "glm//glm.hpp"

class Node3D;
class Entity;
class Mesh;
class Camera;
class PhysicsWorld;

struct CastHit {

	glm::vec3 position;
	glm::vec3 normal;
	float distance = 0;
	Node3D* node = nullptr;
	Entity* entity = nullptr;
	Mesh* mesh = nullptr;
	bool hit = false;

};

class SceneGraph
{
public:

	//Constructors
	SceneGraph();

	//Graph
	void AddNode(Node3D* node);
	Node3D* GetRootNode();
	void Update(float dt);

	CastHit MouseRaycast(glm::vec2 pos,Camera* camera,float width,float height);
	CastHit MouseRaycast(glm::vec2 pos, Camera* camera, float width, float height,Entity* entity);
	CastHit Raycast(glm::vec3 pos, glm::vec3 dir);
	CastHit Raycast(glm::vec3 pos, glm::vec3 dir, std::vector<Mesh*> meshes);
	std::vector<Mesh*> GetMeshes();
	std::vector<Mesh*> GetMeshes(std::vector<Mesh*> meshes,Node3D* node);

	//Play
	void BeginPlay();
	
	void StopNode(Node3D* node);
	void BeginNode(Node3D* node);
	void UpdatePlay(float dt);
	void StopPlay();
	void PausePlay();
	void UpdateNode(Node3D* node,float dt);


private:

	//Graph
	Node3D* _RootNode;

	//General
	std::string _Name;

	PhysicsWorld* _Physics = nullptr;

};

