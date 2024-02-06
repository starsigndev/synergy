#include "Node3DExt.h"
#include <iostream>
#include "Node3D.h"

int TestFunc(lua_State* l) {

	auto node = (Node3D*)lua_touserdata(l, 1);

	std::cout << "N:" << node->GetName() << std::endl;

	return 0;
}

int TurnNode(lua_State* l) {

	auto node = (Node3D*)lua_touserdata(l, 1);
	float p, y, r;
	p = (float)lua_tonumber(l, 2);
	y = (float)lua_tonumber(l, 3);
	r = (float)lua_tonumber(l, 4);
	int glob =  lua_toboolean(l, 5);
	
	if (glob == 1) {
		node->Rotate(glm::vec3(p, y, r), true);
	}
	else {
		node->Rotate(glm::vec3(p, y, r), false);
	}
	return 0;
}