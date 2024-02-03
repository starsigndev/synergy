#include "ScriptHost.h"

ScriptHost::ScriptHost() {

	_L = luaL_newstate();
	luaL_openlibs(_L);


}

void ScriptHost::Run(std::string file) {

	luaL_dofile(_L, file.c_str());

}