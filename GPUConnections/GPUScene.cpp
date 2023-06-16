#include "GPUScene.hh"
#include "GPUFittedPlane.hh"

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

void GPUScene::setBaseObject(shared_ptr<GPUObject> base) {
    // Check the type of base object
    if (auto plane = std::dynamic_pointer_cast<GPUFittedPlane>(base)) {
        basePlane = plane;
    } else {
        throw std::invalid_argument("Invalid base object type.");
    }
}

void GPUScene::removeBaseObject(shared_ptr<GPUObject> base) {
    if (basePlane == base) {
        basePlane.reset();
        objects.erase(std::remove(objects.begin(), objects.end(), base), objects.end());
        calculCapsaMinCont3DEscena();
        calculaRadi();
    }
}

/**
 * @brief GPUScene::addObject
 * @param obj
 */
void GPUScene::addObject(shared_ptr<GPUObject> obj) {
    Scene::objects.push_back(obj);
    objects.push_back(obj);
    calculCapsaMinCont3DEscena();
    calculaRadi();
}

void GPUScene::calculaInOutIntersect(){
    objectsIn.clear();
    objectsOut.clear();
    objectsIntersect.clear();
    for(unsigned int i=0; i < objects.size(); i++){
        if (dynamic_pointer_cast<GPUObject>(objects.at(i))) {
                auto obj = objects.at(i);
                //Decidir en quin array va
                auto capsaObj = obj->calculCapsa3D();
                vec3 pMax = vec3(capsaObj.pmin.x + capsaObj.a, capsaObj.pmin.y + capsaObj.h, capsaObj.pmin.z + capsaObj.p);

                vec3 centre = (pMax + capsaObj.pmin)/2.0;

                // Distancia entre centres
                float dist = length(centre);

                // Si esta completament dins l'esfera
                if( (dist + length(pMax - centre) ) < radi ){
                    qDebug() << "in\n";
                    objectsIn.push_back(obj);
                // Si esta completament fora
                } else if( (dist - radi ) > length(pMax - centre)){
                    qDebug() << "out\n";
                    objectsOut.push_back(obj);
                } else {
                    qDebug() << "intersect\n";
                    objectsIntersect.push_back(obj);
                }
        }
    }
}

void GPUScene::calculaRadi(){
    vec3 pMax = vec3(capsaMinima.pmin.x + capsaMinima.a, capsaMinima.pmin.y + capsaMinima.h, capsaMinima.pmin.z + capsaMinima.p);
    float r = length((capsaMinima.pmin - pMax))/3;
    radi = qMin(90.f, r);
}

/**
 * @brief GPUScene::toGPU
 */
void GPUScene::toGPU(shared_ptr<QGLShaderProgram> p) {

    // Envio el radi de la tempesta
    // Un terç de l'escena
    program = p;

    calculaRadi();

    program->setUniformValue("stormRadius", radi);

    for(unsigned int i=0; i < objects.size(); i++){
        if (dynamic_pointer_cast<GPUObject>(objects.at(i))) {
                auto obj = objects.at(i);
                obj->toGPU(p);
        }
    }
}


/**
 * @brief GPUScene::toGPU
 */
void GPUScene::toGPUIn(shared_ptr<QGLShaderProgram> p) {

    // Envio el radi de la tempesta
    // Un terç de l'escena
    program = p;

    calculaRadi();

    program->setUniformValue("stormRadius", radi);

    for(unsigned int i=0; i < objectsIn.size(); i++){
        if (dynamic_pointer_cast<GPUObject>(objectsIn.at(i))) {
                auto obj = objectsIn.at(i);
                obj->toGPU(p);
        }
    }
}

/**
 * @brief GPUScene::toGPU
 */
void GPUScene::toGPUOut(shared_ptr<QGLShaderProgram> p) {

    // Envio el radi de la tempesta
    // Un terç de l'escena
    program = p;

    calculaRadi();

    program->setUniformValue("stormRadius", radi);

    for(unsigned int i=0; i < objectsOut.size(); i++){
        if (dynamic_pointer_cast<GPUObject>(objectsOut.at(i))) {
                auto obj = objectsOut.at(i);
                obj->toGPU(p);
        }
    }
}


/**
 * @brief GPUScene::toGPU
 */
void GPUScene::toGPUIntersect(shared_ptr<QGLShaderProgram> p) {

    // Envio el radi de la tempesta
    // Un terç de l'escena
    program = p;

    calculaRadi();

    program->setUniformValue("stormRadius", radi);

    for(unsigned int i=0; i < objectsIntersect.size(); i++){
        if (dynamic_pointer_cast<GPUObject>(objectsIntersect.at(i))) {
                auto obj = objectsIntersect.at(i);
                obj->toGPU(p);
        }
    }
}

/**
 * @brief GPUScene::draw
 */
void GPUScene::draw() {
    // Draw the fitted plane first
    if (basePlane) {
        basePlane->draw();
    }

    // Draw the remaining objects
    for(unsigned int i = 0; i < objects.size(); i++){
        if (dynamic_pointer_cast<GPUObject>(objects.at(i)) && objects.at(i) != basePlane) {
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

void GPUScene::removeFittedPlanes() {
    vector<shared_ptr<GPUObject>> objectsToRemove;

    for (const auto& obj : objects) {
        if (dynamic_pointer_cast<GPUFittedPlane>(obj)) {
            objectsToRemove.push_back(obj);
        }
    }

    for (const auto& obj : objectsToRemove) {
        removeObject(obj);
    }
}

void GPUScene::removeObject(shared_ptr<GPUObject> obj) {
    auto it = find(objects.begin(), objects.end(), obj);
    if (it != objects.end()) {
        objects.erase(it);
        calculCapsaMinCont3DEscena();
        calculaRadi();
    }
}
