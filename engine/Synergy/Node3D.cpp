#include "Node3D.h"
#include "StringHelper.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
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

void Node3D::Move(glm::vec3 offset) {

	offset = TransformVector(offset);
	_Position = _Position + offset;


}

void Node3D::LookAt(glm::vec3 position) {

	glm::mat4 lookAtMatrix = glm::lookAt(_Position, position, glm::vec3(0.0f, 1.0f, 0.0f));

	

	// Blank out the translation part of the look-at matrix
	lookAtMatrix[3][0] = 0.0f;
	lookAtMatrix[3][1] = 0.0f;
	lookAtMatrix[3][2] = 0.0f;

	lookAtMatrix = glm::inverse(lookAtMatrix);

	// Set the rotation matrix
	_Rotation = lookAtMatrix;


}

void Node3D::Rotate(float pitch, float yaw, float roll)
{

	pitch = glm::radians(pitch);
	yaw = glm::radians(yaw);

	_Rotation = glm::rotate(glm::mat4(1.0f),yaw,glm::vec3(0,1,0))* glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1, 0, 0));


}

void Node3D::Rotate(glm::vec3 rotation) {

	Rotate(rotation.x, rotation.y, rotation.z);

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

//Vector transform

glm::vec3 Node3D::TransformVector(glm::vec3 vector) {

	glm::vec4 trans_vec = _Rotation * glm::vec4(vector, 1.0f);
	return glm::vec3(trans_vec);

}

glm::vec3 Node3D::TransformPosition(glm::vec3 vector) {

	glm::vec4 trans_vec = GetWorldMatrix() * glm::vec4(vector, 1.0f);
	return glm::vec3(trans_vec);

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

void Node3D::Rotate(glm::vec3 rot, bool global)
{

	float pitch = glm::radians(rot.x);
	float yaw = glm::radians(rot.y);
	float roll = glm::radians(rot.z);


	glm::mat4 rm = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), roll, glm::vec3(0, 0, 1));

	if (global) {

		_Rotation = _Rotation * rm;

	}else{
		_Rotation = rm * _Rotation;
		
	}

}

void Node3D::PushDetails() {

	_PushedRotation = _Rotation;
	_PushedPosition = _Position;
	_PushedScale = _Scale;

}

void Node3D::PopDetails() {

	_Rotation = _PushedRotation;
	_Position = _PushedPosition;
	_Scale = _PushedScale;

}