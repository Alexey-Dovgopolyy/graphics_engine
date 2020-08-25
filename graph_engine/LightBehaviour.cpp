#include "LightBehaviour.h"
#include "ManagersProvider.h"
#include "LightSourceManager.h"

LightBehaviour::LightBehaviour(Object* owner)
    : Behaviour(owner)
{
}

void LightBehaviour::init()
{
    LightSourceManager* lightsManager = ManagersProvider::getInstance().getLightManager();
    lightsManager->registerLightSource(mOwner);
}

void LightBehaviour::update(float dt)
{
    // empty
}
