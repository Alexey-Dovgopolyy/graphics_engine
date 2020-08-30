#include "Window.h"

void Window::swapButters()
{
    // empty
}

float Window::getWidth() const
{
    return mWindowWidth;
}

float Window::getHeight() const
{
    return mWindowHeight;
}

float Window::getAspectRatio() const
{
    return mWindowWidth / mWindowHeight;
}

float Window::getLastX() const
{
    return mLastX;
}

void Window::setLastX(float lastX)
{
    mLastX = lastX;
}

float Window::getLastY() const
{
    return mLastY;
}

void Window::setLastY(float lastY)
{
    mLastY = lastY;
}
