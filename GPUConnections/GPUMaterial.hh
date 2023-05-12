#pragma once

#include "Model/Modelling/Materials/Material.hh"
#include "GPUConnectable.hh"

class GPUMaterial: public Material, public GPUConnectable
{
public:
    GPUMaterial();
    GPUMaterial(vec3 Ka, vec3 Kd, vec3 Ks, float shininess, float opacity);

    void initialize(shared_ptr<QGLShaderProgram> pr);

    bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const override;

    void toGPU(shared_ptr<QGLShaderProgram> p) override;

    void load(const QString matFile) override;

private:
    struct Mat{
       GLuint Ka;
       GLuint Kd;
       GLuint Ks;
       GLuint Kt;
       GLuint shininess;
       GLuint opacity;
    };

    Mat gl_material;
};


