#include "ManagersProvider.h"

#include "TexturesManager.h"
#include "Camera.h"
#include "GEMath.h"
#include "Graphics.h"
#include "LightSourceManager.h"
#include "GLWindow.h"
#include "JsonManager.h"
#include "ShadersManager.h"
#include "SelectedObjectManager.h"

ManagersProvider& ManagersProvider::getInstance()
{
    static ManagersProvider sManagersProvider;
    return sManagersProvider;
}

void ManagersProvider::create()
{
    mTextureManager = std::make_unique<TexturesManager>();
    mCamera = std::make_unique<Camera>();
    mMath = std::make_unique<GEMath>();
    mGraphics = std::make_unique<Graphics>();
    mLightsManager = std::make_unique<LightSourceManager>();
    mWindow = std::make_unique<GLWindow>();
    mJsonManager = std::make_unique<JsonManager>();
    mShadersManager = std::make_unique<ShadersManager>();
    mSelectedObjectsManager = std::make_unique<SelectedObjectManager>();
}

void ManagersProvider::init()
{
    mWindow->init();
    mGraphics->init();
    mJsonManager->init();
    mShadersManager->init();
    mCamera->init();
}

void ManagersProvider::cleanup()
{
}

TexturesManager* ManagersProvider::getTextureManager() const
{
    return mTextureManager.get();
}

Camera* ManagersProvider::getCamera() const
{
    return mCamera.get();
}

GEMath* ManagersProvider::getMath() const
{
    return mMath.get();
}

Graphics* ManagersProvider::getGraphics() const
{
    return mGraphics.get();
}

LightSourceManager* ManagersProvider::getLightManager() const
{
    return mLightsManager.get();
}

Window* ManagersProvider::getWindow() const
{
    return mWindow.get();
}

JsonManager* ManagersProvider::getJsonManager() const
{
    return mJsonManager.get();
}

ShadersManager* ManagersProvider::getShadersManager() const
{
    return mShadersManager.get();
}

SelectedObjectManager* ManagersProvider::getSelectedObjectManager() const
{
    return mSelectedObjectsManager.get();
}
