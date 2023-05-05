#ifndef GPULAMBERTIAN_HH
#define GPULAMBERTIAN_HH
#include "Model/Modelling/Materials/Lambertian.hh"
#include "GPUMaterial.hh"


class GPULambertian: public Lambertian, public GPUMaterial
{
public:
    GPULambertian();
    GPULambertian(const vec3& color);
    GPULambertian(const vec3& a, const vec3& d, const vec3& s, const float k);
    GPULambertian(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);
};

#endif // GPULAMBERTIAN_HH
