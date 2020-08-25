#include "LightSourceManager.h"

void LightSourceManager::registerLightSource(GEVec3 pos)
{
//     LightSourceData light;
//     light.mPosition = pos;
//     mLights.push_back(std::move(light));
}

void LightSourceManager::registerLightSource(LightSourceData lightSource)
{
    //mLights.push_back(std::move(lightSource));
}

void LightSourceManager::registerLightSource(Object* object)
{
    LightSourceData light;
    light.mLightObject = object;
    mLights.push_back(light);
}

const std::vector<LightSourceData>& LightSourceManager::getLights() const
{
    return mLights;
}

GEVec3 LightSourceData::getPosition() const
{
    if (mLightObject)
    {
        return mLightObject->getPosition();
    }
    return GEVec3(0.f, 0.f, 0.f);
}
