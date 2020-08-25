// #include "SceneObject.h"
// #include "ManagersProvider.h"
// #include "LightSourceManager.h"
// 
// SceneObject::SceneObject(const char* path, const char* shader)
//     : Object(path, shader)
// {
// }
// 
// void SceneObject::init(const char* path, const char* shader)
// {
//     Object::init(path, shader);
// }
// 
// void SceneObject::update(float dt)
// {
//     LightSourceManager* lightSourceManager = ManagersProvider::getInstance().getLightManager();
//     const std::vector<LightSourceData>& lights = lightSourceManager->getLights();
// 
//     mShader.use();
//     for (const LightSourceData& light : lights)
//     {
//         mShader.setVec3("lightSource", light.mPosition);
//     }
// 
//     Object::update(dt);
// }
