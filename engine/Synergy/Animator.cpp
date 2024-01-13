#include "Animator.h"
#include "Actor.h"
#include "Animation.h"
#include "AssimpNodeData.h"
#include "BoneInfo.h"

Animator::Animator(Animation* animation) {

	_CurrentTime = 0.0f;
	_CurrentAnimation = animation;

	for (int i = 0; i < 100; i++) {

		_FinalBoneMatrices[i] = glm::mat4(1.0f);

	}

}

void Animator::SetTime(float time) {

	_CurrentTime = time;
	//CalculateBoneTransform;


}

void Animator::UpdateAnimation(float dt) {

	_DeltaTime = dt;
	if (_CurrentAnimation != nullptr) {
		_CurrentTime += _CurrentAnimation->GetTicksPerSecond() * dt;
		_CurrentTime = std::fmod(_CurrentTime, _CurrentAnimation->GetDuration());
	}
	CalculateBoneTransform(_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));

}

void Animator::StopAnimation() {

	for (int i = 0; i < 100; i++)
		_FinalBoneMatrices[i] = glm::mat4(1.0f);

	_CurrentTime = 0.0f;
	_Playing = false;

}

void Animator::Update() {

	if (!_Playing) return;
	_CurrentTime = _CurrentTime + _CurrentAnimation->GetTicksPerSecond() / 120.0f;
	if (_CurrentTime > _CurrentAnimation->GetDuration()) {
		_CurrentTime = 0;
	}
	SetTime(_CurrentTime);
}

void Animator::CalculateBoneTransform(AssimpNodeData* node, glm::mat4 parent_transform)
{

	std::string name = node->_Name;
	glm::mat4 nodeTransform = node->_Transform;

	Bone* bone = _CurrentAnimation->FindBone(name);

	if (bone != nullptr) {

		bone->Update(_CurrentTime);
		nodeTransform = bone->GetLocalTransform();

	}

	glm::mat4 global_transform = parent_transform * nodeTransform;

	std::map<std::string, BoneInfo*>& bmap = _CurrentAnimation->GetBoneIDMap();

	if (bmap.find(name) == bmap.end()) {
		//not found
	}
	else {
		int index = bmap[name]->GetID();
		glm::mat4 offset = bmap[name]->GetOffset();
		_FinalBoneMatrices[index] = global_transform * offset;
	}

	for (int i = 0; i < node->_ChildrenCount; i++) {
		CalculateBoneTransform(node->_Children[i], global_transform);
	}

}