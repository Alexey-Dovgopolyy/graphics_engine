#include "Scene.h"

#include "ManagersProvider.h"
#include "JsonManager.h"
#include "SelectedObjectManager.h"
#include "ShadowMapRenderer.h"
#include "LightSourceData.h"
#include "LightSourceManager.h"
#include "ShadersManager.h"
#include "Graphics.h"

bool Scene::init()
{
    //mObjects.reserve(10);

    JsonManager* jsonManager = ManagersProvider::getInstance().getJsonManager();
    std::vector<ObjectData> objects = jsonManager->readScene();

    for (const ObjectData& objectData : objects)
    {
        const std::string& model = objectData.mModel;
        ObjectType type = objectData.mType;
        GEVec3 position = objectData.mPosition;
        GEVec3 rotation = objectData.mRotation;
        GEVec3 scale = objectData.mScale;

        std::unique_ptr<Object> newObject = std::make_unique<Object>(model.c_str(), type);
		newObject->move(position);
		newObject->rotate(rotation);
		newObject->scale(scale);

        mObjects.push_back(std::move(newObject));
    }

    mSelectedObjectsManager = ManagersProvider::getInstance().getSelectedObjectManager();

    Object* testObj = mObjects.front().get();
    mSelectedObjectsManager->setSelectedObject(testObj);

    return true;
}

void Scene::update(float dt)
{
    for (auto& object : mObjects)
    {
        object->update(dt);
    }
}

void Scene::draw()
{
    // refactor shadow map renderer

    LightSourceManager* lightSourceManager = ManagersProvider::getInstance().getLightManager();
    const LightSourceData& directionLight = lightSourceManager->getDirectionLight();
    GEVec3 directLightPos = -(directionLight.getDirection() * 5.f);

    ShadowMapRenderer* shadowMapRenderer = ManagersProvider::getInstance().getShadowRenderer();
    shadowMapRenderer->renderShadowMap(directLightPos, *this);

    //shadowMapRenderer->drawDebugShadowMap();

    mSelectedObjectsManager->prepareStencilBuffer();

    for (auto& object : mObjects)
    {
        object->draw();   
    }

    mSelectedObjectsManager->drawFrame();
}

void Scene::clean()
{
}
