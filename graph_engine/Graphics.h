#pragma once

struct GLFWwindow;

class Graphics
{
public:
    bool init();

    float getWidth() const;
    float getHeight() const;
    float getAspectRatio() const;

    float getLastX() const;
    void setLastX(float lastX);
    float getLastY() const;
    void setLastY(float lastY);

    bool windowShouldClose() const;

    void beforeUpdate();
    void afterUpdate();
    void cleanup();

    void processInput();

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
    GLFWwindow* mWindow = nullptr;

    float mWindowWidth = 800.f;
    float mWindowHeight = 600.f;

    float mLastX = 0.f;
    float mLastY = 0.f;
};

