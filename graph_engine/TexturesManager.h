#pragma once

#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <vector>
#include <string>
#include <memory>

class TexturesManager
{
public:
    std::vector<Mesh> loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Vertex> processVertices(aiMesh* mesh);
    std::vector<unsigned int> processIndices(aiMesh* mesh);
    std::vector<Texture> processTextures(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

    static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

private:
    std::vector<Texture> mTextures;

    std::string mCurDirectory;
};

