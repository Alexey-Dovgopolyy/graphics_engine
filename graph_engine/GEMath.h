#pragma once

#include "Defines.h"

class GEMath
{
public:
    void translate(GEMat4x4& mat, GEVec3 pos);
    void rotate(GEMat4x4& mat, float angle, GEVec3 axis);
    void scale(GEMat4x4& mat, GEVec3 scaleVec);

    GEMat4x4 getPerspectiveMat();
    GEMat4x4 getViewMat();
    GEMat4x4 getViewMat(GEVec3 pos, GEVec3 dir, GEVec3 up);

    GEMat4x4 ortho(float left, float right, float bottom, float top, float near, float far);

    void rotate(GEQuat& quat, GEVec3 angles);
    void rotate(GEQuat& quat, float angle, GEVec3 axis);
    GEVec3 getEularAngles(GEQuat& quat);
    float getPitch(GEQuat& quat);
    float getRoll(GEQuat& quat);
    float getYaw(GEQuat& quat);
    GEMat4x4 quatToMat(GEQuat& quat);

    void correntAngleDegrees(float& angle);
};

