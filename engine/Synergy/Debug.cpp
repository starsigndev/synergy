#include "Debug.h"
#include <assert.h>

void Debug::Error(std::string msg) {

	std::cout << "Error:" << msg << std::endl;
	assert(false);

}

void Debug::Assert(bool v, std::string msg)
{

	if (!v) {
		Error(msg);
	}

}