#pragma once

#include "ObjectType.h"
#include "Defines.h"

#include <string>
#include <vector>

struct ObjectData
{
    std::string mModel;
    ObjectType mType = ObjectType::sceneObject;
    GEVec3 mPosition;
    GEVec3 mRotation;
    GEVec3 mScale;
};

class JsonManager
{
public:
    bool init();
    static std::vector<ObjectData> readScene();
    void writeScene();

};

