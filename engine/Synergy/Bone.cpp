#include "Bone.h"

Bone::Bone() {

	_NumPositions = _NumRotations = _NumScales = 0;
	_LocalTransform = glm::mat4(1.0f);

}

Bone::Bone(std::string name, int ID, aiNodeAnim* anim)
{
	_NumPositions = _NumRotations = _NumScales = 0;
	_LocalTransform = glm::mat4(1.0f);

	_Name = name;
	_ID = ID;

	_NumPositions = anim->mNumPositionKeys;
	_NumRotations = anim->mNumRotationKeys;
	_NumScales = anim->mNumScalingKeys;

	for (int i = 0; i < _NumPositions; ++i) {

		auto aPos = anim->mPositionKeys[i].mValue;
		float time = anim->mPositionKeys[i].mTime;

		KeyPosition key_pos(glm::vec3((float)aPos.x,(float)aPos.y,(float)aPos.z),time);
		_Positions.push_back(key_pos);


	}

	for (int i = 0; i < _NumRotations; ++i)
	{
		auto aRot = anim->mRotationKeys[i].mValue;
		float time = anim->mRotationKeys[i].mTime;

		KeyRotation key_rot(glm::quat((float)aRot.w, (float)aRot.x, (float)aRot.y, (float)aRot.z), time);
		_Rotations.push_back(key_rot);

	}

	for (int i = 0; i < _NumScales; ++i) {

		auto aScale = anim->mScalingKeys[i].mValue;
		float time = anim->mScalingKeys[i].mTime;

		KeyScale key_scale(glm::vec3((float)aScale.x, (float)aScale.y, (float)aScale.z), time);
		_Scales.push_back(key_scale);
	}


}

void Bone::Update(float anim_time) {

	glm::mat4 translation = InterpolatePosition(anim_time);
	glm::mat4 rotation = InterpolateRotation(anim_time);
	glm::mat4 scale = InterpolateScale(anim_time);

	_LocalTransform = translation * rotation * scale;

}

glm::mat4 Bone::GetLocalTransform()
{

	return _LocalTransform;

}

std::string Bone::GetBoneName() {

	return _Name;

}

int Bone::GetBoneID() {

	return _ID;

}

glm::mat4 Bone::InterpolatePosition(float time) {

	if (1 == _NumPositions)
	{
		return glm::translate(glm::mat4(1.0f),_Positions[0]._Position);
	}

	int p0Index = GetPositionIndex(time);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(_Positions[p0Index]._TimeStamp, _Positions[p1Index]._TimeStamp, time);
	glm::vec3 final_pos = glm::mix(_Positions[p0Index]._Position, _Positions[p1Index]._Position, scaleFactor);
	return glm::translate(glm::mat4(1.0f), final_pos);


}

glm::mat4 Bone::InterpolateRotation(float time) {

	if (1 == _NumRotations) {

		auto rot = glm::normalize(_Rotations[0]._Orientation);
		return glm::mat4_cast(rot);
	}

	int p0Index = GetRotationIndex(time);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(_Rotations[p0Index]._TimeStamp, _Rotations[p1Index]._TimeStamp, time);

	glm::quat q1, q2;

	q1 = _Rotations[p0Index]._Orientation;
	q2 = _Rotations[p1Index]._Orientation;

	glm::quat final_rot = glm::slerp(q1, q2, scaleFactor);
	return glm::mat4_cast(final_rot);

}

glm::mat4 Bone::InterpolateScale(float time) {

	if (1 == _NumScales)
	{
		return glm::translate(glm::mat4(1.0f), _Scales[0]._Scale);
	}

	int p0Index = GetScalingIndex(time);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(_Scales[p0Index]._TimeStamp, _Scales[p1Index]._TimeStamp, time);

	glm::vec3 final_scale = glm::mix(_Scales[p0Index]._Scale, _Scales[p1Index]._Scale, scaleFactor);
	return glm::translate(glm::mat4(1.0f), final_scale);


}


int Bone::GetPositionIndex(float time) {

	for (int index = 0; index < _NumPositions-1; ++index) {

		if (time < _Positions[index+1]._TimeStamp)
			return index;

	}

	return 0;

}

int Bone::GetRotationIndex(float time) {

	for (int index = 0; index < _NumRotations - 1; ++index) {

		if (time < _Rotations[index + 1]._TimeStamp)
			return index;

	}

	return 0;

}

int Bone::GetScalingIndex(float time) {

	for (int index = 0; index < _NumScales - 1; ++index) {

		if (time < _Scales[index + 1]._TimeStamp)
			return index;

	}

	return 0;

}

float Bone::GetScaleFactor(float last_time,float next_time,float anim_time) {

	float scale_factor = 0;
	float mid_way = anim_time - last_time;
	float frame_diff = next_time - last_time;
	scale_factor = mid_way / frame_diff;
	return scale_factor;

}