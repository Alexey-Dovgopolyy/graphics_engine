#pragma once

#include "Shader.h"

#include <map>

class ShadersManager
{
public:
    bool init();
    void cleanup();

    bool initShader(const std::string& name, const std::string& path);
    Shader getShader(const std::string& name) const;
    std::string getShaderPath(const std::string& name) const;
    Shader createShader(const std::string& name, const std::string& path) const;

private:
    std::map<std::string, Shader> mShaders;
    std::map<std::string, std::string> mShaderPathes;
};

