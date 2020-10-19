#pragma once

#include "Window.h"

struct GLFWwindow;

class GLWindow
    : public Window
{
public:
    bool init() override;
    void processInput() override;
    bool windowShouldClose() const override;
    void swapButters() override;
    void setupViewport() override;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
    GLFWwindow* mWindow = nullptr;
};

