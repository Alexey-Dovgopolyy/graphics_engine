#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

class CameraQuat 
{
public:
    CameraQuat(void) = default;
    CameraQuat(const CameraQuat&) = default;

    CameraQuat(const glm::vec3& pos);
    CameraQuat(const glm::vec3& pos, const glm::quat& orient);

    CameraQuat& operator =(const CameraQuat&) = default;

    const glm::vec3& position(void) const;
    const glm::quat& orientation(void) const;

    glm::mat4 view(void) const;

    void translate(const glm::vec3& v);
    void translate(float x, float y, float z);

    void rotate(float angle, const glm::vec3& axis);
    void rotate(float angle, float x, float y, float z);

    void yaw(float angle);
    void pitch(float angle);
    void roll(float angle);

private:
    glm::vec3 mPos;
    glm::quat mOrient;
};

