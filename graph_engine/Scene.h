#pragma once

#include "Object.h"

class SelectedObjectManager;

class Scene
{
    friend class ShadowMapRenderer;

public:
    bool init();
    void update(float dt);
    void draw();
    void clean();

private:
    std::vector<std::unique_ptr<Object>> mObjects;
    SelectedObjectManager* mSelectedObjectsManager = nullptr;
    //Object* mTestObj = nullptr;
};

