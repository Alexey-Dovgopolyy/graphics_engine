#pragma once
#include "Defines.h"

class Shader;
class Scene;

class ShadowMapRenderer
{
public:
    void init();
    void renderShadowMap(GEVec3 lightPos, Scene& scene);

    unsigned int getDepthMap() const;
    GEMat4x4 getLightSpaceMatrix() const;

    void drawDebugShadowMap();

private:
    unsigned int mDepthMapFBO = 0;
    unsigned int mDepthMap = 0;
    float mNearPlane = 1.0f;
    float mFarPlane = 30.5f;
    GEMat4x4 mLightSpaceMatrix;
};

