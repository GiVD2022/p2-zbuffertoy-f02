#include "GPUConnections/GPULightFactory.hh"


//! createLight

// TODO: Pràctica 2: Fase 1: Incloure els diferents tipus de llum
shared_ptr<GPULight> GPULightFactory::createLight( LightFactory::LIGHT_TYPES t) {
    shared_ptr<GPULight> l;
    switch(t) {
    case LightFactory::LIGHT_TYPES::POINTLIGHT:
        l = make_shared<GPUPointLight>();
        break;
    case LightFactory::LIGHT_TYPES::DIRECTIONALLIGHT:
        l = make_shared<GPUDirectionalLight>();
        break;
    default:
        break;
    }
    return l;
}
shared_ptr<GPULight> GPULightFactory::createLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c, LightFactory::LIGHT_TYPES t) {
    shared_ptr<GPULight> l;
    switch(t) {
    case LightFactory::LIGHT_TYPES::POINTLIGHT:
        l = make_shared<GPUPointLight>(posicio, Ia, Id, Is, a, b, c);
        break;
    default:
        break;
    }
    return l;
}
shared_ptr<GPULight> GPULightFactory::createLight(vec3 direction, vec3 Ia, vec3 Id, vec3 Is, float intensity,  LightFactory::LIGHT_TYPES t){
    shared_ptr<GPULight> l;
    switch(t) {
    case LightFactory::LIGHT_TYPES::DIRECTIONALLIGHT:
        l = make_shared<GPUDirectionalLight>(direction, Ia, Id, Is, intensity);
        break;
    default:
        break;
    }
    return l;
}
