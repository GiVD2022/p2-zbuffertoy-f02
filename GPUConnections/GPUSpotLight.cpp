#include "GPUConnections/GPUSpotLight.hh"

GPUSpotLight::GPUSpotLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, vec3 spotDirection, float spotCosineCutoff, float spotExponent): SpotLight(posicio, Ia, Id, Is, spotDirection, spotCosineCutoff, spotExponent) {
}

void GPUSpotLight::toGPU(shared_ptr<QGLShaderProgram> p) {
    // TO DO Pràctica 2: Fase 1: enviar les llums a la GPU
}

vec3 GPUSpotLight::vectorL(vec3 point) {
    return SpotLight::vectorL(point);
}

float GPUSpotLight::attenuation(vec3 point) {
    return SpotLight::attenuation(point);
}

float GPUSpotLight::distanceToLight(vec3 point) {
    return SpotLight::distanceToLight(point);
}
