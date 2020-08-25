#include "GEMath.h"
#include <cmath>

#include "ManagersProvider.h"
#include "Camera.h"
#include "Graphics.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

void GEMath::translate(GEMat4x4& mat, GEVec3 pos)
{
    mat = glm::translate(mat, pos);
}

void GEMath::rotate(GEMat4x4& mat, float angle, GEVec3 axis)
{
    mat = glm::rotate(mat, glm::radians(angle), axis);
}

void GEMath::scale(GEMat4x4& mat, GEVec3 scaleVec)
{
    mat = glm::scale(mat, scaleVec);
}

GEMat4x4 GEMath::getPerspectiveMat()
{
    ManagersProvider& provider = ManagersProvider::getInstance();

    Camera* camera = provider.getCamera();
    float zoom = camera->getZoom();

    Graphics* graphics = provider.getGraphics();
    float scrRatio = graphics->getAspectRatio();

    glm::mat4 proj = glm::perspective(glm::radians(zoom), scrRatio, 0.1f, 100.0f);
    return proj;
}

GEMat4x4 GEMath::getViewMat()
{
    Camera* camera = ManagersProvider::getInstance().getCamera();
    glm::mat4 view = camera->getViewMatrix();
    return view;
}

void GEMath::rotate(GEQuat& quat, GEVec3 angles)
{
    GEVec3 anglesRad = glm::radians(angles);
    quat = glm::quat(anglesRad);
}

void GEMath::rotate(GEQuat& quat, float angle, GEVec3 axis)
{
    float radian = glm::radians(angle);
    quat = glm::angleAxis(radian, axis/* * quat*/);
}

GEVec3 GEMath::getEularAngles(GEQuat& quat)
{
    GEVec3 angles = glm::eulerAngles(quat);
    angles = glm::degrees(angles);
    return angles;
}

float GEMath::getPitch(GEQuat& quat)
{
    return glm::pitch(quat);
}

float GEMath::getRoll(GEQuat& quat)
{
    return glm::roll(quat);
}

float GEMath::getYaw(GEQuat& quat)
{
    return glm::yaw(quat);
}

GEMat4x4 GEMath::quatToMat(GEQuat& quat)
{
    return glm::mat4_cast(quat);
}

void GEMath::correntAngleDegrees(float& angle)
{
    angle = fmod(angle, 360.f);
}
