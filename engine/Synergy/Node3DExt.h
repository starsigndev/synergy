#pragma once
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


int TestFunc(lua_State* state);

int TurnNode(lua_State* state);