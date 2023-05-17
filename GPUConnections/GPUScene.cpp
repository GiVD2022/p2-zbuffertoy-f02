#include "GPUScene.hh"

GPUScene::GPUScene()
{
    pmin.x = -1.0f;  pmin.y = -1.0f; pmin.z = -1.0f;
    pmax.x = 1.0f;  pmax.y = 1.0f; pmax.z = 1.0f;
    // Inicialització de la capsa minima
    capsaMinima.pmin = vec3(-1.0, -1.0,-1.0);
    capsaMinima.a = 2;
    capsaMinima.h = 2;
    capsaMinima.p = 2;
}
/**
 * @brief GPUScene::~GPUScene
 */
GPUScene::~GPUScene() {
    objects.clear();
}

void GPUScene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

/**
 * @brief GPUScene::addObject
 * @param obj
 */
void GPUScene::addObject(shared_ptr<GPUObject> obj) {
    objects.push_back(obj);
    calculCapsaMinCont3DEscena();
}

/**
 * @brief GPUScene::toGPU
 */
void GPUScene::toGPU(shared_ptr<QGLShaderProgram> p) {

    // Envio el radi de la tempesta
    // Un terç de l'escena
    program = p;
    program->setUniformValue("stormRadius", 0.7f);

    vec3 pMax = vec3(capsaMinima.pmin.x + capsaMinima.a, capsaMinima.pmin.y + capsaMinima.h, capsaMinima.pmin.z + capsaMinima.p);
    float r = length((capsaMinima.pmin - pMax))/3;
    float radi = qMin(90.f, r);
    program->setUniformValue("stormRadius", radi);

    for(unsigned int i=0; i < objects.size(); i++){
        if (dynamic_pointer_cast<GPUObject>(objects.at(i))) {
                auto obj = objects.at(i);
                obj->toGPU(p);
        }
    }
}

/**
 * @brief GPUScene::draw
 */
void GPUScene::draw() {

    for(unsigned int i=0; i < objects.size(); i++){
        if (dynamic_pointer_cast<GPUObject>(objects.at(i))) {
                auto obj = objects.at(i);
                obj->draw();
        }
    }
}

/**
 * @brief GPUScene::calculCapsaMinCont3DEscena
 */

void GPUScene::calculCapsaMinCont3DEscena()
{
    Capsa3D c;
    vec3 pmax;

    if (objects.size()==1) {
        capsaMinima = dynamic_pointer_cast<GPUObject>(objects[0])->calculCapsa3D();
        pmax[0] = capsaMinima.pmin[0]+capsaMinima.a;
        pmax[1] = capsaMinima.pmin[1]+capsaMinima.h;
        pmax[2] = capsaMinima.pmin[2]+capsaMinima.p;
    } else {
        capsaMinima.pmin[0]=200;
        capsaMinima.pmin[1]=200;
        capsaMinima.pmin[2]=200;
        pmax[0] = -200;
        pmax[1] = -200;
        pmax[2] = -200;
    }

    for (unsigned int i=0; i<objects.size(); i++) {
       c = dynamic_pointer_cast<GPUObject>(objects[i])->calculCapsa3D();

       if (capsaMinima.pmin[0]>c.pmin[0]) capsaMinima.pmin[0] = c.pmin[0];
       if (capsaMinima.pmin[1]>c.pmin[1]) capsaMinima.pmin[1] = c.pmin[1];
       if (capsaMinima.pmin[2]>c.pmin[2]) capsaMinima.pmin[2] = c.pmin[2];
       if (pmax[0]<c.pmin[0]+c.a) pmax[0] = c.pmin[0]+c.a;
       if (pmax[1]<c.pmin[1]+c.h) pmax[1] = c.pmin[1]+c.h;
       if (pmax[2]<c.pmin[2]+c.p) pmax[2] = c.pmin[2]+c.p;
    }
    capsaMinima.a = pmax[0]-capsaMinima.pmin[0];
    capsaMinima.h = pmax[1]-capsaMinima.pmin[1];
    capsaMinima.p = pmax[2]-capsaMinima.pmin[2];
}
