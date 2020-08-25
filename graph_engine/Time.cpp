#include "Time.h"
#include "GLFW/glfw3.h"

static float sDeltaTime = 0.f;
static float sLastFrame = 0.f;

void Time::updateTick()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    sDeltaTime = currentFrame - sLastFrame;
    sLastFrame = currentFrame;
}

float Time::getDt()
{
    return sDeltaTime;
}
