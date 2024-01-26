#pragma once
#include <vector>
#include <string>

class SynObject
{
public:

	virtual std::string ObjectTypeName() {
		return "SynObject";
	}

	virtual std::string ObjectID() {
		return "EMPTY";
	}
	

};

