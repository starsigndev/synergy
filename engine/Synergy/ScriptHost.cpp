#include "ScriptHost.h"
#include <iostream>
#include <assert.h>

ScriptHost* ScriptHost::_CurHost = nullptr;

// Print the script string to the standard output stream
void print(std::string& msg)
{
	printf("%s", msg.c_str());
}


int L_RegisterClass(lua_State* l) {

	auto name = lua_tostring(l, 1);
	ScriptHost::_CurHost->RegisterClass(name);
	std::cout << "Registered Class:" << name << std::endl;


	return 0;
}



sol::protected_function_result ScriptCall::Call() {

	return _Call();

}
ScriptHost::ScriptHost() {

	_L.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::string);



}

sol::protected_function_result ScriptHost::RunFile(std::string file) {

	return _L.script_file(file);
	

}

sol::protected_function_result ScriptHost::RunCode(std::string code) {
	ScriptHost::_CurHost = this;
	auto r= _L.script(code);
	ScriptHost::_CurHost = nullptr;
	return r;


}

ScriptCall* ScriptHost::GetCallCode(std::string code)
{
	ScriptCall* call = new ScriptCall;

	call->_Call = _L.load(code);

	return call;
}

ScriptCall* ScriptHost::GetCallFile(std::string path) {

	ScriptCall* call = new ScriptCall;

	call->_Call = _L.load_file(path);

	return call;

}


void ScriptHost::GetGlobal(std::string name) {

	lua_getglobal(_L, name.c_str());

}

void ScriptHost::PushString(std::string str) {

	lua_pushstring(_L, str.c_str());

}

void ScriptHost::Call(int pars) {

	lua_pcall(_L, pars, 0, 0);

}

void ScriptHost::GetTable(int index) {

	lua_gettable(_L, index);

}

void ScriptHost::GetMetaTable(int index) {

	//	luaL_getmetatable(_L, index);

}

void ScriptHost::GetMetaTable(std::string name) {

	luaL_getmetatable(_L, name.c_str());

}

void ScriptHost::SearchFunc(std::string name) {

	PushString(name);
	lua_rawget(_L, -1);

}

bool ScriptHost::IsFunction()
{
	return lua_isfunction(_L, -1);

}

void ScriptHost::PushPointer(void* pointer) {

	lua_pushlightuserdata(_L, pointer);

}



void ScriptHost::SetGlobal(std::string name) {

	lua_setglobal(_L, name.c_str());

}

void ScriptHost::RegisterFunc(std::string name, lua_CFunction myCFunc) {


	lua_register(_L, name.c_str(), myCFunc);

}

void ScriptHost::RegisterClass(std::string name) {

	_ClassNames.push_back(name);
}

std::map<std::string, std::vector<Param>> ScriptHost::ProcessClasses() {

	for (auto const& cls : _ClassNames) {
		_Classes[cls] = ProcessTable(cls);

	}
	return _Classes;
}



std::vector<Param> ScriptHost::ProcessTable(std::string name) {


	//ResetStack();
	GetGlobal(name);

	std::vector<Param> res;

	// Iterate through the fields of the "params" table
	lua_pushnil(_L);  // Start with a nil key
	while (lua_next(_L, -2) != 0) {
		Param new_p;
		// key at index -2 and value at index -1
	//	if (lua_isstring(_L, -2)) {
		std::string fieldName = lua_tostring(_L, -2);
		new_p.Name = fieldName;
		std::cout << "Field: " << fieldName << ", Type: " << lua_typename(_L, lua_type(_L, -1)) << std::endl;
		std::string type = lua_typename(_L, lua_type(_L, -1));
		//}
		if (type == "string")
		{
			new_p.Type = PT_String;
			new_p.ClassName = "string";
		}
		if (type == "number")
		{
			new_p.Type = PT_Number;
			new_p.ClassName = "float";
		}
		if (type == "table")
		{
			// Get the type of the nested table
			lua_pushstring(_L, "_type");
			lua_gettable(_L, -2);
			if (lua_isstring(_L, -1)) {
				std::string nestedTableType = lua_tostring(_L, -1);
				lua_pop(_L, 1); // Pop the nested table type
				// Include the nested table type in the name
				new_p.ClassName = nestedTableType;
				if (nestedTableType == "Vector3")
				{
					new_p.Type = PT_Vector3;
				}
				else
					if (nestedTableType == "Vector4")
					{
						new_p.Type = PT_Vector4;
					}
					else {
						new_p.Type = PT_ScriptClass;
					}



				//	auto nestedTable = ProcessTable(new_p.Name);
					//res.insert(res.end(), nestedTable.begin(), nestedTable.end());

			}
		}
		res.push_back(new_p);
		_Params;

		// You can add more conditions to handle other types if needed

		// Pop the value, leaving the key for the next iteration
		lua_pop(_L, 1);
	}

	// Pop the "params" table from the stack
	lua_pop(_L, 1);
	return res;
}

void ScriptHost::ProcessParams() {



}

void ScriptHost::SetParam(Param p, float value) {

	GetGlobal("params");
	PushString(p.Name.c_str());
	PushNumber(value);
	lua_settable(_L, -3);

	lua_pop(_L, 1);

}
void ScriptHost::SetParam(Param p, void* value)
{
	GetGlobal("params");
	PushString(p.Name.c_str());
	PushPointer(value);
	lua_settable(_L, -3);
	lua_pop(_L, 1);

}

void ScriptHost::PushNumber(float value) {

	lua_pushnumber(_L, value);

}

Param ScriptHost::GetParam(std::string name) {

	for (auto const& p : _Params) {
		if (name == p.Name)
		{
			return p;
		}
	}

}

void ScriptHost::ResetStack() {

	lua_settop(_L, 0);

}


float ScriptHost::ToNumber(int index) {

	return lua_tonumber(_L, index);

}

float ScriptHost::GetNumberFromTable(std::string table, std::string field) {

	GetGlobal(table);
	PushString(field);
	GetTable(-2);
	float r = (float)ToNumber(-1);
	lua_pop(_L, 2);
	return r;
}


void ScriptHost::SetNumberInTable(std::string table, std::string field, float value) {

	GetGlobal(table);
	PushNumber(value);
	lua_setfield(_L, -2, field.c_str());
	lua_pop(_L, 1);



}