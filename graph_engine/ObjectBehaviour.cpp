#include "ObjectBehaviour.h"
#include "ManagersProvider.h"
#include "LightSourceManager.h"
#include "Shader.h"

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
    LightSourceManager* lightSourceManager = ManagersProvider::getInstance().getLightManager();
    const std::vector<LightSourceData>& lights = lightSourceManager->getLights();

    Shader& shader = mOwner->getShader();
    shader.use();
    for (const LightSourceData& light : lights)
    {
        GEVec3 lightPos = light.getPosition();
        shader.setVec3("lightPos", lightPos);
    }
}
