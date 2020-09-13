#include "Scene.h"

#include "ManagersProvider.h"
#include "JsonManager.h"
#include "SelectedObjectManager.h"

bool Scene::init()
{
    mObjects.reserve(10);

    JsonManager* jsonManager = ManagersProvider::getInstance().getJsonManager();
    std::vector<ObjectData> objects = jsonManager->readScene();

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

    mSelectedObjectsManager = ManagersProvider::getInstance().getSelectedObjectManager();

    Object* testObj = &(mObjects.front());
    mSelectedObjectsManager->setSelectedObject(testObj);

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
        if (&object != mSelectedObjectsManager->getSelectedObject())
        {
            object.draw();
        }
    }

    mSelectedObjectsManager->drawFrame();
}

void Scene::clean()
{
}
