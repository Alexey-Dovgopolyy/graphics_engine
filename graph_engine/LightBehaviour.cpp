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
    LightSourceData& light = lightsManager->registerLightSource(mOwner);
    //light.debugSetAmbient(GEVec3(0.f, 0.5f, 0.f));
    light.debugSetDiffuse(GEVec3(0.f, 0.5f, 0.f));
    light.debugSetSpecular(GEVec3(0.f, 0.5f, 0.f));
}

void LightBehaviour::update(float dt)
{
    // empty
}
