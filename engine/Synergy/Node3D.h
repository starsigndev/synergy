#pragma once
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <vector>
#include <string>
#include "SynObject.h"

class ScriptHost;
class ScriptModule;


class Node3D : public SynObject
{
public:

	int value = 25;
	//constructors
	Node3D();

	std::string ObjectTypeName() {
		return "Node3D";
	}

	std::string ObjectID() {
		return "Node:" + _Name;
	}

	//transform
	void ResetTransform();

	virtual glm::mat4 GetWorldMatrix();

	void SetPosition(glm::vec3 position);
	void SetRotation(glm::mat4 rotation);
	void SetScale(glm::vec3 scale);
	void Move(glm::vec3 offset);
	void Rotate(glm::vec3 rotate, bool global=false);
	void Rotate(float pitch, float yaw, float roll = 0);
	void Rotate(glm::vec3 rotation);
	

	void LookAt(glm::vec3 position);

	glm::vec3 GetPosition();
	glm::mat4 GetRotation();
	glm::vec3 GetScale();

	//Vector Transforms
	glm::vec3 TransformVector(glm::vec3 vector);
	glm::vec3 TransformPosition(glm::vec3 vector);


	

	//Graph
	void SetRootNode(Node3D* root);
	void AddNode(Node3D* node);

	int NodeCount();
	Node3D* GetNode(int index);
	std::vector<Node3D*> GetChildren() {
		return _Nodes;
	}

	//General
	void SetName(std::string name);
	std::string GetName();

	virtual void UpdateNode(float dt);

	std::vector<Node3D*> GetNodes() {
		return _Nodes;
	}

	virtual void BeginPlay() {};
	virtual void StopPlay() {};

	virtual void PushDetails();
	virtual void PopDetails();

	virtual void AddScript(std::string path);
	ScriptHost* GetHost() {
		return _ScriptHost;
	}
protected:

	//Transform
	glm::mat4 _Rotation;
	glm::vec3 _Position;
	glm::vec3 _Scale;

	glm::mat4 _PushedRotation;
	glm::vec3 _PushedPosition;
	glm::vec3 _PushedScale;

	//General
	std::string _Name;

	//Graph
	Node3D* _RootNode;
	std::vector<Node3D*> _Nodes;

	//script
	ScriptHost* _ScriptHost;
	ScriptModule* _MathsModule;

};

