#pragma once

#include "Defines.h"

class Object;

class SelectedObject
{
public:
    void setSelectedObject(Object* object);

    void move(GEVec3 move);
    void rotate(float angle, GEVec3 axis);
    void scale(GEVec3 scale);

    void drawFrame();

private:
    Object* mSelectedObject = nullptr;
};

