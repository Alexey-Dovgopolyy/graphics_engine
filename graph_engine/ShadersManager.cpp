#include "ShadersManager.h"

bool ShadersManager::init()
{
    return true;
}

void ShadersManager::cleanup()
{
}

bool ShadersManager::initShader(const std::string& name, const std::string& path)
{
    Shader shader = createShader(name, path);
    mShaders.insert({ name, shader });
    mShaderPathes.insert({ name, path });
    return true;
}

Shader ShadersManager::getShader(const std::string& name) const
{
    if (mShaders.empty())
    {
        printf("ERROR: No shaders available");
        return Shader();
    }

    const auto it = mShaders.find(name);
    if (it != mShaders.cend())
    {
        return it->second;
    }
    else
    {
        printf("ERROR: Cannot find shader '%s'", name.c_str());
        return mShaders.begin()->second;
    }
}

std::string ShadersManager::getShaderPath(const std::string& name) const
{
    const auto it = mShaderPathes.find(name);
    if (it != mShaderPathes.cend())
    {
        return it->second;
    }
    else
    {
        printf("ERROR: Cannot find shader's path '%s'", name.c_str());
        return "";
    }
}

Shader ShadersManager::createShader(const std::string& name, const std::string& path) const
{
    Shader shader;

    std::string vertShader = path + ".vert";
    std::string fragShader = path + ".frag";
    shader.init(vertShader.c_str(), fragShader.c_str());

    return shader;
}
