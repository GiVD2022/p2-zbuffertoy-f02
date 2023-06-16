#pragma once

#include "library/Singleton.hh"
#include "GPUConnections/GPULight.hh"
#include "GPUConnections/GPUPointLight.hh"
#include "GPUConnections/GPUDirectionalLight.hh"
#include "GPUConnections/GPUSpotLight.hh"
#include "Model/Modelling/Lights/LightFactory.hh"

class GPULightFactory: public Singleton<GPULightFactory>
{
    // needs to be friend in order to
    // access the private constructor/destructor
    friend class Singleton<GPULightFactory>;
private:
    GPULightFactory() {};
    ~GPULightFactory() {};
public:  

    shared_ptr<GPULight> createLight( LightFactory::LIGHT_TYPES t);
    shared_ptr<GPULight> createLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c,  LightFactory::LIGHT_TYPES t);
    shared_ptr<GPULight> createLight(vec3 direction, vec3 Ia, vec3 Id, vec3 Is, float intensity, LightFactory::LIGHT_TYPES t);
    shared_ptr<GPULight> createLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, vec3 spotDirection, float spotCosineCutoff, float spotExponent, LightFactory::LIGHT_TYPES t);
    };
