#pragma once

struct GLFWwindow;
class Mesh;
class Shader;

class Graphics
{
public:
    bool init();

    void beforeUpdate();
    void afterUpdate();
    void cleanup();

    void clearColorBuffer();

    void beforeDrawOutlinedObject();
    void beforeDrawOutline();
    void afterDrawOutline();

    void LockStencilBuffer();
    void UnlockStencilBuffer();

    static void initMesh(Mesh& mesh);
    static void drawMesh(Mesh& mesh, Shader& shader);
    static void drawMeshShadow(Mesh& mesh);

    static void drawDebugShadow(Shader& shader);

private:
    GLFWwindow* mWindow = nullptr;

    float mWindowWidth = 800.f;
    float mWindowHeight = 600.f;

    float mLastX = 0.f;
    float mLastY = 0.f;
};

