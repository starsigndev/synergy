#include "BoneInfo.h"

BoneInfo::BoneInfo() {

	_Offset = glm::mat4(1.0f);
	_ID = 0;

}

void BoneInfo::SetID(int id) {

	_ID = id;

}

int BoneInfo::GetID() {

	return _ID;

}

void BoneInfo::SetOffset(glm::mat4 offset) {

	_Offset = offset;

}