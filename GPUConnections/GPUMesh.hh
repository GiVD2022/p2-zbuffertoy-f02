#pragma once

#include "library/Common.h"
using namespace Common;

#include <QOpenGLTexture>

#include "GPUObject.hh"
#include "Model/Modelling/Objects/Mesh.hh"
#include "GPUConnections/GPUMaterial.hh"
#include "GPUMaterialFactory.hh"

static int NUMPOINTS = 10000;

class GPUMesh : public Mesh, public GPUObject
{
public:
	GPUMesh();
    GPUMesh(const QString &fileName);
    GPUMesh(const int npoints, const QString &fileName);

    ~GPUMesh();

    virtual void toGPU(shared_ptr<QGLShaderProgram> p) override;
    virtual void draw() override;
    Capsa3D calculCapsa3D() override;
    bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    void aplicaTG(shared_ptr<TG>) override;

    void read(const QJsonObject &json) override;
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
    int Index_n;
    int Index_t;

    shared_ptr<QOpenGLTexture> texture;

    void make();

    void setTexture(shared_ptr<QOpenGLTexture> t);
    void initTexture();
};

