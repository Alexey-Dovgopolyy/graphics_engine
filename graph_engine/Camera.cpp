#include "Camera.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// constructor with vectors
Camera::Camera(glm::vec3 position , glm::vec3 up, float yaw, float pitch) 
    //: mFront(glm::vec3(0.0f, 0.0f, -1.0f))
    : mMovementSpeed(SPEED)
    , mMouseSensitivity(SENSITIVITY)
    , mZoom(ZOOM)
{
    mFront = glm::vec3(0.f, 0.f, -1.f);
    mPosition = position;
    mWorldUp = up;
    mYaw = yaw;
    mPitch = pitch;
    updateCameraVectors();
}
// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
    : mFront(glm::vec3(0.0f, 0.0f, -1.0f))
    , mMovementSpeed(SPEED)
    , mMouseSensitivity(SENSITIVITY)
    , mZoom(ZOOM)
{
    mPosition = glm::vec3(posX, posY, posZ);
    mWorldUp = glm::vec3(upX, upY, upZ);
    mYaw = yaw;
    mPitch = pitch;
    updateCameraVectors();
}

void Camera::init()
{
}

void Camera::setMovementSpeed(float speed)
{
    mMovementSpeed = speed;
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

float Camera::getZoom()
{
    return mZoom;
}

const glm::vec3& Camera::getPosition() const
{
    return mPosition;
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = mMovementSpeed * deltaTime;
    if (direction == FORWARD)
        mPosition += mFront * velocity;
    if (direction == BACKWARD)
        mPosition -= mFront * velocity;
    if (direction == LEFT)
        mPosition -= mRight * velocity;
    if (direction == RIGHT)
        mPosition += mRight * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mMouseSensitivity;
    yoffset *= mMouseSensitivity;

    mYaw += xoffset;
    mPitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (mPitch > 89.0f)
            mPitch = 89.0f;
        if (mPitch < -89.0f)
            mPitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::processMouseScroll(float yoffset)
{
    mZoom -= (float)yoffset;
    if (mZoom < 1.0f)
        mZoom = 1.0f;
    if (mZoom > 45.0f)
        mZoom = 45.0f;
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(front);
    // also re-calculate the Right and Up vector
    mRight = glm::normalize(glm::cross(mFront, mWorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    mUp = glm::normalize(glm::cross(mRight, mFront));
}
