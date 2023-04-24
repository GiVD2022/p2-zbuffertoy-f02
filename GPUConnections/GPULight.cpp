#include "GPUConnections/GPULight.hh"

GPULight::GPULight(vec3 Ia, vec3 Id, vec3 Is): Light(Ia, Id, Is){
}

GPULight::GPULight() {
}

void GPULight::toGPU(shared_ptr<QGLShaderProgram> p) {
    // TO DO Pràctica 2: Fase 1: enviar les propietats de Ia, Id i Is a la GPU
    // 1. Es declara un vector d'identificadors de memòria de la GPU
    idLights idVector[5];
    // 2. obtenció dels identificadors de la GPU: Suposem i l'index de l'i-èssim element del vector
    for (int i = 0; i < 3; i++) {
        idVector[i].idIA = p->uniformLocation(QString("Lights[%1].Ia").arg(i));
        idVector[i].idId = p->uniformLocation(QString("Lights[%1].Id").arg(i));
        idVector[i].idIs = p->uniformLocation(QString("Lights[%1].Is").arg(i));
    }
    // 3. Bind de les zones de memòria que corresponen, element a element de l’array
    for (int i = 0; i < 3; i++) {
        glUniform3fv(idVector[i].idIA, 1, &Ia[0]);
        glUniform3fv(idVector[i].idId, 1, &Id[0]);
        glUniform3fv(idVector[i].idIs, 1, &Is[0]);
    }

}
