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
    struct gl_IdLight {
        GLuint Ia;
        GLuint Id;
        GLuint Is;
    };
    gl_IdLight gl_IdLightVec;
    int i = this->getIndex();
    gl_IdLightVec.Ia = p->uniformLocation(QString("light_info[%1].Ia").arg(i));
    gl_IdLightVec.Id = p->uniformLocation(QString("light_info[%1].Id").arg(i));
    gl_IdLightVec.Is = p->uniformLocation(QString("light_info[%1].Is").arg(i));
    // Bind the values of each property
    glUniform3fv(gl_IdLightVec.Ia, 1, this->getIa());
    glUniform3fv(gl_IdLightVec.Id, 1, this->getId());
    glUniform3fv(gl_IdLightVec.Is, 1, this->getIs());
    qDebug() << "Vector: (" << this->getIa().x << ", " << this->getIa().y << ", " << this->getIa().z << ")";


    qDebug() << "Parent light.....";

}
