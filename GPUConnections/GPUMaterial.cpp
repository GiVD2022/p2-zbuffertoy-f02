#include "GPUMaterial.hh"

GPUMaterial::GPUMaterial():Material()
{
    Ka = vec3(1.0, 0.0, 0.0);
    Kd = vec3(1.0, 0.0, 0.0);
    Ks = vec3(1.0, 0.0, 0.0);
    Kt = vec3(1.0, 0.0, 0.0);
    shininess = 1.0;
    opacity = 1.0;
}

GPUMaterial::GPUMaterial(vec3 Ka, vec3 Kd, vec3 Ks, float shininess, float opacity): Material( Ka,  Kd,  Ks, shininess,  opacity)
{
    Kt = vec3(0.0, 0.0, 0.0);
}

void GPUMaterial::initialize(shared_ptr<QGLShaderProgram> pr){
    program = pr;

    gl_material.Ka = program->uniformLocation("mat_info.Ka");
    gl_material.Kd = program->uniformLocation("mat_info.Kd");
    gl_material.Ks = program->uniformLocation("mat_info.Ks");
    gl_material.Kt = program->uniformLocation("mat_info.Kt");
    gl_material.shininess = program->uniformLocation("mat_info.shininess");
    gl_material.opacity = program->uniformLocation("mat_info.opacity");
}

void GPUMaterial::toGPU(shared_ptr<QGLShaderProgram> p) {
    initialize(p);

    glUniform3fv(gl_material.Ka, 1, Ka);
    glUniform3fv(gl_material.Kd, 1, Kd);
    glUniform3fv(gl_material.Ks, 1, Ks);
    glUniform3fv(gl_material.Kt, 1, Kt);
    glUniform1f(gl_material.shininess, shininess);
    glUniform1f(gl_material.opacity, opacity);

}

bool GPUMaterial::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const{
    return false;
}


