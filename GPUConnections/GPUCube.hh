#pragma once
#include "library/Common.h"
using namespace Common;

#include <QOpenGLTexture>

#include "GPUObject.hh"
#include "Model/Modelling/Objects/Mesh.hh"
#include "GPUConnections/GPUMaterial.hh"
#include "GPUMaterialFactory.hh"

static int NUMPOINTS = 36;

class GPUCube: public Cube, public GPUObject
{
public:
    GPUCube();
    GPUCube(const QString &fileName);
    GPUCube(const int npoints, const QString &fileName);

    ~GPUCube();

    virtual void toGPU(shared_ptr<QGLShaderProgram> p) override;
    virtual void draw() override;
    Capsa3D calculCapsa3D() override;
    bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    void aplicaTG(shared_ptr<TG>) override;

    void read(const QJsonObject &json) override = 0;

    void compute_indirect_mapping();

private:
    // Estructures per passar a la GPU
    GLuint buffer;
    GLuint vao;

    // Representació explícita de l'objecte per poder ser passat a la GPU
    int   numPoints;
    vec4 *points;
    vec4 *normals;
    vec2 *textures;


    int Index; // index de control del numero de vèrtexs a passar a la GPU

    shared_ptr<QOpenGLTexture> texture;
    GPUMaterialFactory::MATERIAL_TYPES type;

    void make();

    void setTexture(shared_ptr<QOpenGLTexture> t);
    void initTexture();
};
