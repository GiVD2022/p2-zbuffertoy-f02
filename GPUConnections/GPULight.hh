#pragma once

#include "library/Common.h"
#include "GPUConnections/GPUConnectable.hh"
#include "Model/Modelling/Lights/Light.hh"

#define MAX 5

using namespace std;

class GPULight: public Light, public GPUConnectable {

public:
    /*
     * Constructor de la classe Light.
     * param Ia: component ambient de la llum.
     * param Id: component difosa de la llum.
     * param Is: component especular de la llum.
     * */
    GPULight(vec3 Ia, vec3 Id, vec3 Is);
    GPULight();
    virtual ~GPULight() {};

    //Calcula el factor d'atenuacio de la llum al punt passat per parametre
    virtual float attenuation(vec3 point) override = 0;
    //Calcula el vector L amb origen el punt passat per parametre
    virtual vec3 vectorL(vec3 point) override = 0;
    //Calcula la distancia del punt a la llum
    virtual float distanceToLight(vec3 point) override = 0;

    virtual void toGPU(shared_ptr<QGLShaderProgram> p) override;

    int getIndex();
    void setIndex(int indx);

    int getType();
    void setType(int type);

    void setValues(vec3 Ia, vec3 Id, vec3 Is);

    struct gl_IdLight {
        GLuint type;
        GLuint Ia;
        GLuint Id;
        GLuint Is;
        GLuint position;
        GLuint coeficients;

        // Directional lights
        GLuint direction;
        GLuint intensity;

        // Spot lights
        GLuint spotDirection;
        GLuint spotCosineCutoff;
        GLuint spotExponent;

    };
    gl_IdLight gl_IdLights;

private:
    int index;
    /*
     * 0 -> point light
     * 1 -> spot light
     * 2 -> directional light
     * */
    int type;

};

