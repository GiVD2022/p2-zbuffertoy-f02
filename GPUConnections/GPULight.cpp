#include "GPUConnections/GPULight.hh"

GPULight::GPULight(vec3 Ia, vec3 Id, vec3 Is): Light(Ia, Id, Is){
}

GPULight::GPULight() {
}

void GPULight::setIndex(int indx) {
    this->index = indx;
}

int GPULight::getIndex() {
    return this->index;
}

void GPULight::toGPU(shared_ptr<QGLShaderProgram> p) {
    // TO DO Pràctica 2: Fase 1: enviar les propietats de Ia, Id i Is a la GPU
    glUniform3fv(gl_IdLights.Ia, 1, this->getIa());
    glUniform3fv(gl_IdLights.Id, 1, this->getId());
    glUniform3fv(gl_IdLights.Is, 1, this->getIs());
    qDebug()<<"Updated lights";
}

void GPULight::setValues(vec3 Ia, vec3 Id, vec3 Is){
    Light::setIa(Ia);
    Light::setId(Id);
    Light::setIs(Is);
}
