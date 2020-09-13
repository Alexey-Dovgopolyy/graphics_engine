#include "Scene.h"

#include "ManagersProvider.h"
#include "JsonManager.h"

bool Scene::init()
{
    mObjects.reserve(10);

    std::vector<ObjectData> objects = JsonManager::readScene();
    for (const ObjectData& objectData : objects)
    {
        const std::string& model = objectData.mModel;
        ObjectType type = objectData.mType;
        GEVec3 position = objectData.mPosition;
        GEVec3 rotation = objectData.mRotation;
        GEVec3 scale = objectData.mScale;

        mObjects.emplace_back(model.c_str(), type);
        mObjects.back().move(position);
        mObjects.back().rotate(rotation);
        mObjects.back().scale(scale);
    }

    //mTestObj = &(mObjects.back());

    return true;
}

void Scene::update(float dt)
{
    for (Object& object : mObjects)
    {
        object.update(dt);
    }
}

void Scene::draw()
{
    for (Object& object : mObjects)
    {
        object.draw();
    }
}

void Scene::clean()
{
}
