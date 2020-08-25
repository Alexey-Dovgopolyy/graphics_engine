#include "Scene.h"

#include "ManagersProvider.h"

bool Scene::init()
{
    mObjects.reserve(10);

    // TODO rework objects creation
    mObjects.emplace_back("models/my_cube/my_cube.obj", "shaders/lightSource", ObjectType::lightSource);
    mObjects.back().move(GEVec3(5.f, 5.f, 0.f));
    mObjects.back().scale(GEVec3(0.2f, 0.2f, 0.2f));

    mObjects.emplace_back("models/my_cube/my_cube.obj", "shaders/model_shader", ObjectType::sceneObject);
    mObjects.back().move(GEVec3(0.f, 0.f, 0.f));

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
