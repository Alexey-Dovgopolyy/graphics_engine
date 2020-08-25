#pragma once

#include "Behaviour.h"

class Object;

class LightBehaviour
    : public Behaviour
{
public:
    LightBehaviour(Object* owner);

    void init() override;
    void update(float dt) override;
};

