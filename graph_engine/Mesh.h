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
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    std::vector<Texture> mTextures;

public:
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);

    void Draw(Shader& shader);

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    void setupMesh();
};

