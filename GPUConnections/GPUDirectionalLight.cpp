#include "GPUConnections/GPUDirectionalLight.hh"

GPUDirectionalLight::GPUDirectionalLight(vec3 direction, vec3 Ia, vec3 Id, vec3 Is, float intensity): DirectionalLight(direction, Ia, Id, Is, intensity) {
}

void GPUDirectionalLight::toGPU(shared_ptr<QGLShaderProgram> p) {
    // TO DO Pràctica 2: Fase 1: enviar les llums a la GPU
    GPULight::toGPU(p);

    struct gl_IdDirectionalLight {
        // Directional lights
        GLuint direction;
        GLuint intensity;

    };
    gl_IdDirectionalLight gl_IdDirectionalLightVec;
    int i = this->getIndex();
    // Directional lights
    gl_IdDirectionalLightVec.direction = p->uniformLocation(QString("light_info[%1].direction").arg(i));
    gl_IdDirectionalLightVec.intensity = p->uniformLocation(QString("light_info[%1].intensity").arg(i));

    glUniform4fv(gl_IdDirectionalLightVec.direction, 1, this->getDirection());
    glUniform1f(gl_IdDirectionalLightVec.intensity, this->getIntensity());
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
