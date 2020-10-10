#pragma once

#include "ObjectType.h"
#include "Defines.h"

#include "json/rapidjson/document.h"

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

    std::vector<ObjectData> readScene();
    void writeScene();

    void readShaders();

    void readMovementSpeed();

private:
    static bool parse(const char* path, rapidjson::Document& document);

private:
    rapidjson::Document mSceneDocument;
    rapidjson::Document mConfigDocument;
};

