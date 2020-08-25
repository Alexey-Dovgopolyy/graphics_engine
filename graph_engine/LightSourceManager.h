#pragma once

#include "Defines.h"
#include "Object.h"

struct LightSourceData
{
    //GEVec3 mPosition = GEVec3(0.f, 0.f, 0.f);
    Object* mLightObject = nullptr;

    GEVec3 getPosition() const;
};

class LightSourceManager
{
public:
    void registerLightSource(GEVec3 pos);
    void registerLightSource(LightSourceData lightSource);
    void registerLightSource(Object* object);

    const std::vector<LightSourceData>& getLights() const;

private:
    std::vector<LightSourceData> mLights;
};

