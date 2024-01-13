#pragma once
#include <string>

class Node3D;

class Importer
{
public:

	Node3D* ImportNode(std::string path);
	Node3D* ImportActor(std::string path);

private:


};

