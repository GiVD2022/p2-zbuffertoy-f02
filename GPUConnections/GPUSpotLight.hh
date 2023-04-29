#pragma once

#include "GPUConnections/GPULight.hh"
#include "Model/Modelling/Lights/SpotLight.hh"

class GPUSpotLight: public GPULight, public SpotLight {
public:
    GPUSpotLight() {};
    /*
     * Constructor de la classe SpotLight.
     * param posicio: posició de la llum.
     * param Ia: component ambient de la llum.
     * param Id: component difosa de la llum.
     * param Is: component especular de la llum.
     * param spotDirection: direcció de la llum
     * param spotCosineCutoff: angle de la llum
     * param spotExponent: no negatiu que determina com la intensitat disminueix
     * */
    GPUSpotLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, vec3 spotDirection, float spotCosineCutoff, float spotExponent);
    virtual ~GPUSpotLight() {}

    virtual void toGPU(shared_ptr<QGLShaderProgram> p) override;
    virtual vec3 vectorL(vec3 point) override;
    virtual float attenuation(vec3 point) override;
    virtual float distanceToLight(vec3 point) override;
};

