#include "GPUConnections/GPUPointLight.hh"

GPUPointLight::GPUPointLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c): PointLight(posicio, Ia, Id, Is, a, b, c) {
}

void GPUPointLight::toGPU(shared_ptr<QGLShaderProgram> p) {
    //setters of the values of GPULights
    GPULight::setValues(PointLight::getIa(), PointLight::getId(), PointLight::getIs());
    // TO DO Pràctica 2: Fase 1: enviar les llums a la GPU
    int i = this->getIndex();
    gl_IdLights.Ia = p->uniformLocation(QString("light_info[%1].Ia").arg(i));
    gl_IdLights.Id = p->uniformLocation(QString("light_info[%1].Id").arg(i));
    gl_IdLights.Is = p->uniformLocation(QString("light_info[%1].Is").arg(i));
    gl_IdLights.position = p->uniformLocation(QString("light_info[%1].position").arg(i));
    gl_IdLights.coeficients = p->uniformLocation(QString("light_info[%1].coeficients").arg(i));

    // Directional lights
    gl_IdLights.direction = p->uniformLocation(QString("light_info[%1].direction").arg(i));
    gl_IdLights.intensity = p->uniformLocation(QString("light_info[%1].intensity").arg(i));

    // Spot lights
    gl_IdLights.spotDirection = p->uniformLocation(QString("light_info[%1].spotDirection").arg(i));
    gl_IdLights.spotCosineCutoff = p->uniformLocation(QString("light_info[%1].spotCosineCutoff").arg(i));
    gl_IdLights.spotExponent = p->uniformLocation(QString("light_info[%1].spotExponent").arg(i));

    GPULight::toGPU(p);
    glUniform4fv(gl_IdLights.position, 1, this->getPosition());
    glUniform3fv(gl_IdLights.coeficients, 1, this->getCoeficients());

}

vec3 GPUPointLight::vectorL(vec3 point) {
    return PointLight::vectorL(point);
}

float GPUPointLight::attenuation(vec3 point) {
    return PointLight::attenuation(point);
}

float GPUPointLight::distanceToLight(vec3 point) {
    return PointLight::distanceToLight(point);
}
