#ifndef GPULAMBERTIAN_HH
#define GPULAMBERTIAN_HH

#include "GPUMaterial.hh"
#include "Model/Modelling/Materials/Lambertian.hh"

class GPULambertian: public GPUMaterial, Lambertian
{
public:
    GPULambertian();
    bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const override = 0;

};

#endif // GPULAMBERTIAN_HH
