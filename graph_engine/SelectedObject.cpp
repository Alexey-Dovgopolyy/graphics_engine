#include "SelectedObject.h"
#include "Object.h"

void SelectedObject::setSelectedObject(Object* object)
{
    mSelectedObject = object;
}

void SelectedObject::move(GEVec3 move)
{
    if (mSelectedObject)
    {
        mSelectedObject->move(move);
    }
}

void SelectedObject::rotate(float angle, GEVec3 axis)
{
    if (mSelectedObject)
    {
        mSelectedObject->rotate(angle, axis);
    }
}

void SelectedObject::scale(GEVec3 scale)
{
    if (mSelectedObject)
    {
        mSelectedObject->scale(scale);
    }
}

void SelectedObject::drawFrame()
{
    if (mSelectedObject == nullptr)
    {
        return;
    }

    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);

    mSelectedObject->draw();

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);

    GEVec3 currentScale = mSelectedObject->getScale();
    mSelectedObject->scale(currentScale + 0.1f);

    mSelectedObject->setShader("outline");
    mSelectedObject->draw();

    mSelectedObject->scale(currentScale);

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glEnable(GL_DEPTH_TEST);
}
