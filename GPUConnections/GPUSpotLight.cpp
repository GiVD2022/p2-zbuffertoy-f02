#include "GPUConnections/GPUSpotLight.hh"

GPUSpotLight::GPUSpotLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, vec3 spotDirection, float spotCosineCutoff, float spotExponent): SpotLight(posicio, Ia, Id, Is, spotDirection, spotCosineCutoff, spotExponent) {
}

void GPUSpotLight::toGPU(shared_ptr<QGLShaderProgram> p) {
    // TO DO Pràctica 2: Fase 1: enviar les llums a la GPU
    GPULight::toGPU(p);

    struct gl_IdSpotLight {
        // Spot lights
        GLuint spotDirection;
        GLuint spotCosineCutoff;
        GLuint spotExponent;

    };
    gl_IdSpotLight gl_IdSpotLightVec;
    int i = this->getIndex();
    // Spot lights
    gl_IdSpotLightVec.spotDirection = p->uniformLocation(QString("light_info[%1].spotDirection").arg(i));
    gl_IdSpotLightVec.spotCosineCutoff = p->uniformLocation(QString("light_info[%1].spotCosineCutoff").arg(i));
    gl_IdSpotLightVec.spotExponent = p->uniformLocation(QString("light_info[%1].spotExponent").arg(i));

    glUniform4fv(gl_IdSpotLightVec.spotDirection, 1, this->getSpotDirection());
    glUniform1f(gl_IdSpotLightVec.spotCosineCutoff, this->getSpotCosineCutoff());
    glUniform1f(gl_IdSpotLightVec.spotExponent, this->getSpotExponent());
    qDebug() << "Vector: (" << this->getIa().x << ", " << this->getIa().y << ", " << this->getIa().z << ")";
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
