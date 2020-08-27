#include "LightSourceManager.h"

void LightSourceManager::init()
{
    setDirectionLight();
}

LightSourceData& LightSourceManager::registerLightSource(Object* object)
{
    LightSourceData light;
    light.init(object);
    mLights.push_back(light);
    return mLights.back();
}

void LightSourceManager::setDirectionLight()
{

}

const LightSourceData& LightSourceManager::getDirectionLight() const
{
    return mDirectionLight;
}

const std::vector<LightSourceData>& LightSourceManager::getLights() const
{
    return mLights;
}
