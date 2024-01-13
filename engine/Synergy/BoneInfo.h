#pragma once
#include "glm/glm.hpp"

class BoneInfo
{
public:

	BoneInfo();
	void SetID(int id);
	void SetOffset(glm::mat4 offset);
	glm::mat4 GetOffset() {
		return _Offset;
	}
	int GetID();

private:

	int _ID = 0;
	glm::mat4 _Offset;

};

