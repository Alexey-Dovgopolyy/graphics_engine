#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Vertex.h"
#include "Texture.h"

#include <string>
#include <vector>

class Shader;

class Mesh 
{
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);

    void Draw(Shader& shader);

    void setVAO(unsigned int vao);
    void setVBO(unsigned int vbo);
    void setEBO(unsigned int ebo);
    unsigned int getVAO() const;
    unsigned int getVBO() const;
    unsigned int getEBO() const;

    const std::vector<Vertex>& getVertices() const;
    const std::vector<unsigned int>& getIndices() const;
    const std::vector<Texture>& getTextures() const;

private:
    void setupMesh();

private:
    unsigned int mVAO = 0;
    unsigned int mVBO = 0;
    unsigned int mEBO = 0;

    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    std::vector<Texture> mTextures;
};

