#include "CameraQuat.h"

CameraQuat::CameraQuat(const glm::vec3& pos) 
    : mPos(pos) 
{
}

CameraQuat::CameraQuat(const glm::vec3& pos, const glm::quat& orient) 
    : mPos(pos)
    , mOrient(orient) 
{
}

const glm::vec3& CameraQuat::position() const 
{ 
    return mPos;
}

const glm::quat& CameraQuat::orientation() const 
{ 
    return mOrient; 
}

glm::mat4 CameraQuat::view() const
{ 
    return glm::translate(glm::mat4_cast(mOrient), mPos);
}

void CameraQuat::translate(const glm::vec3& v) 
{ 
    mPos += v * mOrient; 
}

void CameraQuat::translate(float x, float y, float z) 
{ 
    mPos += glm::vec3(x, y, z) * mOrient;
}

void CameraQuat::rotate(float angle, const glm::vec3& axis) 
{
    mOrient *= glm::angleAxis(angle, axis * mOrient);
}

void CameraQuat::rotate(float angle, float x, float y, float z) 
{ 
    mOrient *= glm::angleAxis(angle, glm::vec3(x, y, z) * mOrient); 
}

void CameraQuat::yaw(float angle)
{ 
    rotate(angle, 0.0f, 1.0f, 0.0f); 
}

void CameraQuat::pitch(float angle) 
{ 
    rotate(angle, 1.0f, 0.0f, 0.0f);
}

void CameraQuat::roll(float angle) 
{ 
    rotate(angle, 0.0f, 0.0f, 1.0f); 
}