#include "LightSourceData.h"
#include "Object.h"

void LightSourceData::init(Object* object)
{
    mLightObject = object;
}

GEVec3 LightSourceData::getPosition() const
{
    if (mLightObject)
    {
        return mLightObject->getPosition();
    }
    return GEVec3(0.f, 0.f, 0.f);
}

GEVec3 LightSourceData::getDirection() const
{
    return mDirection;
}

GEVec3 LightSourceData::getAmbient() const
{
    return mAmbient;
}

GEVec3 LightSourceData::getDiffuse() const
{
    return mDiffuse;
}

GEVec3 LightSourceData::getSpecular() const
{
    return mSpecular;
}

float LightSourceData::getConstant() const
{
    return mConstant;
}

float LightSourceData::getLinear() const
{
    return mLinear;
}

float LightSourceData::getQuadratic() const
{
    return mQuadratic;
}

void LightSourceData::debugSetAmbient(GEVec3 ambient)
{
    mAmbient = ambient;
}

void LightSourceData::debugSetDiffuse(GEVec3 diffuse)
{
    mDiffuse = diffuse;
}

void LightSourceData::debugSetSpecular(GEVec3 specular)
{
    mSpecular = specular;
}

void LightSourceData::debugSetConstant(float constant)
{
    mConstant = constant;
}

void LightSourceData::debugSetLinear(float linear)
{
    mLinear = linear;
}

void LightSourceData::debugSetQuadratic(float quadratic)
{
    mQuadratic = quadratic;
}
