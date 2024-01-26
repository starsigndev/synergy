#pragma once
#include "NodeController.h"
#include <string>

class Node3D;

class NodeController
{
public:

	NodeController() {};
	void InitController(Node3D* node) {};
	void UpdateController(Node3D* node) {};
	void StopController(Node3D* node) {};

private:

	std::string _Name;

};

