#include "Importer.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture2D.h"
#include <iostream>


#include <vector>

class MaterialParser {
public:
    struct MaterialData {
        std::vector<std::string> textureFilePaths;
        aiColor3D diffuseColor;
        aiColor3D specularColor;
    };

    MaterialData ParseMaterial(const aiMaterial* aMaterial) {
        MaterialData materialData;

        // Parse textures
        aiString texturePath;
        // Diffuse textures
        for (unsigned int i = 0; i < aMaterial->GetTextureCount(aiTextureType_DIFFUSE); ++i) {
            if (aMaterial->GetTexture(aiTextureType_DIFFUSE, i, &texturePath) == AI_SUCCESS) {
                materialData.textureFilePaths.push_back(texturePath.C_Str());
            }
        }
        // Specular textures
        for (unsigned int i = 0; i < aMaterial->GetTextureCount(aiTextureType_SPECULAR); ++i) {
            if (aMaterial->GetTexture(aiTextureType_SPECULAR, i, &texturePath) == AI_SUCCESS) {
                materialData.textureFilePaths.push_back(texturePath.C_Str());
            }
        }

        // Parse colors
        aiColor3D color;
        // Diffuse color
        if (aMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
            materialData.diffuseColor = color;
        }
        // Specular color
        if (aMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS) {
            materialData.specularColor = color;
        }

        return materialData;
    }
};

std::vector<Material*> _materials;
std::vector<Mesh*> _meshes;

void ProcessNode(aiNode* node, Entity* entity)
{

    for (int i = 0;i < node->mNumMeshes;i++) {

        entity->AddMesh(_meshes[node->mMeshes[i]]);

    }

    for (int i = 0;i < node->mNumChildren;i++) {

        Entity* new_ent = new Entity;
        entity->AddNode(new_ent);
        ProcessNode(node->mChildren[i], new_ent);

    }


}

Node3D* Importer::ImportNode(std::string path) {

    _meshes.clear();
    _materials.clear();

	Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |            // Triangulate polygons
        aiProcess_FlipUVs |                // Flip the textures' UVs
        aiProcess_CalcTangentSpace |       // Calculate tangents and bitangents
        aiProcess_GenNormals |             // Generate normals
        aiProcess_JoinIdenticalVertices);  // Join identical vertices/ optimize indexing

    // Check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    for (int i = 0;i < scene->mNumMaterials;i++) {

        aiMaterial* amat = scene->mMaterials[i];

        MaterialParser *mparse = new MaterialParser;
        auto data = mparse->ParseMaterial(amat);

        Material* mat = new Material;

        _materials.push_back(mat);

        if (data.textureFilePaths.size() > 0) {

            std::string tpath = data.textureFilePaths[0];
            std::string path = "res/tex/" + tpath;
            mat->SetDiffuseMap(new Texture2D(path));

        }

        if (data.textureFilePaths.size() > 1) {

            mat->SetNormalMap(new Texture2D(data.textureFilePaths[1]));

        }
       
        mat->SetDiffuseColor(glm::vec3(data.diffuseColor.r, data.diffuseColor.g, data.diffuseColor.b));

    }

    for (int i = 0;i < scene->mNumMeshes;i++) {

        aiMesh* amesh = scene->mMeshes[i];

        Mesh* mesh = new Mesh;

        for (int j = 0;j < amesh->mNumVertices;j++) {

            aiVector3D v_pos = amesh->mVertices[j];
            aiVector3D v_norm = amesh->mNormals[j];
            aiVector3D v_bi = amesh->mBitangents[j];
            aiVector3D v_tang = amesh->mTangents[j];
            aiVector3D v_tex = amesh->mTextureCoords[0][j];

            Vertex nv;
            nv.position = glm::vec3(v_pos.x, v_pos.z, v_pos.y);
            nv.normal = glm::vec3(v_norm.x, v_norm.z, v_norm.y);
            nv.binormal = glm::vec3(v_bi.x, v_bi.z, v_bi.y);
            nv.tangent = glm::vec3(v_tang.x, v_tang.z, v_tang.y);
            nv.texcoord = glm::vec3(v_tex.x, v_tex.y, v_tex.z);

            mesh->AddVertex(nv);

        }

        for (int j = 0;j < amesh->mNumFaces;j++) {

            Triangle t;
            t.V0 = amesh->mFaces[j].mIndices[0];
            t.V1 = amesh->mFaces[j].mIndices[1];
            t.V2 = amesh->mFaces[j].mIndices[2];

            mesh->AddTriangle(t);

        }

        mesh->CreateBuffers();

        mesh->SetMaterial(_materials[amesh->mMaterialIndex]);

        _meshes.push_back(mesh);

    }

    Entity* root = new Entity;

    ProcessNode(scene->mRootNode,root);

    return root;
}

Node3D* Importer::ImportSkeletal(std::string path) {


	return nullptr;
}