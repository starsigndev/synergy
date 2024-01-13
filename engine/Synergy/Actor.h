#pragma once
#include "Node3D.h"
#include <vector>
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "glm/glm.hpp"
#include "glm/matrix.hpp"

class BoneInfo;
class Mesh;
class Animator;
class Vertex;


class Actor :
    public Node3D
{
public:

	Actor();
	void AddMesh(Mesh* mesh);
	int MeshCount();
	Mesh* GetMesh(int index);
	void UpdateNode() {};
	std::map<std::string, BoneInfo*>& GetBoneInfoMap();
	int& GetBoneCount();

	Vertex SetVertexBoneData(Vertex vertex, int boneID, float weight);
	void ExtractBoneWeightForMesh(Mesh* mesh, aiMesh* aMesh, const aiScene* aScene);
	const glm::mat4* GetBoneMatrices() const;

	void SetAnimator(Animator* animator) {
		_Animator = animator;
	}
	void UpdateAnimation(float time);

private:

	std::vector<Mesh*> _Meshes;
	std::map<std::string, BoneInfo*> _BoneInfoMap;
	int _BoneCounter = 0;
	glm::mat4 _GlobalInverse;
	Animator* _Animator;
};

