#include "Behaviour.h"
#include "Object.h"
#include "ObjectBehaviour.h"
#include "LightBehaviour.h"

#include <memory>

Behaviour::Behaviour(Object* owner)
    : mOwner(owner)
{
}

Behaviour::~Behaviour()
{
}

void Behaviour::setBehaviour(Object* owner, ObjectType type)
{
    //std::unique_ptr<Behaviour> behaviour;

    if (type == ObjectType::sceneObject)
    {
        std::unique_ptr<Behaviour> behaviour = std::make_unique<ObjectBehaviour>(owner);
        owner->setBehaviour(behaviour);
    }
    else if (type == ObjectType::lightSource)
    {
        std::unique_ptr<Behaviour> behaviour = std::make_unique<LightBehaviour>(owner);
        owner->setBehaviour(behaviour);
    }

    //owner->setBehaviour(std::move(behaviour));
}
