#include "JsonManager.h"

#include "json/rapidjson/document.h"

#include <fstream>

bool JsonManager::init()
{
    return false;
}

std::vector<ObjectData> JsonManager::readScene()
{
    // TODO refactor

    std::vector<ObjectData> sceneObjects;

    const char* fileName = "resources/scene.json";

    std::ifstream inputStream(fileName);
    if (inputStream.is_open() == false)
    {
        printf("ERROR: Cannot open scene file '%s'", fileName);
        return sceneObjects;
    }

    inputStream.seekg(0, inputStream.end);
    int fileSize = static_cast<int>(inputStream.tellg());
    inputStream.seekg(0, inputStream.beg);

    char* fileData = new char[fileSize];
    memset(fileData, 0, fileSize);

    inputStream.read(fileData, fileSize);
    inputStream.close();
    
    rapidjson::Document document;
    document.Parse(fileData);

    if (document.IsObject() == false)
    {
        return sceneObjects;
    }

    const rapidjson::Value& sceneValue = document["objects"];
    assert(sceneValue.IsArray());

    for (rapidjson::SizeType i = 0; i < sceneValue.Size(); i++)
    {
        const rapidjson::Value& objectValue = sceneValue[i];
        if (objectValue.IsObject())
        {
            bool isObjectValid = true;
            isObjectValid = objectValue.HasMember("model") && isObjectValid;
            isObjectValid = objectValue.HasMember("type") && isObjectValid;
            isObjectValid = objectValue.HasMember("pos") && isObjectValid;
            isObjectValid = objectValue.HasMember("rot") && isObjectValid;
            isObjectValid = objectValue.HasMember("scale") && isObjectValid;

            if (isObjectValid == false)
            {
                printf("WARNING: Not valid object. Index %d", i);
                continue;
            }

            ObjectData objectData;

            objectData.mModel = objectValue["model"].GetString();
            objectData.mType = static_cast<ObjectType>(objectValue["type"].GetInt());

            const rapidjson::Value& posValue = objectValue["pos"];
            objectData.mPosition.x = static_cast<float>(posValue[0].GetDouble());
            objectData.mPosition.y = static_cast<float>(posValue[1].GetDouble());
            objectData.mPosition.z = static_cast<float>(posValue[2].GetDouble());

            const rapidjson::Value& rotValue = objectValue["rot"];
            objectData.mRotation.x = static_cast<float>(rotValue[0].GetDouble());
            objectData.mRotation.y = static_cast<float>(rotValue[1].GetDouble());
            objectData.mRotation.z = static_cast<float>(rotValue[2].GetDouble());

            const rapidjson::Value& scaleValue = objectValue["scale"];
            objectData.mScale.x = static_cast<float>(scaleValue[0].GetDouble());
            objectData.mScale.y = static_cast<float>(scaleValue[1].GetDouble());
            objectData.mScale.z = static_cast<float>(scaleValue[2].GetDouble());

            sceneObjects.push_back(objectData);
        }
    }

    delete[] fileData;

    return sceneObjects;
}

void JsonManager::writeScene()
{
}
