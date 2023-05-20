#pragma once

#include <vector>
#include <library/Common.h>
using namespace Common;


#include "GPUConnections/GPUConnectable.hh"
#include "GPUConnections/GPUMesh.hh"
#include "Model/Modelling/Scene.hh"
#include "GPUConnections/GPUFittedPlane.hh"


using namespace std;
using namespace Common;

class GPUScene: public Scene, public GPUConnectable
{
public:

    QString name;

    // dimensions de l'escena virtual que es visualitza: capsa mínima contenidora
    vec3 pmin, pmax;
    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    // Vector d'objectes continguts a l'escena
    std::vector<shared_ptr<GPUObject>> objects;
    std::vector<shared_ptr<GPUObject>> objectsIn;
    std::vector<shared_ptr<GPUObject>> objectsOut;
    std::vector<shared_ptr<GPUObject>> objectsIntersect;

    GPUScene();


    // TO DO: Pràctica 2: Fase 1 Incloure el Fitted Plane que es pugui passar a la GPU
    shared_ptr<GPUFittedPlane> basePlane;
    void setBaseObject(shared_ptr<GPUObject> base);

    // TODO: Pràctica 2: Fase 1
    // Constructora a utilitzar quan s'inicialitza una escena amb un pla base o
    // una esfera base// GPUScene(shared_ptr<GPUFittedPlane> base);

    virtual ~GPUScene();


    void setDimensions(vec3 p1, vec3 p2);

    // TODO Pràctica 2: Fase 1
    // Incloure base a l'escena: FittedPlane
    // void setBasePlane(shared_ptr<FittedPlane> plane);

    // Pràctica 2 opcional: Posible objecte que no sigui un fitted plane: una esfera
    // void setBaseSphere(shared_ptr<Sphere> sphere);

    void addObject(shared_ptr<GPUObject> obj);

    void toGPU(shared_ptr<QGLShaderProgram> p) override;
    void toGPUIn(shared_ptr<QGLShaderProgram> p);
    void toGPUOut(shared_ptr<QGLShaderProgram> p);
    void toGPUIntersect(shared_ptr<QGLShaderProgram> p);

    void calculaInOutIntersect();
    void draw() override;

    void calculCapsaMinCont3DEscena();

private:
    void calculaRadi();
    float radi;

};

