#include "ManagersProvider.h"

#include "TexturesManager.h"
#include "Camera.h"
#include "GEMath.h"
#include "Graphics.h"
#include "LightSourceManager.h"

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
}

void ManagersProvider::init()
{
    mGraphics->init();
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
