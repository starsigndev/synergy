#pragma once
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <vector>
#include <string>

class Node3D
{
public:

	//constructors
	Node3D();

	//transform
	void ResetTransform();

	virtual glm::mat4 GetWorldMatrix();

	void SetPosition(glm::vec3 position);
	void SetRotation(glm::mat4 rotation);
	void SetScale(glm::vec3 scale);
	void Move(glm::vec3 offset);

	void Rotate(float pitch, float yaw, float roll = 0);
	void Rotate(glm::vec3 rotation);

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

	//General
	void SetName(std::string name);
	std::string GetName();

	virtual void UpdateNode() {};



private:

	//Transform
	glm::mat4 _Rotation;
	glm::vec3 _Position;
	glm::vec3 _Scale;

	//General
	std::string _Name;

	//Graph
	Node3D* _RootNode;
	std::vector<Node3D*> _Nodes;


};

