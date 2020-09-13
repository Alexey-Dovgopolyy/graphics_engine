#include "SelectedObjectManager.h"
#include "Object.h"
#include "ManagersProvider.h"
#include "Graphics.h"

void SelectedObjectManager::setSelectedObject(Object* object)
{
    mSelectedObject = object;
}

Object* SelectedObjectManager::getSelectedObject() const
{
    return mSelectedObject;
}

void SelectedObjectManager::move(GEVec3 move)
{
    if (mSelectedObject)
    {
        mSelectedObject->move(move);
    }
}

void SelectedObjectManager::rotate(float angle, GEVec3 axis)
{
    if (mSelectedObject)
    {
        mSelectedObject->rotate(angle, axis);
    }
}

void SelectedObjectManager::scale(GEVec3 scale)
{
    if (mSelectedObject)
    {
        mSelectedObject->scale(scale);
    }
}

void SelectedObjectManager::drawFrame()
{
    if (mSelectedObject == nullptr)
    {
        return;
    }

    Graphics* graphics = ManagersProvider::getInstance().getGraphics();
    graphics->beforeDrawOutlinedObject();

    mSelectedObject->draw();

    graphics->beforeDrawOutline();

    Shader currentShader = mSelectedObject->getShader();

    mSelectedObject->setShader("outline");

    GEVec3 currentScale = mSelectedObject->getScale();
    GEVec3 newScale = GEVec3(1.1f, 1.1f, 1.1f);

    mSelectedObject->scale(newScale);
    mSelectedObject->update(0.f);

    mSelectedObject->draw();

    mSelectedObject->setShader(currentShader);
    mSelectedObject->scale(currentScale);

    graphics->afterDrawOutline();
}
