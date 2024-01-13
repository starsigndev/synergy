#pragma once

#include<vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "AssimpNodeData.h"
#include "Bone.h"
#include <map>
class Actor;
class BoneInfo;


class Animation
{
public:

	Animation(const aiScene* scene, aiAnimation* anim, Actor* actor);
	void ReadHeirarchy(AssimpNodeData* dest, aiNode* src);
	void ReadMissingBones(aiAnimation* anim, Actor* actor);
	std::map<std::string, BoneInfo*>& GetBoneIDMap() {
		return _BoneinfoMap;
	}
	Bone* FindBone(std::string name);
	float GetTicksPerSecond() {
		return _TicksPerSecond;
	}
	float GetDuration() {
		return _Duration;
	}
	AssimpNodeData* GetRootNode() {
		return _RootNode;
	}
private:

	float _Duration = 0;
	int _TicksPerSecond = 0;
	std::string _Name;
	std::string _AnimPath;
	float _Priority;
	std::vector<Bone*> _Bones;
	AssimpNodeData* _RootNode;
	std::map<std::string, BoneInfo*> _BoneinfoMap;

};

