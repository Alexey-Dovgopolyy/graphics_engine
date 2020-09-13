#pragma once

#include "Defines.h"
#include "Model.h"
#include "Shader.h"

#include "ObjectType.h"
#include "Behaviour.h"

#include <memory>

class Behaviour;

class Object
{
public:
    Object(const char* path, ObjectType type);
    virtual void init(const char* path, const char* shader);

    virtual void update(float dt);
    void draw();

    void move(GEVec3 offset);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void rotate(float angle, GEVec3 axis);
    void rotate(GEVec3 angles);
    void scale(GEVec3 scaleVec);

    GEVec3 getPosition() const;
    GEVec3 getScale() const;
    GEVec3 getAngles();

    void setBehaviour(std::unique_ptr<Behaviour>& behaviour);

    void setShader(const std::string& name);
    void setShader(Shader& shader);
    Shader& getShader();

protected:
    void updateTransform();

protected:
    ObjectType mType;
    std::unique_ptr<Behaviour> mBehaviour;

    Model mModel;
    Shader mShader;

    GEVec3 mPosition = GEVec3(0.f, 0.f, 0.f);
    GEVec3 mScale = GEVec3(1.f, 1.f, 1.f);
    GEVec3 mEulerAngles = GEVec3(0.f, 0.f, 0.f);
    GEQuat mOrientation = GEQuat(1.0, 0.0, 0.0, 0.0);
    bool mDirty = true;

    GEMat4x4 mTransform = GEMat4x4(1.f);
};

