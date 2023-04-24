#pragma once

#include "library/Singleton.hh"
#include "Light.hh"
#include "PointLight.hh"

class LightFactory : public Singleton<LightFactory>
{
    // needs to be friend in order to
    // access the private constructor/destructor
    friend class Singleton<LightFactory>;
private:
    LightFactory() {}
    virtual ~LightFactory() {}

public:

    typedef enum  {
        POINTLIGHT,
        DIRECTIONALLIGHT,
        SPOTLIGHT,
        AREALIGHT
    } LIGHT_TYPES;



    shared_ptr<Light> createLight( LIGHT_TYPES t);
    shared_ptr<Light> createLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c,  LIGHT_TYPES t);
    LIGHT_TYPES getIndexType (shared_ptr<Light> l);
    LIGHT_TYPES getLightType( QString name);
    QString getNameType(LIGHT_TYPES  t);

};
