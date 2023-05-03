#include "GPUConnections/GPUSpotLight.hh"

GPUSpotLight::GPUSpotLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, vec3 spotDirection, float spotCosineCutoff, float spotExponent): SpotLight(posicio, Ia, Id, Is, spotDirection, spotCosineCutoff, spotExponent) {
}

void GPUSpotLight::toGPU(shared_ptr<QGLShaderProgram> p) {
    // TO DO Pràctica 2: Fase 1: enviar les llums a la GPU
    GPULight::setValues(SpotLight::getIa(), SpotLight::getId(), SpotLight::getIs());
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
    glUniform4fv(gl_IdLights.position, 1, this->getPos());
    glUniform4fv(gl_IdLights.spotDirection, 1, this->getSpotDirection());
    glUniform1f(gl_IdLights.spotCosineCutoff, this->getSpotCosineCutoff());
    glUniform1f(gl_IdLights.spotExponent, this->getSpotExponent());
    qDebug() << "spot lights.....";
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
