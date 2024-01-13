#include "Animation.h"
#include "Actor.h"
#include <string>
#include <map>
#include "BoneInfo.h"

glm::mat4 ConvertAssimpMatrixToGLMMatrix2(const aiMatrix4x4& ai_mat) {
	glm::mat4 glm_mat;
	glm_mat[0][0] = ai_mat.a1; glm_mat[0][1] = ai_mat.b1; glm_mat[0][2] = ai_mat.c1; glm_mat[0][3] = ai_mat.d1;
	glm_mat[1][0] = ai_mat.a2; glm_mat[1][1] = ai_mat.b2; glm_mat[1][2] = ai_mat.c2; glm_mat[1][3] = ai_mat.d2;
	glm_mat[2][0] = ai_mat.a3; glm_mat[2][1] = ai_mat.b3; glm_mat[2][2] = ai_mat.c3; glm_mat[2][3] = ai_mat.d3;
	glm_mat[3][0] = ai_mat.a4; glm_mat[3][1] = ai_mat.b4; glm_mat[3][2] = ai_mat.c4; glm_mat[3][3] = ai_mat.d4;
	return glm_mat;
}


Animation::Animation(const aiScene* scene, aiAnimation* anim, Actor* actor)
{

	_RootNode = new AssimpNodeData;

	_Duration = anim->mDuration;
	_TicksPerSecond = anim->mTicksPerSecond;

	ReadHeirarchy(_RootNode, scene->mRootNode);
	ReadMissingBones(anim, actor);
	_Name = anim->mName.C_Str();


}

void Animation::ReadMissingBones(aiAnimation* anim, Actor* actor) {

	int size = anim->mNumChannels;

	std::map<std::string,BoneInfo*>& bone_map = actor->GetBoneInfoMap();
	int& bone_count = actor->GetBoneCount();

	for (int i = 0; i < size; i++) {

		auto chan = anim->mChannels[i];
		std::string boneName = chan->mNodeName.C_Str();

		if (bone_map.find(boneName) == bone_map.end()) {

			BoneInfo *nbone = new BoneInfo;
			bone_map[boneName] = nbone;
			bone_map[boneName]->SetID(bone_count);

			bone_count++;
			

		}

		_Bones.push_back(new Bone(chan->mNodeName.C_Str(), bone_map[chan->mNodeName.C_Str()]->GetID(), chan));

	}

	_BoneinfoMap = bone_map;

}

void Animation::ReadHeirarchy(AssimpNodeData* dest, aiNode* node) {

	dest->_Name = node->mName.C_Str();
	auto trans = node->mTransformation;

	dest->_Transform = ConvertAssimpMatrixToGLMMatrix2(node->mTransformation);

	dest->_ChildrenCount = node->mNumChildren;

	for (int i = 0; i < node->mNumChildren; i++) {

		auto newData = new AssimpNodeData;
		ReadHeirarchy(newData, node->mChildren[i]);
		dest->_Children.push_back(newData);

	}

}

Bone* Animation::FindBone(std::string name) {

	for (auto const& bone : _Bones)
	{
		if (bone->GetBoneName() == name)
		{
			return bone;
		}
	}
	return nullptr;
}