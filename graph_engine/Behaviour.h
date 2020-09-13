#pragma once

#include "ObjectType.h"

class Object;

class Behaviour
{
public:
    Behaviour(Object* owner);
    virtual ~Behaviour();

    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual const char* getShaderName() = 0;

    static void setBehaviour(Object* owner, ObjectType type);

protected:
    Object* mOwner = nullptr;
};

