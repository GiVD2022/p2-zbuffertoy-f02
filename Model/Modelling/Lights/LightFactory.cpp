#include "LightFactory.hh"

//! createLight
//! TODO: Fase 2: Incloure els diferents tipus de llum
shared_ptr<Light> LightFactory::createLight(LIGHT_TYPES t) {
    shared_ptr<Light> l;
    switch(t) {
    case POINTLIGHT:
        l = make_shared<PointLight>();
        break;
    default:
        break;
    }
    return l;
}
shared_ptr<Light> LightFactory::createLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c, LIGHT_TYPES t) {
    shared_ptr<Light> l;
    switch(t) {
    case POINTLIGHT:
        l = make_shared<PointLight>(posicio, Ia, Id, Is, a, b, c);
        break;
    default:
        break;
    }
    return l;
}


LightFactory::LIGHT_TYPES LightFactory::getIndexType (shared_ptr<Light> l) {
    if (dynamic_pointer_cast<PointLight>(l) != nullptr) {
        return LIGHT_TYPES::POINTLIGHT;
    }
    return LIGHT_TYPES::POINTLIGHT;
}

LightFactory::LIGHT_TYPES LightFactory::getLightType( QString name) {
    if (name=="POINTLIGHT") return LIGHT_TYPES::POINTLIGHT;
    else if (name=="SPOTLIGHT") return LIGHT_TYPES::SPOTLIGHT;
    else if (name=="DIRECTIONALLIGHT") return LIGHT_TYPES::DIRECTIONALLIGHT;
    else if (name=="AREALIGHT") return LIGHT_TYPES::AREALIGHT;
    else return  LIGHT_TYPES::POINTLIGHT;
}

QString LightFactory::getNameType(LIGHT_TYPES t)
{
    switch(t) {
    case POINTLIGHT:
        return(QString("POINTLIGHT"));
        break;
    case DIRECTIONALLIGHT:
        return(QString("DIRECTIONALLIGHT"));
        break;
    case SPOTLIGHT:
        return(QString("SPOTLIGHT"));
        break;
    case AREALIGHT:
        return(QString("AREALIGHT"));
    default:
        return(QString("POINTLIGHT"));
        break;
    }
}
