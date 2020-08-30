#pragma once
class Window
{
public:
    virtual bool init() = 0;
    virtual void processInput() = 0;
    virtual bool windowShouldClose() const = 0;
    virtual void swapButters();

    float getWidth() const;
    float getHeight() const;
    float getAspectRatio() const;

    float getLastX() const;
    void setLastX(float lastX);
    float getLastY() const;
    void setLastY(float lastY);

protected:
    float mWindowWidth = 800.f;
    float mWindowHeight = 600.f;

    float mLastX = 0.f;
    float mLastY = 0.f;
};

