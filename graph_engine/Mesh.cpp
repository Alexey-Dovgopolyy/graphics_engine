#include "Mesh.h"
#include "Shader.h"

#include "ManagersProvider.h"
#include "Graphics.h"

#include <glad/glad.h>


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
    : mVertices(vertices)
    , mIndices(indices)
    , mTextures(textures)
{
    setupMesh();
}

void Mesh::Draw(Shader& shader)
{
    ManagersProvider::getInstance().getGraphics()->drawMesh(*this, shader);
}

void Mesh::setupMesh()
{
    ManagersProvider::getInstance().getGraphics()->initMesh(*this);
}

void Mesh::setVAO(unsigned int vao)
{
    mVAO = vao;
}

void Mesh::setVBO(unsigned int vbo)
{
    mVBO = vbo;
}

void Mesh::setEBO(unsigned int ebo)
{
    mEBO = ebo;
}

unsigned int Mesh::getVAO() const
{
    return mVAO;
}

unsigned int Mesh::getVBO() const
{
    return mVBO;
}

unsigned int Mesh::getEBO() const
{
    return mEBO;
}

const std::vector<Vertex>& Mesh::getVertices() const
{
    return mVertices;
}

const std::vector<unsigned int>& Mesh::getIndices() const
{
    return mIndices;
}

const std::vector<Texture>& Mesh::getTextures() const
{
    return mTextures;
}

