#include "Node3D.h"
#include "StringHelper.h"

int node_index = 0;

//Constructors

Node3D::Node3D() {

	node_index++;
	_Name = StringHelper::AddToString("Node", node_index);
	_RootNode = nullptr;
	_Nodes.clear();

	ResetTransform();


}

//Transforms

void Node3D::ResetTransform()
{

	_Rotation = glm::mat4(1.0f);
	_Position = glm::vec3(0, 0, 0);
	_Scale = glm::vec3(1, 1, 1);

}

glm::mat4 Node3D::GetWorldMatrix() {

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), _Scale);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), _Position);

	// Assuming _Rotation is already a 4x4 matrix representing rotation
	glm::mat4 localMatrix = translationMatrix * _Rotation * scaleMatrix;

	// If this node has a parent, apply its transformation as well
	if (_RootNode != nullptr) {
		return _RootNode->GetWorldMatrix() * localMatrix;
	}
	else {
		return localMatrix; // No parent, return the local transformation
	}

}

void Node3D::SetPosition(glm::vec3 position) {

	_Position = position;

}

void Node3D::SetRotation(glm::mat4 rotation) {

	_Rotation = rotation;

}

void Node3D::SetScale(glm::vec3 scale) {
	
	_Scale = scale;

}


glm::vec3 Node3D::GetPosition() {

	return _Position;

}

glm::mat4 Node3D::GetRotation() {

	return _Rotation;

}

glm::vec3 Node3D::GetScale() {

	return _Scale;

}

//Graph

void Node3D::SetRootNode(Node3D* node) {

	_RootNode = node;

}

void Node3D::AddNode(Node3D* node)
{

	node->SetRootNode(this);
	_Nodes.push_back(node);

}

int Node3D::NodeCount() {

	return _Nodes.size();

}

Node3D* Node3D::GetNode(int index) {

	return _Nodes[index];

}


//General

void Node3D::SetName(std::string name) {

	_Name = name;

}

std::string Node3D::GetName() {

	return _Name;

}