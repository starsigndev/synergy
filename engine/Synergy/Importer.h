#pragma once
#include <string>

class Node3D;
class Resource;

class Importer
{
public:

	Node3D* ImportNode(std::string path);
	Node3D* ImportNodeFromMemory(char* data, int size);
	Node3D* ImportNodeFromResource(Resource* resource);
	Node3D* ImportActor(std::string path);


private:


};

