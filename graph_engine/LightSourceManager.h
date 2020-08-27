#pragma once

#include "Defines.h"
#include "LightSourceData.h"

#include <vector>

class Object;

class LightSourceManager
{
public:
    void init();

    LightSourceData& registerLightSource(Object* object);

    void setDirectionLight();

    const LightSourceData& getDirectionLight() const;
    const std::vector<LightSourceData>& getLights() const;

private:
    std::vector<LightSourceData> mLights;
    LightSourceData mDirectionLight;
};

