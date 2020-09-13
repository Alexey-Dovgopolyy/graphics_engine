#pragma once

#include "Behaviour.h"

class Object;

class ObjectBehaviour
    : public Behaviour
{
public:
    ObjectBehaviour(Object* owner);

    void init() override;
    void update(float dt) override;
    const char* getShaderName() override;
};

