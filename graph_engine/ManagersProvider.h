#pragma once

#include <memory>

class TexturesManager;
class Camera;
class GEMath;
class Graphics;
class LightSourceManager;
class Window;
class JsonManager;

class ManagersProvider
{
public:
    static ManagersProvider& getInstance();

    ~ManagersProvider() = default;

    void create();
    void init();
    void cleanup();

    TexturesManager* getTextureManager() const;
    Camera* getCamera() const;
    GEMath* getMath() const;
    Graphics* getGraphics() const;
    LightSourceManager* getLightManager() const;
    Window* getWindow() const;
    JsonManager* getJsonManager() const;

private:
    ManagersProvider() = default;
    ManagersProvider(const ManagersProvider& other) = delete;
    ManagersProvider& operator = (const ManagersProvider& other) = delete;

private:
    std::unique_ptr<TexturesManager> mTextureManager;
    std::unique_ptr<Camera> mCamera;
    std::unique_ptr<GEMath> mMath;
    std::unique_ptr<Graphics> mGraphics;
    std::unique_ptr<LightSourceManager> mLightsManager;
    std::unique_ptr<Window> mWindow;
    std::unique_ptr<JsonManager> mJsonManager;
};

