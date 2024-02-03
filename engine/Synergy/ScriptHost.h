#pragma once
#include <string>
#include <vector>

// include Lua headers
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

class ScriptHost
{
public:
	ScriptHost();
	void Run(std::string path);
private:
	lua_State* _L;

};

