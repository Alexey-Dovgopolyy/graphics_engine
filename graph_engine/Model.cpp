#include "Model.h"
#include "Shader.h"

#include "ManagersProvider.h"
#include "TexturesManager.h"

#include <iostream>

Model::Model()
{
}

Model::Model(const char* path)
{
    loadModel(path);
}

void Model::draw(Shader& shader)
{
    for (unsigned int i = 0; i < mMeshes.size(); i++)
    {
        mMeshes[i].Draw(shader);
    }
}

void Model::drawShadow()
{
    for (unsigned int i = 0; i < mMeshes.size(); i++)
    {
        mMeshes[i].drawShadow();
    }
}

void Model::loadModel(const std::string& path)
{
    mMeshes = ManagersProvider::getInstance().getTextureManager()->loadModel(path);
}
