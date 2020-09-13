#include "Object.h"
#include "ManagersProvider.h"
#include "GEMath.h"

#include "Camera.h"

Object::Object(const char* path, ObjectType type)
    : mType(type)
{
    Behaviour::setBehaviour(this, mType);
    std::string shader = std::string("shaders/") + mBehaviour->getShaderName();
    init(path, shader.c_str());
}

void Object::init(const char* path, const char* shader)
{
    mTransform = GEMat4x4(1.f);
    mModel.loadModel(path);

    std::string vertShader = std::string(shader) + ".vert";
    std::string fragShader = std::string(shader) + ".frag";
    mShader.init(vertShader.c_str(), fragShader.c_str());

    mBehaviour->init();
}   

void Object::update(float dt)
{
    updateTransform();

    GEMath* math = ManagersProvider::getInstance().getMath();
    GEMat4x4 projection = math->getPerspectiveMat();
    GEMat4x4 view = math->getViewMat();

    mShader.use();

    Camera* camera = ManagersProvider::getInstance().getCamera();
    mShader.setVec3("viewPos", camera->getPosition());

    mShader.setMat4("projection", projection);
    mShader.setMat4("view", view);    
    mShader.setMat4("model", mTransform);

    mBehaviour->update(dt);
}

void Object::draw()
{
    mShader.use();
    mModel.draw(mShader);
}

void Object::move(GEVec3 offset)
{
    mPosition += offset;
    mDirty = true;
}

void Object::rotateX(float angle)
{
    mEulerAngles.x = angle;
    rotate(angle, GEVec3(1.f, 0.f, 0.f));
}

void Object::rotateY(float angle)
{
    mEulerAngles.y = angle;
    rotate(angle, GEVec3(0.f, 1.f, 0.f));
}

void Object::rotateZ(float angle)
{
    mEulerAngles.z = angle;
    rotate(angle, GEVec3(0.f, 0.f, 1.f));
}

void Object::rotate(float angle, GEVec3 axis)
{
    GEMath* math = ManagersProvider::getInstance().getMath();
    math->rotate(mOrientation, angle, axis);
    mDirty = true;
}

void Object::rotate(GEVec3 angles)
{
    GEMath* math = ManagersProvider::getInstance().getMath();

    mEulerAngles += angles;
    math->correntAngleDegrees(mEulerAngles.x);
    math->correntAngleDegrees(mEulerAngles.y);
    math->correntAngleDegrees(mEulerAngles.x);
    math->rotate(mOrientation, mEulerAngles);
    mDirty = true;
}

void Object::scale(GEVec3 scaleVec)
{
    mScale = scaleVec;
    mDirty = true;
}

GEVec3 Object::getPosition() const
{
    return mPosition;
}

GEVec3 Object::getScale() const
{
    return mScale;
}

GEVec3 Object::getAngles()
{
    return mEulerAngles;
}

void Object::setBehaviour(std::unique_ptr<Behaviour>& behaviour)
{
    mBehaviour = std::move(behaviour);
}

Shader& Object::getShader()
{
    return mShader;
}

void Object::updateTransform()
{
    if (mDirty)
    {
        GEMath* math = ManagersProvider::getInstance().getMath();

        mTransform = GEMat4x4(1.f);

        math->translate(mTransform, mPosition);
        math->scale(mTransform, mScale);
        mTransform *= math->quatToMat(mOrientation);

        mDirty = false;
    }
}
