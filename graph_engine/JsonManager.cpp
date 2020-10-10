#include "JsonManager.h"

#include "ManagersProvider.h"
#include "ShadersManager.h"
#include "Camera.h"

#include <fstream>

bool JsonManager::init()
{
    bool sceneResult = parse("resources/scene.json", mSceneDocument);
    bool configResult = parse("resources/config.json", mConfigDocument);

    bool isResourcesValid = (sceneResult && configResult);
    if (isResourcesValid == false)
    {
        return false;
    }

    readShaders();
    readMovementSpeed();

    return true;
}

std::vector<ObjectData> JsonManager::readScene()
{
    std::vector<ObjectData> sceneObjects;

    const rapidjson::Value& sceneValue = mSceneDocument["objects"];
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

    return sceneObjects;
}

void JsonManager::writeScene()
{
}

void JsonManager::readShaders()
{
    ShadersManager* shadersManager = ManagersProvider::getInstance().getShadersManager();

    const rapidjson::Value& shadersValue = mConfigDocument["shaders"];
    assert(shadersValue.IsArray());

    for (rapidjson::SizeType i = 0; i < shadersValue.Size(); i++)
    {
        const rapidjson::Value& shaderVal = shadersValue[i];
        if (shaderVal.IsObject())
        {
            bool isObjectValid = true;
            isObjectValid = shaderVal.HasMember("name") && isObjectValid;
            isObjectValid = shaderVal.HasMember("path") && isObjectValid;

            if (isObjectValid == false)
            {
                printf("WARNING: Not valid object. Index %d", i);
                continue;
            }

            std::string shaderName = shaderVal["name"].GetString();
            std::string path = shaderVal["path"].GetString();

            shadersManager->initShader(shaderName, path);
        }
    }
}

void JsonManager::readMovementSpeed()
{
    const rapidjson::Value& speedValue = mConfigDocument["camera_speed"];
    float cameraSpeed = static_cast<float>(speedValue.GetDouble());

    Camera* camera = ManagersProvider::getInstance().getCamera();
    camera->setMovementSpeed(cameraSpeed);
}

bool JsonManager::parse(const char* path, rapidjson::Document& document)
{
    std::ifstream inputStream(path);
    if (inputStream.is_open() == false)
    {
        printf("ERROR: Cannot open scene file '%s'", path);
        return false;
    }

    inputStream.seekg(0, inputStream.end);
    int fileSize = static_cast<int>(inputStream.tellg());
    inputStream.seekg(0, inputStream.beg);

    char* fileData = new char[fileSize];
    memset(fileData, 0, fileSize);

    inputStream.read(fileData, fileSize);
    inputStream.close();

    document.Parse(fileData);

    delete[] fileData;

    if (document.IsObject() == false)
    {
        printf("ERROR: Cannot parse file");
        return false;
    }

    return true;
}
