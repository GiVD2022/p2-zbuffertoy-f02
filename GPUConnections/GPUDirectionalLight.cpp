#include "GPUConnections/GPUDirectionalLight.hh"

GPUDirectionalLight::GPUDirectionalLight(vec3 direction, vec3 Ia, vec3 Id, vec3 Is, float intensity): DirectionalLight(direction, Ia, Id, Is, intensity) {
}

void GPUDirectionalLight::toGPU(shared_ptr<QGLShaderProgram> p) {
    // TO DO Pràctica 2: Fase 1: enviar les llums a la GPU
    GPULight::setValues(DirectionalLight::getIa(), DirectionalLight::getId(), DirectionalLight::getIs());
    GPULight::setType(2);
    int i = this->getIndex();
    gl_IdLights.Ia = p->uniformLocation(QString("light_info[%1].Ia").arg(i));
    gl_IdLights.Id = p->uniformLocation(QString("light_info[%1].Id").arg(i));
    gl_IdLights.Is = p->uniformLocation(QString("light_info[%1].Is").arg(i));
    gl_IdLights.type = p->uniformLocation(QString("light_info[%1].type").arg(i));
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
    glUniform1f(gl_IdLights.type, 1);
    glUniform4fv(gl_IdLights.direction, 1, this->getDirection());
    glUniform1f(gl_IdLights.intensity, this->getIntensity());
    qDebug() << "directional lights.....";

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
