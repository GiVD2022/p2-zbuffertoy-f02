#include "GPUConnections/GPUPointLight.hh"

GPUPointLight::GPUPointLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c): PointLight(posicio, Ia, Id, Is, a, b, c) {
}

void GPUPointLight::toGPU(shared_ptr<QGLShaderProgram> p) {
    // TO DO Pràctica 2: Fase 1: enviar les llums a la GPU
    GPULight::toGPU(p);

    struct gl_IdPointLight {
        // Point lights
        GLuint position;
        GLuint coeficients;
    };
    gl_IdPointLight gl_IdPointLightVec;
    int i = this->getIndex();

    gl_IdPointLightVec.position = p->uniformLocation(QString("light_info[%1].position").arg(i));
    gl_IdPointLightVec.coeficients = p->uniformLocation(QString("light_info[%1].coeficients").arg(i));

    glUniform4fv(gl_IdPointLightVec.position, 1, this->getPosition());
    glUniform3fv(gl_IdPointLightVec.coeficients, 1, this->getCoeficients());
    qDebug() << "point lights.....";
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
