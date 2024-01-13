#pragma once
#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/ext/quaternion_common.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext/matrix_transform.hpp"
//#include <glm/glm.hpp>

//#include <glm/gtc/quaternion.hpp>

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct KeyPosition {

	glm::vec3 _Position;
	float _TimeStamp;
	KeyPosition(glm::vec3 position, float time) {

		_Position = position;
		_TimeStamp = time;

	}

};

struct KeyRotation {

	glm::quat _Orientation;
	float _TimeStamp;
	KeyRotation(glm::quat orientation, float time) {
	
		_Orientation = orientation;
		_TimeStamp = time;

	}

};


struct KeyScale {

	glm::vec3 _Scale;
	float _TimeStamp;
	KeyScale(glm::vec3 scale, float time) {

		_Scale = scale;
		_TimeStamp = time;

	}

};

class Bone
{
public:

	Bone();
	Bone(std::string name, int ID, aiNodeAnim* anim);
	void Update(float anim_time);
	glm::mat4 GetLocalTransform();
	std::string GetBoneName();
	int GetBoneID();
	glm::mat4 InterpolatePosition(float time);
	glm::mat4 InterpolateRotation(float time);
	glm::mat4 InterpolateScale(float time);

	float GetScaleFactor(float last_time, float next_time, float anim_time);
	int GetPositionIndex(float time);
	int GetRotationIndex(float time);
	int GetScalingIndex(float time);


private:

	std::vector<KeyPosition> _Positions;
	std::vector<KeyRotation> _Rotations;
	std::vector<KeyScale> _Scales;
	int _NumPositions;
	int _NumRotations;
	int _NumScales;

	glm::mat4 _LocalTransform;
	std::string _Name;
	int _ID = 0;

};

