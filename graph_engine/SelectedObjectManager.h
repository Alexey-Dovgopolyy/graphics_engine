#pragma once

#include "Defines.h"

class Object;

class SelectedObjectManager
{
public:
    void setSelectedObject(Object* object);
    Object* getSelectedObject() const;

    void move(GEVec3 move);
    void rotate(float angle, GEVec3 axis);
    void scale(GEVec3 scale);

    void drawFrame();

private:
    Object* mSelectedObject = nullptr;
};

