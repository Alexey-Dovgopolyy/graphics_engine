#include "ShadowMapRenderer.h"
#include "ManagersProvider.h"
#include "ShadersManager.h"
#include "Graphics.h"
#include "GEMath.h"

#include "ShadowMapRenderer.h"
#include "LightSourceData.h"
#include "LightSourceManager.h"
#include "ShadersManager.h"
#include "Scene.h"
#include "Window.h"

const unsigned int SHADOW_WIDTH = 1024;
const unsigned int SHADOW_HEIGHT = 1024;

void ShadowMapRenderer::init()
{
    glGenFramebuffers(1, &mDepthMapFBO);

    // create depth texture
    glGenTextures(1, &mDepthMap);
    glBindTexture(GL_TEXTURE_2D, mDepthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, mDepthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMapRenderer::renderShadowMap(GEVec3 lightPos, Scene& scene)
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT);

    GEMath* math = ManagersProvider::getInstance().getMath();

    GEMat4x4 lightProjection;
    GEMat4x4 lightView;
    
    lightProjection = math->ortho(-10.0f, 10.0f, -10.0f, 10.0f, mNearPlane, mFarPlane);
    lightView = math->getViewMat(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));

    mLightSpaceMatrix = lightProjection * lightView;

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, mDepthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    for (Object& object : scene.mObjects)
    {
        Shader curShader = object.getShader();
        object.setShader("shadowMap");
        object.drawShadow(mLightSpaceMatrix);
        object.setShader(curShader);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ManagersProvider::getInstance().getWindow()->setupViewport();
}

unsigned int ShadowMapRenderer::getDepthMap() const
{
    return mDepthMap;
}

GEMat4x4 ShadowMapRenderer::getLightSpaceMatrix() const
{
    return mLightSpaceMatrix;
}

void ShadowMapRenderer::drawDebugShadowMap()
{
    ShadersManager* shaderManager = ManagersProvider::getInstance().getShadersManager();
    Shader debugShadowMap = shaderManager->getShader("debugShadowMap");

    debugShadowMap.use();
    debugShadowMap.setFloat("near_plane", mNearPlane);
    debugShadowMap.setFloat("far_plane", mFarPlane);
    
    Graphics* graphics = ManagersProvider::getInstance().getGraphics();
    graphics->drawDebugShadow(debugShadowMap);
}

