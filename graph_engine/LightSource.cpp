// #include "LightSource.h"
// #include "ManagersProvider.h"
// #include "LightSourceManager.h"
// 
// LightSource::LightSource(const char* path, const char* shader)
//     : Object(path, shader)
// {
// }
// 
// void LightSource::init(const char* path, const char* shader)
// {
//     Object::init(path, shader);
// 
//     LightSourceManager* lightsManager = ManagersProvider::getInstance().getLightManager();
//     lightsManager->registerLightSource(this);
// }
