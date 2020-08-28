#pragma once

#include "Mesh.h"

#include <vector>

class Shader;

class Model
{
public:
    Model();
    Model(const char* path);
    
    void loadModel(const std::string& path);

    void draw(Shader& shader);

private:
    std::vector<Mesh> mMeshes;
};

