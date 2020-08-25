#include <iostream>

#include "Time.h"
#include "ManagersProvider.h"
#include "Scene.h"
#include "Graphics.h"

int main()
{
    ManagersProvider& managersProvider = ManagersProvider::getInstance();
    managersProvider.create();
    managersProvider.init();

    Scene scene;
    scene.init();

    Graphics* graphics = managersProvider.getGraphics();

    while (graphics->windowShouldClose() == false)
    {
        Time::updateTick();
        float dt = Time::getDt();

        graphics->processInput();
        graphics->beforeUpdate();

        scene.update(dt);
        scene.draw();

        graphics->afterUpdate();
    }

    graphics->cleanup();

    return 0;
}
