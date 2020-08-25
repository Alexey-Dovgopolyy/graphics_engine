#pragma once

#include "Object.h"

class Scene
{
public:
    bool init();
    void update(float dt);
    void draw();
    void clean();

private:
    std::vector<Object> mObjects;
    //Object* mTestObj = nullptr;
};

