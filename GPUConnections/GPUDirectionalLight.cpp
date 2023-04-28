#include "GPUConnections/GPUDirectionalLight.hh"

GPUDirectionalLight::GPUDirectionalLight(vec3 direction, vec3 Ia, vec3 Id, vec3 Is, float intensity): DirectionalLight(direction, Ia, Id, Is, intensity) {
}

void GPUDirectionalLight::toGPU(shared_ptr<QGLShaderProgram> p) {
    // TO DO Pràctica 2: Fase 1: enviar les llums a la GPU
}

vec3 GPUDirectionalLight::vectorL(vec3 point) {
    return DirectionalLight::vectorL(point);
}

float GPUDirectionalLight::attenuation(vec3 point) {
    return DirectionalLight::attenuation(point);
}

float GPUDirectionalLight::distanceToLight(vec3 point) {
    return DirectionalLight::distanceToLight(point);
}
