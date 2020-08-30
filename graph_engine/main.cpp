#include <iostream>

#include "Time.h"
#include "ManagersProvider.h"
#include "Scene.h"
#include "Graphics.h"
#include "Window.h"

int main()
{
    ManagersProvider& managersProvider = ManagersProvider::getInstance();
    managersProvider.create();
    managersProvider.init();

    Scene scene;
    scene.init();

    Window* window = managersProvider.getWindow();
    Graphics* graphics = managersProvider.getGraphics();

    while (window->windowShouldClose() == false)
    {
        Time::updateTick();
        float dt = Time::getDt();

        window->processInput();
        graphics->beforeUpdate();

        scene.update(dt);
        scene.draw();

        graphics->afterUpdate();
    }

    graphics->cleanup();

    return 0;
}
