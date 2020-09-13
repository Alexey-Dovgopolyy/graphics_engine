#include "ObjectBehaviour.h"
#include "ManagersProvider.h"
#include "LightSourceManager.h"
#include "Shader.h"
#include "Object.h"

ObjectBehaviour::ObjectBehaviour(Object* owner)
    : Behaviour(owner)
{
}

void ObjectBehaviour::init()
{
    // empty
}

void ObjectBehaviour::update(float dt)
{
    Shader& shader = mOwner->getShader();
    shader.use();

    LightSourceManager* lightSourceManager = ManagersProvider::getInstance().getLightManager();

    const LightSourceData& directionLight = lightSourceManager->getDirectionLight();
    shader.setVec3("dirLight.direction", directionLight.getDirection());
    shader.setVec3("dirLight.ambient", directionLight.getAmbient());
    shader.setVec3("dirLight.diffuse", directionLight.getDiffuse());
    shader.setVec3("dirLight.specular", directionLight.getSpecular());

    const std::vector<LightSourceData>& lights = lightSourceManager->getLights();

    shader.setInt("pointLightsCount", static_cast<int>(lights.size()));

    for (int i = 0; i < lights.size(); i++)
    {
        const LightSourceData& light = lights[i];

        std::string lightStr = "pointLights[" + std::to_string(i) + "].";

        shader.setVec3(lightStr + "position", light.getPosition());
        shader.setVec3(lightStr + "ambient", light.getAmbient()); 
        shader.setVec3(lightStr + "diffuse", light.getDiffuse());
        shader.setVec3(lightStr + "specular", light.getSpecular());
        shader.setFloat(lightStr + "constant", light.getConstant());
        shader.setFloat(lightStr + "linear", light.getLinear());
        shader.setFloat(lightStr + "quadratic", light.getQuadratic());
    }
}

const char* ObjectBehaviour::getShaderName()
{
    return "model";
}
