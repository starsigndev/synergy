#pragma once
#include "glm/glm.hpp"
#include "glm/ext/matrix_common.hpp"
#include <vector>

class Actor;
class Animation;
class AssimpNodeData;

class Animator
{
public:

	Animator(Animation* animation);
	void SetTime(float time);
	void CalculateBoneTransform(AssimpNodeData* data, glm::mat4 parent_transform);
	void UpdateAnimation(float dt);
	void StopAnimation();
	const glm::mat4* GetFinalBoneMatrices() const {
		return _FinalBoneMatrices;
	}
	bool GetPlaying() {
		return _Playing;
	}
	void Update();

private:

	bool _Playing = false;
	Actor* _Actor;
	glm::mat4 _FinalBoneMatrices[100];
	float _Speed = 0.025f;
	Animation* _CurrentAnimation = nullptr;
	std::vector<Animation*> _Animations;
	float _CurrentTime = 0.0f;
	float _DeltaTime = 0.0f;

};

