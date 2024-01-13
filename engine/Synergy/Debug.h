#pragma once

#include <string>
#include <iostream>

class Debug
{
public:

	static void Error(std::string msg);
	static void Assert(bool v, std::string msg);

private:
};

