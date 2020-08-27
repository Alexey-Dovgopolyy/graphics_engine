#pragma once

#include "Defines.h"

class Object;

class LightSourceData
{
public:
    void init(Object* object);

    GEVec3 getPosition() const;
    GEVec3 getDirection() const;
    GEVec3 getAmbient() const;
    GEVec3 getDiffuse() const;
    GEVec3 getSpecular() const;
    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;

    void debugSetAmbient(GEVec3 ambient);
    void debugSetDiffuse(GEVec3 diffuse);
    void debugSetSpecular(GEVec3 specular);
    void debugSetConstant(float constant);
    void debugSetLinear(float linear);
    void debugSetQuadratic(float quadratic);

private:
    GEVec3 mDirection = GEVec3(-1.f, -1.f, -1.f);

    float mConstant = 1.f;
    float mLinear = 0.f;
    float mQuadratic = 0.f;

    GEVec3 mAmbient = GEVec3(0.2f, 0.2f, 0.2f);
    GEVec3 mDiffuse = GEVec3(1.f, 1.f, 1.f);
    GEVec3 mSpecular = GEVec3(1.f, 1.f, 1.f);

    Object* mLightObject = nullptr;
};

