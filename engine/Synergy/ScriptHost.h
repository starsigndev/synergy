#pragma once
#include <string>
#include <vector>
#include <map>
#include "sol/sol.hpp"
 

enum ParamType {
	PT_Number,PT_String,PT_NIL,PT_Bool,PT_Vector3,PT_Vector4,PT_Matrix4,PT_ScriptClass
};

struct Param {
	
	std::string Name;
	ParamType Type;
	std::string ClassName;

	
};


class ScriptCall {

public:

	sol::protected_function_result Call();

	sol::load_result _Call;

};


class ScriptHost
{
public:
	ScriptHost();
	ScriptCall* GetCallFile(std::string path);
	ScriptCall* GetCallCode(std::string code);

	sol::protected_function_result RunFile(std::string path);
	sol::protected_function_result RunCode(std::string code);
	void GetGlobal(std::string name);
	void PushString(std::string str);
	void PushNumber(float value);
	void Call(int pars);
	void GetTable(int index);
	void GetMetaTable(int index);
	void GetMetaTable(std::string name);
	void SearchFunc(std::string name);
	bool IsFunction();
	void PushPointer(void* pointer);
	//void RunCode(std::string code);
	void SetGlobal(std::string name);
	void RegisterFunc(std::string name, lua_CFunction myCFunc);
	void ProcessParams();
	std::vector<Param> ProcessTable(std::string table);
	std::map<std::string, std::vector<Param>> ProcessClasses();
	Param GetParam(std::string name);
	std::vector<Param> GetParams() {
		return _Params;
	}
	void SetParam(Param p, float value);
	void SetParam(Param p, void* value);
	void ResetStack();
	void RegisterClass(std::string name);
	static ScriptHost* _CurHost;
	void SetParams(std::vector<Param> params)
	{
		_Params = params;
	}
	float GetNumberFromTable(std::string table, std::string field);
	void SetNumberInTable(std::string table, std::string field, float value);
	float ToNumber(int index);



private:

	sol::state _L;
	std::vector<Param> _Params;

	std::map<std::string, std::vector<Param>> _Classes;
	std::vector<std::string> _ClassNames;
	
};

