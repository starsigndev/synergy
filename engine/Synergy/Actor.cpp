#include "Actor.h"

#include "Vertex3D.h"
#include "BoneInfo.h"
#include "Debug.h"
#include "Mesh.h"
#include "Animator.h"


glm::mat4 ConvertAssimpMatrixToGLMMatrix(const aiMatrix4x4& ai_mat) {
	glm::mat4 glm_mat;
	glm_mat[0][0] = ai_mat.a1; glm_mat[0][1] = ai_mat.b1; glm_mat[0][2] = ai_mat.c1; glm_mat[0][3] = ai_mat.d1;
	glm_mat[1][0] = ai_mat.a2; glm_mat[1][1] = ai_mat.b2; glm_mat[1][2] = ai_mat.c2; glm_mat[1][3] = ai_mat.d2;
	glm_mat[2][0] = ai_mat.a3; glm_mat[2][1] = ai_mat.b3; glm_mat[2][2] = ai_mat.c3; glm_mat[2][3] = ai_mat.d3;
	glm_mat[3][0] = ai_mat.a4; glm_mat[3][1] = ai_mat.b4; glm_mat[3][2] = ai_mat.c4; glm_mat[3][3] = ai_mat.d4;
	return glm_mat;
}

Actor::Actor() {

	//_Position = glm::vec3(0, 0, 0);
	//_Rotation = glm::mat4(1.0f);
	//_Scale 


}


void Actor::AddMesh(Mesh* mesh) {

	_Meshes.push_back(mesh);

}

int Actor::MeshCount() {

	return _Meshes.size();

}

Mesh* Actor::GetMesh(int index) {

	return _Meshes[index];

}

std::map<std::string, BoneInfo*>& Actor::GetBoneInfoMap() {

	return _BoneInfoMap;

}

int& Actor::GetBoneCount() {

	return _BoneCounter;

}

Vertex Actor::SetVertexBoneData(Vertex vertex, int boneID, float weight) {

	if (vertex.boneids.x < 0) {

		vertex.boneids.x = boneID;
		vertex.weights.x = weight;
		return vertex;
	}

	if (vertex.boneids.y < 0) {

		vertex.boneids.y = boneID;
		vertex.weights.y = weight;
		return vertex;
	}

	if (vertex.boneids.z < 0) {

		vertex.boneids.z = boneID;
		vertex.weights.z = weight;
		return vertex;
	}

	if (vertex.boneids.w < 0) {

		vertex.boneids.w = boneID;
		vertex.weights.w = weight;
		return vertex;
	}

	return vertex;


}

void Actor::ExtractBoneWeightForMesh(Mesh* mesh, aiMesh* aMesh,const aiScene* aScene)
{

	for (int boneIndex = 0; boneIndex < aMesh->mNumBones; boneIndex++) {

		int boneID = -1;
		std::string boneName = aMesh->mBones[boneIndex]->mName.C_Str();
		if (_BoneInfoMap.find(boneName) == _BoneInfoMap.end()) {
			// Code for when the boneName is not in the map
			BoneInfo* bone = new BoneInfo;

			auto a_os = aMesh->mBones[boneIndex]->mOffsetMatrix;

			bone->SetID(_BoneCounter);
			bone->SetOffset(ConvertAssimpMatrixToGLMMatrix(a_os));
			_BoneInfoMap[boneName] = bone;
			boneID = _BoneCounter;
			_BoneCounter++;
		}
		else {

		

			boneID = _BoneInfoMap[boneName]->GetID();
		}

		if (boneID == -1) {

			Debug::Error("BoneID==-1");

		}


		auto weights = aMesh->mBones[boneIndex]->mWeights;
		int numWeights = aMesh->mBones[boneIndex]->mNumWeights;

		for (int weightIndex = 0; weightIndex < numWeights; weightIndex++) {

			int vertexID = weights[weightIndex].mVertexId;
			float weight = weights[weightIndex].mWeight;
			
			Debug::Assert(vertexID < mesh->VertexCount(), "VertexID > VertexCount");

			Vertex vertex = SetVertexBoneData(mesh->GetVertex(vertexID), boneID, weight);
			mesh->SetVertex(vertexID, vertex);





		}
		
	}

}

void Actor::UpdateAnimation(float time) {

	_Animator->UpdateAnimation(time);

}

const glm::mat4* Actor::GetBoneMatrices() const {

	return _Animator->GetFinalBoneMatrices();

}