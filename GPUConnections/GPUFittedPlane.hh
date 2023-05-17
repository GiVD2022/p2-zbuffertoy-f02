#pragma once

#include <library/Common.h>
using namespace Common;

#include "GPUObject.hh"
#include "Model/Modelling/Objects/FittedPlane.hh"


class GPUFittedPlane: public FittedPlane, public GPUObject
{
public:
    GPUFittedPlane();
    GPUFittedPlane(vec3 pmin, vec3 pmax);
    GPUFittedPlane(const QString &fileName);

    ~GPUFittedPlane(){}

    virtual void toGPU(shared_ptr<QGLShaderProgram> p) override;
    virtual void draw() override;
    bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    void aplicaTG(shared_ptr<TG>) override;

    void read(const QJsonObject &json) override;
    Capsa3D calculCapsa3D() override;
    virtual void print(int indentation) const override;

private:
    // Estructures per passar a la GPU
    GLuint buffer;
    GLuint vao;

    vec4 *points; // els vèrtexs repetits
    vec4 *normals;

    int Index; // index de control del numero de vèrtexs a passar a la GPU
    int Index_n;

    void make(); // Funció per fer els triangles a partir de punts
};

