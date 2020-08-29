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

//     unsigned int diffuseNr = 1;
//     unsigned int specularNr = 1;
//     unsigned int normalNr = 1;
//     unsigned int heightNr = 1;
// 
//     for (unsigned int i = 0; i < mTextures.size(); i++)
//     {
//         glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
// 
//         // retrieve texture number (the N in diffuse_textureN)
//         std::string number;
//         std::string name = mTextures[i].type;
// 
//         if (name == "texture_diffuse")
//             number = std::to_string(diffuseNr++);
//         else if (name == "texture_specular")
//             number = std::to_string(specularNr++); // transfer unsigned int to stream
//         else if (name == "texture_normal")
//             number = std::to_string(normalNr++); // transfer unsigned int to stream
//         else if (name == "texture_height")
//             number = std::to_string(heightNr++); // transfer unsigned int to stream
// 
//         std::string locationStr = "material." + name + number;
//         shader.setInt(locationStr.c_str(), i);
//         //shader.setInt((name + number).c_str(), i);
//         glBindTexture(GL_TEXTURE_2D, mTextures[i].id);
//     }
// 
//     shader.setFloat("material.shininess", 32.f);
// 
//     glActiveTexture(GL_TEXTURE0);
// 
//     // draw mesh
//     glBindVertexArray(VAO);
//     glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT, 0);
//     glBindVertexArray(0);
}

void Mesh::setupMesh()
{
    ManagersProvider::getInstance().getGraphics()->initMesh(*this);

//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);
// 
//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 
//     glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);
// 
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int),
//         &mIndices[0], GL_STATIC_DRAW);
// 
//     // vertex positions
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//     // vertex normals
//     glEnableVertexAttribArray(1);
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
//     // vertex texture coords
//     glEnableVertexAttribArray(2);
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
// 
//     glBindVertexArray(0);
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

