#include "Graphics.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "ManagersProvider.h"
#include "Camera.h"
#include "Time.h"

#include <iostream>

bool Graphics::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = static_cast<int>(mWindowWidth);
    int height = static_cast<int>(mWindowHeight);

    mWindow = glfwCreateWindow(width, height, "Graph Engine", nullptr, nullptr);
    if (mWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(mWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glfwSetFramebufferSizeCallback(mWindow, framebufferSizeCallback);
    glfwSetCursorPosCallback(mWindow, mouseCallback);
    glfwSetScrollCallback(mWindow, scrollCallback);

    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    mLastX = mWindowWidth / 2.f;
    mLastY = mWindowHeight / 2.f;

    glEnable(GL_DEPTH_TEST);

    return true;
}

float Graphics::getWidth() const
{
    return mWindowWidth;
}

float Graphics::getHeight() const
{
    return mWindowHeight;
}

float Graphics::getAspectRatio() const
{
    return mWindowWidth / mWindowHeight;
}

float Graphics::getLastX() const
{
    return mLastX;
}

void Graphics::setLastX(float lastX)
{
    mLastX = lastX;
}

float Graphics::getLastY() const
{
    return mLastY;
}

void Graphics::setLastY(float lastY)
{
    mLastY = lastY;
}

bool Graphics::windowShouldClose() const
{
    return glfwWindowShouldClose(mWindow);
}

void Graphics::beforeUpdate()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::afterUpdate()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

void Graphics::cleanup()
{
    glfwTerminate();
}

void Graphics::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Graphics::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    Graphics* graphics = ManagersProvider::getInstance().getGraphics();
    float lastX = graphics->getLastX();
    float lastY = graphics->getLastY();

    static bool firstMouse = true;
    if (firstMouse)
    {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - lastX;
    float yoffset = lastY - static_cast<float>(ypos); // reversed since y-coordinates go from bottom to top

    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    graphics->setLastX(lastX);
    graphics->setLastY(lastY);

    Camera* camera = ManagersProvider::getInstance().getCamera();
    camera->processMouseMovement(xoffset, yoffset);
}

void Graphics::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera* camera = ManagersProvider::getInstance().getCamera();
    camera->processMouseScroll(static_cast<float>(yoffset));
}

void Graphics::processInput()
{
    float deltaTime = Time::getDt();

    Camera* camera = ManagersProvider::getInstance().getCamera();

    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(mWindow, true);
    }

    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->processKeyboard(FORWARD, deltaTime);
    }

    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->processKeyboard(BACKWARD, deltaTime);
    }

    if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera->processKeyboard(LEFT, deltaTime);
    }

    if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera->processKeyboard(RIGHT, deltaTime);
    }
}
